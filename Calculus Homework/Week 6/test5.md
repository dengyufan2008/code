Prob 1. 讨论 $f(x)=(1+\frac{1}{x})^{x+a}$ 的单调性.

显然当 $x<-1$ 时, 设 $y=-1-x$, 我们有 $f(x)=(1+\frac{1}{-1-y})^{-1-y+a}=(1+\frac{1}{y})^{y-a+1}$. 故 $x<-1$ 时的结论即为 $a$ 沿 $\frac{1}{2}$ 翻转, $x$ 沿 $-\frac{1}{2}$ 翻转后 $x>0$ 时的结论. 故下文假设 $x>0$.

设 $g(x)=\ln(f(x))=(x+a)\ln(1+\frac{1}{x})$. 我们有 $g'(x)=\ln(1+\frac{1}{x})-\frac{x+a}{x(x+1)}$. 设 $h(x)=x(x+1)g'(x)=x(x+1)\ln(1+\frac{1}{x})-(x+a)$. 有 $h'(x)=(2x+1)\ln(1+\frac{1}{x})-2$.

我们现在证明 $h'(x)>0$. 我们先证明 $\ln(1+x)>\frac{2x}{2+x}$. 两边求导分别为 $\frac{1}{1+x}$ 和 $\frac{4}{(2+x)^2}$. 我们有 $\frac{1}{1+x}-\frac{4}{(2+x)^2}=\frac{x^2}{(1+x)(2+x)^2}>0$. 又有 $x=0$ 时两式均为 0, 且两式连续. 故得证. 令 $y=\frac{1}{x}>0$, 有 $\ln(1+y)>\frac{2y}{2+y}$, $(\frac{2}{y}+1)\ln(1+y)>2$, 即 $(2x+1)\ln(1+\frac{1}{x})-2>0$.

故 $h$ 在 $(0, +\infty)$ 单调递增. 有 $\lim_{x \rightarrow 0^+} x(x+1)\ln(1+\frac{1}{x})=\lim_{x \rightarrow 0^+} x(x+1)\ln(x+1)-\lim_{x \rightarrow 0^+} x(x+1)\ln x=0-0=0$. $\lim_{x \rightarrow +\infty} x(x+1)\ln(1+\frac{1}{x})-x=\lim_{x \rightarrow 0^+} \frac{x+1}{x^2}\ln(1+x)-\frac{1}{x}=\lim_{x \rightarrow 0^+} \frac{(1+x)(x-\frac{x^2}{2}+o(x^2))-x}{x^2}=\lim_{x \rightarrow 0^+} \frac{1}{2}+o(x)=\frac{1}{2}$. 故 $\lim_{x \rightarrow 0^+} h(x)=-a$, $\lim_{x \rightarrow +\infty} h(x)=\frac{1}{2}-a$.

容易发现当 $a \le 0$ 或 $a \ge \frac{1}{2}$ 时 $h$ 在 $(0, +\infty)$ 上没有零点, 故 $g'(x)$ 没有零点. 否则 $h$ 在 $(0, +\infty)$ 上有恰好一个零点, 故 $g'(x)$ 有恰好一个零点.

当 $a \le 0$ 时, $g'(1)=\ln 2 - \frac{a+1}{2}=(\ln 2 - \frac{1}{2})-\frac{a}{2}>0$, 故 $g$ 单调递增, $f$ 单调递增.

当 $a \ge \frac{1}{2}$ 时, $g'(1)=-(\frac{3}{4}- \ln 2)-\frac{a-\frac{1}{2}}{2}<0$, 故 $g$ 单调递减, $f$ 单调递减.

当 $0 < a < \frac{1}{2}$ 时, $\lim_{x \rightarrow 0^+} g'(x) = \lim_{x \rightarrow 0^+} \frac{h(x)}{x(x+1)}=-a \cdot +\infty=-\infty$. 故 $g$ 和 $f$ 均在 $(0, x_0)$ 单调递减, $(x_0, +\infty)$ 单调递增. 其中 $x_0$ 满足 $\ln(1+\frac{1}{x_0})=\frac{x_0+a}{x_0(x_0+1)}$.
