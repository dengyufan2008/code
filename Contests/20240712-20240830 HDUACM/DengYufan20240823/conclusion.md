# 20240823 总结

## T1(game) [博弈论] [Dp]

期望:100 实际:100 难度:2 用时:1h

若博弈的基本元之间没有相互的影响, 但博弈非对称, 则可将所有基本元对博弈结果的贡献合并.

## T2(perm) [转化意义] [Dp]

期望:40 实际:40 难度:3.5 用时:2h

若对于所有二元组 $(x, y) \space (x < y)$ 组成的序列, 有 $(x, y)$ 必然在 $(x, z)$ 与 $(z, y)$ 之间, 则将二元组视为一次交换值为 $x$ 和 $y$ 的操作, 从一个升序序列开始操作, 必然满足每次交换的都是相邻的数, 且最终能得到降序序列.

对于与排列相关的 Dp, 直接枚举序数并转化为排列再转化回去需要 $O(n^2)$ 的时间, 但可以搜索全排列, 并维护每个数后面有多少个小于它 (具体地, 每次找到一个可用的数后就令这个值加一). 但操作后转化回去需要一定技巧.

## T3(seg) [二分答案] [贪心]

期望:40 实际:40 难度:4.5 用时:1.5h

对于一类需要二分答案的问题, 若要对多个类似问题的答案求和, 不好直接维护答案. 可以考虑维护转置后的函数 (即答案的估价函数), 将求和式子变形可以使得答案之和只与函数面积有关.

## 结算

一直在卡常, 忽略了有 30pts 的部分分是通过打表好拿的.

用 ``__int128_t`` 来存一个 $2^{46}$ 的数, 导致无法使用 ``unordered_map`` 而只能用 ``map``. 事实上手写哈希并优化常数就能过 T2.
