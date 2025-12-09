设 $P_n(x)=e^x\frac{\text{d}^n}{\text{d}x^n}(e^{-x}x^n)$.

---

Lemma 1. $P_n$ 是 $n$ 次多项式.

Proof. 我们证明 $P_{n, m}=e^x\frac{\text{d}^m}{\text{d}x^m}(e^{-x}x^n)$ 是 $n$ 次多项式. 对 $m$ 使用数学归纳法. 当 $m=0$ 时有 $P_{n, 0}=x^n$. 假设 $m$ 成立, 下证 $m+1$ 成立.

当 $n=0$ 时有 $P_{0, m+1}=(-1)^{m+1}$. 故假设 $n>0$.

我们有 $P_{n, m+1}=e^x\frac{\text{d}^m}{\text{d}x^m}(ne^{-x}x^{n-1}-e^{-x}x^n)=ne^x\frac{\text{d}^m}{\text{d}x^m}(e^{-x}x^{n-1})-e^x\frac{\text{d}^m}{\text{d}x^m}(e^{-x}x^n)=nP_{n-1, m}-P_{n, m}$.

由于 $P_{n-1, m}$ 是 $n-1$ 次多项式, 则其 $n$ 次项系数为 0. 故 $P_{n, m+1}$ 为 $n$ 次多项式. $\blacksquare$

---

设 $F_{n, m}=\frac{\text{d}^m}{\text{d}x^m}(e^{-x}x^n)=\frac{P_{n, m}}{e^x}$.

---

引理. 当 $m<n$ 时, $F_{n, m}(0)=0$ 且 $\lim_{x \rightarrow +\infty} F_{n, m}(x)=0$.

Proof. 对 $m$ 使用数学归纳法. 当 $m=0<n$ 时有 $F_{n, 0}=\frac{x^n}{e^x}$, 则有 $0^n=0$. 我们又有 $\lim_{x \rightarrow +\infty} (x-n\ln x) \ge \lim_{x \rightarrow +\infty} (x-n(\frac{1}{n+1}x-1+\ln(n+1))) = \lim_{x \rightarrow +\infty} (\frac{1}{n+1}x+n-n\ln(n+1))=+\infty$ (由于 $\ln(x)$ 是凹的). 故 $\lim_{x \rightarrow +\infty}\frac{e^x}{x^n}=+\infty$, $\lim_{x \rightarrow +\infty}\frac{x^n}{e^x}=0$. 假设 $m$ 成立, 下证 $m+1$ 成立.

我们有 $F_{n, m+1}=nF_{n-1, m}-F_{n, m}$. 又有 $F_{n-1, m}(0)=F_{n, m}(0)=0$, $\lim_{x \rightarrow +\infty} F_{n-1, m}(x)\lim_{x \rightarrow +\infty} F_{n, m}(x)=0$. 故成立.

---

Lemma 2. $P_n$ 有 $n$ 个不同的正数根.

Proof. 对于 $m \le n$, 我们证明 $P_{n, m}$ 有至少 $m$ 个不同的正数根. 根据代数基本定理, 可以得到原命题. 对 $m$ 使用数学归纳法. 当 $m=0$ 时成立. 假设 $m$ 成立, 下证 $m+1$ 成立.

假设有 $0<x_1<x_2<\cdots<x_m$ 使得 $P_{n, m}(x_i)=0$, 则有 $F_{n, m}(x_i)=0$. 又有 $F_{n, m}(0)=0$ 和 $\lim_{x \rightarrow +\infty} F_{n, m}(x)=0$. 故存在 $0<y_1<x_1<y_2<x_2<\cdots<x_m<y_{m+1}$ 使得 $F_{n, m+1}=\frac{\text{d}}{\text{d}x}F_{n, m}$ 有 $F_{n, m+1}(y_i)=0$. $\blacksquare$
