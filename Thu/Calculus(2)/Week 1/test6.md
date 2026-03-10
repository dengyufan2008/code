Prob 1. 设 $f(x, y) = \log_x(x+y)$, 讨论 $\lim_{x \rarr 1, y \rarr 0} f(x, y)$ 和 $\lim_{x \rarr 1} \lim_{y \rarr 0} f(x, y)$, $\lim_{y \rarr 0} \lim_{x \rarr 1} f(x, y)$.

$$
\begin{aligned}
\lim_{x \rarr 1} \lim_{y \rarr 0} f(x, y) &= \lim_{x \rarr 1} \lim_{y \rarr 0} \frac{\ln(x+y)}{\ln x}
\\
&= \lim_{x \rarr 1} 1
\\
&= 1.
\end{aligned}
$$

$$
\begin{aligned}
\lim_{y \rarr 0} \lim_{x \rarr 1} f(x, y) &= \lim_{y \rarr 0} \lim_{x \rarr 1} \frac{\ln(x+y)}{\ln x}
\\
&= \lim_{y \rarr 0} \frac{\ln(1+y)}{0}
\\
&= \lim_{y \rarr 0} +\infty
\\
&= +\infty.
\end{aligned}
$$

故 $\lim_{x \rarr 1, y \rarr 0} f(x, y)$ 不存在.
