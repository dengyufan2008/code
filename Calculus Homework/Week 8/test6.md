Prob 1. 求 $\lim_{x \rightarrow 0} \frac{\int_0^{2x} \tan(u^2) \text{d}u}{x^3}$.

设 $f(x)=\int_0^{2x} \tan(u^2) \text{d}u$, 则 $f'(x)=2\tan(4x^2)$, $f''(x)=16x(1+\tan^2(4x^2))$, $f'''(x)=16(1+\tan^2(4x^2)+16x^2\tan(4x^2))$. 我们有 $f(0)=f'(0)=f''(0)=0$, $f'''(0)=16$. 故 $f(x)=\frac{8}{3}x^3+o(x^3)$, $x \rightarrow 0$. 故 $\lim_{x \rightarrow 0} \frac{\int_0^{2x} \tan(u^2) \text{d}u}{x^3} = \frac{8}{3}$.
