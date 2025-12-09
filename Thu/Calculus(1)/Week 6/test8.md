设 $a>0$.

Prob 1. 猜出一个 $ay'-y=0$ 的非零解.

我们有 $f(x)=e^{\frac{1}{a}x}$ 满足 $f'(x)=\frac{1}{a}e^{\frac{1}{a}x}$, 故 $af'-f=0$.

---

Prob 2. 设 $g(x)=C(x)e^{\frac{1}{a}x}$ 也是解. 求 $C$ 满足的微分方程.

我们有 $g'=C'(x)e^{\frac{1}{a}x}+\frac{1}{a}C(x)e^{\frac{1}{a}x}$, 故 $ag'-g=aC'(x)e^{\frac{1}{a}x}=0$. 因此 $C'(x)=0$.

---

Prob 3. 求 $C(x)$ 的所有解, 并给出最初方程的所有解.

显然 $C(x)=k$, 其中 $k$ 为任意常数. 故最初方程所有解形如 $g(x)=ke^{\frac{1}{a}x}$.

---

Prob 4. 求满足 $f(1)=1$ 的解.

我们有 $ke^{\frac{1}{a}}=1 \rightarrow k=e^{-\frac{1}{a}}$. 故 $f(x)=e^{\frac{1}{a}x-\frac{1}{a}}$.

---

Prob 5. 设 $f$ 在 $(0, +\infty)$ 可微, 证明任意 $0<a<b$ 存在 $\xi \in (a, b)$ 使得 $f(\xi)-\xi f'(\xi)=\frac{af(b)-bf(a)}{a-b}$.

(使用 deepseek) 令 $g(x)=\frac{f(x)}{x}$, 则 $f=xg$, $f'=g+xg'$, $f-xf'=-x^2g'$. 根据柯西中值定理, 我们能找到 $\xi \in (a, b)$ 满足 $\frac{g'(\xi)}{-\frac{1}{\xi^2}}=\frac{g(b)-g(a)}{\frac{1}{b}-\frac{1}{a}}$, 即 $-\xi^2g'(\xi)=\frac{abg(b)-abg(a)}{a-b}$, 也即 $f(\xi)-\xi f'(\xi)=\frac{af(b)-bf(a)}{a-b}$.
