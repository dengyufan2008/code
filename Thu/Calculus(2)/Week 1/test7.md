Prob 1. 令 $f:[0, 1] \times (0, 1]$ 满足 $f(x, y) = \frac{1}{1+(1+xy)^\frac{1}{y}}$. $f$ 是否可以连续延拓到 $[0, 1] \times [0, 1]$?

可以连续延拓.

$$
\begin{aligned}
\lim_{(x, y) \rarr (x_0, 0)} \frac{\ln(1+xy)}{y} &= \lim_{(x, y) \rarr (0, 0)} \frac{\ln(1+x_0y+xy)}{y}
\\
&= \lim_{(x, y) \rarr (0, 0)} \frac{x_0y + xy + o(y)}{y}
\\
&= \lim_{(x, y) \rarr (0, 0)} x_0 + x + o(1)
\\
&= x_0.
\end{aligned}
$$

故 $\lim_{(x, y) \rarr (x_0, 0)} f(x, y) = \frac{1}{1+e^{x_0}}$.
