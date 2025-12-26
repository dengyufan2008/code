Prob 1. 求 $x^3+y^3=3xy$ 和它的渐近线围成的面积.

设 $t=\frac{y}{x}$, 则有 $x=\frac{3x^2y}{x^3+y^3}=\frac{3t}{t^3+1}$, 故 $y=\frac{3t^2}{t^3+1}$.

当且仅当 $t \rightarrow -1$ 时 $x \rightarrow \infty$, 此时 $y=-x+o(x)$. 又有 $x+y=\frac{3t^2+3t}{t^3+1}=\frac{3t}{t^2-t+1}$, 故 $t \rightarrow -1$ 时 $x+y \rightarrow -1$. 故 $x+y=-1$ 是渐近线.

容易发现曲线和渐近线被分为 $t \le 0$ 与渐近线 以及 $t \ge 0$ 两段简单曲线. 第一部分的面积为 $\int_{-\infty}^0 (\frac{3t^2}{t^3+1}+\frac{3t}{t^3+1}+1) \frac{-6t^3+3}{(t^3+1)^2} \text{d}t = \frac{3}{2}$, 第二部分的面积为 $-\int_0^{+\infty} \frac{3t^2}{t^3+1} \frac{-6t^3+3}{(t^3+1)^2} \text{d}t = \frac{3}{2}$.
