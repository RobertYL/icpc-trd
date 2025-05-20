/**
 * Author: zhtluo
 * Source: cp-reference
 * Description: Min-cost max-flow.
 * EK is better for sparse graphs
 */
#pragma once

template <int MAXN = 1000, int MAXM = 100000>
struct MCMF_EK {
  struct EdgeList {
    int size,begin[MAXN],dest[MAXM],next[MAXM],cost[MAXM],flow[MAXM];
    void clear(int n) { size = 0; fill(begin, begin + n, -1); }
    EdgeList(int n = MAXN) { clear(n); }
    void addEdge(int u, int v, int c, int f) {
      dest[size] = v; next[size] = begin[u];
      cost[size] = c; flow[size] = f; begin[u] = size++;
      dest[size] = u; next[size] = begin[v];
      cost[size] = -c; flow[size] = 0; begin[v] = size++;
    }
  };
  int n, s, t, prev[MAXN], dist[MAXN], occur[MAXN];
  bool augment(EdgeList &e) {
    vector<int> queue; queue.push_back(s);
    fill(dist, dist + n, INF); dist[s] = 0;
    fill(occur, occur + n, 0); occur[s] = true;
    for (int head = 0; head < (int)queue.size(); ++head) {
      int x = queue[head];
      for (int i = e.begin[x]; ~i; i = e.next[i]) {
        int y = e.dest[i];
        if (e.flow[i] && dist[y] > dist[x] + e.cost[i]) {
          dist[y] = dist[x] + e.cost[i]; prev[y] = i;
          if (!occur[y]) {
            occur[y] = true; queue.push_back(y);
          } } }
      occur[x] = false;
    }
    return dist[t] < INF;
  }
  pair<int, int> solve( EdgeList &e, int n_, int s_, int t_) {
    n = n_; s = s_; t = t_;
    pair<int, int> ans = make_pair(0, 0);
    while (augment(e)) {
      int num = INF;
      for (int i = t; i != s; i = e.dest[prev[i] ^ 1])
        num = min(num, e.flow[prev[i]]);
      ans.first += num;
      for (int i = t; i != s; i = e.dest[prev[i] ^ 1]) {
        e.flow[prev[i]] -= num; e.flow[prev[i] ^ 1] += num;
        ans.second += num * e.cost[prev[i]];
      } }
    return ans;
  }
};
