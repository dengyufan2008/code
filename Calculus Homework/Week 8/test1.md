设 $f, g:[0, 1] \rightarrow [0, 1]$, $f, g$ 连续, $f$ 单调递增.

Lemma 1. $\int_0^1 f(g(x)) \text{d}x \le \int_0^1 f(x) \text{d}x + \int_0^1 g(x) \text{d}x$.

Proof. 设 $t = \max \{f(x)-x \mid x \in [0, 1]\} \ge f(0)-0 \ge 0$, 只需证明 $t \le \int_0^1 f(x) \text{d}x$, 则有 $\int_0^1 (f(g(x)) - g(x)) \text{d}x \le \max \{f(g(x))-g(x) \mid x \in [0, 1]\} \le t \le \int_0^1 f(x) \text{d}x$.

设 $p \in [0, 1]$ 满足 $f(p)-p=t \ge 0$, 则 $\int_0^1 f(x) \text{d}x \ge \int_p^1 f(x) \text{d}x \ge \int_p^1 f(p) \text{d}{x} = (1-p)(t+p) = t + p(1 - t - p) = t + p(1 - f(p)) \ge t$. $\blacksquare$
