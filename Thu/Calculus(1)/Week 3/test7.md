设 $f:\R\rightarrow\R$ 满足 $f(\frac{x+y}{2}) \le \frac{f(x)+f(y)}{2}$.

---

Lemma 1. 对于任意有理数 $t \in [0, 1]$, $f((1-t)x+ty) \le (1-t)f(x)+tf(y)$.

Proof. 改写条件为 $f(\frac{x+y}{2})-f(x) \le f(y)-f(\frac{x+y}{2})$, 进一步改写为对于任意长度为 3 公差为 $d>0$ 的等差数列 $z_1, z_2, z_3$ 有 $f(z_2)-f(z_1) \le f(z_3)-f(z_2)$. 下试证明对于任意长度为 $n \ge 3$ 公差为 $d>0$ 的等差数列 $\set{z_i}$ 有 $f(z_2)-f(z_1) \le f(z_3)-f(z_2) \le \cdots \le f(z_n)-f(z_{n-1})$.

设 $A=\set{n \in \N \ge 3 | \forall \text{ 长度为 } n \text{ 公差为 } d>0 \text{ 的等差数列 } \set{z_i} \text{ 有 } f(z_2)-f(z_1) \le f(z_3)-f(z_2) \le \cdots \le f(z_n)-f(z_{n-1})}$. 显然 $3 \in A$, 下证 $n \in A \rightarrow n+1 \in A$.

