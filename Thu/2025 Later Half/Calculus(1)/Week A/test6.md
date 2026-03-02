Prob 1. 计算 $\int_0^{+\infty} \frac{x\ln x}{(1+x^2)^3} \text{d}x$.

$$
\begin{aligned}
\int_0^{+\infty} \frac{x\ln x}{(1+x^2)^3} \text{d}x &= \frac{1}{4} \int_0^{+\infty} \frac{\ln x^2}{(1+x^2)^3} \text{d}x^2
\\
&= \frac{1}{4} \int_0^{+\infty} \frac{\ln x}{(1+x)^3} \text{d}x
\\
&= \frac{1}{4} \int_1^{+\infty} \frac{\ln (x-1)}{x^3} \text{d}x
\\
&= -\frac{1}{8} \int_1^{+\infty} \ln (x-1) \text{d} \frac{1}{x^2}
\\
&= -\frac{1}{8} \left. \frac{\ln(x-1)}{x^2} \right|_{x=1}^{+\infty}+\frac{1}{8} \int_1^{+\infty} \frac{1}{x^2(x-1)} \text{d}x
\\
&= -\frac{1}{8} \left. \frac{\ln(x-1)}{x^2} \right|_{x=1}^{+\infty}+\frac{1}{8} \int_1^{+\infty} (\frac{1}{x-1}-\frac{1}{x}-\frac{1}{x^2}) \text{d}x
\\
&= -\frac{1}{8} \left. \frac{\ln(x-1)}{x^2} \right|_{x=1}^{+\infty}+\frac{1}{8} \left. (\ln \frac{x-1}{x}+\frac{1}{x}) \right|_{x=1}^{+\infty}
\\
&= \frac{1}{8} \ln(0) + \frac{1}{8} \ln(1) - \frac{1}{8} \ln(0) - \frac{1}{8}
\\
&= -\frac{1}{8}.
\end{aligned}
$$

Prob 2. 计算 $\int_0^{+\infty} \frac{\arctan x}{(1+x^2)^\frac{3}{2}} \text{d}x$.

$$
\begin{aligned}
\int_0^{+\infty} \frac{\arctan x}{(1+x^2)^\frac{3}{2}} \text{d}x &= \int_0^{\frac{\pi}{2}} \frac{x}{\sqrt{1+\tan^2 x}} \text{d}x
\\
&= \int_0^{\frac{\pi}{2}} x \text{d} \sin x
\\
&= \left. x \sin x \right|_{x=0}^{\frac{\pi}{2}} - \int_0^{\frac{\pi}{2}} \sin x \text{d}x
\\
&= \frac{\pi}{2} - 1.
\end{aligned}
$$

Prob 3. 计算 $\int_0^1 \ln x \text{d}x$.

$$
\begin{aligned}
\int_0^1 \ln x \text{d}x &= \left. (x\ln x-x) \right|_{x=0}^1
\\
&= -1.
\end{aligned}
$$
