考虑 $\frac{y''}{1+y'^2}+a\frac{xy'-y}{x^2+y^2}=0$.

Prob 1. 求在坐标系 $u, v$ 下的形式, $u=\lambda x$, $v=\lambda y$.

容易发现不变.

Prob 2. 求在极坐标系下的形式.

即 $(\arctan y')' + a (\arctan \frac{y}{x})'=0$, 即 $\frac{\text{d}\phi}{\text{d}x}+a\frac{\text{d}\theta}{\text{d}x}=0$, 即 $\text{d}\phi + a\text{d}\theta=0$. 其中 $\phi$ 为切线与 $x$ 轴的夹角.

即 $\frac{\text{d}\phi}{\text{d}\theta}=-a$, $\arctan y'=-a\theta+C$, $\frac{\sin \theta \text{d}r + r \cos \theta \text{d}\theta}{\cos \theta \text{d}r - r \sin \theta \text{d}\theta} = \tan(-a \theta + C)$, $\frac{\text{d}r}{\text{d}\theta}=-r \frac{\cos \theta + \sin \theta \tan(-a\theta+C)}{\sin \theta - \cos \theta \tan(-a\theta+C)} = -r\frac{1+\tan\theta\tan(-a\theta+C)}{\tan \theta - \tan(-a\theta+C)} = -r\cot((1+a)\theta+C)$.

Prob 3. 解方程.

即 $-\frac{1}{r}\text{d}r=\cot((1+a)\theta+C) \text{d}\theta$.

若 $a \ne -1$, 即 $-\ln r = \frac{1}{1+a} \ln |\sin((1+a)\theta+C)| + K$, 即 $r = K|\sin((1+a)\theta+C)|^{-\frac{1}{1+a}} \space (K > 0)$.

当 $a=-1$ 时, 即 $-\ln r = \theta \cot C + K$, 即 $r = Ke^{-\theta \cot C} \space (K > 0)$.
