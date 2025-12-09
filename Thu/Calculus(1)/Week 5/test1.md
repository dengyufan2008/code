Prob 1. 设 $0 < \epsilon < 1$, 有曲线 $\left\{
\begin{aligned}
& x(t)=t-\epsilon \sin t
\\
& y(t)=1-\epsilon \cos t
\end{aligned}
\right.$, 求 $\frac{\text{d}^2y}{\text{d}x^2}$.

---

我们有 $\frac{\text{d}y}{\text{d}t}=\epsilon \sin t$, 以及 $x=t-\epsilon \sin t$. 两侧对 $x$ 求导, 得到 $1=t'-\epsilon t' \cos t$, 得 $\frac{\text{d}t}{\text{d}x}=\frac{1}{1-\epsilon \cos t}$. 故 $\frac{\text{d}y}{\text{d}x}=\frac{\epsilon \sin t}{1-\epsilon \cos t}$.

进一步求导有

$$
\begin{aligned}
\frac{\text{d}^2y}{\text{d}x^2} &= \frac{\epsilon t' \cos t -\epsilon^2 t' \cos^2 t - \epsilon^2 t' \sin^2 t}{(1-\epsilon \cos t)^2}
\\
&= \frac{\epsilon (\cos t - \epsilon)}{(1-\epsilon \cos t)^3}.
\end{aligned}
$$
