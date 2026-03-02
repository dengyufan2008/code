Prob 1. 解方程 $(x^2+y^2+3)y'=2x(2y-\frac{x^2}{y})$.

即 $(x^2+y^2+3) \frac{\text{d}y}{\text{d}x}=2x \frac{2y^2-x^2}{y}$, 即 $(x^2+y^2+3) (y \text{d}y) = (4y^2-2x^2) (x\text{d}x)$, 即 $(x^2+y^2+3) \text{d}y^2 = (4y^2-2x^2) \text{d}x^2$.

令 $u=x^2+2$, $v=y^2+1$. 即 $(2u-4v)\text{d}u+(u+v)\text{d}v=0$. 令 $w = \frac{v}{u}$, 即 $(2u-4wu)\text{d}u+(u+wu)(w\text{d}u+u\text{d}w)=0$, 即 $(2-3w+w^2)\text{d}u+u(1+w)\text{d}w=0$, 即 $-\frac{1}{u}\text{d}u=\frac{1+w}{2-3w+w^2} \text{d}w = (\frac{3}{w-2} - \frac{2}{w-1}) \text{d}w$.

故 $-\ln u = 3\ln(w-2)-2\ln(w-1)+C$, 即 $\frac{1}{u} = C\frac{(w-2)^3}{(w-1)^2}$, 即 $\frac{(v-2u)^3}{(v-u)^2} = C$, 即 $\frac{(y^2-2x^2-3)^3}{(y^2-x^2-1)^2} = C$. 经检验, $y^2=x^2+1$ 也是解.
