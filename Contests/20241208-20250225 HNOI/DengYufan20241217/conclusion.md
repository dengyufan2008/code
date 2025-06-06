# 20241217 总结

## T1(a) [模拟]

期望:0 实际:0 难度:4 用时:**4h**

少考虑了一种情况, 且应当会被卡常. 思维难度极其低的题目, 但直到下考后 3h 都没有调出来, 遂放弃.

对于一类看一眼就知道难度集中在实现的题, 在写代码之前先 **暴力** 地枚举每种可能出现的情况, 而不应当认为自己发现了一个良好的性质便理所当然的认可其的正确性.

对于一类有大量分类讨论的题目, 无论自己的算法能否兼容其中的某些 特殊/边界 情况, 都应当将其 **记录** 下来以便以后调试.

## T2(b) [观察力] [计数 Dp]

期望:100 实际:0 难度:2.5 用时:0.5h

快速的想出来了做法, 但并没有实现.

对于一类涉及元素极少 (两个) 的操作, 若每次会对序列中每对相邻元素都同时进行操作, 则通过手画一个稍大的序列, 观察序列的变化满足的性质. 注意应当考虑到每种情况.

与 之前正睿考过的一道题 (每次询问一个区间最后剩下的是什么字符) 的观察力部分相同.

## T3(c) [构造] [高斯消元]

期望:0 实际:0 难度:4 用时:0h

构造题的常见套路是, 考虑一个局面合法的必要条件, 并试图通过构造来说明其也为充分条件. 则途中可以对序列提前进行一些操作, 以将一些局面规约到同一个特殊的局面, 便于处理.

对于一类操作为对 $n$ 个元素做线性变换, 需要构造长度为 $n$ 的操作序列, 每次操作的参数恰为一个且可以自由设置, 但最终每个元素都要恰为一个给定值的构造题, 考虑高斯消元并构造一个特殊的操作序列, 使得解这个由操作序列推出的方程组是简单的, 并只要满足某些合法的必要条件则方程组有解.

## 结算

不妨庆祝今天的 **小金鱼记忆力**, **唐氏考试策略** 和 **久违的爆零**.

很快的把 T1 与 T2 都口胡了, 但 T1 口胡的做法少考虑了一些情况 (头藏在身体中间, 对四个最值没有影响, 则最小值不取在折线的两端点; 头和尾相向而行, 最小值取在中点), 因此自认为 T1 的实现难度不高而索性顺序写题. 在 2.5h 后发现了少考虑的第一种情况, 并快速的修复了自己的算法, 然后一直写 & 调第二种情况到最后.

值得一提的是, 在最初开始实现 T1 时我便意识到了第二个特殊情况, 但我自信的认为自己的算法能够兼容这种情况, 在最后却忘记了这种特殊情况而没有检查程序在这种情况下的的正确性.

事实上理应先把 T2 写完 (T1 的未知实现时间和 T2 的 <1h 实现时间显然是容易比较的), 略微地思考 T3 并写暴力再实现 T1.
