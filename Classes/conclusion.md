# 20240404 讲[题](https://www.luogu.com.cn/paste/jxb7b3lp)总结

## Trick

- 计算 $\prod (1 - a_ix)$ 或 $\sum \frac{b_i}{1 - a_ix}$ 可以用分治 NTT. $O(n\log^2n)$.

- 对于一个生成函数的单项求值可以考虑按奇偶分类并使规模减半.
  
  如给定 $a_{[1,k]}$ 与 $b_{[1,k]}$, 求 $b_n = \sum_{i = 1}^k a_i b_{n - i} \space (n > k)$, 则有 $\sum_{i = 0}^k a_i b_{n - i} = 0 \space (a_0 = -1)$.
  
  故 $A(z) * Ans(z) = B(z)$, 其中 $A(z) = \sum_{i = 0}^k a_i z^i$, $B(z) = \sum_{i = 1}^k b_iz^i$, $Ans(z) = \sum_{i = 1}^\infty b_iz^i$.

  那么 $Ans(z) = \frac{B(z)}{A(z)} = \frac{B(z) * A(-z)}{A(z) * A(-z)}$. 设 $C(z^2) = A(z) * A(-z)$, $D(z^2) + z * E(z^2) = B(z) * A(-z)$, 则 $Ans(z) = \frac{D(z^2)}{C(z^2)} + z * \frac{E(z^2)}{C(z^2)}$, 从而可以分类讨论 $n$ 的奇偶性来只考虑右侧式子的前项或后项. $O(k\log k\log n)$.

## Cheese Point

- 转置原理: 对于一个算法, 若其可以处理输入一个矩阵 $[X]$, 输出矩阵 $[Y] = [A] * [X] \space ([A]$为常量$)$, 则必然可以处理输入一个矩阵 $[Y']$, 输出矩阵 $[X'] = [A^T] * [X]$.
  
  体现在具体实现上为将所有的操作转置并将顺序反向.

- LGB Lemma: 对于两条路径 $i \rightarrow l$ 与 $j \rightarrow k$, 满足 $i$ 在 $j$ 的左侧, $k$ 在 $l$ 的左侧, 若必然有这两条路径交叉, 那么对于 $|L| = |R| = n$ 的两个点集之间对应有路径且不交的方案数为 矩阵 $A_{i, j} = (L$ 中 $i$ 号元素到 $R$ 中 $j$ 号元素的路径条数$)$ 的行列式.

- 子集卷积: 若要计算
  $$C_{S} = \sum_{I \cup J = S, I \cap J = \varnothing} A_I B_J$$

  考虑条件等价于 $I | J = S, |I| + |J| = |S|$, 故按 PopCount 将下标分为 $n$ 组, 每组之间两两进行 Or 卷积. $O(2^n n^2)$.

- 子集 Exp: 从 $1$ 到 $n$ 递推, 每次枚举一个最大值为 $i$ 的集合并与之前得到的结果做子集卷积. $O(\sum_{i = 1}^n 2^i i^2) = O(2^n n^2)$.

# 20240405 讲[题](https://www.luogu.com.cn/paste/dys1maqq)总结

- 对于一个没有什么性质的序列, 考虑其是否可以拆成两 (多?) 个有特殊性质的序列的和 (差). [例](https://www.luogu.com.cn/paste/pakicoyg)

- 对于一类矩形求和的问题, 若其还带有一维时间轴, 考虑通过割补法将与时间强相关的块变成只与 x y 其中一维相关. 则可以把三维偏序优化成二维. [例](https://www.luogu.com.cn/problem/P9061)

- 对于一类树上要查 一个点到根的路径上的 所有子树中的点 的信息的问题, 考虑将要查的点不断跳重链挂在线段树对应位置上, 则可以方便地查询. [例](https://loj.ac/p/3661)

- 对于线段树上一类与前缀最大值有关的问题, 考虑分类讨论传入的最大值与左区间最大值的关系. [例](https://www.luogu.com.cn/problem/P4198)

- 对于一类序列长度为 1 时好做的数据结构题, 考虑对序列进行线段树分治. [例](https://contest.xinyoudui.com/contest/93/problem/372)

- 静态的区间询问可以通过扫描线变成动态的后缀 (前缀) 询问. [例](https://www.luogu.com.cn/paste/7d2ib1x8)

  后缀询问 + 单点修改 可以通过扫描线变成 单点询问 + 区间修改. [例](https://uoj.ac/problem/515)

- 模拟费用流的一种方法是, 考虑建图中的若干关键点, 两两维护路径的最大 (小) 值, 然后对这些关键点暴力跑 SPFA. [例](https://www.luogu.com.cn/paste/fgt41p1o)

# 20240406 讲题(uoj [709, 720])总结 & [题解](https://www.cnblogs.com/dmoransky/p/16052837.html)

- 对于一类极多维的偏序问题, 可以将序列分为 $O(\log n)$ 块, 每块内维护某一维 $\le x$ 的下标集合. $O(\frac{n^2}{\log n})$. [例](https://uoj.ac/problem/710)

- 对于一类会了前一半不会后一半的问题, 考虑后一半能否规约到前一半. [例](https://uoj.ac/problem/710)

- 做凸包时一个点弹掉的点集就是删了这个点之后需要加回来的点集. 很显然但是没有想到.

- 对于树上一些与根有关的限制与贡献, 若根会发生变化, 考虑将其转化为仅跟点与边有关的表述. [例](https://uoj.ac/problem/715)

- 从 0 开始每次随一个 $[-v, v]$ 的数并加上, 走到的数的范围期望是 $O(\sqrt v)$ 的. 但随着步数的增加, 实际的数字会越发趋于稳定, 故越不可能成为最大 (小) 值. [例](https://uoj.ac/problem/716)

- 对于字符串 $S, T$ 有 $S^\infty < T^\infty \Leftrightarrow ST < TS$. [例 (不会)](https://uoj.ac/problem/717)

- 复习 SG 函数: 若先后手能进行的操作相同, 且每次只能操作一个最小的操作单位 (如 Nim 游戏中的每堆石子, 例题中的每颗棋子), 且会转移到拓扑序靠后的一些单位状态 (集), 则每个单位状态的 sg 值为后继的 mex, 多个单位状态的并的 sg 值为 Xor 和. 0 必败, 非 0 必胜. [例](https://uoj.ac/problem/719)

- 序列上两个人博弈, 一个人取完一个数后另一个人取相邻的其中一个数, 要让自己的和最大. 可以转化成带权最大匹配, 边权为两边的 min. [例 (不会)](https://uoj.ac/problem/720)
