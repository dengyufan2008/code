设 $f:\R\rightarrow\R$ 满足 $f(x+y)=f(x)+f(y)$.

---

引理. 对于任意 $n \in \N$, $x \in \R$, 有 $f(nx)=f(x)n$.

Proof. 设 $A(x)=\set{n \in \N | f(nx)=f(x)n}$.

考虑 $f(0+0)=f(0)+f(0)$ 即 $f(0)=2f(0)$, 故 $f(0)=0$. 故 $0, 1 \in A(x)$. 试证明 $n \in \N^* \in A(x) \rightarrow n+1 \in A(x)$.

我们有 $f((n+1)x)=f(nx+x)=f(nx)+f(x)=f(x)n+f(x)=f(x)(n+1)$. 故 $A(x)=\N$. $\blacksquare$

---

Lemma 1. 对于任意 $n \in \N$ 有 $f(n) = f(1)n$.

Proof. 根据引理可得. $\blacksquare$

---

Lemma 2. 对于任意 $n \in \Z$ 有 $f(n) = f(1)n$.

Proof. 对于 $n \in \N$, 我们有 $f((n-0)+(0-n))=f(0-0)=f(n-0)+f(0-n)=0$. 我们又有 $f(n-0)=f(1)(n-0)$, 故 $f(0-n)=f(1)(0-n)$. $\blacksquare$

---

Lemma 3. 对于任意 $x \in \mathbb{Q}$ 都有 $f(x) = f(1)x$.

Proof. 设 $x=\frac{m}{n}$, 其中 $n \in \N^*$. 根据引理可得 $f(m)=f(\frac{m}{n})n$, 以及 $f(m)=f(1)m$. 故 $f(\frac{m}{n})=f(1)\frac{m}{n}$. $\blacksquare$

---

Lemma 4. 若 $f$ 连续, 则对于任意 $x \in \R$ 都有 $f(x) = f(1)x$.

Proof. 考虑任意一个 $x \in \R$. 设有数列 $\set{a_n}$ 满足 $a_n \in \mathbb{Q}$ 且 $x - \frac{1}{n} < a_n < x$. 则根据夹逼定理有 $\lim_{n \rightarrow +\infty} a_n = x$.

由于 $a_n \ne x$, 有 $\lim_{y \rightarrow x} f(y) = \lim_{n \rightarrow +\infty} f(a_n) = f(1) \lim_{n \rightarrow +\infty} a_n = f(1)x$. 由于 $f$ 连续, 有 $f(x) = \lim_{y \rightarrow x} f(y) = f(1)x$. $\blacksquare$

---

Lemma 5. 若 $f$ 单调, 则 $f$ 连续.

Proof. 若 $f(1)=0$, 则对于任何 $x \in \mathbb{Q}$ 有 $f(x)=0$. 对于任意 $x \in \R$, 可以找到有理数 $x_1 < x < x_2$, 故 $f(x)=0$. 故 $f$ 连续. 若 $f(1)<0$, 取 $f'(x)=-f(x)$ 即可. 故下文假定 $f(1)>0$. 由于 $f(0)=0$, $f(1)>0$, 则 $f$ 单调不减.

任取 $x \in \R$. 设集合 $S=\set{f(r) | r \in \mathbb{Q}, r \le x}$, $T=\set{f(r) | r \in \mathbb{Q}, r \ge x}$. 由于 $f(1)x$ 是 $S$ 的上界, $T$ 的下界, 故分别存在上确界和下确界. 显然有 $S=\set{f(1)r | r \in \mathbb{Q}, r \le x}$, 根据第二题的引理 1, 有 $\sup S=f(1)\sup \set{r | r \in \mathbb{Q}, r \le x}=f(1)x$. 类似地, 我们也有 $\inf T=f(1)x$. 故 $\sup S=\inf T$.

由于 $f$ 单调不减, 则 $f(x)$ 是 $S$ 的一个上界, 故 $f(x) \ge \sup S$. 同理 $f(x) \le \inf T$. 故 $f(x)=f(1)x$, 也即 $f$ 是一个一次函数或常数函数, 自然连续. $\blacksquare$

---

Lemma 6. 若 $f$ 至多只有第一类间断点, 则 $f$ 连续.

Proof (使用 deepseek). 根据定义, 至多只有第一类间断点等价于处处存在单侧极限. 故 $\lim_{x \rightarrow 0^+} f(x)$ 和 $\lim_{x \rightarrow 0^-} f(x)$ 存在且有限.

任取 $x \ne 0$, 容易得到 $\lim_{n \rightarrow +\infty} \frac{x}{n}=0$. 由于 $\frac{x}{n} \ne 0$, 则 $\lim_{n \rightarrow +\infty} f(\frac{x}{n}) = \lim_{x \rightarrow 0^+} f(x)$. 根据引理, 我们有 $f(x)=\lim_{n \rightarrow +\infty} f(x)=\lim_{n \rightarrow +\infty} f(\frac{x}{n})n=\lim_{x \rightarrow 0^+} f(x) \lim_{n \rightarrow +\infty} n$. 显然后一项极限为正无穷大, 但 $f(x)$ 有限, 故 $\lim_{x \rightarrow 0^+} f(x)=0$. 由于 $f$ 是奇函数, 有 $\lim_{x \rightarrow 0^-} f(x)=0$. 故 $\lim_{x \rightarrow 0} f(x)=0=f(0)$, 即 $f$ 在 0 上连续.

任取 $x \in \R$, 考虑 $\lim_{y \rightarrow x^+} f(y)$ 存在且有限. 我们有 $\lim_{y \rightarrow x^+} f(y) = \lim_{y \rightarrow x^+} f(x)+f(y-x)=f(x)+\lim_{z \rightarrow 0^+} f(z)=f(x)$. 同理有 $\lim_{y \rightarrow x^-} f(y)=f(x)$. 故 $f$ 在 $x$ 上连续. $\blacksquare$

---

Lemma 7. 若 $f$ 局部有界, 则 $f$ 连续.

Proof (使用 deepseek). 设 $g(x)=f(x)-f(1)x$. 不难验证 $g(x)$ 满足 $g(x+y)=g(x)+g(y)$, 且 $\forall x \in \mathbb{Q}, g(x)=0$.

由于 $f$ 局部有界, 则存在 $\delta > 0$ 和 $M > 0$, 使得 $|x| < \delta \rightarrow |f(x)| < M$. 故有对于任意 $x \in \R$, $|g(x)| = |f(x)-f(1)x| \le |f(x)|+|f(1)||x| < M+|f(1)|\delta$. 令 $K=M+|f(1)|\delta$, 则 $|g(x)| < K$.

根据引理, 我们有 $\forall n \in \N$, $g(x)n=g(nx) \in (-K, K)$, 即 $-\frac{K}{n}<g(x)<\frac{K}{n}$. 故 $g(x)=0$. 故 $f(x)=f(1)x$, $f$ 是一个一次函数或常数函数, 自然连续. $\blacksquare$

---

Lemma 8. $f$ 有非平凡解.

Proof. 根据 deepseek, 构造非平凡解需要使用选择公理等一系列复杂过程. 而我并没有学会, 故略.
