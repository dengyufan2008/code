Lemma 1. 若 $f:I \rightarrow \R$ 在区间 $I$ 上处处可导, 且对于任意 $x \in I$, $f'(x)>0$, 则 $f$ 在 $I$ 上严格递增.

Proof. 任取一个 $a \in I$, 我们有 $\lim_{h \rightarrow 0} \frac{f(a+h)-f(a)}{h}>0$. 从而 $\exist \delta>0, \forall 0<|h|<\delta, \frac{f(a+h)-f(a)}{h}>0$. 稍加变形, 得到 $\exist \delta>0, \forall 0<h<\delta, f(a-h)<f(a)<f(a+h)$.

考虑使用反证法. 假设存在 $x, y \in I$ 且 $x < y$, $f(x) \ge f(y)$. 我们尝试证明 $\exist a, \forall \delta>0, \exist 0<h_1, h_2<\delta, f(a-h_1) \ge f(a+h_2)$, 即可推出矛盾.

设 $a_1=x, b_1=y$, 我们用以下策略构造 $a_2$ 和 $b_2$. 取 $z=\frac{a_1+b_1}{2}$, 对 $f(z)$ 进行分类讨论. 若 $f(a_1) \ge f(z)$, 则取 $a_2=a_1$, $b_2=z$; 否则 $f(z)>f(a_1) \ge f(b_1)$, 则取 $a_2=z$, $b_2=b_1$. 总之, 我们有 $f(a_2) \ge f(b_2)$. 反复施用上述过程, 我们得到有界闭区间套 $[a_k, b_k]$, 使得 $f(a_k) \ge f(b_k)$, $b_k-a_k=\frac{y-x}{2^{k-1}}$, $\lim_{k \rightarrow +\infty} b_k-a_k=0$. 故存在 $A$ 使得 $\{A\}=\bigcap_k[a_k, b_k]$.

任取一个 $\delta>0$, 则存在一个 $k_0$ 使得 $\frac{y-x}{2^{k_0-1}} < \delta$. 由于我们有 $a_{k_0} \le A \le b_{k_0}$, 且 $b_{k_0}-a_{k_0}<\delta$, 则取 $h_1=A-a_{k_0}<\delta$, $h_2=b_{k_0}-A<\delta$, 有 $f(A-h_1) \ge f(A+h_2)$. $\blacksquare$
