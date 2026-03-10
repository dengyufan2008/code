Prob 1. 设 $f:R^2 \rarr R$ 连续, $\lim_{(x, y) \rarr \infty} f(x, y) = -\infty$. 证明 $\forall C < f(0, 0)$, $\{(x, y) \mid f(x, y) = C\}$ 非空有界闭; $f$ 有最大值.

Proof. 假设存在 $C < f(0, 0)$ 使得 $\{(x, y) \mid f(x, y) = C \}$ 空或无界或非闭.

假设集合为空. 存在 $(x_0, y_0)$ 使得 $f(x_0, y_0) < C$. 则 $f(x_0, y_0) < C < f(0, 0)$, 且 $f$ 连续. 矛盾.

假设集合无界. 则存在点列 $(x_i, y_i)$, 使得 $\lVert (x_i, y_i) \rVert > i$, $f(x_i, y_i) = C$. 沿该点列求 $\lim_{(x, y) \rarr \infty} f(x, y)$, 则极限为 $C$. 矛盾.

假设集合非闭. 则存在点列 $(x_i, y_i)$, 使得 $f(x_i, y_i) = C$, 但 $f(x^*, y^*) \ne C$, 其中 $(x^*, y^*) = \lim_{n \rarr +\infty} (x_n, y_n)$. 但是由于 $f$ 连续, 矛盾.

我们证明 $S=\{(x, y) \mid f(x, y) \ge f(0, 0)\}$ 非空有界闭. 非空显然. 假设无界, 则存在趋于无穷的点列使得函数值不小于 $f(0, 0)$, 矛盾. 假设非闭, 则与连续矛盾.

则可以取 $t = \max_{(x, y) \in S} f(x, y)$. 由于 $(x, y) \notin S \rarr f(x, y) < f(0, 0) \le t$, 则 $t$ 为最大值.
