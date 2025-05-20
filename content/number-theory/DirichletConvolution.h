/**
  * Author: zhtluo
  * Description: Define the Dirichlet convolution $f*g(n)$ as:
  * 
  * $$f*g(n)=\sum^n_{d=1}[d|n]f(n)g(\frac{n}{d})$$
  * 
  * Assume we are going to calculate some function $S(n)=\sum^n_{i=1}f(i)$,
  * where $f(n)$ is a multiplicative function.
  * Say we find some $g(n)$ that is simple to calculate,
  * and $\sum^n_{i=1}f*g(i)$ can be figured out in $O(1)$ complexity.
  * Then we have
  * 
  * \[\begin{aligned}
  * \sum^n_{i=1}f*g(i)	&=\sum^n_{i=1}\sum_d[d|i]g(\frac{i}{d})f(d)
  * 					&&=\sum^n_{\frac{i}{d}=1}\sum^{\floor*{\frac{n}{\frac{i}{d}}}}_{d=1}g(\frac{i}{d})f(d)\\
  * 					&=\sum^n_{i=1}\sum^{\floor*{\frac{n}{i}}}_{d=1}g(i)f(d)
  * 					&&=g(1)S(n)+\sum^n_{i=2}g(i)S(\floor*{\frac{n}{i}}),
  * \end{aligned}\]
  * \[
  * S(n) = \frac{\sum^n_{i=1}f*g(i)-\sum^n_{i=2}g(i)S(\floor*{\frac{n}{i}})}{g(1)}.
  * \]
  * 
  * It can be proven that $\floor*{\frac{n}{i}}$ has at most $O(\sqrt{n})$ possible values.
  * Therefore, the calculation of $S(n)$ can be reduced to $O(\sqrt{n})$ calculations of $S(\floor*{\frac{n}{i}})$.
  * By applying the master theorem, it can be shown that the complexity of such method is $O(n^{\frac{3}{4}})$.
  * 
  * Moreover, since $f(n)$ is multiplicative, we can process the first $n^{\frac{2}{3}}$ elements via linear sieve,
  * and for the rest of the elements, we apply the method shown above. The complexity can thus be enhanced to $O(n^{\frac{2}{3}})$.
  * 
  * For the prefix sum of Euler's function $S(n)=\sum^n_{i=1}\varphi(i)$, notice that $\sum_{d|n}\varphi(d)=n$.
  * Hence $\varphi*I=id$. ($I(n)=1,id(n)=n$)
  * Now let $g(n)=I(n)$, and we have $S(n)=\sum^n_{i=1}i-\sum^n_{i=2}S(\floor*{\frac{n}{i}})$.
  * 
  * For the prefix sum of Mobius function $S(n)=\sum^n_{i=1}\mu(i)$, notice that $\mu*I=(n)\{[n=1]\}$.
  * Hence $S(n)=1-\sum^n_{i=2}S(\floor*{\frac{n}{i}})$.
  * 
  * Some other convolutions include $(p^k)\{1-p\}*id=I$, $(p^k)\{p^k-p^{k+1}\}*id^2=id$ and $(p^k)\{p^{2k}-p^{2k-2}\}*I=id^2$.
  * \begin{enumerate}
  * 	\item \mintinline{cpp}|CUBEN| should be $N^{\frac{1}{3}}$.
  * 	\item Pass \mintinline{cpp}|p_f| that returns the prefix sum of $f(x)(1\le x<th)$.
  * 	\item Pass \mintinline{cpp}|p_g| that returns the prefix sum of $g(x)(0\le x\le N)$.
  * 	\item Pass \mintinline{cpp}|p_c| that returns the prefix sum of $f*g(x)(0\le x\le N)$.
  * 	\item Pass \mintinline{cpp}|th| as the thereshold, which generally should be $N^{\frac{2}{3}}$.
  * 	\item Pass \mintinline{cpp}|mod| as the module number, \mintinline{cpp}|inv| as the inverse of $g(1)$ regarding \mintinline{cpp}|mod|.
  * 	\item \textbf{Remember that $x$ in \mintinline{cpp}|p_g(x)| and \mintinline{cpp}|p_c(x)| may be larger than \mintinline{cpp}|mod|!}
  * 	\item Run \mintinline{cpp}|init(n)| first.
  * 	\item Use \mintinline{cpp}|ans(x)| to fetch answer for $\frac{n}{x}$.
  * \end{enumerate}
*/
template <int CUBEN = 3000>
struct prefix_mul {
  typedef ll (*func)(ll);
  func p_f, p_g, p_c;
  ll mod, th, inv, n, mem[CUBEN];

  prefix_mul(func p_f, func p_g, func p_c, ll th, ll mod, ll inv)
      : p_f(p_f),p_g(p_g), p_c(p_c), th(th), mod(mod), inv(inv) {}

  void init(ll n) {
    prefix_mul::n = n;
    for (ll i = 1, la; i <= n; i = la + 1) {
      if ((la = n / (n / i)) < th) continue;
      ll &ans = mem[n / la] = p_c(la);
      for (ll j = 2, ne; j <= la; j = ne + 1) {
        ne = la / (la / j);
        ans = (ans + mod - (p_g(ne) - p_g(j - 1) + mod)
            * (la / j < th ? p_f(la / j) : mem[n / (la / j)]) % mod);
        if (ans >= mod) ans -= mod;
      }
      if (inv != 1) ans = ans * inv % mod;
    }
  }

  ll ans(ll x) {
    if (n / x < th) return p_f(n / x);
    return mem[n / (n / x)];
  }
};
