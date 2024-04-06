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
