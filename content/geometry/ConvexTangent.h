/**
 * Author: 8BQube, RobertYL
 * Date: 2025-08-26
 * License: CC0
 * Source: https://github.com/brianbbsu/8BQube
 * Description: Given convex polygon and a point strictly outside, compute
 * right/left (+1/-1) (relative) tangent. Arbitrary point on tangent line
 * Time: O(\log n)
 * Status: Tested with kattis:spin
*/
#pragma once

#include "Point.h"
#include "SideOf.h"

typedef Point<ll> P;
int convexTangent(const vector<P>& h, P p, int sign) {
  int n = sz(h), a = 0, b = n, c;
  auto ori = [&](int i, int j) {
    return sideOf(p, h[i], h[j%n]) == sign; };
  if(n < 3) return ori(1, 0) ? 1 : 0;
  while(a+1 < b) {
    c = (a+b)/2;
    ((ori(0, c) ? ori(1, 0) : ori(c, c+1)) ? b : a) = c;
  }
  return ori(a, b) ? a : b%n;
}
