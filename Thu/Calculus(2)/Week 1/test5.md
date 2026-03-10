Prob 1. 给出一个 $f(x, y)$ 对 $x$, $y$ 分别连续, 但自身不连续.

有 $f(x, y) = \left\{\begin{aligned}&\frac{xy}{x^2+y^2} &x^2+y^2 > 0 \\ &0 &x^2+y^2=0\end{aligned}\right. \space$. 由于是对称函数, 考虑固定 $y$.

若 $y=0$, 则 $f(x, y)=0$, 显然连续. 若 $y \ne 0$, 则 $f(x, y)$ 是有理分式, 显然连续.

但是 $\lim_{\{(z, z)\} \ni (x, y) \rarr (0, 0)} f(x, y) = \frac{1}{2} \ne f(0, 0)$, 故不连续.
