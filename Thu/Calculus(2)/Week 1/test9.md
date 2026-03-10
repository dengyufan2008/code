Prob 1. 设 $f(x, y)$ 在区域 $G$ 中定义. $f$ 关于 $x$ 连续, 存在 $k > 0$ 使得 $|f(x, y_1) - f(x, y_2)| \le k|y_1 - y_2|$. 证明 $f$ 连续.

对于任意 $(x_0, y_0) \in G$, 存在 $r > 0$ 使得 $r$ 邻域在 $G$ 内. 对于任意 $\epsilon > 0$, 可以取 $\delta_1$ 使得 $|x-x_0| < \delta_1 \rarr |f(x, y_0) - f(x_0, y_0)| < \frac{1}{2}\epsilon$. 又可以取 $\delta < \min(\delta_1, \frac{1}{2k}\epsilon, r)$.

对于任意 $(x, y)$ 满足 $\lVert (x, y) - (x_0, y_0) \rVert_\infty < \delta$, 我们有 $|x-x_0| < \delta < \delta_1$, $|y-y_0| < \delta < \frac{1}{2k}\epsilon$. 故 $|f(x, y_0) - f(x_0, y_0)| < \frac{1}{2}\epsilon$, $|f(x, y) - f(x, y_0)| \le k|y-y_0| < \frac{1}{2}\epsilon$. 故 $|f(x, y) - f(x_0, y_0)| < \epsilon$.
