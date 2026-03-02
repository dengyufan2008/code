Prob 1. 设 $0<a<b$. 讨论 $f(x)=(\frac{a^x+b^x}{2})^\frac{1}{x}$ 的连续性, 单调性. 计算 $\lim_{x \rightarrow \plusmn\infty} f(x)$, $\lim_{x \rightarrow 0} f(x)$.

设 $c=\frac{b}{a}>1$, $g(x)=\ln \frac{f(x)}{a}=\frac{1}{x}\ln(\frac{1+c^x}{2})$.

当 $x \rightarrow 0$ 时, 我们有 $g(x)=\frac{\ln(1+\frac{x\ln c}{2}+o(x))}{x}=\frac{\frac{x \ln c}{2} + o(x)}{x}=\frac{\ln c}{2} + o(1)$. 故 $g$ 在 0 处有可去间断点, 极限为 $\frac{\ln c}{2}$. 因此 $f$ 在 0 处有可去间断点, 极限为 $\sqrt{ab}$.

我们有 $g'(x)=\frac{xc^x\ln c - (1+c^x)\ln(\frac{1+c^x}{2})}{x^2(1+c^x)}$. 设 $h(x)=x^2(1+c^x)g'(x)=xc^x\ln c - (1+c^x)\ln(\frac{1+c^x}{2})$, 我们有 $h'(x)=xc^x\ln^2 c - c^x \ln(\frac{1+c^x}{2}) \ln c$. 设 $p(x)=e^\frac{h'(x)}{c^x \ln c}=\frac{2c^x}{1+c^x}$.

我们有当 $x<0$ 时, $2c^x<1+c^x$, 即 $p(x)<1$; $x>0$ 时 $p(x)>1$; $x=0$ 时 $p(x)=1$. 故 $h'$ 与 $x$ 同号. 我们又有 $h(0)=0$ 且 $h$ 在 $(-\infty, +\infty)$ 上连续, 故 $h(x) > 0 \space (x \ne 0)$. 故 $g'(x) > 0 \space (x \ne 0)$. 故 $g$ 在 $(-\infty, 0)$ 和 $(0, +\infty)$ 单调递增, $f$ 在 $(-\infty, 0)$ 和 $(0, +\infty)$ 单调递增. 由于 $f$ 在 0 处可去间断, 若将 $f(0)$ 补充为极限值, 则 $f$ 单调递增.

显然 $\lim_{x \rightarrow -\infty} g(x)=\ln(\frac{1+\lim_{x \rightarrow -\infty}c^x}{2})\lim_{x \rightarrow -\infty} \frac{1}{x}=\ln \frac{1}{2} \cdot 0=0$. 故 $\lim_{x \rightarrow -\infty} f(x)=a$.

又有 $\lim_{x \rightarrow +\infty} \ln (\frac{1+c^x}{2}) - \ln \frac{c^x}{2}=\lim_{x \rightarrow +\infty} \ln (1+\frac{1}{c^x})=0$, 故 $\lim_{x \rightarrow +\infty} g(x) = \lim_{x \rightarrow +\infty} \frac{\ln \frac{c^x}{2}}{x}=\lim_{x \rightarrow +\infty} \frac{x \ln c - \ln 2}{x}=\ln c$. 故 $\lim_{x \rightarrow +\infty} f(x)=b$.

综上, $f$ 在 0 处可去间断, 极限为 $\sqrt{ab}$; 去间断后单调递增; $\lim_{x \rightarrow -\infty} f(x)=a$, $\lim_{x \rightarrow +\infty} f(x)=b$.
