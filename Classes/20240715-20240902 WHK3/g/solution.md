# [整数分解为 2 的幂](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1048) 题解

给定正整数 $n$, 求可重集 $S$ 的数量, 满足 $n = \sum_{i \in S} i \land \forall i \in S, i = 2^k (k \ge 0)$. 高精度.

$1 \le n \le 10^{30}$.

---

浪费一个下午想到的做法:

设 $f_i$ 表示 $i$ 的可重集数量, 边界为 $f_0 = 1$, 考虑转移, 有

$$f_i = f_{i-1} + [2 \mid i] f_{\frac{i}{2}}$$

意义是, 考虑 $S$ 中最小的元素, 若为 $1$ 则转移到 $i-1$; 若大于 $1$ 则所有数都是偶数, 转移到 $\frac{i}{2}$.

发现转移是一个前缀和的形式, 考虑将其展开, 有

$$f_i = \sum_{j=0}^{\lfloor \frac{i}{2} \rfloor} f_j$$

由于只要求 $f_n$, 考虑利用上面的式子将 $f_n$ 展开, 有

$$f_n = \sum_{j=0}^{\lfloor \frac{n}{2} \rfloor} f_j \times 1$$

再次展开, 有

$$f_n = \sum_{j=0}^{\lfloor \frac{n}{4} \rfloor} f_j \times (\lfloor \frac{n}{2} \rfloor + 1 - 2j)$$

观察到每次求和的上指标会减少一半, 而 $f_j$ 系数的次数只会增加 $1$, 启发我们动态地维护后面这个多项式.

设二元组 $(x, G)$ 表示 $f_n = \sum_{i=0}^x f_i G(i)$, 初始时有二元组 $(\lfloor \frac{n}{2} \rfloor, 1)$, 考虑将 $(x, G)$ 转移到 $(y, H)$, 其中 $y = \lfloor \frac{x}{2} \rfloor$.

$$
\begin{aligned}
f_n &= \sum_{i=0}^x f_i G(i)
\\
&= \sum_{i=0}^x G(i) \sum_{j=0}^{\lfloor \frac{i}{2} \rfloor} f_j
\\
&= \sum_{j=0}^{\lfloor \frac{x}{2} \rfloor} f_j \sum_{i=2j}^x G(i)
\end{aligned}
$$

设 $G$ 有 $t$ 项, 则

$$
\begin{aligned}
H(i) &= \sum_{j=2i}^x G(j)
\\
&= \sum_{j=2i}^x \sum_{k=0}^{t-1} j^kg_k
\\
&= \sum_{k=0}^{t-1} g_k \sum_{j=2i}^x j^k
\end{aligned}
$$

设 $W_k(j) = \sum_{i=0}^{j-1} i^k$, 则

$$H(i) = \sum_{k=0}^{t-1} g_k (W_k(x+1) - W_k(2i))$$

由于 $W_k$ 为一个 $k+1$ 项的多项式, 则 $H$ 只有 $t+1$ 项. 使用拉格朗日插值预处理 $W_k$, 按上述式子递推 $(x, G)$, 设递推若干次后的结果为 $(0, P)$, 则答案为 $P(0)$.

由于只会递推 $O(\log n)$ 次, 则 $G$ 至多只有 $O(\log_n)$ 项, $W_k$ 只需预处理前 $O(\log n)$ 个, 拉插一次复杂度为 $O(\log^2 n)$, 故预处理复杂度 $O(\log^3 n)$; 递推一次需要点乘并累加 $O(\log n)$ 个多项式, 故递推复杂度 $O(\log^3 n)$.

总时间复杂度 $O(\log^3 n)$.

---

题解做法:

设 $a_i$ 为将 $n$ 拆分后的序列且长度至少为 $2$, 满足 $a_i \le a_{i+1}$, 则对于最大的整数 $k$ 满足 $2^k < n$, 必然存在一个 $a_i$ 的前缀 $t$, 使得 $\sum_{i=1}^{t} a_i = n-2^k$.

<details><summary>Proof</summary>

> 反证法. 显然有 $a_i \le 2^k$. 必然存在一个最小的前缀 $t$, 使得 $\sum_{i=1}^{t} a_i > n-2^k$. 设 $s = \sum_{i=1}^t a_i$, 有 $a_t > s-(n-2^k) > 0$.
> 
> 则 $t$ 之后的项之和为 $n-s$. 由于 $a_i \le a_{i+1}$, 则 $a_i \mid a_{i+1}$, 则 $a_t \mid n-s$. 由于有 $n-s = 2^k-(s-(n-2^k))$, 则 $n-s \equiv -(s-(n-2^k)) \pmod {a_t}$. 又由于 $a_t > s-(n-2^k) > 0$, 则 $n-s \not \equiv 0 \pmod {a_t}$, 即 $a_t \nmid n-s$, 矛盾.
</details>

故可以设 $f_{i, j}$ 表示拆分 $n \bmod 2^i$ 且所有数都不超过 $2^j$ 的方案数. 转移考虑若 $n$ 的第 $i$ 位为 $0$ 则直接转移到 $i+1$, 否则需要与拆分 $2^i$ 且对 $a_i$ 的取值范围有限制的方案数相乘再转移. 考虑拆分 $2^i$ 时最大的数为 $2^k$, 则 $f_{i, j}$ 转移到 $f_{i+1, k}$ 需要乘上一个拆分 $2^i$ 时所有数在 $[2^j, 2^k]$ 之间的方案数. 显然其等于拆分 $2^{i-j}$ 时所有数在 $[1, 2^{k-j}]$ 之间的方案数.

设 $g_{i, j}$ 表示拆分 $2^i$ 且所有数都不超过 $2^j$ 的方案数. 则有 $f_{i, j} g_{i-j, k-j} \rightarrow f_{i+1, k}$. 则 $g_{i, j}$ 转移到 $g_{i+1, k}$ 需要乘上一个拆分 $2^i$ 时所有数在 $[2^j, 2^k]$ 之间的方案数. 显然其等于 $g_{i-j, k-j}$. 故 $g_{i, j} g_{i-j, k-j} \rightarrow g_{i+1, k}$.

显然所有的下标范围都是 $O(\log n)$ 级别, 故 $O(\log^3 n)$.
