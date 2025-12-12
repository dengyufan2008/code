Prob 1. 求椭圆 $Ax^2+2Bxy+Cy^2=1 \space (A>0, AC>B^2)$ 的面积.

考虑 $y=\tan \theta x$ 与椭圆的交点, 有 $x = \plusmn \frac{1}{\sqrt{A+2B\tan \theta+C\tan^2 \theta}}$, $y = \plusmn \frac{\tan \theta}{\sqrt{A+2B\tan \theta+C\tan^2 \theta}}$.

此时 $r = \frac{\sqrt{1+\tan^2 \theta}}{\sqrt{A+2B\tan \theta+C\tan^2 \theta}}$.

我们有椭圆面积为 $S=2\int_{-\frac{\pi}{2}}^{\frac{\pi}{2}} \frac{r(\theta)^2}{2} \text{d}\theta = \int_{-\frac{\pi}{2}}^{\frac{\pi}{2}} \frac{1+\tan^2 \theta}{A + 2B \tan \theta  + C \tan^2 \theta} \text{d} \theta = \int_{-\frac{\pi}{2}}^{\frac{\pi}{2}} \frac{1}{A+2B\tan \theta+C \tan^2 \theta} \text{d} \tan \theta = \int_{-\infty}^{+\infty} \frac{1}{A+2Bx+Cx^2} \text{d}x = \frac{1}{\sqrt{AC-B^2}} \left. \arctan \frac{Cx+B}{\sqrt{AC-B^2}} \right |_{-\infty}^{+\infty} = \frac{\pi}{\sqrt{AC-B^2}}$.
