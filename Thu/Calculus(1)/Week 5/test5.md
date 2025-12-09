设 $0 < \epsilon < 1$, 有曲线 $\gamma=\left\{
\begin{aligned}
& x(t)=t-\epsilon \sin t
\\
& y(t)=1-\epsilon \cos t
\end{aligned}
\right.$, 按以下步骤求 $\gamma$ 经过点 $P(0, 1-\epsilon)$ 时的曲率 $\kappa$.

---

Prob 1. 写出 $\gamma$ 在 $P$ 处的切线和法线 $L_1$ 方程.

解 $t-\epsilon \sin t=0$ 得 $t=0$. 又根据第一题有 $\frac{\text{d}y}{\text{d}x}=\frac{\epsilon \sin t}{1-\epsilon \cos t}=0$. 故在 $P$ 的切线为 $y=1-\epsilon$, 法线为 $x=0$.

---

Prob 2. 求 $\gamma$ 在点 $Q(t-\epsilon \sin t, 1-\epsilon \cos t)$ 处的法线 $L_2$ 与 $L_1$ 的交点坐标.

有 $\frac{\text{d}y}{\text{d}x}=\frac{\epsilon \sin t}{1-\epsilon \cos t}$, 故在 $Q$ 的法线为 $y=\frac{\epsilon \cos t-1}{\epsilon \sin t} x + \frac{t-\epsilon t \cos t}{\epsilon \sin t} \space (t \ne k \pi)$, 与 $x=0$ 交于 $(0, \frac{t-\epsilon t \cos t}{\epsilon \sin t})$.

---

Prob 3. 让 $t \rightarrow 0$, 求交点的极限 $C$.

我们有

$$
\begin{aligned}
\lim_{t \rightarrow 0} \frac{t-\epsilon t \cos t}{\epsilon \sin t} &= \frac{1}{\epsilon \lim_{t \rightarrow 0} \frac{\sin t}{t}} - \frac{1}{\lim_{t \rightarrow 0} \frac{\tan t}{t}}
\\
&= \frac{1}{\epsilon \lim_{t \rightarrow 0} \frac{t+o(t)}{t}} - \frac{1}{\lim_{t \rightarrow 0} \frac{t+o(t)}{t}}
\\
&= \frac{1}{\epsilon} - 1.
\end{aligned}
$$

故 $C(0, \frac{1-\epsilon}{\epsilon})$.

---

Prob 4. 求 $C$ 与 $P$ 的距离的倒数 $\kappa$.

我们有 $\frac{1-\epsilon}{\epsilon}-(1-\epsilon)=\frac{(1-\epsilon)^2}{\epsilon}$. 故 $\kappa=\frac{\epsilon}{(1-\epsilon)^2}$.
