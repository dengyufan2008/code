# 20250410 总结

## T1(a) [最短路] [观察力] [优化建图]

应得:100 实得:60 难度:3 用时:**4h**

线段树优化建图没有卡过去.

对于一类需要优化建图的最短路题, 如果有形如不能连续经过两个相同颜色的点的限制, 考虑是否有别的路径边权与这条边的边权相等, 若有则无需考虑这一限制. 如在数轴上移动, 边权为两点距离, 则若两个相同颜色点中间夹了别的颜色的点则依旧可以连边, 故只需考虑颜色连续段内不能互达的限制.

## T2(b) [倒推] [刻画合法条件]

应得:17 实得:17 难度:3 用时:0.5h

对于将多个数合并成一个数的操作, 正向考虑会有组合数种可能的情况, 但反向考虑只有线性种情况, 故应当反向考虑.

对于一类对序列反复进行神秘操作, 并对可能的局面进行计数的题目, 考虑刻画最终局面合法的条件, 或设计一个简单的算法来判断是否合法, 然后对着这个东西 Dp. 但大概率会遗漏或误算, 需要此后手动修正. 如 [联合省选 2025 Day2 T3](https://www.luogu.com.cn/problem/P11835).

## T3(c) [观察力] [关键元]

应得:28 实得:28 难度:3.5 用时:0.5h

对于一类矩阵上连通性的问题, 能观察出的性质大概率是 一个点能到达的位置/能到达一个点的位置 是一个矩形.

随后可以称可能由这种方式生成的矩阵为关键矩阵, 并尝试刻画关键矩阵的条件, 由其中的某些条件说明关键矩阵是不多的, 就可以考虑如何找到这些矩阵. 或者可以将这个技巧理解为, 用格子找矩形那么矩形的情况有 $O(n^4)$ 种, 但找到矩形后用矩形配对格子情况就只有 $O(n^2)$ 种.

在矩阵中选取若干个子矩阵, 彼此只能相离或包含, 则最多选取 $2nm-1$ 个子矩阵. 区间可以自然规约. 证明考虑先把大小为 1 的选了, 然后每次选都会合并两个元素.

## 结算

在发现线段树优化建图被卡常后没有想优化算法, 而是考虑卡边数, 浪费了 1h.

实现 T1 的过程中, 错误地未将排序后的数组还原就直接输出, 发现 WA 了之后还以为是结论错了, 多写了很多数据结构和扫描线.
