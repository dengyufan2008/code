Lemma 1. 若 $f$ 连续, $\lim_{x \rightarrow \infty} f(f(x)) = \infty$, 则 $\lim_{x \rightarrow \infty} f(x) = \infty$.

Proof. 考虑逆否命题, 即若 $\lim_{x \rightarrow \infty} f(x) = \infty$ 不成立, 则 $\lim_{x \rightarrow \infty} f(f(x)) = \infty$ 不成立.

若 $x \rightarrow +\infty$ 时 $f(x)$ 有界, 则 $x \rightarrow +\infty$ 时 $f(f(x))$ 有界, 故 $\lim_{x \rightarrow \infty} f(f(x)) = \infty$ 不成立.

若 $x \rightarrow +\infty$ 时 $f(x)$ 无界, 不妨设 $f(x)$ 无上界, 否则令 $f(x)$ 取相反数即可. 我们有 $x \rightarrow +\infty$ 时 $f(x)$ 不收敛到无穷, 则我们有 $\exist M, \forall N, \exist x_0 > f(N), |f(x_0)| \le M$.

我们有 $x \rightarrow +\infty$ 时 $f(x)$ 无上界, 故存在一个 $x_1>N$ 使得 $f(x_1)>x_0$. 我们有 $N<x_1$, $f(N)<x_0<f(x_1)$, 且 $f$ 连续, 则存在一个 $N < x_2 < x_1$ 使得 $f(x_2)=x_0$, 进一步有 $|f(f(x_2))| \le M$.

故 $\exist M, \forall N, \exist x_2 > N, |f(f(x_2))| \le M$, 也即 $x \rightarrow +\infty$ 时 $f(f(x))$ 不收敛到无穷. $\blacksquare$
