设 $f$ 凸, $\phi$ 连续.

Lemma 1. 对 $a>0$ 有 $\frac{1}{a}\int_0^a f(\phi(t))\text{d}t \ge f(\frac{1}{a}\int_0^a \phi(t)\text{d}t)$.

设 $g(x)=\phi(ax)$. 只需证明 $\int_0^1 f(g(t))\text{d}t \ge f(\int_0^1 g(t)\text{d}t)$ 即可.

对于任意 $n$, 有 $\sum_{i=1}^n \frac{1}{n} f(g(\frac{1}{n}i)) \ge f(\sum_{i=1}^n \frac{1}{n} g(\frac{1}{n} i))$. 令 $n \rightarrow +\infty$ 即可得证. $\blacksquare$
