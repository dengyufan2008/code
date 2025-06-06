# 20250102 总结

## T1(a) [观察力] [线段树]

期望:100 实际:100 难度:1.5 用时:**1.5h**

很显然的性质: 杀一只怪需要至少 $a_i$ 的等级, 杀完获得 $b_i$ 的等级, 最小化杀 $k$ 只怪的初始等级, 则杀的怪是 $a_i$ 最小的 $k$ 个.

对于一类与前缀按顺序合并有关的贡献, 显然可以用线段树维护.

## T2(b) [问题刻画] [推式子] [扫描线]

期望:43 实际:43 难度:3 用时:**2h**

对于一类最长下降子序列长度不超过 2 的限制, 若需要刻画问题以寻找性质则将元素分为是前缀最大值和不是前缀最大值两类, 若需要判断合法条件则考虑每个元素的 $pre$ 和 $nxt$.

对于一类明显需要得出一个能够 $O(1)$ 计算的式子的计数问题, 可以先考虑一个较为暴力的多项式 Dp, 再转化考虑它的组合意义. 事实上与 HNOI Day 1 T3 的部分思想一致.

范德蒙德卷积有两种形式, 常见的为 $\sum_i {n \choose i} {m \choose k-i} = {n+m \choose k}$, 另一种为 $\sum_i {i \choose n} {k-i \choose m} = {k+1 \choose n+m+1}$.

## T3(c) [组合意义] [生成函数]

期望:35 实际:35 难度:3.5 用时:1h

对于一类序列计数问题, 若一个下标 $i$ 满足某些条件时权值会乘上 $a_i$, 则有两种方式可以刻画这个问题. 一是使用组合意义变为在 $a_i$ 个互不相同的球中删去一个, 二是使用生成函数变为求导.

对于一类进行 $n$ 次操作, 每次加入或删去恰一个元素 (所有曾出现过的元素都互不相同), 计数从 $s$ 个元素变为 $t$ 个元素的方案数的问题, 考虑枚举 $s$ 个元素与 $t$ 个元素的交集大小, 则可以线性计算.

对于一类形如 $F_i = F_{i-1}P + F'_{i-1}$ 的生成函数的递推式, 其中 $P$ 为常多项式, 考虑设 $G_i = F_i e^Q$, 使得 $Q' = P$, 则有

$$
\begin{aligned}
G'_i&=(F_ie^Q)'
\\
&=F_iQ'e^Q + F'_ie^Q
\\
&=G_{i+1}
\end{aligned}
$$

则可以方便地计算 $F_n$, 将 $e^Q$ 泰勒展开即可.

## 结算

在 T1 上花费了过多时间来思考 Dp 以选取 $k$ 个最优的敌人, 以至于最终的结论都是通过 Dp 得出的, 导致没有时间思考 T2. 事实上若有额外的一个小时则 T2 应当是能够想到的.

T2 在找规律上同样浪费了大量时间. 事实上对于我来说与组合数相关的规律较难找到 (即使只是一个卡特兰数), 应当直接思考上文提到的 Dp 转组合意义以得到式子.

好在 T3 简单的双阶乘找规律不难看出.
