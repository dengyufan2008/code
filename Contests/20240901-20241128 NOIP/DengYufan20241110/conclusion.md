# 20241110 总结

## T1(tracy) [贪心]

期望:100 实际:100 难度:1 用时:1h

对于一类对每个位置被区间覆盖的次数有限制的问题, 从左到右能选就选右端点最靠左的一定最优. 证明考虑两个位置构成的三种区间 (都跨过, 只跨过一个), 选完 只跨过左侧的 后 都跨过的 和 只跨过右侧的 对 右侧位置 的贡献是相同的, 则继续选没有问题.

进一步地, 对于一类区间有关的问题, 一些策略的最优性的证明可以考虑两个位置构成的三种区间.

## T2(gravekeeper) [树形 Dp] [背包]

期望:100 实际:55 难度:3 用时:**2h**

写了一个含有 $O(n)$ 次拉格朗日插值的做法, 跑满的 $O(n^3)$ 被卡常了, 虽然不是正解但感觉很不应该啊.

非换根的树形 Dp 也不一定是从儿子转移到父亲, 也可以自上往下地转移. 尤其是在与 Dfn 有关时.

对于计数题, 由于含有较多的乘法和取模, 1s 内运算次数大约只能到 $10^8$.

## T3(thief) [区间 Dp] [观察力] [Bitset 优化]

期望:100 实际:100 难度:3 用时:1h

对于区间 Dp, 可以在写完转移后观察其是否只与区间长度有关, 从而优化掉一个 $n$.

另一种理解方式为, 对于重排 $a_i$ 得到的每个 $\min(\max_{j<i}a_j, \max_{j>i}a_j)$ 的取值, 必有一种方案满足最大值在最右侧. 证明考虑将最大值两侧的 前缀最大值/后缀最大值 序列归并.

进一步地, 对于一类前后缀均有关的可行性/最优化问题, 考虑以全局最大值为基准将两边的序列分开. 如 梦熊题单 20241029 j.

## T4(seer) [观察力] [主席树]

期望:100 实际:5 难度:2 用时:0.5h

没有时间写了, 事实上改题时 0.5h 就写完了, 且是四道题中次简单的题.

当题目中出现 $\lfloor \frac{x}{k} \rfloor$, 其中 $k$ 为常数时, 大概率复杂度有一个 $O(\log_kV)$.

静态区间查询后继可以用主席树实现.

## 结算

顺序开题大失败, 实现完 T2 的大常数做法后反复尝试卡常与优化算法, 浪费了若干时间. 在穷尽优化的可能性后应当及时的回退思路, 不过这次的正解我大概率想不出.

当一道题已经拿到了 60 左右的分数时, 无论这道题在什么位置, 无论估计做法有多么接近正解, 都应当先对后面的每道题思考 30min, 在拿到了一定分数后再回来集中思考这道题. 事实上想别的题的同时可以换脑子.
