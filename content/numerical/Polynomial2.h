/**
 * Author: zhtluo
 * Description: \begin{enumerate}
 * \item \mintinline{cpp}|inverse|: Find a polynomial $b$ so that $a(x)b(x)\equiv 1\mod x^n\mod mod$.
 * $n$ must be a power of $2$. The max length of the array should be at least twice the actual length. 
 * \item \mintinline{cpp}|sqrt|: Find a polynomial $b$ so that $b^2(x)\equiv a(x)\mod x^n\mod mod$. 
 * $n\ge 2$ must be a power of $2$. The max length of the array should be at least twice the actual length. 
 * \item \mintinline{cpp}|divide|: Given polynomial $a$ and $b$ with degree $n$ and $m$ respectively, find $a(x)=d(x)b(x)+r(x)$ with $\operatorname{deg}(d)\le n-m$ and $\operatorname{deg}(r)<m$. The max length of the array should be at least four times the actual length. 
 * \end{enumerate}
 */

template <int MAXN = 1000000>
struct polynomial {
  ntt<MAXN> tr;

  void inverse(int *a, int *b, int n, int mod, int prt) {
    static int c[MAXN];
    b[0] = ::inverse(a[0], mod);
    b[1] = 0;
    for (int m = 2, i; m <= n; m <<= 1) {
      copy(a, a + m, c);
      fill(b + m, b + m + m, 0);
      fill(c + m, c + m + m, 0);
      tr.solve(c, m + m, 0, mod, prt);
      tr.solve(b, m + m, 0, mod, prt);
      for (int i = 0; i < m + m; ++i)
        b[i] = 1LL * b[i] *
          (2 - 1LL * b[i] * c[i] % mod + mod) % mod;
      tr.solve(b, m + m, 1, mod, prt);
      fill(b + m, b + m + m, 0);
    }
  }

  void sqrt(int *a, int *b, int n, int mod, int prt) {
    static int d[MAXN], ib[MAXN];
    b[0] = 1;
    b[1] = 0;
    int i2 = ::inverse(2, mod), m, i;
    for (int m = 2; m <= n; m <<= 1) {
      copy(a, a + m, d);
      fill(d + m, d + m + m, 0);
      fill(b + m, b + m + m, 0);
      tr.solve(d, m + m, 0, mod, prt);
      inverse(b, ib, m, mod, prt);
      tr.solve(ib, m + m, 0, mod, prt);
      tr.solve(b, m + m, 0, mod, prt);
      for (int i = 0; i < m + m; ++i)
        b[i] = (1LL * b[i] * i2 +
                 1LL * i2 * d[i] % mod * ib[i]) %
          mod;
      tr.solve(b, m + m, 1, mod, prt);
      fill(b + m, b + m + m, 0);
    }
  }

  void divide(int *a, int n, int *b, int m, int *d, int *r,
    int mod, int prt) {
    static int u[MAXN], v[MAXN];
    while (!b[m - 1]) --m;
    int p = 1, t = n - m + 1;
    while (p < t << 1) p <<= 1;
    fill(u, u + p, 0);
    reverse_copy(b, b + m, u);
    inverse(u, v, p, mod, prt);
    fill(v + t, v + p, 0);
    tr.solve(v, p, 0, mod, prt);
    reverse_copy(a, a + n, u);
    fill(u + t, u + p, 0);
    tr.solve(u, p, 0, mod, prt);
    for (int i = 0; i < p; ++i)
      u[i] = 1LL * u[i] * v[i] % mod;
    tr.solve(u, p, 1, mod, prt);
    reverse(u, u + t);
    copy(u, u + t, d);
    for (p = 1; p < n; p <<= 1);
    fill(u + t, u + p, 0);
    tr.solve(u, p, 0, mod, prt);
    copy(b, b + m, v);
    fill(v + m, v + p, 0);
    tr.solve(v, p, 0, mod, prt);
    for (int i = 0; i < p; ++i)
      u[i] = 1LL * u[i] * v[i] % mod;
    tr.solve(u, p, 1, mod, prt);
    for (int i = 0; i < m; ++i)
      r[i] = (a[i] - u[i] + mod) % mod;
    fill(r + m, r + p, 0);
  }
};