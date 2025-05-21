/**
	* Author: RobertYL
  * Description: Intersect left half planes defined by s and t.
  * Consider adding a bounding box. Hull may degenerate to a point.
  * Time: O(n\log{n})
  */

#include "Point.h"

#define eps 1e-9
template<class P>
struct HP {
  P s, t;
  double a;
  explicit HP(P s=P(), P t=P()) : s(s), t(t) {
    a = atan2((t-s).y, (t-s).x);
  }
  bool operator==(const HP &hp) const {
    return fabs(a - hp.a) < eps;
  }
  bool operator<(const HP &hp) const {
    if(fabs(a - hp.a) < eps)
      return sgn((t-s).cross(hp.s-s)) < 0;
    return a < hp.a;
  }
  bool out(const P &p) const { // check if outside HP
    return (t-s).cross(p-s) < -eps;
  }
  P inter(const HP &hp) const { // assume never parallel
    auto d = (t-s).cross(hp.t-hp.s); // d != 0
    auto p = hp.s.cross(t, hp.t), q = hp.s.cross(hp.t, s);
    return (s * p + t * q) / d;
  }
};

template<class P>
vector<P> halfPlaneInter(vector<HP<P>> &hp){
  sort(all(hp)); hp.erase(unique(all(hp)), hp.end());

  deque<HP<P>> dq; int ln = 0;
  rep(i, 0, sz(hp)) {
    while(ln > 1 && hp[i].out(dq[ln-1].inter(dq[ln-2])))
      dq.pop_back(), --ln;
    while(ln > 1 && hp[i].out(dq[0].inter(dq[1])))
      dq.pop_front(), --ln;
    dq.push_back(hp[i]), ++ln;
  }
  while(ln > 2 && dq[0].out(dq[ln-1].inter(dq[ln-2])))
    dq.pop_back(), --ln;
  while(ln > 2 && dq[ln-1].out(dq[0].inter(dq[1])))
    dq.pop_front(), --ln;
  vector<P> res;
  if(ln < 3) return res;
  rep(i, 0, ln) res.push_back(dq[i].inter(dq[(i+1)%ln]));
  return res;
}

