# 20240406 讲[题](https://uoj.ac/problems?search=%E8%AE%AD2021)总结 & [解](https://www.cnblogs.com/dmoransky/p/16052837.html)

- 对于一类极多维的偏序问题, 可以将序列分为 $O(\log n)$ 块, 每块内维护某一维 $\le x$ 的下标集合. $O(\frac{n^2}{\log n})$.

  对于一类会了前一半不会后一半的问题, 考虑后一半能否规约到前一半. [例](https://uoj.ac/problem/710)

- 做凸包时一个点弹掉的点集就是删了这个点之后需要加回来的点集. 很显然但是没有想到.

- 对于树上一些与根有关的限制与贡献, 若根会发生变化, 考虑将其转化为仅跟点与边有关的表述. [例](https://uoj.ac/problem/715)

- 从 0 开始每次随一个 $[-v, v]$ 的数并加上, 走到的数的范围期望是 $O(\sqrt v)$ 的. 但随着步数的增加, 实际的数字会越发趋于稳定, 故越不可能成为最大 (小) 值. [例](https://uoj.ac/problem/716)

- 对于字符串 $S, T$ 有 $S < T^\infty \Leftrightarrow S < TS$, $S^\infty < T^\infty \Leftrightarrow ST < TS$. LCP 同样相等 (显然取等号时不等但不重要). [例 (不会)](https://uoj.ac/problem/717)

- 复习 SG 函数: 若先后手能进行的操作相同, 且每次只能操作一个最小的操作单位 (如 Nim 游戏中的每堆石子, 例题中的每颗棋子), 且会转移到拓扑序靠后的一些单位状态 (集), 则每个单位状态的 sg 值为后继的 mex, 多个单位状态的并的 sg 值为 Xor 和. 0 必败, 非 0 必胜. [例](https://uoj.ac/problem/719)

- 序列上两个人博弈, 一个人取完一个数后另一个人取相邻的其中一个数, 要让自己的和最大. 可以转化成带权最大匹配, 边权为两边的 min. [例 (不会)](https://uoj.ac/problem/720)

附: [算术](https://uoj.ac/problem/718) 的解

![](https://cdn.luogu.com.cn/upload/image_hosting/me5lkgw7.png)
