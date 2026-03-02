Lemma 1. 若 $f$ 是 $[a, +\infty]$ 上的有界连续函数, 则对于任意 $\lambda>0$, 存在数列 $\{x_n\}$ 满足 $\lim_{n \rightarrow +\infty} x_n=+\infty$ 且 $\lim_{n \rightarrow +\infty} f(x_n+\lambda)-f(x_n)=0$.

Proof (使用 deepseek). 设 $g(x)=f(x+\lambda)-f(x)$, 则 $g$ 有界连续. 使用反证法. 假设 $\exist \lambda>0, \forall \{x_n\} \text{ that } \lim_{n \rightarrow +\infty} x_n = +\infty, \lnot (\lim_{n \rightarrow +\infty} g(x_n)=0)$.

对于这个 $\lambda$, 我们有 $\exist \epsilon>0, N \ge a, \forall x>N, |g(x)| \ge \epsilon$. 否则 $\forall \epsilon>0, \{x \ge a : |g(x)|< \epsilon\}$ 无上界, 则取 $\{x_n\}$ 满足 $x_n>a+n$, $|g(x_n)|<\frac{1}{n}$, 有反证假设不成立.

假设有 $x_1>N$ 和 $x_2>N$, $g(x_1)<-\epsilon$ 且 $g(x_2)>\epsilon$, 则存在一个 $x_0>N$, $g(x_0)=0$, 矛盾. 故不妨设 $\forall x>N, g(x)>\epsilon$, 否则可以考虑 $-f$.

任取一个 $x > N$, 我们有 $f(x+n\lambda)=f(x)+\sum_{i=0}^{n-1}g(x+i\lambda)>f(x)+n\epsilon$. 故 $\lim_{x \rightarrow +\infty} f(x)=+\infty$, 与有界矛盾. $\blacksquare$
