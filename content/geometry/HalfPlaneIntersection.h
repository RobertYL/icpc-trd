/**
	* Author: RobertYL
  * Description: Intersect left half planes defined by s and t.
  * Consider adding a bounding box. Hull may degenerate to a point.
  * Time: O(n\log{n})
  */

#include "Point.h"

const double eps = 1e-9;
int sgn(double x) { return (x > eps) - (x < -eps); }
template<class P>
struct L {
  P s, t;
  double a;
  explicit L(P s=P(), P t=P()) : s(s), t(t), a((t-s).angle()) {}
  bool operator==(const L &l) const { return sgn(a-l.a) == 0; }
  bool operator<(const L &l) const {
    if(sgn(a-l.a) == 0) return sgn((t-s).cross(l.s-s)) < 0;
    return a < l.a;
  }
  bool out(const P &p) const { // check if outside HP
    return sgn((t-s).cross(p-s)/(t-s).dist()) < 0; // < 1 for degen case
  }
  P inter(const L &l) const { // assume never parallel
    auto d = (t-s).cross(l.t-l.s); // d != 0
    auto p = l.s.cross(t, l.t), q = l.s.cross(l.t, s);
    return (s * p + t * q) / d;
  }
};

template<class P>
vector<P> HPI(vector<L<P>> &l){
  sort(all(l)); l.erase(unique(all(l)), l.end());

  deque<L<P>> dq; int sz = 0;
  rep(i, 0, sz(l)) {
    while(sz > 1 && l[i].out(dq[sz-1].inter(dq[sz-2])))
      dq.pop_back(), --sz;
    while(sz > 1 && l[i].out(dq[0].inter(dq[1])))
      dq.pop_front(), --sz;
    dq.push_back(l[i]), ++sz;
  }
  while(sz > 2 && dq[0].out(dq[sz-1].inter(dq[sz-2])))
    dq.pop_back(), --sz;
  while(sz > 2 && dq[sz-1].out(dq[0].inter(dq[1])))
    dq.pop_front(), --sz;
  if(sz < 3) return {};
  vector<P> res;
  rep(i, 0, sz) res.push_back(dq[i].inter(dq[(i+1)%sz]));
  return res;
}

