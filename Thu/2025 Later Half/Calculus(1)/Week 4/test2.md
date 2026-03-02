Lemma 1. 设 $f$, $g$ 是 $[a, b]$ 上的连续函数, 且存在数列 $\{x_n\} \subset [a, b]$ 满足 $g(x_n)=f(x_{n+1})$, 则存在 $x_0 \in [a, b]$, 使得 $f(x_0)=g(x_0)$.

Proof. 反证法, 假设 $f$ 与 $g$ 在 $[a, b]$ 上不相交. 不妨设 $f(x)<g(x)$, 否则考虑 $-f$ 和 $-g$ 即可.

我们有 $f(x_1)<g(x_1)=f(x_2)<g(x_2)=\cdots$. 故 $f(x_1)<f(x_2)<\cdots$, $g(x_1)<g(x_2)<\cdots$. 但由于 $f$, $g$ 是在 $[a, b]$ 上的连续函数, 则存在最大值. 故数列 $\{f(x_n)\}$ 和 $\{g(x_n)\}$ 单调有界, 从而存在极限, 且由于 $g(x_n)=f(x_{n+1})$, 两数列有相同的极限. 设 $\lim_{k \rightarrow +\infty} f(x_k)=\lim_{k \rightarrow +\infty} g(x_k)=A$.

由于列紧性, 可以找到 $n_1<n_2<\cdots$ 使得 $\lim_{k \rightarrow +\infty}x_{n_k}=x_0$. 由于 $[a, b]$ 是闭集, $x_0 \in [a, b]$. 我们有 $A=\lim_{k \rightarrow +\infty} f(x_k)=\lim_{k \rightarrow +\infty} f(x_{n_k})=f(\lim_{k \rightarrow +\infty} x_{n_k})=f(x_0)$. 同理 $g(x_0)=A$. 故 $f$ 和 $g$ 在 $x_0$ 上相交, 矛盾. $\blacksquare$
