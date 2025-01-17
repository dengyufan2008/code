# 20240404 讲[题](https://www.luogu.com.cn/paste/jxb7b3lp)总结

## Trick

- 计算 $\prod (1 - a_ix)$ 或 $\sum \frac{b_i}{1 - a_ix}$ 可以用分治 NTT. $O(n\log^2n)$.

- 对于一个生成函数的单项求值可以考虑按奇偶分类并使规模减半.
  
  如给定 $a_{[1,k]}$ 与 $b_{[1,k]}$, 求 $b_n = \sum_{i = 1}^k a_i b_{n - i} \space (n > k)$, 则有 $\sum_{i = 0}^k a_i b_{n - i} = 0 \space (a_0 = -1)$.
  
  故 $A(z) * Ans(z) = B(z)$, 其中 $A(z) = \sum_{i = 0}^k a_i z^i$, $B(z) = \sum_{i = 1}^k b_iz^i$, $Ans(z) = \sum_{i = 1}^\infty b_iz^i$.

  那么 $Ans(z) = \frac{B(z)}{A(z)} = \frac{B(z) * A(-z)}{A(z) * A(-z)}$. 设 $C(z^2) = A(z) * A(-z)$, $D(z^2) + z * E(z^2) = B(z) * A(-z)$, 则 $Ans(z) = \frac{D(z^2)}{C(z^2)} + z * \frac{E(z^2)}{C(z^2)}$, 从而可以分类讨论 $n$ 的奇偶性来只考虑右侧式子的前项或后项. $O(k\log k\log n)$.

## Cheese Point

- 转置原理: 对于一个算法, 若其可以处理输入一个矩阵 $[X]$, 输出矩阵 $[Y] = [A] * [X] \space ([A]$为常量$)$, 则必然可以处理输入一个矩阵 $[Y']$, 输出矩阵 $[X'] = [A^T] * [X]$.
  
  体现在具体实现上为将所有的操作转置并将顺序反向.

- LGV Lemma: DAG 中, 对于两个大小均为 $n$ 的有序点集 $S$ 与 $T$, 每对点之间有路径且路径彼此不交的 所有 $n$ 条路径的边权积之和 (带一个 $(-1)^{逆序对个数}$ 的系数) 为 矩阵 $A_{i, j} = ($ 所有 $s_i \rightarrow t_j$ 边权积之和$)$ 的行列式.

- 子集卷积: 若要计算
  $$C_{S} = \sum_{I \cup J = S, I \cap J = \varnothing} A_I B_J$$

  考虑条件等价于 $I | J = S, |I| + |J| = |S|$, 故按 PopCount 将下标分为 $n$ 组, 每组之间两两进行 Or 卷积. $O(2^n n^2)$.

- 子集 Exp: 从 $1$ 到 $n$ 递推, 每次枚举一个最大值为 $i$ 的集合并与之前得到的结果做子集卷积. $O(\sum_{i = 1}^n 2^i i^2) = O(2^n n^2)$.

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

# 20240411 讲[题](https://www.luogu.com.cn/paste/gg40dcu5)总结

