/**
 * Author: zhtluo
 * Source: cp-reference
 * Description: Min-cost max-flow.
 * ZKW is better for dense graphs.
 */
#pragma once

template <int MAXN = 1000, int MAXM = 100000>
struct MCMF_ZKW {
  // struct EdgeList { ... };
  // see MCMF_EK
  int n, s, t, tf, tc, dis[MAXN], slack[MAXN], visit[MAXN];
  int modlable() {
    int delta = INF;
    rep(i, 0, n) {
      if (!visit[i] && slack[i] < delta) delta = slack[i];
      slack[i] = INF;
    }
    if (delta == INF) return 1;
    rep(i, 0, n) if (visit[i]) dis[i] += delta;
    return 0;
  }
  int dfs(EdgeList &e, int x, int flow) {
    if (x == t) {
      tf += flow; tc += flow * (dis[s] - dis[t]);
      return flow;
    }
    visit[x] = 1;
    int left = flow;
    for (int i = e.begin[x]; ~i; i = e.next[i])
      if (e.flow[i] > 0 && !visit[e.dest[i]]) {
        int y = e.dest[i];
        if (dis[y] + e.cost[i] == dis[x]) {
          int delta = dfs(e, y, min(left, e.flow[i]));
          e.flow[i] -= delta; e.flow[i ^ 1] += delta; left -= delta;
          if (!left) { visit[x] = false; return flow; }
        } else {
          slack[y] = min(slack[y], dis[y] + e.cost[i] - dis[x]);
        } }
    return flow - left;
  }
  pair<int, int> solve( EdgeList &e, int n_, int s_, int t_) {
    n = n_; s = s_; t = t_;
    tf = tc = 0; fill(dis + 1, dis + n + 1, 0);
    do { do {
      fill(visit + 1, visit + n + 1, 0);
    } while (dfs(e, s, INF)); } while (!modlable());
    return make_pair(tf, tc);
  }
};
