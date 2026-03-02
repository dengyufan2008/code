已知 $\sum_{i=0}^{+\infty} \frac{(-1)^n}{2n+1} = \frac{\pi}{4}$.

Prob 1. 求 $\lim_{n \rightarrow +\infty} \int_0^\frac{\pi}{2} \frac{\sin 2nx}{\sin x} \text{d}x$.

我们有 $\sin 2nx - \sin (2n-2)x = (\sin (2n-1)x\cos x + \cos (2n-1)x\sin x) - (\sin (2n-1)x\cos x - \cos (2n-1)x\sin x) = 2\cos (2n-1)x\sin x$. 使用数学归纳法不难得出 $2\sin x(\cos x + \cos 3x + \cdots + \cos (2n-1)x) = \sin 2nx$, 故 $\frac{1}{2}\frac{\sin 2nx}{\sin x} = \cos x + \cos 3x + \cdots + \cos (2n-1)x$.

由此 $\lim_{n \rightarrow +\infty} \int_0^\frac{\pi}{2} \frac{\sin 2nx}{\sin x} \text{d}x = 2\lim_{n \rightarrow +\infty} \int_0^\frac{\pi}{2} \sum_{i=0}^{n-1} \cos (2i+1)x \text{d}x = 2\lim_{n \rightarrow +\infty} \sum_{i=0}^{n-1} \int_0^\frac{\pi}{2} \cos (2i+1)x \text{d}x = 2 \sum_{i=0}^{+\infty} \frac{(-1)^i}{2i+1} = \frac{\pi}{2}$.
