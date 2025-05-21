/**
 * Author: PURDUE
 * Description: TAG (a,b) means apply f(x) = ax+b to all elements in a range. Segments contain either MAX or +, and you're able to recompute a segment if all elements have a TAG applied to it.
 * Usage: On each test case, reset the value of N. Initialize seg (and len) from i = N to 2N, and iterate backwards from N-1 to 0 to build seg and lazy
 */
const int MAXN = 200000;
struct Lazy{
  using T = long long;
  using TAG = pair<T,T>;
  static constexpr T defT = 0;     //<- edit
  static constexpr TAG defTAG = {1,0}; //<- edit
 
  int N;
  TAG lazy[MAXN];
  T seg[2*MAXN];
  int len[2*MAXN];
 
  T f( T a, T b ){ return a+b; } //merge two segments
  void apply( TAG f, int i ){
    TAG g = lazy[i];
    if(i < N) lazy[i] = { f.first*g.first, f.first*g.second + f.second }; //compose two tags
    seg[i] = f.first*seg[i] + f.second*len[i]; //evaluate tag on segment
  }
 
  void hammer_down( int i ){
    for( int k = 20; k > 0; k-- ){
      int j = (i>>k);
      if(j==0) continue;
      apply( lazy[j], 2*j );
      apply( lazy[j], 2*j+1 );
      lazy[j] = defTAG;
    }
  }
  void boiler_up( int i ){
    i /= 2;
    while(i){
      seg[i] = f(seg[2*i],seg[2*i+1]);
      i /= 2;
    }
  }
  void update( int l, int r, TAG tag ){
    l += N, r += N;
    int l0 = l, r0 = r;
    while(l0%2==0) l0 /= 2;
    while(r0%2==0) r0 /= 2;
    hammer_down(l0);
    hammer_down(r0-1);
    while( l < r ){
      if(l&1) apply(tag,l++);
      if(r&1) apply(tag,--r);
      l /= 2, r /= 2;
    }
    boiler_up(l0);
    boiler_up(r0-1);
  }
  T query( int l, int r ){ //range sum on [l,r)
    l += N, r += N;
    hammer_down(l);
    hammer_down(r-1);
    T m1 = defT, m2 = defT;
    while( l < r ){
      if(l&1) m1 = f(m1,seg[l++]);
      if(r&1) m2 = f(seg[--r],m2);
      l /= 2, r /= 2;
    }
    return f(m1,m2);
  }
 
  void build( int n, vector<T> &a ){
    N = n;
    for( int i = 0; i < n; i++ ){
      seg[i+n] = a[i];
      len[i+n] = 1;
    }
    for( int i = n-1; i > 0; i-- ){
      lazy[i] = defTAG;
      seg[i] = f(seg[2*i], seg[2*i+1]);
      len[i] = len[2*i] + len[2*i+1];
    }
  }
};
