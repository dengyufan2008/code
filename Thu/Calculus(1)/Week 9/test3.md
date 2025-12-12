Prob 1. 求星形线 $|x|^\frac{2}{3} + |y|^\frac{2}{3} = a^\frac{2}{3} \space (a > 0)$ 的弧长, 面积.

考虑 $f(x) = (a^\frac{2}{3} - x^\frac{2}{3})^\frac{3}{2} \space (0 \le x \le a)$. 有 $f'(x) = - x^{-\frac{1}{3}}(a^\frac{2}{3} - x^\frac{2}{3})^\frac{1}{2}$.

$f$ 弧长为 $\int_0^a \sqrt{1+x^{-\frac{2}{3}}(a^\frac{2}{3}-x^\frac{2}{3})} \text{d}x = \int_0^a (\frac{a}{x})^\frac{1}{3} \text{d}x = \frac{3}{2}a$.

我们有 $f$ 的原函数为 $\frac{3a^2}{16}(\frac{8}{3}\sin^3(t)\cos^3(t)+2\sin^3(t)\cos(t)-\sin(t)\cos(t)+t)+C$, 其中 $x=a\sin^3(t)$ 即 $t=\arcsin [(\frac{x}{a})^\frac{1}{3}]$. 故 $f$ 面积为 $\frac{3}{32}\pi a^2$.

故原图形弧长为 $6a$, 面积为 $\frac{3}{8} \pi a^2$.
