设 $f(x)=xe^x$.

Prob 1. 讨论 $f$ 的单调性, 极值, 最值.

我们有 $f'(x)=(x+1)e^x$, 故 $f$ 在 $[-1, +\infty)$ 单调递增, $(-\infty, -1]$ 单调递减.

显然 $f$ 有唯一极值点 $-1$, 不难看出其为极小值点.

因此 $f$ 有最小值 $f(-1)=-\frac{1}{e}$, 没有最大值.

---

Prob 2. 讨论 $y=f(x)$ 的渐近线.

我们有 $\lim_{x \rightarrow +\infty} xe^x-kx = \lim_{x \rightarrow +\infty} x \lim_{x \rightarrow +\infty} e^x-k = +\infty \cdot +\infty = +\infty$, 故 $x \rightarrow +\infty$ 时不存在渐近线.

我们又有 $\lim_{x \rightarrow -\infty} xe^x = -\lim_{x \rightarrow +\infty} \frac{x}{e^x}$. 当 $x > 0$ 时有 $e^x > \frac{x^2}{2}$, 故 $0 \le \lim_{x \rightarrow +\infty} \frac{x}{e^x} \le \lim_{x \rightarrow +\infty} \frac{x}{\frac{1}{2}x^2}=0$. 故 $x \rightarrow -\infty$ 时有水平渐近线.

---

Prob 3. 讨论 $f$ 凹凸性.

我们有 $f''(x)=(x+2)e^x$, 则 $f$ 在 $[-2, +\infty)$ 上凸, $(-\infty, -2]$ 上凹.

---

Prob 4. 证明 $f$ 在 $(-1, +\infty)$ 上有反函数 $g$, 求 $g$ 的定义域.

由于 $f$ 单调递增, 则存在反函数 $g$. 我们只需求 $f$ 在 $(-1, +\infty)$ 的值域即可, 有 $\lim_{x \rightarrow -1} f(x) = f(-1) = -\frac{1}{e}$, $\lim_{x \rightarrow +\infty} f(x) = +\infty$, 故值域为 $(-\frac{1}{e}, +\infty)$.

---

Prob 5. 讨论 $g$ 的单调性, 凹凸性, 渐近线.

由于 $f$ 单调递增, 则 $g$ 单调递增. 我们有 $g' = \frac{1}{f'(g)} = \frac{e^{-g}}{g+1}$, 则 $g'' = -\frac{g'(g+2)e^{-g}}{(g+1)^2}$. 由于 $g$ 单调递增, 且 $g > -1$, 故 $g'' < 0$, $g$ 凹.

由于 $g$ 连续, 则其至多有斜渐近线. 由于 $\lim_{y \rightarrow +\infty} g(y) = +\infty$, 我们有 $\lim_{y \rightarrow +\infty} \frac{g(y)}{y} = \lim_{y \rightarrow +\infty} g'(y) = \frac{\lim_{y \rightarrow +\infty} e^{-g(y)}}{\lim_{y \rightarrow +\infty g(y)+1}} = \frac{0}{+\infty}=0$. 故对于任意 $k>0$ 有 $\lim_{y \rightarrow +\infty} g(y)-ky = (+\infty)(0-k) = -\infty$. 故 $g$ 不存在渐近线.

---

Prob 6. 证明 $\lim_{x \rightarrow +\infty} \frac{g(x)}{\ln x} = 1$.

我们有 $\lim_{x \rightarrow +\infty} \frac{g(x)}{\ln x} = \lim_{x \rightarrow +\infty} \frac{x}{\ln f(x)} = \lim_{x \rightarrow +\infty} \frac{x}{x + \ln x} = \frac{1}{1+\lim_{x \rightarrow +\infty} \frac{\ln x}{x}}$. 又有 $\lim_{x \rightarrow +\infty} \frac{\ln x}{x} = \lim_{x \rightarrow +\infty} \frac{1}{x} = 0$, 故 $\lim_{x \rightarrow +\infty} \frac{g(x)}{\ln x}=1$.
