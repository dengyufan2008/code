Lemma 1. 若 $f$, $g$ 都是 $I \subseteq \R$ 上的连续函数, 则 $\max(f, g)$ 和 $\min(f, g)$ 都是连续函数.

Proof. 设 $h(x) = f(x)-g(x)$ 为连续函数, 则 $\max(f(x), g(x)) = \max(h(x), 0)+g(x)$, $\min(f(x), g(x)) = f(x)+g(x)-\max(f(x), g(x))$. 故只需证明任意连续函数 $h$, 有 $\max(h, 0)$ 为连续函数即可.

考虑对于任意 $\max(h(x_0), 0) > 0$, 有 $\lim_{x \rightarrow x_0} h(x) > 0$, 故存在一个 $\delta > 0$ 使得 $x \in I \land 0 < |x-x_0| < \delta \rightarrow h(x)>0$. 故在 $x_0$ 邻域和 $x_0$ 上有 $f(x)>0$, 即 $\max(h(x), 0)=h(x)$, 故 $\max(h, 0)$ 在 $x_0$ 上连续.

考虑任意一个极长的区间 $L \subseteq I$ 满足 $x \in L \rightarrow \max(h(x), 0) = 0$. 则显然对于任意不是 $L$ 端点的 $x_0 \in L$, 有 $\max(h, 0)$ 在 $x_0$ 上连续. 考虑 $L$ 的左端点 $x_1$ (如果存在且不是 $I$ 的左端点), 由于 $L$ 是极长区间, 则存在一个 $\delta > 0$ 使得 $x_1-\delta < x < x_1 \rightarrow \max(h(x), 0) \ne 0 \leftrightarrow \max(h(x), 0) = h(x) > 0$. 由于 $h(x)$ 连续且 $x_1$ 的一个左邻域有 $h(x)>0$, 且 $h(x_1)\le 0$, 故 $h(x_1) = 0 = \max(h(x_1), 0)$. 故 $\max(h, 0)$ 在 $x_1$ 上左连续. 同理得 $L$ 的右端点 $x_2$ (如果存在且不是 $I$ 的右端点) 右连续. 故 $\max(h, 0)$ 在 $L$ 内连续.

综上所述, $\max(h, 0)$ 连续. $\blacksquare$

---

推论. 若 $f_1, \cdots, f_n$ 都是 $I \subseteq \R$ 上的连续函数, 则 $\max_{i=1}^n f_i$ 和 $\min_{i=1}^n f_i$ 是连续函数.

Proof. 设 $A=\set{n \in \N^* | f_1, \cdots, f_n \text{ 都是 } I \subseteq \R \text{ 上的连续函数} \rightarrow \max_{i=1}^n f_i \text{ 和 } \min_{i=1}^n f_i \text{ 是连续函数}}$. 显然有 $1 \in A$. 下试证明正整数 $n$, 有 $n \in A \rightarrow n+1 \in A$.

考虑任意 $f_1, \cdots, f_{n+1}$ 都是连续函数, 则由归纳假设得 $\max_{i=1}^n f_i$ 和 $\min_{i=1}^n f_i$ 是连续函数. 再由 Lemma 1 得 $\max(\max_{i=1}^n f_i, f_{n+1})$ 即 $\max_{i=1}^{n+1} f_i$ 是连续函数. 同理 $\min_{i=1}^{n+1} f_i$ 是连续函数. 故 $A=\N^*$. $\blacksquare$

---

引理. 若 $I$ 是有限集合, 有 $f:I \rightarrow \R$, 设 $\max[k]_{i \in I} f(i)$ 表示集合 $\set{f(i) | i \in I}$ 中的第 $k$ 大 ($k \in [1, |I|] \cap \N$), 设集合 $S_m = \set{T | T \subseteq I, |T| = m}$, 则有 $\max[k]_{i \in I} f(i) = \max_{T \in S_k} \min_{i \in T} f(i)$.

Proof. 可以将每个 $f(i)$ 变为二元组 $(f(i), i)$, 比较方式为先比较第一项, 如果相等再比较第二项. 故可以认为每个 $f(i)$ 互不相同.

先证明 $\max[k]_{i \in I} f(i) \le \max_{T \in S_k} \min_{i \in T} f(i)$. 考虑取一个集合 $T' = \set{i \in I | f(i) \ge \max[k]_{i \in I} f(i)}$, 有 $T' \in S_k$, 且 $\min_{i \in T'} f(i) = \max[k]_{i \in I} f(i)$. 故 $\max[k]_{i \in I} f(i) \le \max_{T \in S_k} \min_{i \in T} f(i)$.

再证明 $\max[k]_{i \in I} f(i) \ge \max_{T \in S_k} \min_{i \in T} f(i)$. 考虑反证法, 假设 $\max[k]_{i \in I} f(i) < \max_{T \in S_k} \min_{i \in T} f(i)$, 则存在一个 $T' \in S_k$ 使得 $\max[k]_{i \in I} f(i) < \min_{i \in T'} f(i)$. 而我们知道 $|\set{i \in I | f(i) > \max[k]_{i \in I} f(i)}| = k-1$, 故 $|T'| < k$, 矛盾.

综上所述, $\max[k]_{i \in I} f(i) = \max_{T \in S_k} \min_{i \in T} f(i)$. $\blacksquare$

---

Lemma 2. 若有 $f_1, \cdots, f_n$ 都是 $I \subseteq \R$ 上的连续函数, 则对于任意 $1 \le k \le n \land k \in \N$, 有 $\max[k]_{i=1}^n f_i$ 是连续函数.

Proof. 设集合 $S_m = \set{T | T \subseteq [1, n] \cap \N, |T| = m}$, 根据引理有 $\max_{T \in S_k} \min_{i \in T} f_i = \max[k]_{i=1}^n f_i$.

运用推论得到, $\forall T \in S_k$, $\min_{i \in T} f_i$ 是连续函数. 进一步运用推论得到, $\max_{T \in S_k} \min_{i \in T} f_i$ 是连续函数. $\blacksquare$
