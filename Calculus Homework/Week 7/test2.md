Lemma 1. 若 $I$ 为非空开区间, 则 $f:I \rightarrow \R$ 凸 iff $\forall c \in I, \exist \lambda, \forall x \in I, f(x) \ge f(c) + \lambda(x-c)$.

Proof. Only if: 我们有 $x > c \rightarrow f(x) \ge f(c) + f'_+(c)(x-c)$ 和 $x < c \rightarrow f(x) \ge f(c) + f'_-(c)(x-c)$. 故取 $\lambda=\min(f'_+(c), f'_-(c))$ 即可.

If: 反证法. 假设存在 $x, y, z \in I$, $x < z < y$, $f(z) > \frac{y-z}{y-x}f(x)+\frac{z-x}{y-x}f(y)$.

则有 $f(x) \ge f(z) + \lambda(x-z)$, $f(y) \ge f(z) + \lambda(y-z)$, 故 $\frac{f(z)-f(x)}{z-x} \le \lambda \le \frac{f(y)-f(z)}{y-z}$, $\frac{y-x}{(z-x)(y-z)}f(z) \le \frac{1}{z-x}f(x)+\frac{1}{y-z}f(y)$, $f(z) \le \frac{y-z}{y-x}f(x)+\frac{z-x}{y-x}f(y)$. 矛盾. $\blacksquare$
