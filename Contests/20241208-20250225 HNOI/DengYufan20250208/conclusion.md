# 20250208 总结

## T1(a) [观察力] [分类讨论] [背包] [决策单调性]

期望:100 实际:100 难度:3 用时:3h

对于完全背包问题, 若所有物品的重量的最大值为 $w$, 则当背包容量 $\ge w^2$ 时, 最优方案一定包含了至少一个性价比最高的物品, 则可以将背包容量缩减到 $w^2$ 范围内. 证明考虑 $w$ 个数一定存在一个非空前缀使得和为 $w$ 的倍数.

对于一类定义域极大而不好枚举求最大值的函数, 考虑能否通过数学分析找到最大值. 如 $f(x) = \frac{a}{x} + bx$.

## T2(b) [搜索] [构造]

期望:0 实际:0 难度:4.5 用时:**1h**

构造题应当写一些显然的特殊性质或者写一个暴搜 (尤其是给了暴搜分的时候) 就过. 不应浪费太多时间.

事实上存在一类构造题的正解就是通过暴搜得到很好的构造, 再将若干暴搜得到的构造组合在一起.

## T3(c) [逆向变换] [观察力] [树状数组]

期望:15 实际:15 难度:4 用时:0.5h

对于一类正向维护序列的变化, 则一次操作就需要 $O(n)$, 但查询是单点询问的题目, 考虑逆向变化, 并只维护这个单点的值.

树状数组也支持二分. 具体来说, 将树状数组的范围补全至 2 的幂, 然后从尾向头倍增.

## 结算

直到过了 T1 才开始看后面的题. 或许在对题目很有把握时不失为一种策略.

在构造题上死磕了 1h, 但毫无收获, 甚至正解与特殊性质毫无关系.
