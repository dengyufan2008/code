设 $f$ 是 $[0, +\infty)$ 上的正连续函数. 记 $\phi(x)=\frac{\int_0^x tf(t)\text{d}t}{\int_0^x f(t)\text{d}t}$.

Lemma 1. $\phi$ 单调递增.

Proof. 我们有 $\phi'=\frac{xf(x)\int_0^x f(t)\text{d}t - f(x)\int_0^x tf(t)\text{d}t}{(\int_0^x f(t)\text{d}t)^2}$. 只需证明 $x\int_0^x f(t)\text{d}t > \int_0^x tf(t)\text{d}t$ 即可. 当 $x=0$ 时两项均为 0, 故只需证明左侧导数更大即可.

我们有左侧导数为 $\int_0^x f(t)\text{d}t + xf(x)$, 右侧导数为 $xf(x)$. $\blacksquare$