考虑任意一个长度为 $n$ 的等差数列 $\set{z_i}$, 构造长度为 $n+1$ 的等差数列 $\set{z'_i}$ 满足 $z'_i=z_i \space (1 \le i \le n)$, $z'_{n+1}=z_n+d$. 显然对于 $z'_{n-1}, z'_n, z'_{n+1}$ 有 $f(z'_n)-f(z'_{n-1}) \le f(z'_{n+1})-f(z'_n)$, 又有 $f(z'_2)-f(z'_1) \le f(z'_3)-f(z'_2) \le \cdots \le f(z'_n)-f(z'_{n-1})$, 故 $f(z'_2)-f(z'_1) \le f(z'_3)-f(z'_2) \le \cdots \le f(z'_{n+1})-f(z'_n)$, $n+1 \in A$. 故 $A=\N$.

考虑当 $t=0$ 或 $t=1$ 时不等式显然取等, 故下文假定 $t \notin \set{0, 1}$. 将有理数 $t$ 写成 $\frac{m}{n}$ 的形式, 有 $0 < m < n$. 考虑长度为 $n+1$ 的等差数列 $\set{z_i = \frac{n-i}{n}x+\frac{i}{n}y} \space (0 \le i \le n)$, 我们有

$$
\begin{aligned}
\frac{1}{m}(f(z_m)-f(z_0)) &= \frac{1}{m}(f(z_m)-f(z_{m-1})+f(z_{m-1})-f(z_{m-2})+\cdots+f(z_1)-f(z_0))
\\
& \le f(z_m)-f(z_{m-1})
\\
& \le f(z_{m+1})-f(z_m)
\\
& \le \frac{1}{n-m}(f(z_{m+1})-f(z_m)+f(z_{m+2})-f(z_{m+1})+\cdots+f(z_n)-f(z_{n-1}))
\\
&= \frac{1}{n-m}(f(z_n)-f(z_m)).
\end{aligned}
$$

进一步改写为 $(n-m)(f(z_m)-f(z_0)) \le m(f(z_n)-f(z_m))$ 即 $f(z_m) \le \frac{n-m}{n}f(z_0)+\frac{m}{n}f(z_n)$. 由于我们有 $z_0=x$, $z_n=y$, $z_m=\frac{n-m}{n}x+\frac{m}{n}y$, 则有 $f(\frac{n-m}{n}x+\frac{m}{n}y) \le \frac{n-m}{n}f(x)+\frac{m}{n}f(y)$, 即 $f((1-t)x+ty) \le (1-t)f(x)+tf(y)$. $\blacksquare$

---

Lemma 2. 若 $f$ 连续, 则对任意实数 $t \in [0, 1]$, $f((1-t)x+ty) \le (1-t)f(x)+tf(y)$.

Proof. 对于任意 $t \in \mathbb{Q} \cap [0, 1]$, 有 $g(t)=(1-t)f(x)+tf(y)-f((1-t)x+ty) \ge 0$, 且 $g$ 连续.

考虑数列 $\set{a_n}$ 满足 $a_i$ 为 $(\max(t-\frac{1}{i}, 0), t)$ 间的一个有理数, 则有 $\lim_{n \rightarrow +\infty} a_n = t$. 故 $g(t)=\lim_{n \rightarrow +\infty} g(a_n) \ge 0$. $\blacksquare$

---

Lemma 3. 若 $f$ 连续, 则对满足 $t_1+t_2+\cdots+t_n=1$ 的任意非负实数 $t_1,t_2,\cdots,t_n$ 有 $f(t_1x_1+\cdots+t_nx_n) \le t_1f(x_1)+\cdots+t_nf(x_n)$.

Proof. 设集合 $A=\set{n \in \N^* | t_1+t_2+\cdots+t_n=1 \rightarrow f(t_1x_1+\cdots+t_nx_n) \le t_1f(x_1)+\cdots+t_nf(x_n)}$. 显然 $1, 2 \in A$, 下证若 $n \in A$, 则 $n+1 \in A$.

我们有 $f(t_1x_1+\cdots+c_{n+1}x_{n+1}) \le (1-c_{n+1})f(\frac{t_1x_1+\cdots+c_nx_n}{1-c_{n+1}})+c_{n+1}f(x_{n+1}) \le (1-c_{n+1})(\frac{t_1}{1-c_{n+1}}f(x_1)+\cdots+\frac{t_n}{1-c{n+1}}f(x_n))+c_{n+1}f(x_{n+1}=t_1f(x_1)+\cdots+t_{n+1}f(x_{n+1})$. 故 $A=\N^*$. $\blacksquare$

---

Lemma 4. 若 $f$ 单调, 则 $f$ 连续.

Proof. 若 $f$ 单调不增, 则考虑 $g(x)=f(-x)$, 有 $g$ 满足中点凸条件, 且 $g$ 单调不减. 故不妨设 $f$ 单调不减.

对于任意 $x \in \R$, 由于 $f$ 单调不减, 则存在 $A=\lim_{y \rightarrow x^-} f(y)$ 和 $B=\lim_{y \rightarrow x^+} f(y)$, 且 $A \le f(x) \le B$.

考虑有 $f(x-\frac{h}{2})=f(\frac{(x-h)+x}{2}) \le \frac{f(x-h)+f(x)}{2}$, 则有 $\lim_{h \rightarrow 0^+} f(x-\frac{h}{2}) \le \lim_{h \rightarrow 0^+} \frac{f(x-h)+f(x)}{2}$, 即 $A \le \frac{A+f(x)}{2}$, $A \le f(x)$. 故 $f(x)=A$. 同理有 $f(x)=B$. 故 $\lim_{y \rightarrow x} f(y)=f(x)$, $f$ 连续.

---

Lemma 5. 若 $f$ 局部有界, 则 $f$ 连续.

Proof (使用 deepseek). 考虑任意 $x \in \R$. 存在 $\delta > 0$, $M > 0$ 使得 $|h|<\delta \rightarrow |f(x+h)| < M$.

考虑任意 $0 < |h| < \frac{1}{2}\delta$, 设 $n$ 为最大的正整数满足 $2^n|h| < \delta$, 则 $2^{n+1}|h| \ge \delta$, $\frac{1}{2^n} \le \frac{2}{\delta}|h|$.

我们有 $f(x+h)=f(\frac{x+(x+2h)}{2}) \le \frac{f(x)+f(x+2h)}{2}$, 即 $f(x+h)-f(x) \le \frac{f(x+2h)-f(x)}{2}$. 进一步, 有 $f(x+h)-f(x) \le \frac{f(x+2h)-f(x)}{2} \le \frac{f(x+4h)-f(x)}{4} \le \cdots \le \frac{f(x+2^nh)-f(x)}{2^n}$. 故 $f(x+h)-f(x) \le \frac{2}{\delta}|h| (f(x+2^nh)-f(x)) < \frac{4M}{\delta}|h|$.

简单推论得到 $f(x-h)-f(x)<\frac{4M}{\delta}|h|$. 又有 $f(x)-f(x-h) \le f(x+h)-f(x)$, 故 $f(x+h)-f(x)>-\frac{4M}{\delta}|h|$. 综上所述, $|f(x+h)-f(x)|<\frac{4M}{\delta}|h|$. 故 $f$ 连续.

---

Lemma 6. 若 $f$ 至多只有第一类间断点, 则 $f$ 连续.

Proof. 至多只有第一类间断点等价于处处有单侧极限. 考虑任意 $x \in \R$, 设 $\lim_{y \rightarrow x^-} f(y)=A$, $\lim_{y \rightarrow x^+} f(y)=B$.

考虑有 $\lim_{y \rightarrow x^-} f(\frac{x+y}{2}) \le \lim_{y \rightarrow x^-} \frac{f(x)+f(y)}{2}$, 即 $A \le \frac{f(x)+A}{2}$, $A \le f(x)$. 同理有 $B \le f(x)$. 故 $A+B \le 2f(x)$.

考虑有 $f(x) \le \lim_{y \rightarrow x^-} \frac{f(y)+f(2x-y)}{2}$, 即 $f(x) \le \frac{A+B}{2}$, $2f(x) \le A+B$.

综上所述, 有 $A+B=2f(x)$. 又因为 $A \le f(x)$, $B \le f(x)$, 则 $A=B=f(x)$. $f$ 连续.

---

Lemma 7. 存在 $f$ 满足 $f(\frac{x+y}{2}) \le \frac{f(x)+f(y)}{2}$ 但不满足对任意实数 $t \in [0, 1]$, $f((1-t)x+ty) \le (1-t)f(x)+tf(y)$.

Proof. 根据 deepseek, 构造这样的函数需要使用选择公理等一系列复杂过程. 而我并没有学会, 故略.
