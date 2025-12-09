Lemma 1. 若 $f$ 是 $(a, b)$ 上的连续函数, 且 $\lim_{x \rightarrow a^+} f(x)=+\infty$, $\lim_{x \rightarrow b^-} f(x)=-\infty$; $g$ 是 $(a, b)$ 上的连续函数, 且当 $x \rightarrow a^+$ 或 $x \rightarrow b^-$ 时 $g(x)=o(f(x))$, 则 $f+g$ 在 $(a, b)$ 内有零点.

Proof. 我们有存在一个 $\delta_1$ 使得 $x \in (a, a+\delta_1), f(x)>1$. 并且存在一个 $\delta_2$ 使得 $x \in (a, a+\delta_2), |g(x)|<\frac{1}{2}|f(x)|$.

设 $\delta=\min(\delta_1, \delta_2)$, 则对于 $x \in (a, a+\delta)$, 有 $f(x)>1$, $|g(x)|<\frac{1}{2}|f(x)|=\frac{1}{2}f(x)$, $f(x)+g(x) \ge f(x)-|g(x)|>\frac{1}{2}f(x)>\frac{1}{2}>0$.

同理存在一个 $\delta'$ 使得 $x \in (b-\delta', b)$ 有 $f(x)+g(x)<0$. 故有零点. $\blacksquare$
