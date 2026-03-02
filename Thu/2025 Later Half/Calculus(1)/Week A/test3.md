Prob 1. 求半径为 $R$ 的球壳对球内与球心距离为 $r$ 的质量为 $m$ 的质点的引力.

$\int_0^\pi \frac{G \rho m 2\pi R^2\sin \theta}{(R\cos \theta - r)^2+(R\sin \theta)^2} \frac{R\cos \theta-r}{((R\cos \theta - r)^2+(R\sin \theta)^2)^\frac{1}{2}} \text{d}\theta = (2 \pi G \rho m) \int_0^\pi \frac{\sin \theta (\cos \theta - t)}{((\cos \theta - t)^2+\sin^2 \theta)^\frac{3}{2}} \text{d}\theta = (2 \pi G \rho m) \int_{-1}^1 \frac{x-t}{((x-t)^2+1-x^2)^\frac{3}{2}} \text{d}x = (2 \pi G \rho m) \int_{-1}^1 \frac{x-t}{(-2tx+t^2+1)^\frac{3}{2}} \text{d}x = -\frac{\pi G \rho m}{2t^2} \int_{(1-t)^2}^{(1+t)^2} \frac{x+t^2-1}{x^\frac{3}{2}} \text{d}x = -\frac{\pi G \rho m}{t^2} \left. (\sqrt x + \frac{(1+t)(1-t)}{\sqrt x}) \right|_{x=(1-t)^2}^{(1+t)^2} = 0$, 其中 $t=\frac{r}{R}$.

故引力为 0.
