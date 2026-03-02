设 $n \in N^*$, 称 $P_n(x)=\frac{1}{2^nn!} \frac{\text{d}^n}{\text{d} x^n}[(x^2-1)^n]$ 是 Legendre 多项式.

---

Lemma 1 (使用 deepseek). Legendre 多项式满足 $(1-x^2)y''-2xy'+n(n+1)y=0$.

Proof. 设 $f(x)=(x^2-1)^n$. 我们有 $f'(x)=2nx(x^2-1)^{n-1}$, 故 $(1-x^2)f'+2nxf=0$. 对两侧求 $n$ 阶导, 得到

$$[(1-x^2)f^{(n+1)}-2nxf^{(n)}-n(n-1)f^{(n-1)}] + [2nxf^{(n)}+2n^2f^{(n-1)}] = 0$$

即

$$(1-x^2)f^{(n+1)}+n(n+1)f^{(n-1)}=0.$$

继续对两侧求导, 得到

$$(1-x^2)f^{(n+2)}-2xf^{(n+1)}+n(n+1)f^{(n)}=0$$

设 $g(x)=f(x)^{(n)}=((x^2-1)^n)^{(n)}=2^nn!P_n(x)$, 有 $(1-x^2)g''-2xg'+n(n+1)g=0$. 故 $(1-x^2)P_n''-2xP_n'+n(n+1)P_n=0$. $\blacksquare$
