Lemma 1. 若 $f$ 是 $(a, b)$ 上的连续函数, 且 $\lim_{x \rightarrow a^+} f(x)=\lim_{x \rightarrow b^-} f(x)=+\infty$; $g$ 是 $(a, b)$ 上的连续函数, 且当 $x \rightarrow a^+$ 或 $x \rightarrow b^-$ 时 $g(x)=o(f(x))$, 则 $f+g$ 在 $(a, b)$ 内有最小值.

Proof. 取 $w=(f+g)(\frac{a+b}{2})$, 则存在 $\delta_1>0$ 满足 $\forall x \in (a, a+\delta_1) \cup (b-\delta_1, b), f(x)>2|w|$; 存在 $\delta_2>0$ 满足 $\forall x \in (a, a+\delta_2) \cup (b-\delta_2, b), |g(x)| \le \frac{1}{2}|f(x)|$.

设 $\delta=\min(\delta_1, \delta_2, \frac{b-a}{2})$. 则 $\forall x \in (a, a+\delta) \cup (b-\delta, b)$, $f(x)>2|w|$, $|g(x)|\le \frac{1}{2}f(x)$, $f(x)+g(x)\ge f(x)-|g(x)|\ge \frac{1}{2}f(x)>|w|\ge w$. 我们又有 $[a+\delta, b-\delta]$ 内 $f+g$ 存在最小值 $w_0$. 由于 $\frac{a+b}{2} \in [a+\delta, b-\delta]$, $w \ge w_0$, 故 $\forall x \in (a, a+\delta) \cup (b-\delta, b), (f+g)(x)>w_0$. 故 $(a, b)$ 内 $f+g$ 存在最小值. $\blacksquare$
