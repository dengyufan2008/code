# 20240412 讲[题](https://www.luogu.com.cn/paste/g7ouh9sl)总结

- 对于一类需要二分答案再用网络流 Check 的问题, 若总流量较小, 可以依次加边并维护 $S$ 能到达的点集, 能到 $T$ 后直接跑一次 Dinic 即可, 可以不用二分.

  因此, 大多数情况下, 二分+网络流 往往可以改成 动态加边的网络流, 从而少一个 $\log$.

- 稠密图上 BFS 可以使用 ``bitset`` 优化. [这两点对应的例](https://www.luogu.com.cn/problem/CF513F2)

- 网络流中一个元素若有两种决策, 考虑钦定其为其中一种, 并利用网络流进行调整. [例](https://www.luogu.com.cn/problem/CF1250K)

- 偏序图中 $最小链覆盖 = 最长反链 = 最小点覆盖$.

  因此, 偏序图同样是一个很强的性质. [例](https://www.luogu.com.cn/problem/CF1662J)

- 边权全为 $1$ 的网络流中, 使用 Dinic 至多扩展 $O(\sqrt n)$ 轮. So as 二分图. [例](https://www.luogu.com.cn/problem/CF1630F)

- 网络流中不仅可以动态加边, 也能动态删边. 具体地, 若要删一条边 $(x, y, w)$, 求出其实际流量 $w_0$, 连两条边 $(S, y, w_0)$ 与 $(x, T, w_0)$, 令其退流后删掉这三条边即可. (没有例)

- 正则二分图 (每个点均可匹配 $k$次, 故有 $kn$ 条边) 求完美匹配的方法: 匈牙利套随机可以单次 $O(n \log n)$, 共 $O(kn \log n)$.

  一个更优的做法 (但常数大了) 是, 若 $2 | k$ 则使用 $O(kn)$ 的欧拉回路将其分为两个 $\frac{k}{2}$ 的子问题, 否则使用 $O(n \log n)$ 的匈牙利套随机. 有 $T(k) = 2T(\frac{k}{2}) + O(kn + n \log n) = O(n^2 \log n)$. [例](https://www.luogu.com.cn/problem/P10062)

- 形如 $\le i$ 的至多只能有 $j$ 个 的限制可以等价于 第 $j + 1$ 小要 $> i$. [例](https://www.luogu.com.cn/problem/AT_agc031_e)

- Hall 定理: 对于一张二分图 $G$ 的左部点集 $L$, 若 $\forall S \subseteq L \space s.t. \space |S| \le |N(S)|$, 则 $G$ 存在完美匹配. $N(S)$ 表示 $S$ 的邻集.

  由此, 若要求存在完美匹配的二分图 $G$ 中所有的 $S \space s.t. \space |S| = |N(S)|$, 则随便跑一个完美匹配, 对于一条非匹配边 $(x, y)$, 在一张新图 $G'$ 中连有向边 $(x, Match(y))$, 表示选了 $x$ 就要选 $Match(y)$. $G'$ 显然是 DAG, 缩点后拓扑排序即可. [例](https://www.luogu.com.cn/problem/CF1835F)

- 建立最小割模型时, 里面的主要结点应当是能对题目所求的东西造成贡献的最小元素. [例](https://codeforces.com/gym/103861/problem/h)

- 平面图最短路等于对偶图最大流. 但这个最大流会有多个源点与汇点, 需要建立超级源/汇. [例](https://codeforces.com/gym/104849/problem/c)
