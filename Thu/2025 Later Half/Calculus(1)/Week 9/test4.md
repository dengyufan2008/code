Prob 1. 求 $x=t-\sin t$, $y=1-\cos t$, $0 \le t \le 2\pi$ 的弧长和面积.

$\frac{\text{d}x}{\text{d}t}=1-\cos t$, $\frac{\text{d}y}{\text{d}t}=\sin t$. 故 $\frac{\text{d}y}{\text{d}x}=\frac{\sin t}{1-\cos t}$.

我们有弧长为 $\int_0^{2\pi} \sqrt{1+f'(x)^2} \text{d}x = \int_0^{2\pi} \sqrt{1+\frac{\sin^2 t}{(1-\cos t)^2}} \text{d} t-\sin t = 2\int_0^{2\pi} \sqrt{\frac{1-\cos t}{2}} \text{d}t = 4\int_0^{2\pi} \sin \frac{t}{2} \text{d}\frac{t}{2}=8$.

我们有面积为 $\int_0^{2\pi} f(x) \text{d}x = \int_0^{2\pi} 1-\cos t \text{d} t-\sin t = \int_0^{2\pi} (1-\cos t)^2 \text{d}t = 3\pi$.
