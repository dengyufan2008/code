Prob 1. 是否存在 $a>0$ 使得 $\lim_{(x, y) \rarr (0, 0)} \frac{(x^2+y^2) \sin \frac{1}{\sqrt{x^2+y^2}}}{(x^2+y^2)^a}$ 存在且非 0? 解释理由.

不存在. 反证法, 假设存在, 则 $\lim_{(x, y) \rarr (0, 0)} \frac{(x^2+y^2) \sin \frac{1}{\sqrt{x^2+y^2}}}{(x^2+y^2)^a} = \lim_{r \rarr 0} \frac{r^2 \sin \frac{1}{r}}{r^{2a}} = \lim_{r \rarr 0} r^{2(1-a)} \sin \frac{1}{r}$.

观察后一个式子. 若 $a < 1$, 则极限为 0; 若 $a > 1$, 则极限为 $\infty$；若 $a = 1$, 则不收敛. 均不满足条件, 故不存在.
