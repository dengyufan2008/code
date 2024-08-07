# HNOI 2024 总结

# Day1

## T1(wind) [解不等式]

期望:100 实际:100 难度:2 用时:2h

刚开始写代码的时候没意识到是解不等式, 浪费了很多时间. 对于代码实现中很多相似的问题, 考虑将其规约到同一个.

## T2(xor) [01 Trie] [贪心]

期望:40 实际:16 难度:3 用时:2h

冲正解没时间打部分分.

唯一没想到的是把加法操作改为删除操作. 以及对这个贪心的理解不够透彻.

对于一类贪心问题, 考虑其中某些特殊元素的决策情况 (如最小值最大的贪心, 考虑元素中最小值的决策).

分位贪心先判答案这一位能否为 $1$, 再讨论这一位的决策.

## T3(wormhole) [同构] [哈希] [Dp] [找规律] [Dp 方程转实际意义转 Dp 方程] & [解](https://www.luogu.com.cn/article/q2hc9n0u)

期望:32 实际:0 难度:5 用时:0.25h

冲 T2 没有想 T3, 事实上部分分是好想的.

对于 $p_{q_i} = q_{p_i}$ 的条件, 可以视为在 $p_{p_{q_{p_{q_{i}}}}}$ 或类似的东西中, 交换一对相邻的 $p$ 和 $q$ 不改变式子的值.

若需要将可能出现的种类极多, 判等较为困难的元素划分等价类, 考虑形式化表述出相等的条件并据此哈希, 有时需要先发现一些性质再进行映射.

对于方案数 Dp, 一种降低状态数的方式是寻找不同状态间的关系式.

对于一类较简洁的 Dp 方程, 若仅需其拓扑序最末尾的状态的对应属性, 考虑其的非本题的实际意义, 并考虑在拓扑序一维上从一次加 $1$ 变为加更多的转移方式.

# Day2

## T1(maze) [Dp] [贪心]

期望:100 实际:0 难度:2 用时:2.5h

线段树中《kMaxM * kMaxN * 56》. 1795MiB.

贪心时每次决策都要证明是否最优. 错误的贪心会浪费很多时间.

## T2(timeline) [DAG 计数] [拉格朗日插值]

期望:30 实际:30 难度:4.5 用时:1.5h

对于一类计数问题, 考虑如何判断两个方案是本质相同的.

若方案重排列不影响合法性但本质不同, 考虑不按排列而按集合 Dp. 此时状态要带上最后要乘的阶乘.

对于一类对 DAG 计数的问题, 考虑一个集合序列 $S$, $S_1$ 为 DAG 上入度为 $0$ 的点集, $S_2$ 为删去 $S_1$ 内的点后 DAG 上入度为 $0$ 的点集, 以此类推. 则 DAG 可以映射到集合序列上, 但 $\forall x \in S_i, \exist y \in S_{i - 1}$ 需满足有边 $(y, x) \space (i > 1)$. 发现这个条件不好满足, 考虑容斥. 钦定至少有 $S_i$ 内的点在删去 $S_1, S_2, ..., S_{i - 1}$ 后入度为 $0$, 条件变为 $\neg \space \exist x \in S_i, y \in S \setminus S_1 \setminus S_2 \setminus ... \setminus S_{i - 1}$ 使得存在边 $(y, x)$, 即 $\neg \space \exist x \in S_i, y \in S_1 \cup S_2 \cup ... \cup S_{i-1}$ 使得存在边 $(x, y)$, 容斥系数为 $(-1)^{|S_i + 1|}$.

对于一类转移为卷积形式的 Dp, 考虑维护 $[0,n]$ 的点值, 最后插值回来.

## T3(sleep) [不会]

期望:0 实际:0 难度:5 用时:0.25h

远超实力的题目.

## 结算
Day1 和 Day2 的考场策略出了同样问题, 每道题都应当留至少 1h 的思考和代码时间. 事实上, Day1 T3 的 32 分部分分对于排名来说很关键.

最后 10min 用来检查. 考前想好要检查什么.
- -fsanitize=address,undefined
- /bin/time 的时间与**空间**
- 调试信息 (Ctrl+F) 与文件读写 (最后测一遍样例)
