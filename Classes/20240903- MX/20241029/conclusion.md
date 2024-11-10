# 20241029 [梦熊题单](https://www.luogu.com.cn/paste/09up24mt)

- 一张可以被拆分为若干完全图的无向图的最小生成树, 所用到的边只会在每个完全图的最小生成树的边集之并中. [例](https://www.luogu.com.cn/problem/CF1981E)

- 对于一类求和大整数 bitwise 运算恰好等于某个大整数的题目, 应当从高位往低位考虑, 在除以当前位的位权下, 实际与目标的差值不会大于等于求和的项数. [例](https://www.luogu.com.cn/problem/CF1994G)

- 在树上选取若干条链使得覆盖的点数最大, 则考虑长链剖分. [例](https://www.luogu.com.cn/problem/CF1976F)

- 将一个数集 $S$ 中的每个元素看作一条边的长度, 能够组成一个多边形当且仅当 $2\max(S) < \sum(S)$.
  
  笛卡尔树也可以合并, 复杂度为 $O(较大深度)$. 代码实现上同 FHQ Treap. [例](https://www.luogu.com.cn/problem/CF1990F)

- 对于一类 Dp 题, 若题面给了你一个合法状态的构造方式, 则考虑直接按照这个构造方式来 Dp. [例](https://www.luogu.com.cn/problem/CF2001E2)

- 对于一类最优化问题, 若合法条件仅为满足一维偏序, 当答案可能的取值数量较少时, 考虑对每个答案计算最紧的合法条件, 查询时直接二分. [例 (本题单最好的一道)](https://www.luogu.com.cn/problem/CF1973F)

- 对于一类分块题, 若需要支持 checkmax 操作, 而没有区间修改, 则考虑类似吉司机线段树的做法, 维护 min 和 min2. 若仅更新 min 时可以快速修改, 则至少更新到 min2 的可以暴力重构. 容易发现对于一个块至多重构 $O(B)$ 次.
  
  若 $x \ge 1$, 对排列 $p$ 定义 $pre$ 为前面第一个大于的数的下标, $suf$ 为后面第一个大于的, 有
  $$\sum \min(nxt_i - pre_i, x) = \sum min(nxt_i - i, x) + \sum min(i - pre_i, x) - n - x + 1$$
  . 证明考虑在序列末尾加入 $x-1$ 个空位, 值域上从大往小枚举每个位置, 将其后的总共 $x$ 个格子标记, 则总共的被标记的格子数为 $n+x-1$, 但还有另一种计算方法, 细节如图
  ![](https://cdn.luogu.com.cn/upload/image_hosting/akr57twz.png)
  [例](https://www.luogu.com.cn/problem/CF1967F)

- $\text{mex}$ 为集合内未出现的数的最小值, 则对于一类最小化问题, 可以用 自行决策取哪个数的技巧 来 Dp. [例](https://www.luogu.com.cn/problem/CF1981F)

- 对于一类和排列的前缀最大值个数有关的题目, 考虑每次把最小的数插在哪里.
  
  对于一类和排列的前缀最大值个数与后缀最大值个数都有关的题目, 考虑全局最大值在哪里以将序列分开. [例](https://www.luogu.com.cn/problem/CF1988F)

- 若每次操作至多只会新增一个 0, 且每次操作后 0 都会扩散至少 1 格, 则 0 的连续段数为 $O(\sqrt n)$. [例](https://qoj.ac/problem/9311)

- 还有一道困难概率 Dp [题](https://www.luogu.com.cn/problem/CF1975I)
