已知 $f$ 满足 $f(1)=1$, $f'(x)=\frac{1}{x^2+f^2(x)}$.

Lemma 1. $\lim_{x \rightarrow +\infty} f(x)$ 存在且不超过 $1+\frac{1}{4}\pi$.

Proof. 只需证明 $\int_1^{+\infty} \frac{1}{x^2+f^2(x)} \text{d}x \le \frac{1}{4}\pi$ 即可. 显然 $f'(x)=\frac{1}{x^2+f^2(x)}>0$, 则 $f(x) \ge 1 \space (x \ge 1)$.

故 $\int_1^{+\infty} \frac{1}{x^2+f^2(x)} \text{d}x \le \int_1^{+\infty} \frac{1}{x^2+1} \text{d}x = \lim_{x \rightarrow +\infty}\arctan(x) - \arctan(1) = \frac{1}{4}\pi$. $\blacksquare$
