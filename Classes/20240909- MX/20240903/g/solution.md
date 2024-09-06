# QOJ8820 [Exchanging Kubic 2](https://qoj.ac/problem/8820) 题解

对于一个序列 $a_i$, 定义操作一个位置 $x$ 为令
$$
\begin{cases}
a_i \leftarrow a_i+1 &(a_i < a_x)
\\
a_i \leftarrow a_i &(a_i = a_x)
\\
a_i \leftarrow a_i-1 &(a_i > a_x)
\end{cases}$$
, 定义 $a_i$ 的权值为对序列中每个位置均操作恰好一次后序列的最小极差. 给定 $n$ 个集合 $S_i$, 对于每个满足 $\forall 1 \le i \le n, a_i \in S_i$ 且 $\forall 2 \le i \le n, a_{i-1} \le a_i$ 的序列, 将权值求和.

$1 \le n \le 400$, $\forall j \in S_i, 0 \le j \le 800$.

---

考虑放宽限制, 一次操作可以钦定两个数 $u$ 和 $v$ 满足 $u \le a_x, v \ge a_x$, 让 $a_i < u$ 的数 $+1$, $a_i > v$ 的数 $-1$. 显然按这样操作最终的极差不会小于原操作.

考虑长为 $n$ 的序列 $b_i$ 满足 $b_1 = 0, b_i = a_i-a_{i-1} (2 \le i \le n)$. 则操作位置 $x$ 会使得 $[1, x]$ 内任意一个 $>0$ 的位置 $-1$, $[x+1, n]$ 内任意一个 $>0$ 的位置 $-1$ (没有则无事发生), 最终的答案为操作后 $\sum_{i=1}^n b_i$ 的最小值, 也即操作前 $\sum_{i=1}^n b_i$ 减去非无事发生的次数, 又即无法分配到任意一个 $x$ 上的值的数量.

考虑操作的最终形态, 对每个位置 $x$ 记 $l_x$ 和 $r_x$ 表示 $-1$ 的位置 (没有则为 $-\infty$ / $\infty$). 考虑贪心地为每个 $x$ 分配 $l_x$ 与 $r_x$. 从左到右考虑 $b_i$, 依次为 $i \le x \le n$ 分配 $l_x$ 为 $i$, 再为 $i-1 \ge x \ge 1$ 分配 $r_x$. 显然这样能够分配到的是最多的.

考虑类似自动机地计算答案, 以更为方便地进行计数 Dp. 考虑维护目前所有 $b_i$ 的和 $s$, 则每次加入一个 $b_i$ 会使 $s \leftarrow s + b_i$. 由于当 $s < i$ 时, $[1, i]$ 的 $l_i$ 必然会有 $i - s$ 个无法分配, 则不妨认为这 $i - s$ 次无事发生事实上是有事发生, 并将 $s \leftarrow i$. 若 $s > n + i - 1$, 此时由于至多只有 $[1, n]$ 的 $l_i$ 与 $[1, i-1]$ 的 $r_i$ 能够分配, 则必然有 $s - (n + i - 1)$ 个值无法分配到 $l_i$ 或 $r_i$ 上, 因此 $ans \leftarrow ans + [s - (n + i - 1)]$, $s \leftarrow n + i - 1$.

总结一下, 自动机的流程为 $s \leftarrow \max(s + a_i, i)$, $ans \leftarrow ans + s - (n + i - 1)$, $s \leftarrow \min(s, n + i - 1)$.

设 $f_{i, j, s}$ 表示考虑到了 $S_i$, 值选了 $j$, 变量 $s$ 的值的方案数. 由于贡献完答案后还需将后面的序列补全, 需设 $g_{i, j, s}$ 为答案, 转移完全一致并额外有 $f \rightarrow g$ 的一个转移. 前缀和优化转移即可.

$O(n^3)$.
