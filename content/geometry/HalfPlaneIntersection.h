/**
	* Author: Zhongtang Luo
  * Description: \begin{enumerate}
  * \item \mintinline{cpp}|cut|: Online in $O(n^2)$.
  * \item \mintinline{cpp}|half_plane_intersect|: Offline in $O(mlogm)$.
  * \end{enumerate}
*/

vector<point> cut(
  const vector<point> &c, line p) {
  vector<point> ret;
  if (c.empty()) return ret;
  for (int i = 0; i < (int)c.size(); ++i) {
    int j = (i + 1) % (int)c.size();
    if (turn_left(p.s, p.t, c[i])) ret.push_back(c[i]);
    if (two_side(c[i], c[j], p))
      ret.push_back(line_intersect(p, line(c[i], c[j])));
  }
  return ret;
}

bool turn_left(cl l, cp p) {
  return sgn(det(l.t - l.s, p - l.s)) >= 0;
}

int cmp(cp a, cp b) {
  return a.dim() != b.dim() ? (a.dim() < b.dim() ? -1 : 1)
                            : -sgn(det(a, b));
}

vector<point> half_plane_intersect(vector<line> h) {
  typedef pair<point, line> polar;
  vector<polar> g;
  g.resize(h.size());
  for (int i = 0; i < (int)h.size(); ++i)
    g[i] = make_pair(h[i].t - h[i].s, h[i]);
  sort(g.begin(), g.end(),
    [&](const polar &a, const polar &b) {
      if (cmp(a.first, b.first) == 0)
        return sgn(det(a.second.t - a.second.s,
                 b.second.t - a.second.s)) < 0;
      else
        return cmp(a.first, b.first) < 0;
    });
  h.resize(unique(g.begin(), g.end(),
             [](const polar &a, const polar &b) {
               return cmp(a.first, b.first) == 0;
             }) -
    g.begin());
  for (int i = 0; i < (int)h.size(); ++i)
    h[i] = g[i].second;
  int fore = 0, rear = -1;
  vector<line> ret(h.size(), line());
  for (int i = 0; i < (int)h.size(); ++i) {
    while (fore < rear &&
      !turn_left(
        h[i], line_intersect(ret[rear - 1], ret[rear])))
      --rear;
    while (fore < rear &&
      !turn_left(
        h[i], line_intersect(ret[fore], ret[fore + 1])))
      ++fore;
    ret[++rear] = h[i];
  }
  while (rear - fore > 1 &&
    !turn_left(
      ret[fore], line_intersect(ret[rear - 1], ret[rear])))
    --rear;
  while (rear - fore > 1 &&
    !turn_left(
      ret[rear], line_intersect(ret[fore], ret[fore + 1])))
    ++fore;
  if (rear - fore < 2) return vector<point>();
  vector<point> ans;
  ans.resize(rear + 1);
  for (int i = 0; i < rear + 1; ++i)
    ans[i] =
      line_intersect(ret[i], ret[(i + 1) % (rear + 1)]);
  return ans;
}
