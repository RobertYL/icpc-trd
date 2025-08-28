/**
 * Author: std_abs, RobertYL
 * Date: 2025-08-28
 * License: CC0
 * Source: https://github.com/abc864197532/std_abs
 * Description: Find boundary arcs of circle union. Compute area union
 * with Green's theorem
 * Time: O(n^2\log n)
 * Status: TIOJ 1503
 */
#pragma once

#include "Point.h"
#include "CircleIntersection.h"

struct C { P o; double r; };

typedef Point<double> P;
vector<pair<P, P>> circleBorder(vector<C> c, int id) {
  auto [o, r] = c[id];
  vector<pair<P, int>> ev;
  int cnt = 0;
  auto cmp = [](P a, P b) { return a.half() < b.half()
    || (a.half() == b.half() && sgn(a.cross(b)) == 1); };
  rep(i, 0, sz(c)) if(i != id) {
    if(sgn(c[i].r-r) < 0 && (c[i].o-o).dist2()
        <= (r-c[i].r)*(r-c[i].r)) { ++cnt; continue; }
    pair<P, P> pq;
    if(circleInter(P(), c[i].o-o, r, c[i].r, pq)) {
        // c[i] != c[id]
      auto [p, q] = pq;
      ev.emplace_back(q, +1);
      ev.emplace_back(p, -1);
      if(cmp(p, q)) cnt++;
    }
  }
  ev.emplace_back(P(-r, 0), 0);
  sort(all(ev), [&](auto l, auto r) {
      return cmp(l.first, r.first); });
  ev.emplace_back(P(r, 0), 0);
  P prv(r, 0);
  vector<pair<P, P>> out;
  for(auto [cur, id] : ev) {
    if(cnt == 0) out.emplace_back(prv + o, cur + o); // == k
    prv = cur, cnt += id;
  }
  return out;
}

double circleArea(vector<C> c) {
  double area = 0;
  rep(i, 0, sz(c)) {
    auto [o, r] = c[i];
    auto arcs = circleBorder(c, i);
    auto F = [&](double t) {
      return r * (r*t + o.x*sin(t) - o.y*cos(t));
    };
    for(auto [l, r] : arcs) {
      double tl = (l-o).angle(), tr = (r-o).angle();
      if(sgn(tl - tr) == 1) tr += 2*PI;
      area += F(tr) - F(tl);
    }
  }
  return area/2;
}
