/**
 * Author: zhtluo
 * Date: 2025-03-06
 * License: MIT
 * Source: https://github.com/zhtluo/cp-reference
 * Description: $\mathcal{O}(VE\log U)$ where $U = \max |\text{cap}|$.
 * $\mathcal{O}(\min( E^{1/2}, V^{2/3})E)$ if $U = 1$; $\mathcal{O}(\sqrt{V}E)$ for bipartite matching.
 * Status: Untested
 */
#pragma once

template <int MAXN = 1000, int MAXM = 100000>
struct Dinic {
  struct FlowEdgeList {
    int size, begin[MAXN],dest[MAXM],next[MAXM]; ll flow[MAXM];
    void clear(int n) { size = 0; fill(begin, begin + n, -1); }
    FlowEdgeList (int n = MAXN) { clear(n); }
    void addEdge(int u, int v, ll f) {
      dest[size] = v; next[size] = begin[u];
      flow[size] = f; begin[u] = size++;
      dest[size] = u; next[size] = begin[v];
      flow[size] = 0; begin[v] = size++;
    }
  };
  int n, s, t, d[MAXN], w[MAXN], q[MAXN];
  int bfs(FlowEdgeList &e) {
    fill(d, d + n, -1); int l, r;
    q[l = r = 0] = s, d[s] = 0;
    for (; l <= r; ++l)
      for (int k = e.begin[q[l]]; ~k; k = e.next[k])
        if (!~d[e.dest[k]] && e.flow[k] > 0)
          d[e.dest[k]] = d[q[l]] + 1, q[++r] = e.dest[k];
    return ~d[t] ? 1 : 0;
  }
  ll dfs(FlowEdgeList &e, int u, ll ext) {
    if (u == t) return ext;
    int k = w[u]; ll ret = 0;
    for (; ~k; k = e.next[k], w[u] = k) {
      if (ext == 0) break;
      if (d[e.dest[k]] == d[u] + 1 && e.flow[k] > 0) {
        ll flow = dfs(e, e.dest[k], min(e.flow[k], ext));
        if (flow > 0) {
          e.flow[k] -= flow, e.flow[k ^ 1] += flow;
          ret += flow, ext -= flow;
        } } }
    if (!~k) d[u] = -1;
    return ret;
  }
  int solve(FlowEdgeList &e, int n_, int s_, int t_) {
    ll ans = 0; n = n_, s = s_, t = t_;
    while (bfs(e)) {
      for (int i = 0; i < n; ++i) w[i] = e.begin[i];
      ans += dfs(e, s, LLONG_MAX);
    }
    return ans;
  }
};
