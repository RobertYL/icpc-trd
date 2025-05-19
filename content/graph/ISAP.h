/**
 * Author: zhtluo
 * Date: 2025-03-06
 * License: MIT
 * Source: https://github.com/zhtluo/cp-reference
 * Description: Better than Dinic for sparse graph.
 * Status: Untested
 */
#pragma once

template <int MAXN = 1000, int MAXM = 100000>
struct ISAP {
  // struct FlowEdgeList { ... };
  // see Dinic

  int pre[MAXN], d[MAXN], gap[MAXN], cur[MAXN], que[MAXN], vis[MAXN];

  ll solve(FlowEdgeList &e, int n, int s, int t) {
    for (int i = 0; i < n; ++i) {
      pre[i] = d[i] = gap[i] = vis[i] = 0;
      cur[i] = e.begin[i];
    }
    int l = 0, r = 0;
    que[0] = t, gap[0] = 1, vis[t] = 1;
    while (l <= r) {
      int u = que[l++];
      for (int i = e.begin[u]; ~i; i = e.next[i])
        if (e.flow[i] == 0 && !vis[e.dest[i]]) {
          que[++r] = e.dest[i];
          vis[e.dest[i]] = true;
          d[e.dest[i]] = d[u] + 1;
          ++gap[d[e.dest[i]]];
        }
    }
    for (int i = 0; i < n; ++i)
      if (!vis[i]) d[i] = n, ++gap[n];
    int u = pre[s] = s, v; ll maxflow = 0;
    while (d[s] < n) {
      v = n;
      for (int i = cur[u]; ~i; i = e.next[i])
        if (e.flow[i] && d[u] == d[e.dest[i]] + 1) {
          v = e.dest[i];
          cur[u] = i;
          break;
        }
      if (v < n) {
        pre[v] = u;
        u = v;
        if (v == t) {
          ll dflow = LLONG_MAX; int p = t;
          u = s;
          while (p != s) {
            p = pre[p];
            dflow = min(dflow, e.flow[cur[p]]);
          }
          maxflow += dflow;
          p = t;
          while (p != s) {
            p = pre[p];
            e.flow[cur[p]] -= dflow;
            e.flow[cur[p] ^ 1] += dflow;
          }
        }
      } else {
        int mindist = n + 1;
        for (int i = e.begin[u]; ~i; i = e.next[i])
          if (e.flow[i] && mindist > d[e.dest[i]]) {
            mindist = d[e.dest[i]];
            cur[u] = i;
          }
        if (!--gap[d[u]]) return maxflow;
        gap[d[u] = mindist + 1]++;
        u = pre[u];
      }
    }
    return maxflow;
  }
};
