/**
 * Author: neal, RobertYL
 * Date: 2025-08-28
 * License: CC0
 * Source: https://codeforces.com/blog/entry/62393
 * Description: Hash syntax for unordered map. Example for Point<Frac>
 * Usage: unordered_map<P, set<int>, hash_P> mp;
 * Status: NWRRC 2024 E
 */
#pragma once

struct hash_P {
  static ll sm(ll x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(const P& p) const {
    auto h = std::hash<ll>();
    return h(p.x.a)+sm(h(p.x.b)+sm(h(p.y.a)+sm(h(p.y.b))));
  }
}; 
