# 20240915 总结

## T1(wind) [二分] [单调队列]

期望:100 实际:90 难度:1 用时:0.5h

少判了二分到 $n+1$ 的情况, 此时 ``Calc(n+1)`` 的结果未定义, 应赋为极劣值, 但直接求得的是极优值.

略.

## T2(jadeite) [交换求和顺序] [等比数列求和]

期望:100 实际:66 难度:2 用时:2h

最后一步的交换求和符号卡住了, 认为需要计算自然数等幂和, 浪费了 1h, 然后急了, 放弃去想 T3 了. 怎么跟 20240809 T6 结局一样啊 (悲).

当等比数列的公比为 1 时, 使用 $\frac{1-x^{n+1}}{1-x}$ 将会得到 ``nan``, 需要特判.

答案式子有两个求和符号时一定要先考虑交换!!! 走投无路了再将其拆开!!! 😓

## T3(empty) [转化图论]

期望:55 实际:55 难度:3 用时:1.5h

若有多个序列, 且需要将一个序列拆成前缀和后缀来判断限制条件, 可以让前缀和后缀之间连边, 将限制条件转化为图论问题.

判断是否存在三/四元环可以让大度点向小度点连有向边, 时间复杂度 $O(\sum_i\sum_{j \in Out_i}|In_j| + |Out_j|)$, 根号分类讨论即可证明为 $O(m \sqrt m)$ 级别.

## T4(sinner) [贪心博弈] [DDp] [Treap]

期望:0 实际:0 难度:4.5 用时:0.5h

读错题了, 但事实上题面的确写的不好.

当一类博弈论的题目需要计算的不是先手必胜或必败, 而是某个式子最终的值时, 若无法使用类似 20240823 T1 的 Dp, 则可以大胆猜测最终的状态为某个较为简洁的形式, 可以通过造一些稍大的样例手玩来得到这一形式.

在证明满足某个条件的局面一定最优时, 可以考虑一个不满足条件的局面, 并考虑其是否存在一种方案 (操作方案/博弈策略) 调整到满足条件的局面, 且能变得更优.

``FHQ Treap`` 的删除某个值的其中一个点的写法应当是 ``Split`` 出只有这个值的树, 合并左右儿子.

调试时, 若代码中使用了 ``Rand``, 则应当重复测试同一组大数据, 看答案是否会发生变化.

## 结算

这场的失误难以归结为考试策略的问题. 事实上应当多回退思路, 以防止死磕在某个点上.
