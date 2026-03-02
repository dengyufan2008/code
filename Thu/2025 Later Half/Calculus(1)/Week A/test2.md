Prob 1. 求 $x=t-\sin t$, $y=1-\cos t$, $(0 \le t \le 2\pi)$ 的质心.

我们有 $x'=1-\cos t$, $y'=\sin t$. $\frac{\text{d}{l}}{\text{d}t} = \sqrt{(1-\cos t)^2+\sin^2 t} = \sqrt{2-2\cos t} = 2\sin \frac{t}{2}$.

$L = 4 \int_0^{\pi} \sin t \text{d}t=8$.

$x_0=\frac{2}{L}\int_0^{2\pi} (t-\sin t)\sin \frac{t}{2} \text{d}t=\pi$.

$y_0=\frac{2}{L}\int_0^{2\pi} (1-\cos t)\sin \frac{t}{2} \text{d}t=\frac{4}{3}$.

故质心为 $(\pi, \frac{4}{3})$.

---

Prob 2. 求曲线与 $x$ 轴围成的区域的质心.

$S=\int_0^{2\pi} (1-\cos t)^2 \text{d}t=3\pi$.

$x_0 = \frac{1}{S} \int_0^{2\pi} (t-\sin t)(1-\cos t)^2 \text{d}t=\pi$.

$y_0 = \frac{1}{2S} \int_0^{2\pi} (1-\cos t)^3 \text{d}t=\frac{5}{6}$.

故质心为 $(\pi,\frac{5}{6})$.

---

Prob 3. 求绕 $x$ 轴旋转一周的体积.

$V=\pi\int_0^{2\pi} (1-\cos t)^3 \text{d}t=5\pi^2$.

---

Prob 4. 求旋转体的侧面积.

$S=4\pi\int_0^{2\pi} (1-\cos t) \sin \frac{t}{2}=\frac{64}{3} \pi$.
