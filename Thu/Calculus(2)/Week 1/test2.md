Prob 1. 设 $f(x, y)$ 在区域 (即道路连通的开集) $G$ 中定义, 且 $f(x, y)$ 关于 $x$ 连续; 关于 $y$ 连续且单调. 证明 $f$ 在 $G$ 中连续.

Proof. 对于任意 $(x_0, y_0) \in G$, 存在 $r > 0$ 使得 $(x_0, y_0)$ 的 $r$ 邻域都在 $G$ 内. 对于任意 $\epsilon > 0$, 取 $0 < \delta_0 < r$ 使得 $f(x_0, y_0) - \frac{1}{2}\epsilon < f(x_0, y_0 - \delta_0) < f(x_0, y_0) < f(x_0, y_0 + \delta_0) < f(x_0, y_0) + \frac{1}{2}\epsilon$.

取 $0 < \delta_1 < r$ 满足 $|x-x_0| < \delta_1 \rarr |f(x, y_0 - \delta_0) - f(x_0, y_0 - \delta_0)| < \frac{1}{2}\epsilon$. 取 $0 < \delta_2 < r$ 满足 $|x-x_0| < \delta_1 \rarr |f(x, y_0 + \delta_0) - f(x_0, y_0 + \delta_0)| < \frac{1}{2}\epsilon$.

令 $\delta = \min(\delta_0, \delta_1, \delta_2)$, 则对于任意 $(x, y)$ 满足 $\lVert (x, y) - (x_0, y_0) \rVert_\infty < \delta$, 有 $|y-y_0| < \delta_0$, $|x-x_0| < \min(\delta_1, \delta_2)$.

故 $f(x, y) < f(x, y_0 + \delta_0) < f(x_0, y_0 + \delta_0) + \frac{1}{2}\epsilon < f(x_0, y_0) + \epsilon$. 且 $f(x, y) > f(x, y_0 - \delta_0) > f(x_0, y_0 - \delta_0) + \frac{1}{2}\epsilon > f(x_0, y_0) - \epsilon$.
