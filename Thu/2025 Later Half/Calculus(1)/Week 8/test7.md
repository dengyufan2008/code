Prob 1. 求由方程 $\int_0^y \frac{\text{d}t}{\sqrt{1+t^2}}=x$ 确定的函数 $y(x)$.

两侧对 $y$ 求导, 得 $\frac{\text{d}x}{\text{d}y} = \frac{1}{\sqrt{1+y^2}}$, 故 $\frac{\text{d}y}{\text{d}x} = \sqrt{1+y^2}$, $(\frac{\text{d}y}{\text{d}x})^2 = 1+y^2$.

现在求解 $f'^2 = 1 + f^2 > 0$. 两边求导得 $2f'f'' = 2ff'$, 即 $f=f''$. 故 $f = Ae^x + Be^{-x}$. 代入回 $f'^2 = 1+f^2$, 有 $AB=-\frac{1}{4}$. 故 $f = Ae^x - \frac{1}{4A}e^{-x}$.

$\frac{\text{d}x}{\text{d}y} = \frac{1}{\sqrt{1+y^2}}$ 两侧对 $y$ 积分, 得 $x(y)+C = \int \frac{1}{\sqrt{1+t^2}} \text{d}t$, 故 $\int_0^y \frac{\text{d}t}{\sqrt{1+t^2}} = (x(y)+C) - (x(0)+C) = x(y)-x(0)$. 故只需保证 $x(0)=0$ 即可. 由于 $f'>0$, 只需保证 $f(0)=0$ 即可. 故有 $Ae^0-\frac{1}{4A}e^0 = 0$, $A = \frac{1}{2}$.

综上所述, $y(x)$ 有唯一解 $y=\sinh x$.