- 奇偶位分别考虑是一种常见思路. 在计数问题中若奇偶位没有互相限制, 则可以分别统计奇偶位的贡献, 从而减少状态数. [例](https://qoj.ac/problem/8330)

- 同理, 可以将横纵坐标分开. [例](https://www.luogu.com.cn/problem/AT_arc171_e)

- 对于一类从一个状态会 $O(1)$ 转移到多个状态, 但状态数不好优化只能优化转移的 Dp, 发现其类似有 $O(1)$ 的查询和 $O(\ge 1)$ 的修改, 则可考虑进行平衡.

  如做的是集合 Dp 要转移到超集, 则可以考虑 Meet-in-the-Middle, 前一半枚举转移后的集合, 后一半枚举转移前的集合. 则前一半对应查询, 后一半对应修改. [例](https://qoj.ac/problem/8005)

- 对于一类计数问题, 若要在 枚举每一种可能的集合 的情况下还要 对每个集合计算一个抽象式子, 可以考虑那个式子的组合意义 (要能简单表述的最好), 从而得到一些光看式子想不到的抽象转化. 事实上这一思路的适用范围较广, 如 HNOI 2024 Day1 T3 wormhole. [例](https://www.luogu.com.cn/problem/AT_wtf22_day2_d)

- 对于一类需要快速判断一些奇怪的问题是否成立的问题, 考虑将问题的成立与否转化为一些条件的真假, 然后根据这些条件设计 Hash 方程. 
  
  如长为 $n$ 的环 $a_i$ 上每次可以将长为 $m$ 的一段 +1/-1 $(m | n)$, 问能否变成全 0, 即问每个 $\bmod m$ 意义下的等价类中 $a_i$ 的和是否均相等. 可以取一个常质数 $p$, 哈希函数为 $Hash(a) = \sum_i a_i p^{i \bmod m}$, 判断即为 $Hash(a) * m = \sum_i a_i \sum_{j = 0}^{m - 1} p^j$. [例](https://qoj.ac/problem/7782)

- 当一个问题同时有两个经典弱化时, 先考虑假设自己会了其中一个能不能推广到原问题 (如树上 Xor 可以变成 序列上 Xor/01 Xor). 取更容易的一个并舍弃另一个. [例](https://www.luogu.com.cn/problem/AT_apc001_f)

- 对于树上的任意一个连通块, 其都对应了点分治中以某个中心为根, 不经过已经分治过的中心的连通块.

  Proof. 考虑原树的重心, 若其不在那个连通块里, 则它只会位于重心的一个子树中, 此时删掉重心没有影响; 若其在则重心即为要的那个分治中心.

- 满足某一性质的点构成的连通块中 $x$ 所在的那个连通块, 等价于所有 $i$ 满足 $x$ 到 $i$ 的路径上的所有点都满足性质构成的集合. 可以将一个跟很多点有关的连通块问题变成只跟自己有关的元素问题. [这两点对应的例](https://www.luogu.com.cn/problem/P5311)

- 同样的字符串技巧复刻. 对于字符串 $S, T$ 有 $S < T^\infty \Leftrightarrow S < TS$, $S^\infty < T^\infty \Leftrightarrow ST < TS$. LCP 同样相等 (显然取等号时不等但不重要).

  特别地, 利用 SA 可以求 $S_i S_j$ 和 $S_j S_i$ 的 LCP, 具体来说可以预处理 $S_1 S_2 S_3 ... S_n$ 的 SA, 先求 $S_i$ 和 $S_j$ 的 LCP, 然后再继续求两次. [例](https://www.luogu.com.cn/problem/AT_arc175_f)

- 若有两个区间 $R_1$ 与 $R_2$ 有交, 则对应线段树上的结点集合 $S_1$ 与 $S_2$ 中, 必然分别存在一个元素 $x \in S_1$ 和 $y \in S_2$, 使得 $x$ 与 $y$ 成祖孙关系.
  
  由此, 可以把每个修改对应的结点的祖先也打上相同的标记. 然后换成查询同样做一遍即可不重不漏.

- 构造一个满足条件的最小 DFA 方法: 随便构造一个合法的 DFA (可能有冗余), 然后进行缩点, 将每条出边指向的点全部对应等价的点缩在一起, 注意非结束结点与结束结点始终不等价, 缩第 $k$ 轮 (Base 0) 时要忽略 $k$ 步内能到达结束结点的结点. [例](https://www.luogu.com.cn/problem/P4339)

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

# 20240503 讲[上午题](https://www.luogu.com.cn/api/team/downloadFile/9nt80yus)总结 & 哈哈一大半都是原

- 对于一个带权元素, 考虑将其视为多个权值为 1 的元素. [例](https://www.luogu.com.cn/problem/CF1172C2)

- 对于局面中一个有单调性的维度, 考虑它对转移的影响, 若可能的情况较少且具体影响与该维度无关, 则可以分类讨论分别 Dp. [例](http://zhengruioi.com/contest/1500/problem/2802)

# 20240503 讲[下午题](https://www.luogu.com.cn/api/team/downloadFile/pcpfoxpt)总结 & 哈哈一大半都不会

- 对于一个不一定是积性函数的函数 $F(n)$ 的前缀和单点求值问题, 考虑 $F(n)$ 的递推式, 若能写成一个类似狄利克雷卷积的形式, 则考虑构造另一个积性函数 $G(n)$ 使得卷积后的是好求前缀和的函数 $H(n)$, 从而杜教筛. [例](https://loj.ac/p/6714)
  
- $(a - b)^k \le a^k - b^k$. [例](https://cpc.csgrandeur.cn/csgoj/problemset/problem?pid=1245)

附: 讲[上午课](https://www.luogu.com.cn/api/team/downloadFile/9nt80yus) & [下午课](https://www.luogu.com.cn/api/team/downloadFile/pcpfoxpt)内容

# 20240504 讲[题](https://www.luogu.com.cn/api/team/downloadFile/5n4g6qh1)总结

- 对于一类贪心问题, 找到对贡献影响很大的关键点, 据此来调整非关键点从而得到特殊性质.
  
  若要查是否存在一个任意的元素满足其附带属性恰好为 $k$, 若有存在 $k$ 则必存在 $k - 2$, 则可以分奇偶维护 $k$ 的最大值. [例](https://www.luogu.com.cn/problem/AT_agc028_e)

- 对于一类排序后两两对应需满足同一类不等关系的限制, 考虑一个值域上的前缀/后缀和数组, 限制变为任意一个位置都 $\ge 0$. [例](https://www.luogu.com.cn/problem/CF533A)

- 对于一类贡献形如 $\max(a_i, a_{i + 1})$, 考虑将其变形为 $a_i + max(a_{i + 1} - a_i, 0)$, 则只需考虑上升部分的距离. [例](https://www.luogu.com.cn/problem/P10197)

- 对于一类确定树的形态的问题, 只需考虑一个点的邻点集合与邻点中哪个是父亲. [例](https://www.luogu.com.cn/problem/CF1129E)

- 对于一类限定某些元素要在两个元素之间的问题, 考虑从两边往中间构造. [例](https://www.luogu.com.cn/problem/P7056)

附: 讲[课](https://www.luogu.com.cn/api/team/downloadFile/byor0cng)内容

# 20240505 好[题](https://www.luogu.com.cn/paste/yard06r4)分享

# 20240506 好[题](https://www.luogu.com.cn/paste/49557exa)分享

# 20240507 好[题](https://www.luogu.com.cn/paste/f99xji7t)分享

附: 讲[课](https://www.luogu.com.cn/api/team/downloadFile/vwgjlhf2)内容

# 20240521-0621 PTY 特供题单 ([精简版](https://www.luogu.com.cn/paste/bqg2225v))

# 20240623-0714 PTY 特供题单 ([精简版](https://www.luogu.com.cn/paste/8ldma22f))

# 20240715-0902 PTY 特供题单 ([精简版](https://www.luogu.com.cn/paste/xrwpc3ar))

# 20240903 [梦熊题单](https://www.luogu.com.cn/paste/3uzzihcg)

- 对于一类图论中靠前的点不确定的边, 可以直接认为是只有出度的边来考虑, 从而保留了每条边都恰好经过一次的性质.

  对于贪心后有可能不合法的情况, 考虑不合法的条件, 并直接对当前局面进行调整以改为合法. 为保证没有后效性, 需要能够反悔.

  当不需要构造方案时, 无需考虑实际方案的形态, 可以降低思维难度. [例](https://qoj.ac/problem/8824)

- 对于一类求与凸包类似的东西的问题, 考虑用类似的算法, 只需要保证每次转移最近的点一定最优, 且一个元素其后面不合法的元素构成一个后缀即可. [例](https://qoj.ac/problem/8556)

- 判断一个序列是否是等差序列可以用 ``set`` 维护数集, ``multiset`` 维护相邻两项的差值. 支持动态增删. [例](https://www.luogu.com.cn/problem/P7205)

- 对于一类每个元素的贡献都为一个凸壳且贡献方式为加法的问题, 若元素之间的限制仅有偏序关系, 则寻找贡献的最值可以使用整体二分. 具体参考 [保序回归](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点. [例](https://loj.ac/p/6518)

- 对于一类形如 "所有在范围内的数 +1/-1" 的表述, 考虑差分.
  
  对于一类求每种方案的贡献和的计数题, 若一种方案的贡献不好求, 考虑构造一种 "维护一个 (几个) 变量并进行操作贡献答案" 的类自动机算法, 从而可以 Dp 转移.
  
  比如, 例题中的类自动机算法为 $s \leftarrow \max(s + a_i, i)$, $ans \leftarrow ans + s - (n + i - 1)$, $s \leftarrow \min(s, n + i - 1)$. [例](https://qoj.ac/problem/8820) & [解](https://www.luogu.com.cn/article/68ltezbd)

# 20240910 [wxl 好题分享](https://www.luogu.com.cn/paste/oyuk6nk7)

# 20240912 [梦熊题单](https://www.luogu.com.cn/paste/5oyp5wr8)

- 当题目的模数是一个合数, 且与题中的某些常数有较大联系时, 不妨将其拆成若干互质数的乘积并使用 CRT. [例](https://qoj.ac/problem/4888)

- 当题中给的操作有看似很合理的性质 (如本题每次都会选 $m$ 个) 时, 应当多思考其的正确性, 有可能会少考虑情况. [例](https://qoj.ac/problem/8683)

# 20240918 [qyb 好题分享](https://www.luogu.com.cn/paste/6szkjlpz)

# 20240912 [梦熊题单](https://www.luogu.com.cn/paste/c7xke3op)

- 对于一类期望的题目, 变换钦定的顺序再求概率可能会降低难度. 如本题先钦定最开始选择的点再钦定逆序对 比 先钦定逆序对再钦定最开始选择的点 容易. [例](https://www.luogu.com.cn/problem/CF1540B)

- 当数据范围只有 $10^5$ 且 $O(n^2)$ 做法显然时, 考虑使用 ``bitset``. [例](https://loj.ac/p/6499)

- 计算平面上欧几里得距离的近似值的一种方法为, 考虑一个极小的角 $\theta$ 满足 $k \theta = 2\pi \space (k \in \N)$, 每次将点绕原点旋转 $\theta$ 并求和 $x$ 坐标之差, 和除以 $(1, 0)$ 每次旋转后到原点的 $x$ 轴无符号距离和即为距离的近似值. 需要注意的是这种方法误差较大, 当 $\theta = \frac{2\pi}{1024}$ 时才能获得 $10^{-6}$ 的绝对误差精度. [例](https://qoj.ac/problem/9289)

- 最优化问题中, 若贡献的计算方式与区间高度相关, 考虑四边形不等式. [例](https://www.luogu.com.cn/problem/P9732)

- 对于 删除若干元素 使得 剩下元素两两之间都需满足某个限制 的题目, 考虑将不满足限制的元素连边, 则成为最小点覆盖问题. [例](https://www.luogu.com.cn/problem/CF164D) & 20240323 T3

- [杨表](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点. [例](https://www.luogu.com.cn/problem/P3774)

# 20240924 [hjc 好题分享](https://www.luogu.com.cn/paste/6w8amjif)

# 20240929 [梦熊题单](https://www.luogu.com.cn/paste/od08eg6w)

- 对于一类指数级做法的题目, $q$ 次询问一般是没有意义的, 需要对于每个集合都求出答案.
  
  类似 20240228 T2 地, 若一个状态 $P$ 能够转移到若干状态 $Q_i$, 而取其中一个转移 $\mathcal F: P \rightarrow R$, 对所有 $Q_i \neq R$ 有 $\mathcal F(Q_i) = P$, 则可以将每个状态 $P$ 的期望 $E(P)$ 用 $A_P + B_P E(\mathcal F(P))$ 表示, 由于 $E(Q_i) = A_{Q_i} + B_{Q_i} E(P)$ , 可以分别得到 $A_P$ 和 $B_P$ 的递推式. 例如树上转移到每个邻点的问题可以用父亲的期望来表示. [例](https://www.luogu.com.cn/problem/P5643)

- 当最小化问题的答案存在明显上界时, 考虑其是否同时也是下界. [例](https://www.luogu.com.cn/problem/CF2B)

- 当题目只需要求生成树时, 同样也应当使用生成树算法, 且此时可以自行添加边权. [例](https://www.luogu.com.cn/problem/CF653E)

- 当存在两种元素, 其中只有第一种元素有限制时, 考虑先将第一种元素满足限制地排列好, 再将第二种元素插进去. [例](https://www.luogu.com.cn/problem/CF316D3)

- 找到规律后一定要验证. 验证之后考虑规律能否化简 (比如白色的连续段奇偶交替出现且两侧恰好有一个奇段 $\Leftrightarrow$ 白色个数为奇数). [例](https://www.luogu.com.cn/problem/AT_arc143_e)

- 当问题涉及到的元素过多时, 考虑将元素划分等价类使得不同等价类之间的元素无关.
  
  对于两维长度差异较大的数组, 要么将较大一维放在前面, 要么使用滚动或类似背包的处理方式消去一维, 可以大大降低常数. [未使用滚动数组, >8s](https://atcoder.jp/contests/arc184/submissions/58274623) & [使用滚动数组, <5s](https://atcoder.jp/contests/arc184/submissions/58274888). [例](https://www.luogu.com.cn/problem/AT_arc184_b)

- 将二维状态的 Dp 优化到 $< O(n^2)$ 时, 不仅需要考虑类似重链剖分中的第二维不超过子树大小, 同样需要考虑有无更加紧的限制.
  
  对于一类分数规划的二分答案解法, 判断完后用 ``mid`` 来更新左右端点是不优的, 应当用本次求解出的答案来更新. [例](https://www.luogu.com.cn/problem/P3319)

- 对于一类字符串题目, 寻找性质时不要在 SAM 上找, 而应当在字符串上找并将其映射至 SAM 上. [例 (线性做法)](https://qoj.ac/problem/562)

- 回文串需要考虑回文中心的每个可能出现的位置, 尤其是当回文串长度为偶数时. [例](https://www.luogu.com.cn/problem/P4324)

# 20241001 [syc 好题分享](https://www.luogu.com.cn/paste/8dikkv6q)

# 20241008 [梦熊题单](https://www.luogu.com.cn/paste/63oierme)

水题单, 只有 c 还有点意思.

# 20241015 [梦熊题单](https://www.luogu.com.cn/paste/w61ybe9d)

- $k$ 条树上可交路径, 对于到最近叶子距离相同的点至多覆盖 $k$ 个, 且对于每个距离都能取到这个上界. [例](https://www.luogu.com.cn/problem/P3441)

- 选择若干连通块的限制比选择恰好一个连通块的限制松. 事实上选择若干连通块就是随便选.

  若选择一个连通块的代价为 所有连接 非连通块点 与 连通块点 的边的边权和, 则其只与一条边两侧的点是否选择有关, 将视角从点改为边可以用最小割解决. [例](https://darkbzoj.cc/problem/2965)

  写这道题时的脑瘫错误: 网络流里边 Base0 存储, 但 Dfs 的时候写的是 ``i && in`` 而非 ``~i && in``; 没有把平面图上度数为 1 的点删掉; 按极角排序时没有认真考虑 Cross 为 0 的情况, Cross 相同时没有取距离近的那一个.

- 前缀与至多只有 $O(\log V)$ 个连续值段, 且若将非连续段首删去对值无影响.

  $O(\log V)$ 个关键点要比 $O(n \log V)$ 种可能成为最优方案的操作更好考虑. 因为后者舍弃了多个操作之间的联系. [例](https://www.luogu.com.cn/problem/P9696)

- 对于一类所有元素两两都有大小关系的限制, 用排列刻画限制不如用边来刻画限制. 因为前者的合法性只能全局判断, 但后者可以考虑是否较小的形状合法则全局也合法, 从而将有关的元素缩减至 $O(1)$ 个.

# 20241022 [xh 好题分享](https://www.luogu.com.cn/paste/jyum3oqn)

# 20241028 [dyf 好题分享](https://www.luogu.com.cn/paste/z9uxq8ts)

# 20241029 [梦熊题单](https://www.luogu.com.cn/paste/09up24mt)

- 一张可以被拆分为若干完全图的无向图的最小生成树, 所用到的边只会在每个完全图的最小生成树的边集之并中. [例](https://www.luogu.com.cn/problem/CF1981E)

- 对于一类求和大整数 bitwise 运算恰好等于某个大整数的题目, 应当从高位往低位考虑, 在除以当前位的位权下, 实际与目标的差值不会大于等于求和的项数. [例](https://www.luogu.com.cn/problem/CF1994G)

- 在树上选取若干条链使得覆盖的点数最大, 则考虑长链剖分. [例](https://www.luogu.com.cn/problem/CF1976F)

- 将一个数集 $S$ 中的每个元素看作一条边的长度, 能够组成一个多边形当且仅当 $2\max(S) < \sum(S)$.
  
  笛卡尔树也可以合并, 复杂度为 $O(较大深度)$. 代码实现上同 FHQ Treap. [例](https://www.luogu.com.cn/problem/CF1990F)

- 对于一类 Dp 题, 若题面给了你一个合法状态的构造方式, 则考虑直接按照这个构造方式来 Dp. [例](https://www.luogu.com.cn/problem/CF2001E2)

- 对于一类最优化问题, 若合法条件仅为满足一维偏序, 当答案可能的取值数量较少时, 考虑对每个答案计算最紧的合法条件, 查询时直接二分. [例 (本题单最好的一道)](https://www.luogu.com.cn/problem/CF1973F)

- 对于一类分块题, 若需要支持 checkmax 操作, 而没有区间修改, 则考虑类似吉司机线段树的做法, 维护 min 和 min2. 若仅更新 min 时可以快速修改, 则至少更新到 min2 的可以暴力重构. 容易发现对于一个块至多重构 $O(B)$ 次.
  
  若 $x \ge 1$, 对排列 $p$ 定义 $pre$ 为前面第一个大于的数的下标, $suf$ 为后面第一个大于的, 有
  $$\sum \min(nxt_i - pre_i, x) = \sum min(nxt_i - i, x) + \sum min(i - pre_i, x) - n - x + 1$$
  . 证明考虑在序列末尾加入 $x-1$ 个空位, 值域上从大往小枚举每个位置, 将其后的总共 $x$ 个格子标记, 则总共的被标记的格子数为 $n+x-1$, 但还有另一种计算方法, 细节如图
  ![](https://cdn.luogu.com.cn/upload/image_hosting/akr57twz.png)
  [例](https://www.luogu.com.cn/problem/CF1967F)

- $\text{mex}$ 为集合内未出现的数的最小值, 则对于一类最小化问题, 可以用 自行决策取哪个数的技巧 来 Dp. [例](https://www.luogu.com.cn/problem/CF1981F)

- 对于一类和排列的前缀最大值个数有关的题目, 考虑每次把最小的数插在哪里.
  
  对于一类和排列的前缀最大值个数与后缀最大值个数都有关的题目, 考虑全局最大值在哪里以将序列分开. [例](https://www.luogu.com.cn/problem/CF1988F)

- 若每次操作至多只会新增一个 0, 且每次操作后 0 都会扩散至少 1 格, 则 0 的连续段数为 $O(\sqrt n)$. [例](https://qoj.ac/problem/9311)

- 还有一道困难概率 Dp [题](https://www.luogu.com.cn/problem/CF1975I)

# 20241105 [lsl 好题分享](https://www.luogu.com.cn/paste/oczcmfkz)

# 20241106 [梦熊题单](https://www.luogu.com.cn/paste/ft9nu2ko)

# 20241106 [梦熊题单](https://www.luogu.com.cn/paste/ft9nu2ko)

- 对于 2048 游戏, 若其局面上的数列具有单调性, 则可以看作一个二进制数. [例](https://www.luogu.com.cn/problem/P7093)

- 一个数的前驱更大值为大根笛卡尔树上对应子树对应区间的左侧一个位置, 后继同理.
  
  $\sum \min(i-p_i, s_i-i)$ 为 $O(n \log n)$ 级别. 证明考虑笛卡尔树上启发式合并. [例](https://www.luogu.com.cn/problem/AT_joi2020ho_e)

- 当有一个 $O(n)$ 和一个对称的 $O(m)$ 做法时, 若 $O(nmk)$ 较小, 则考虑一个 $O(k)$ 做法. 即三次根号分治. [例](https://www.luogu.com.cn/problem/AT_joi2018ho_e)

- 对于一类计数合法的排列问题, 若以排列的值为拓扑序不好考虑, 则考虑题目所给的拓扑序, 并将有限制的元素对应排列的值放进状态中. [例](https://www.luogu.com.cn/problem/AT_joisc2016_c) & 20241110 T2 gravekeeper

- 给定若干区间, 使得每个位置被覆盖至少 $a_i$ 次 这一问题是板的, 可以直接贪心. [例](https://www.luogu.com.cn/problem/AT_joisc2017_d) & 20241110 T1 tracy

byd 在做完这两道题后这天考的两个 Trick 怎么一个想了 1h 一个直接不会.

# 20241112 [fzx 好题分享](https://www.luogu.com.cn/paste/sw0eplz9)

# 20241113 [梦熊题单](https://www.luogu.com.cn/paste/teuun37l)

- 对于一类对转移有限制的题目, 可以考虑多设一个状态, 表示其中某些维已经转移, 某些维未转移, 并将非法的部分置 0 或极劣值. [例](https://qoj.ac/problem/7006)

- 对于一类把 $S$ 变为 $T$ 的最优化问题, 若操作序列必须为给定的操作序列的一个区间, 则考虑对于最优方案的区间的后缀, 同时对 $S$ 和 $T$ 进行操作, 则选取的操作序列变为一个后缀. [例](https://www.luogu.com.cn/problem/CF1392G)

- 对于一类计数问题, 若总量很庞大但限制很少, 考虑计算其满足限制的概率, 为了好算可以在保证不漏的情况下删去一些情况. [例](https://www.luogu.com.cn/problem/AT_agc023_e)

i 不会啊

# 20241119 [jjz 好题分享](https://www.luogu.com.cn/paste/kyb8w87m)

# 20241122 [梦熊题单](https://www.luogu.com.cn/paste/lj9y5xnp)

- 本质不同子序列个数的 Dp 式子应当是
  $$f_i = 2f_{i-1} - f_{p_i-1}$$
  而不是
  $$f_i = 2f_{i-1} - f_{p_i}$$
  [例](https://www.luogu.com.cn/problem/CF645E)

- 对于一类用一条格路将平面上点分类, 并分别按坐标轴顺序算贡献的 Dp, 若两类点的贡献互不影响, 考虑按其中一维扫描线, 另一维的贡献直接放在线段树上, 靠前的 Dp 值转移过来时在线段树上按顺序加上另一维的贡献. [例](https://qoj.ac/problem/9222)

- 对于一类背包容量极大, 但物品体积较小的最优化问题, 考虑先贪心, 再调整解. 类似小了加大了减的策略, 可以证明调整的部分是多项式级别的, 使用背包 Dp 即可. [例](https://www.luogu.com.cn/problem/P8392)

- 对于一类限制与集合的最大值有关, 且每次操作为让集合异或上自己选择的一个元素的 Dp, 若值域较小, 除直接 Dp 同时维护集合外有另一种更优做法.
  
  按值域考虑每个位置的限制形成的序列, 对于 $\ge i$ 的位置形成的若干极长连续段, 使用 Dp 计算只有这一段, 初始集合为空的答案, 显然状态中也要记下这个集合. 转移考虑该连续段内 $> i$ 的连续段已经计算完, 则考虑 $= i$ 的连续段的计算, 显然只需认为只能加入或删除 $[1, i]$ 内的元素即可. 对于与 $> i$ 的连续段的合并, 其为异或卷积的形式.

  随后可以发现, 对于 $\ge i$ 的连续段, 所有 $\le i$ 的元素都是等价的, 故可以将状态中的集合缩减为集合大小.

- 对于异或卷积有 $f'_S = \sum_T (-1)^{\mid S \cap T \mid} f_T$. [例](https://qoj.ac/problem/9438)

k 不会啊

# 20241127 [梦熊题单](https://www.luogu.com.cn/paste/re1kw5qc)

d 我想假了啊

g i 很好啊 我是容斥废物

h 是大奋题啊

j 很复杂不想写啊

# 20241216 代码源 1

https://www.luogu.com.cn/api/team/downloadFile/82i7o190

# 20241218 代码源 2

https://qoj.ac/contest/1872

# 20241220 代码源 3

CF2052K
CF2052H
CF2052C
CF1930H
CF1801E
QOJ8922
QOJ9798
QOJ9800
QOJ9809

# 20241223 代码源 4

P11343~11348

# 20241225 代码源 5

P11105-11107 P11109-11111

# 20241230 代码源 6

QOJ1257
[ajo2024final](https://atcoder.jp/contests/ajo2024-final/tasks) A~E

# 20250103 代码源 7

AGC070 A-D CF2053G-I2

# 20250106 代码源 8

## 题 & 解

比较套路的题：
https://vjudge.net/problem/TopCoder-14588 dfs序计数。

dp[S][u] 表示 u 为根，S 这个点集的 dfs 序。删去 S 之后分成若干个联通块，可以任意排列。

DAG容斥：

dp[S] 表示 S 这个点集定向之后是 DAG 的方案。考虑枚举源点的的一个子集，系数为 (-1)^ (点数-1)。

acyclic orientation 等于 色多项式 P(x) (-1)^n P(-1)。应用：网格图 acyclic orientation

https://codeforces.com/gym/102012/problem/L 可以至少做到 O(bell(m) poly(nm))

https://atcoder.jp/contests/abc306/tasks/abc306_h DAG容斥

定向，使得相等或者 DAG。类似枚举子集。

https://uoj.ac/problem/37 强联通图计数，DAG容斥。 

枚举点改成枚举 SCC 的子集即可。

https://qoj.ac/contest/1543/problem/8325 DAG容斥

先求出每个块的拓扑序。然后要求整体直接有拓扑序，类似前面的，枚举子集。

直接做可能是 O(3^n * n^2) 的，其中一维可以用插值优化。

https://acm.hdu.edu.cn/showproblem.php?pid=5330 简单的魔改高维前缀和

dp[i][s1][s2][k] 表示和前 i 位为 s1 的所有串，后 s2 位的距离为 k 的方案数。

https://atcoder.jp/contests/agc017/tasks/agc017_f 魔改高维前缀和。

回顾前缀和，按某种顺序确定，这一位删或者不删。这样能保证每个点向子集恰好一条路径即可。

这里可以考虑路径上每一格要不要翻转，这样可以做到 O(2^n * n)。或者也可以按题解说的从上往下决定每一位要不要翻。

https://atcoder.jp/contests/agc024/tasks/agc024_f 魔改高维前缀和。

状态设计成已经确定了 t 的前几位，s现在后面还有几位的方案。等比数列算一下应该是 O(2^n * n)

https://qoj.ac/problem/2068 2^(n/2) 求一般图匹配的手法

把 2i-1 和 2i 连一条边，整个图会变成若干个环和链。可以用 2^(n/2) * n^2 算出来。后面子集并，

https://codeforces.com/contest/468/problem/E 2^pathwidth 的状压 dp 手法

构造一个顺序状压，每次只需要统计压一下有边跨过这个位置的点的状态即可。这个最大的值叫做pathwidth。

有如下的理论结果，可以理解成非常小常数的 2^O(n)：

In any cubic graph, or more generally any graph with maximum vertex degree three, the pathwidth is at most n⁄6 + o(n), where n is the number of vertices in the graph. There exist cubic graphs with pathwidth 0.082n, but it is not known how to reduce this gap between this lower bound and the n⁄6 upper bound.

咋克的近似做法：对于每一列，枚举额外增加的是哪一行，或是不选择额外增加的，然后状压哪些行已经被占用了。考虑优化。注意到如果一行在之后的列都不会用到了，那就可以不状压这行。注意到如果一行的元素很少，那我们去掉这一行就会很容易。于是每次找到元素数最少的行，并找到用到这行的列，先枚举这些被用到的列。这样跑得飞快，在 CF 上是最优解（截至 2021.11.4）。

https://loj.ac/p/6719

题解写了集合幂级数的 exp，ln。众所周知在 n<=18 的情况下，2^n * n^2 和 3^(n-1) 跑的差不多快，所以只要暴力就行了。

考虑这么个过程，初始都是一些环和单点。然后考虑从 1 到 n，每个点把边上的块并起来。

几个比较杂的题，不一定讲。

https://codeforces.com/gym/102759/problem/C 定向，最小代价强联通图。处理手法比较神秘。

每次从当前的 SCC 上面伸一条回自己的路径。然后对着这个过程压即可。

https://atcoder.jp/contests/agc016/tasks/agc016_f 删源点。

每次删去 sg = 0 的点之后，我们发现每个点的 sg 值恰好减一。（这个思路和求树 hackenbush 有点类似）

https://qoj.ac/contest/1648/problem/8364 更加有手法的高维前缀和。

https://acm.hdu.edu.cn/showproblem.php?pid=7470 十分魔怔的压状态方法。
https://acm.hdu.edu.cn/showproblem.php?pid=7476
https://uoj.ac/contest/43/problem/372
https://codeforces.com/contest/1569/problem/F 杂题，想办法压状态
https://loj.ac/p/6729 边双联通计数。和仙人掌有点类似。

https://vjudge.net/problem/TopCoder-14299 直接偷 2^pathwidth 的做法即可。

## 总结

- 无向图给每条边定向使得形成 DAG 的方案数 = 用 -1 种颜色染色使得相邻点的颜色不同的方案数 $\times (-1)^{n}$, 其中 $n$ 为 无向图的点数. -1 种颜色可以理解为随便选则系数乘 -1, 排除掉一种则系数乘 -2, 以此类推; 或可理解为 $(\omega - 1)$ 种颜色, 其中 $\omega$ 大于所有自然数, 并忽略所有非常数项.

  <details><summary>Proof</summary>

  > 考虑后者的方案数. 设 $f(G, m)$ 表示将无向图 $G$ 用 $m$ 种颜色染色的方案数, 使得相邻点的颜色不同的方案数.
  >
  > 考虑一条边 $(x, y)$, 若不管这条边的限制, 则方案数为 $x$ 和 $y$ 颜色不同的方案数加上相同的方案数. 那么还需要把相同的方案数减去, 则直接将 $x$ 和 $y$ 合并成一个点即可. 故 $f(G, m) = f(G \setminus (x, y), m) - f(G', m)$, 其中 $G'$ 为合并 $x$ 和 $y$ 点之后的图. 边界条件为 $G$ 中一条边都没有, 方案数为 $m^{|G|}$.
  >
  > 考虑前者的方案数. 设 $g(G)$ 表示将无向图 $G$ 定向使得形成 DAG 的方案数.
  >
  > 考虑一条边 $(x, y)$, 若最后考虑这条边该如何定向, 则若 $x$ 与 $y$ 互相不可达有两种定向方式, 否则只有一种. 则可以变为删去这条边后的方案数 + 删去这条边后 $x$ 和 $y$ 互相不可达的方案数. 故 $g(G) = g(G \setminus (x, y)) + g(G')$, 其中 $G'$ 的定义同上. 边界条件同上, 方案数为 1.
  >
  > 不妨设 $f'(G, m) = f(G, m) \times (-1)^{|G|}$, 则 $f'$ 的边界条件方案数为 $(-m)^{|G|}$, 递推式为 $f'(G, m) = f'(G \setminus (x, y), m) + f'(G', m)$. 发现当 $m=-1$ 时 $f'$ 的边界条件与递推式与 $g$ 完全一致. 故 $g(G) = f(G, -1) \times (-1)^{|G|}$.
  </details>

- 求匹配方案数 (或别的需要记每个点的状态的问题) 时若图中边数较少, 则只需记后面还会用到的点, 可以大幅降低常数 (原来的 1% 左右). 其实差不多类似于一个每次枚举度数最大的点的状态然后把它删去的 Trick, 直到只剩环和链为止, 而且这个枚举度数最大的点的方法更优.

- 计数无向图的仙人掌子图可以用 Floyd 思想, 每次把多个连通块用 i 号点合并, 初始状态是所有的单个环. 需要使用子集 Exp. 点双/边双子图同理.

- SCC 可以划分为一个环然后每次加入一条端点在点集内, 其余点不在点集内的路径. 注意需要在路径的开头就钦定结尾是哪个点, 不然不知道有没有回来. 且会算重, 只能求解最优化问题.

# 20250108 代码源 9

https://qoj.ac/contest/1890 CDEFL
https://codeforces.com/contest/2057 FG

# 20250110 代码源 10

https://qoj.ac/category/341
