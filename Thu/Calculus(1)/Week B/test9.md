解方程.

Prob 1. $(1+x^2)y''-2xy'=0$.

设 $z=y'$, 则 $(1+x^2)\frac{\text{d}z}{\text{d}x}-2xz=0$, 即 $\frac{1}{z}\text{d}z=\frac{2x}{1+x^2}\text{d}x$, 即 $\ln z = \ln (1+x^2) + C$, 即 $y' = C(1+x^2)$, 即 $y=C(x+\frac{1}{3}x^3)+C'$.

Prob 2. $y''+\frac{2y'^2}{1-y}=0$.

令 $z=y'$, 则 $z'z + \frac{2z^2}{1-y} = 0$, 即 $\frac{\text{d}z}{\text{d}y} + \frac{2z}{1-y}=0$, 即 $\frac{1}{2z} \text{d}z = \frac{1}{y-1}\text{d}y$. 故 $\frac{1}{2} \ln z = \ln(y-1) + C$, $\frac{\text{d}y}{\text{d}x} = C(y-1)^2$.

故 $\frac{1}{(y-1)^2} \text{d}y = C\text{d}x$, 即 $-\frac{1}{y-1} = Cx+C'$, 即 $y = 1 - \frac{1}{Cx+C'}$.

Prob 3. $yy''-y'^2=0$.

令 $z=y'$, 则 $yz'z-z^2=0$, 即 $\frac{\text{d}z}{\text{d}y}=\frac{z}{y}$, 即 $\ln z = \ln y + C$, 即 $y' = Cy$, 即 $y=C'e^{Cx}$.

Prob 4. $y''-y'^3 = 0$.

令 $z=y'$, 则 $z'z-z^3=0$, 即 $z'=z^2$, 即 $\frac{\text{d}y}{\text{d}x}=-\frac{1}{y+C}$, 即 $(y+C)\text{d}y=-\text{d}x$, 即 $\frac{1}{2}y^2+Cy=-x+C'$, 故 $y=C \plusmn \sqrt{-2x+C'}$.

Prob 5. $x(x+1)y''-(4x+2)y'+6y=0$.

不难验证 $y_0=3x^2+3x+1$ 是解. 若 $y=C(x)y_0$ 是解, 则

$$x(x+1)(C''y_0+2C'y_0')-(4x+2)C'y_0=0.$$

设 $z=C'$, 则

$$x(x+1)y_0z'+2[x(x+1)y_0'-(2x+1)y_0]z=0.$$

即 $x(x+1)y_0z'=(4x+2)z$, 即 $\frac{1}{z} \text{d}z = \frac{4x+2}{x(x+1)y_0} \text{d}x = (\frac{2}{x}+\frac{2}{x+1}-\frac{12x+6}{y_0})\text{d}x$, 即 $\ln z = 2\ln x + 2 \ln(x+1) - 2 \ln y_0 + K$, 即 $z = K\frac{x^2(x+1)^2}{y_0^2}$. 故 $C(x)=\frac{1}{9}K(x+\frac{2x+1}{y_0})+K'$, 即 $y=K(xy_0+2x+1)+K'y_0=3Kx^3+(K+K')(3x^2+3x+1)=Kx^3+K'(3x^2+3x+1)$.

Prob 6. $x^2y''-(x-1)^2y'+y=0$.

令 $z=x^2y'-y$, 则 $z'-z=0$, $z=Ce^x$. 故 $x^2y'-y=Ce^x$.

利用积分因子法, 得到 $y=e^{-\frac{1}{x}}(C\int_{x_0}^x \frac{e^{t+\frac{1}{t}}}{t^2} \text{d}t + C')$.

Prob 7. $y''-y'^2=0$, $y(0)=0$, $y'(0)=1$.

令 $z=y'$, 则 $z'-z^2=0$, $z=-\frac{1}{x+C}$. 由于 $z(0)=1$, 则 $z=-\frac{1}{x-1}$. $y=-\ln|x-1|+C$, 由于 $y(0)=0$, 则 $y=-\ln|x-1|$.
