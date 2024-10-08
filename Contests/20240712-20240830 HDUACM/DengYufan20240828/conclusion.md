# 20240828 总结

## T1(occur) [SAM] [分块] [DAG 链剖分]

期望:60 实际:60 难度:3 用时:2.5h

SAM 能够维护一个字符串 ``pop_front`` 和 ``push_back``, 但有时只有其中一种操作能同时维护答案. 此时分块的做法 (以只有 ``push_back`` 能维护答案为例) 为每个块区间都维护正串和反串的相关信息, 设 $L \le l \le mid \le R \le r$, 其中 $L$ 与 $R$ 为询问区间, $l$, $mid$ 与 $r$ 为块的间隙. 查正串表 $[l, mid]$ 并 ``push_back`` 到 $[l, R]$; 查反串表 $[l, r]$ 并 ``pop_front`` 到 $[l, R]$, 将答案置为正串的正确答案, 再 ``push_back`` 到 $[L, R]$.

[DAG 链剖分](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点.

## T2(include) [根号分治]

期望:10 实际:5 难度:3.5 用时:1h

手贱多写了一个数据分治, 成功没有过数据随机的 5pts.

对于一类询问区间内是否有一对元素满足条件的问题, 考虑对每个元素维护下一个满足条件的元素的位置.

总和一定时考虑根号分治!!!!!

根号分治时要分清两类元素, 数据结构中不能出现另一类元素. 实现上比较重要, 大部分调试时间都花在这里.

``set`` 常数远大于其他 STL, 需要使用的尽量少. 可以通过 ``priority_queue`` 来实现固定一点的 ``lower_bound``, 但这样操作的数量不能过多.

## T3(unsolved) [贪心]

期望:60 实际:28 难度:3 用时:1h

归并排序时忘记判对面是否为空了. 神奇的是 $10^7$ 的大样例都过了.

对于一类使贡献最小的贪心, 可以考虑什么情况下一定会有贡献, 并构造一种方案使得只有这些情况会贡献. 此时相比直接贪心统计答案, 统计一定会有贡献的情况数一般更容易.

## 结算

卡常所花费的时间不能超过 15min, 否则一般都是复杂度错误.

同时因为这一点没时间对拍导致挂分, 比较可惜.
