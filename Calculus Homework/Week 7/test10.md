![](image.png)

Prob 1. 如图, 漂在河面上一根木桩能够通过这个直角转弯, 请问木桩长度最长是多少?

显然, 题意即为所有通过 $(a, b)$ 的斜率为负的直线中, 与 $x$ 轴交点和与 $y$ 轴交点的距离的最小值.

设直线斜率为 $-\tan x \space (0 < x < \frac{\pi}{2})$, 则两交点距离为 $f(x)=\frac{a}{\cos x}+\frac{b}{\sin x}$. 我们有 $f'(x)=a\frac{\sin x}{\cos^2 x} - b\frac{\cos x}{\sin^2 x}$, 则 $f$ 有唯一驻点 $x_0 = \arctan \sqrt[3]{\frac{b}{a}}$. 由于 $f$ 连续, 且 $\lim_{x \rightarrow 0} f(x) = \lim_{x \rightarrow \frac{\pi}{2}} f(x) = +\infty$, 则 $f$ 有最小值. 故 $x_0$ 是 $f$ 的最小值点.

不难看出 $\tan x_0 = \sqrt[3]{\frac{b}{a}}$, $\sin x_0 = \frac{b^\frac{1}{3}}{(a^\frac{2}{3}+b^\frac{2}{3})^\frac{1}{2}}$, $\cos x_0 = \frac{a^\frac{1}{3}}{(a^\frac{2}{3}+b^\frac{2}{3})^\frac{1}{2}}$. 故 $f(x_0) = (a^\frac{2}{3}+b^\frac{2}{3})^\frac{3}{2}$.
