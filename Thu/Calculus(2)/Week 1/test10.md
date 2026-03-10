Prob 1. $f:I \rarr R$ 是区间 $I \subseteq R$ 上的凸函数. 任取 $\varnothing \ne (x, y) \subset [a_1, b_1] \subset [a_2, b_2] \subset I$, 证明 $|\frac{f(y)-f(x)}{y-x}| \le \max(|\frac{f(b_2)-f(b_1)}{b_2-b_1}|, |\frac{f(a_2)-f(a_1)}{a_2-a_1}|)$.

有 $\frac{f(a_2)-f(a_1)}{a_2-a_1} \le \frac{f(x)-f(a_2)}{x-a_2} \le \frac{f(y)-f(x)}{y-x} \le \frac{f(b_1)-f(y)}{b_1-y} \le \frac{f(b_2)-f(b_1)}{b_2-b_1}$.

---

Prob 2. 设 $K \subseteq R^m$ 是凸开集. 证明凸函数 $f:K \rarr R$ 是局部 Lipschitz 函数, 即对 $x_0 \in K$, 存在邻域 $U$ 和 $L > 0$, 对 $x, y \in U$ 有 $|f(x)-f(y)| \le L\lVert x-y \rVert$.

任取 $x_0 \in K$. 取 $r>0$ 使得 $x_0$ 的 $2r$ 邻域在 $K$ 内 (使用 $\lVert \cdot \rVert_1$ 作为范数). 则容易发现邻域内所有点都能用 $S = \{x_0 \plusmn 2re_i \mid e_i \space 为标准正交基\}$ 的凸组合表示. 故邻域内的函数值有界 $M = \max_{x \in S} |f(x)|$.

任取 $r$ 邻域内 $x, y$. 令 $z=x + r\frac{x-y}{\lVert x-y \rVert}$, 则 $\lVert z \rVert \le \lVert x \rVert + r < 2r$. 故 $x, y, z$ 均在 $2r$ 邻域内, 且 $x=(1-t)y+tz$, 其中 $t=\frac{\lVert x-y \rVert}{r+\lVert x-y \rVert}$.

故 $f(x) \le (1-t)f(y) + tf(z)$, 即 $f(x)-f(y) \le t(f(z)-f(y))$.

故 $f(x)-f(y) \le t(f(z)-f(y)) \le 2Mt \le 2M \frac{\lVert x-y \rVert}{r}$. 同理 $f(y)-f(x) \le 2M \frac{\lVert x-y \rVert}{r}$.

取 $U$ 为半径为 $r$ 的 $\lVert \cdot \rVert_1$ 下的邻域, $L=\frac{2M}{r}$ 即可.
