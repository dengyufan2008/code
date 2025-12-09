设 $f$ 在 $(a, b)$ 内凸.

Lemma 1. 对于 $x_0 \in (a, b)$ 有 $x \in (x_0, b) \rightarrow f(x) \ge f(x_0) + f'_+(x_0)(x-x_0)$ 和 $x \in (a, x_0) \rightarrow f(x) \ge f(x_0) + f'_-(x_0)(x-x_0)$.

Proof. 不妨假设 $(a, b)$ 是 $f$ 的定义域, 并且我们只证明前一项性质. 后一项性质对 $f(-x)$ 施用前一项性质即可得到.

设 $x_0 < x < y < b$. 我们有 $\frac{y-x}{y-x_0} f(x_0) + \frac{x-x_0}{y-x_0} f(y) \ge f(x)$, 则 $\frac{f(x_0)}{x-x_0} + \frac{f(y)}{y-x} \ge \frac{y-x_0}{(y-x)(x-x_0)} f(x)$, $\frac{f(y)-f(x)}{y-x} \ge \frac{f(x)-f(x_0)}{x-x_0}$. 故 $\frac{f(y)-f(x_0)}{y-x_0} \ge \frac{f(x)-f(x_0)}{x-x_0}$. 故 $\frac{f(x)-f(x_0)}{x-x_0}$ 关于 $x$ 单调不减.

由于我们中途得到了 $\frac{f(y)-f(x)}{y-x} \ge \frac{f(x)-f(x_0)}{x-x_0}$, 类似地我们能够得到 $a < x < x_0 < y < b$, 则 $\frac{f(y)-f(x_0)}{y-x_0} \ge \frac{f(x_0)-f(x)}{x_0-x}$.

故 $f'_+(x_0) = \inf_{x_0 < x < b} \frac{f(x)-f(x_0)}{x-x_0}$. 对于任意 $x \in (x_0, b)$, 我们有 $f'_+(x_0) \le \frac{f(x)-f(x_0)}{x-x_0}$, 故 $f(x) \ge f(x_0) + f'_+(x_0)(x-x_0)$. $\blacksquare$

---

Lemma 2. 若 $b=+\infty$, $y=kx+m$ 是 $y=f(x)$ 当 $x \rightarrow +\infty$ 时的渐近线, 则 $x > a \rightarrow f(x) \ge kx+m$.

Proof. 设 $g(x)=f(x)-kx-m$, 则 $g$ 在 $(a, b)$ 内凸, $\lim_{x \rightarrow +\infty} g(x)=0$. 我们只需证 $x > a \rightarrow g(x) \ge 0$.

假设存在 $a < x < y$ 满足 $g(x) < g(y)$. 对于任意 $z > y$, 我们有 $0 < \frac{g(y)-g(x)}{y-x} \le \frac{g(z)-g(y)}{z-y}$, 故 $f'_+(y) > 0$. 考虑 $t=y+\max(0, -\frac{f(y)}{f'_+(y)}) + 1$. 如果 $f(y) \ge 0$ 则 $t=y+1$, 有 $x \ge t \rightarrow f(x) \ge f(y) + f'_+(y) > 0$; 否则 $f(y) < 0$ 则 $t=y-\frac{f(y)}{f'_+(y)}+1 > y$, 有 $x \ge t \rightarrow f(x) \ge f(y) + f'_+(y)(1-\frac{f(y)}{f'_+(y)})=1$. 总之存在一个 $M$ 使得 $x > M \rightarrow f(x) > 0$. 矛盾. 故 $g$ 在 $(a, +\infty)$ 单调不增.

故 $0$ 是 $g(x)$ 在 $(a, +\infty)$ 的下确界, $g(x) \ge 0$. $\blacksquare$
