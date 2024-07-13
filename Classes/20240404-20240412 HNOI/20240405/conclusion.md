# 20240405 讲[题](https://www.luogu.com.cn/paste/dys1maqq)总结

- 对于一个没有什么性质的序列, 考虑其是否可以拆成两 (多?) 个有特殊性质的序列的和 (差). [例](https://www.luogu.com.cn/paste/pakicoyg)

- 对于一类矩形求和的问题, 若其还带有一维时间轴, 考虑通过割补法将与时间强相关的块变成只与 x y 其中一维相关. 则可以把三维偏序优化成二维. [例](https://www.luogu.com.cn/problem/P9061)

- 对于一类树上要查 一个点到根的路径上的 所有子树中的点 的信息的问题, 考虑将要查的点不断跳重链挂在线段树对应位置上, 则可以方便地查询. [例](https://loj.ac/p/3661)

- 对于线段树上一类与前缀最大值有关的问题, 考虑分类讨论传入的最大值与左区间最大值的关系. [例](https://www.luogu.com.cn/problem/P4198)

- 对于一类序列长度为 1 时好做的数据结构题, 考虑对序列进行线段树分治. [例](https://contest.xinyoudui.com/contest/93/problem/372)

- 静态的区间询问可以通过扫描线变成动态的后缀 (前缀) 询问. [例](https://www.luogu.com.cn/paste/7d2ib1x8)

  后缀询问 + 单点修改 可以通过扫描线变成 单点询问 + 区间修改. [例](https://uoj.ac/problem/515)

- 模拟费用流的一种方法是, 考虑建图中的若干关键点, 两两维护路径的最大 (小) 值, 然后对这些关键点暴力跑 SPFA. [例](https://www.luogu.com.cn/paste/fgt41p1o)

- 对于一类 $n$ 的范围稍小于 $q$ 的范围的含有点对查询的题目, 极有可能是考虑求出所有的支配点对并查询, 一般数量级为 $O(n \log n)$. [例](https://www.luogu.com.cn/problem/P9058)
