Prob 1. 证明 $y'=\frac{x^2(y-2x^3)}{2y+3x^3}$ 在坐标变换 $(x, y) \rightarrow (\lambda x, \lambda^3 y)$ 下表示不变.

令 $x=\lambda s$, $y=\lambda^3 t$, 有 $\frac{\lambda^3 \text{d}t}{\lambda \text{d}s} = \frac{\lambda^2s^2(\lambda^3t-2\lambda^3s^3)}{2\lambda^3t+3\lambda^3s^3}$, 即 $t'=\frac{s^2(t-s^3)}{2t+3s^3}$, 故保持不变.

Prob 2. 求微分方程的解.

令 $y=x^3f(x)$, 则有 $\frac{2f+3}{(3f+1)(f+1)} \text{d}f = -\frac{2}{x} \text{d}x$, 即 $7\ln(3f+1)-3\ln(f+1)=-12\ln x+C$, 即 $\frac{(3y+x^3)^7}{(y+x^3)^3}=C$. 经过检验得到 $y=-x^3$ 同样是一个特解.
