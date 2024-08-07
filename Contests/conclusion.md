> 20240111 - 20240116 没有写每道题的用时.

# 历史遗留

- **DP中需要枚举时, 将等于某个数改为大于等于/小于等于某个数可能更优.**
  
  **当值域过大时, 考虑能否排除不可能出现的值域.**
  
  例题(20230814 T3):\
  给定一个长为 $n$ 的序列 $a$ , 定义一个序列的完美度为任意两个数差的绝对值的最小值, 求该序列长度为 $k$ 的不一定连续子序列的完美度之和. 对 $998244353$ 取模.\
  $2 \le k \le n \le 10^3, 1 \le a_i \le 10^5$ .

  题解:\
  枚举完美度, 范围为 $\frac {kMaxV}{k - 1}$ , 考虑计算完美度大于等于该值的方案数. 设 $f_{i,j}$ 表示前 $i$ 个位置中选择了 $j$ 个, 且第 $i$ 个必选的方案数, $pre_i$ 表示当枚举的完美度为 $w$ 时, 满足 $a_{pre_i} + w \le a_i$ 的最大的 $pre_i$ . 则 $f_{i,j} = \sum_{k=0}^{pre_i} f_{k,j-1}$, 使用前缀和优化即可.

- **推式子时注意不要打错符号, 注意枚举的范围.**

  例题(20230814 T1):\
  给定长为 $n$ 的序列 $a$ , 将其分为 $left$ , $mid$ , $right$ 的非空三段, 令其代价为 $\max(sum_{left}, sum_{mid}, sum_{right}) - \min(sum_{left}, sum_{mid}, sum_{right}) + x \times mid$, 其中 $x$ 为给定的常数, 求最小代价.\
  $3 \le n \le 10^5$, 运算中每个数都不超过 $2^{63} - 1$ .

  题解:\
  不妨设 $sum_i$ 为序列 $a_i$ 的前缀和, $i$ 为 $left$ 与 $mid$ 的分割点, $j$ 为 $mid$ 与 $right$ 的分割点, $sum_{left} \le sum_{mid} \le sum_{right}$ .

  则 $sum_{left} = sum_i, sum_{mid} = sum_j - sum_i, sum_{right} = sum_n - sum_j$ .

  此时代价为 $sum_n - sum_j - sum_i + x \times j - x \times i = (sum_n - sum_j + x \times j) + (-sum_i - x \times i)$, 同时需满足 $sum_i \le sum_j - sum_i \le sum_n - sum_j$ , 即 $sum_i \le \min(\frac{sum_j}{2}, sum_n - sum_j)$ .

  从 $2$ 到 $n - 1$ 枚举 $j$ , 对于每个 $j$ 使用平衡树维护对应的区间最小值即可.

- **当出现绝对值时, 考虑枚举每一项的大小关系或正负性.**
  
  例题(20230814 T4):\
  给定 $n$ 个 $k$ 维的点, 定义 $n$ 个点间的权值为任意两点之间的曼哈顿距离的最大值. 在 $q$ 个询问中, 每次修改一个点的坐标, 或者查询编号 $[l, r]$ 间的点的权值.\
  $2 \le n \le 2 \times 10^5, 2 \le k \le 5, 1 \le q \le 2 \times 10^5$ .

  题解:\
  考虑每个点贡献的方式, 每一个维度要么为正数要么为负数, 则枚举每个维度的情况, 开 $2^k$ 棵线段树维护即可.

- **线段树使用动态开点时, 空间消耗要计算清楚, 否则就使用全局变量优化并开到低于空间限制25Mib.**
  
  例题(20230818 T2):\
  给定一个长为 $n$ 的序列 $a_i$, 定义一个查询 $(l_i, r_i, c_i)$ 代表在区间 $[l_i, r_i]$ 内, 严格跨越下标 $c_i$ 的相同值的点对的距离之和(每个值仅计算距离最小的).\
  $1 \le n \le 2 \times 10^5, 1 \le q \le 2 \times 10^5, 1 \le a_i \le 10^9$ .

  题解:\
  咕咕咕

- **准备乱搞前先考虑DP做法.**

  例题(20230818 T3):\
  给定通过 $n + 1$ 条路段的所需时间, 每两条路段间设有一个红绿灯, 全体红绿灯都从时刻 $0$ 开始以 绿 $g$ 秒 - 红 $r$ 秒循环的方式切换状态, 现有 $q$ 辆车分别于时刻 $t_i$ 穿越这些路段, 求完成穿越的时刻.

  题解:\
  考虑设 $f_i$ 表示在红灯切换为绿灯时通过第 $i$ 个红绿灯后穿越剩余的路段所需时间. 则有 $f_i=f_{nt_i} + dis_{i, nt_i} + wait_{i, nt_i}$ , 其中 $nt_i$ 表示下次被红灯挡住的红绿灯编号, $dis$ 与 $wait$ 显然容易求得. 从后往前遍历红绿灯, 使用平衡树维护红绿灯信息, 求区间最小值即可求得 $nt_i$ . 对于每个询问使用相同方法处理.

- **DP不了再考虑贪心做法.**
  
  例题(20230818 T4):\
  咕咕咕

  题解:\
  咕咕咕

# 20240111 总结

## T1(road) [竞赛图三元环] [扫描线]

期望:20 实际:20 难度:3

想到了容斥, 但卡在了出边指向的任意两个点间都有连边的性质上.

考虑容斥三元环并未用到完全图这一强性质, 每次思路卡住时应回过头观察已有条件.

## T2(graph) [费用流] [随机化]

期望:30+ 实际:50 难度:3

发现状态过于庞大, 大概只能用网络流.
费用流的建图不难想到, 发现这种模型只适用于二分图; 最终答案为森林不难想到.

考虑只适用于二分图的原因为无法考虑内部的连边, 于是只需保证答案的边均不在内部. 当确定思路的大体方向正确时, 考虑当前错误做法的原因并修正.

## T3(jigsaw) [链求和转子树求和] [莫比乌斯反演]

期望:24 实际:24 难度:4.5

考虑 $(a, b)$ 只有至多一种转移, 故形成树结构. 对于计数问题考虑变换求和顺序使得求和更为简洁.

注意到, 分段打表可以多拿24.

## 结算

前一天晚上没睡好, 晕了两小时. ~~但是睡眠时间比平时长1.5h~~

# 20240112 总结

## T1(key) [格点多边形内格点数量]

期望:100- 实际:23 难度:2

猜了一个显然错误的结论, 考场上竟然没有意识到.

凸包的部分容易想到. 考虑怎么计算多边形内格点数量.

根据 Pick 定理:

$$
格点多边形面积 = 内部的格点数量 + \dfrac{边界的格点数量}{2} - 1
$$

或许可以记忆为, 教室里的学生交学费, 挂墙上半价, 老师不用付.

其实也想到了 三角剖分 + 拆一般三角为直角三角, 但由于自我感觉实现过于复杂一直没有动手, 实际上写出来只有 2.7k .

## T2(hammer) [整体操作小范围考虑] [构造]

期望:5 实际:0 难度:5

将 字典序排名 转化回 排列 的过程出错了. 第一次写这玩意. 使用 ```map``` 可以容易避免这一错误.

对于一个允许你搞的很长很复杂的操作, 考虑一些特例使得操作变简单(对任意长度的连续段 -> 对长度为 3 的连续段).

对于要求构造方案且不好 Dp 的问题, 考虑将其的规模一步步缩减为子问题(如求 排列 的 字典序排名).

## T3(shoes) [非 Dp 类计数]

期望:38 实际:25 难度:3

$n = 20$ 的 $O(n^6)$ 做法, 由于没写 $O(1)$ LCA 导致多了一个 log , 最后 1min 大力手算 $n = m = 2$ 的情况, 结果由于题意记反而算错.

大体思路与题解一致, 缺少了部分细节与实现的时间. 考虑到 网格图 本身具有拓扑序, 无需进行 树形 Dp , 可降低实现难度.

## 结算

做 T1 时过于犹豫, 反而浪费了很多时间.

难写的保证正确性的算法 >> 不算好写的不保证正确性的算法 .

# 20240115 总结

## T1(matrix) [分治] [二维转一维]

期望:60 难度:3

大体思路与正解一致, 但由于特殊性质想到了循环节, 后发现去掉特殊性质后循环节不好做放弃.

对于一个二维不好搞的问题, 考虑将其归约至一维.

## T2(road) [三角剖分] [异或 Hash]

期望:10 难度:4

看到平面图边数为 $2n - 3$ 居然没想到是三角剖分.

对于一个复杂的构造问题, 考虑一种最简单的构造(如菊花图).

## T3(shoes) [神秘线段树]

期望:3 难度:4

主要是没有想到一个数能连的边很少, 但实际上即使这个常数为因数个数 $O(n^{\frac{1}{3}})$ 也是可接受的.

## 结算

做完 T1 60分后想冲正解, 结果浪费了大量时间(虽然也有 vp 的因素在).

# 20240116 总结

## T1(cheer) [树上差分] [枚举质因数求 Gcd]

期望:10 实际:5 难度:4

没有特判一堆东西.

求 Gcd 一类的东西时, 各质因数是独立的可以分别考虑, 只需已知一个数作为 Gcd 确定的倍数.
同时, 给一个数加上一个数比直接删掉一个数好做.

树上差分不仅可以差父亲, 也可以把儿子全差一遍.

## T2(memory) [二分答案] [圆内直线交点计数]

期望:15 实际:15 难度:3

圆内两直线有交点即对应的弧有交且不包含. 与圆有关的直线要转成弧(Pty 题单里 奶牛互相看见 那道题).

## T3(return) [根号分治] [分块] [类天使玩偶] [莫队]

期望:40 实际:32 难度:3.5

莫队中使用 树状数组 而未使用 值域分块 平衡复杂度.

对于一类暴力求需要维护很多信息($O(n)$ 这种)的题目, 除 莫队 外还有 分块 可以考虑.

## 结算

再次在 T1 上浪费了大量时间, 简直像是被外星人附体了.

找要开的题的一种方法: 挑一眼就会的部分分最多的. 并且, 若连续 30min 没有想出新的部分分, 弃掉换另一道题.

别再在老歪脖子树上吊死了.

# 20240117 总结

## T1(witch) [大型树形 Dp] [线段树合并]

期望:56 实际:60 难度:2 用时:3h

数据过水导致的.

对于 Dp 中需要统计子树内各类点的信息的一类问题, 若 分类的限制容易满足 且 统计的合并方式较简单(如直接求和) 但 不好直接由儿子继承, 则考虑线段树合并.

写 Dp 方程前一定考虑清楚每个状态代表什么.

## T2(tree) [边分治] [Kruskal]

期望:30 实际:30 难度:4 用时:1h

对于复杂的树上路径问题(即别的算法都想过了之后), 考虑点/边分治.

Boruvka 的思想并不局限于全程都要找最小的. 也可以对于一些神秘连通块做一遍, 最小生成树的边集 一定属于 得出来的边组成的边集.

## T3(string) [矩阵乘法] [循环匹配]

期望:0 实际:0 难度:4.5 用时:0.5h

看到 $id \le 10^{18}$ 居然没有想到矩阵乘法.

对于求 字符串 在 一个由一堆字符串拼接起来的大字符串 中的匹配, 考虑让这一堆字符串的长度都不少于模式串的长度, 这样至多只会跨越一个串, 可以大力分讨.

对于求 字符串 在 另一个字符串 中循环匹配的问题, 考虑复制一遍, 母串建 SAM, 找到每个位置作为结尾匹配的最大长度, 再一步步跳 fail, 累加 |endpos|.

## 结算

做出 T1 的 $O(n^2)$ 算法后, 及时放弃开写代码, 减少了时间浪费. 事实上, 观察代码不难发现线段树合并的优化.

# 20240119 总结

## T1(mulsign) [莫队] [分治]

期望:40 实际:40 难度:2 用时:2h

带有各种前缀和的式子不难推出, 想维护不难想到莫队.

在发现这玩意不好维护之后, 应及时回到最初的式子考虑别的思路. 事实上, 分治的想法是不难想到的.

用线段树维护一坨与 绝对位置/前缀和 等有关的东西时, 不要直接维护, 而是在合并两个区间时将右侧区间的上述值进行偏移, 可以极大降低实现难度与常数.

## T2(emotion) [贡献拆分] [子集卷积]

期望:0 实际:0 难度:4 用时:1h

考场上想到的是枚举 组成环的点集 并统计 每种方案的路径权值和, 但显然可以只枚举一条边统计作为基环树中环的方案数.

## T3(chorus) [笛卡尔树]

期望:25 实际:25 难度:4.5 用时:2h

笛卡尔树可以极大的降低思维难度, 当看到序列上可以离散化的问题时, 考虑用笛卡尔树辅助思考并描述条件.

Dp 时每个状态的转移的限制条件可以不用依次求出, 而是全部一起求完后再进行 Dp. 有时当前状态的限制可以用以前的限制辅助求出.

## 结算

做 T1 时思路陷入了死路, 当很久没有进展之后考虑向后回退一步考虑其他思路.

# 20240120 总结

## T1(a) [Nim 游戏]

期望:100 实际:100 难度:1 用时:1h

略.

## T2(b) [Dp 状态化简] [FWT]

期望:60 实际:60 难度:2.5 用时:2.5h

Or 卷积的点值表达式就是高维前缀和, 而 And 卷积为高维后缀和. 利用这一性质可以直接维护点值表达式, 而可以避免 FWT 与 IFWT .

对于限制较多的 Dp, 考虑先进行容斥消去一些限制, 如 20240117 witch.

## T3(c) [alcS] [分治]

期望:10 实际:10 难度:5 用时:1.5h

想了很久只想到了可以分治. 原来是论文题.

## 结算

T3 仍浪费了一定时间, 中途有大约 1h 的时间没有进展. 用来想 T2 应该能切.
(一样的还不一定能做到的考场策略此处不重复).

# 20240122 总结

## T1(physics) [组合数学]

期望:100 实际:100 难度:2.5 用时:2.5h

当发现做了碰球问题一步经典转化后无法做了之后及时重新调整思路.

最后化式子的时候居然没一眼看出来吸收公式多想了 10min .

## T2(vaguelette) [拆分贡献] [拉格朗日插值]

期望:10 实际:0 难度:4.5 用时:30min

想了 10min 没有想到 $F(T, a)$ 的求法. 实际上考虑一条边是否会有贡献是一个很经典的思路(如 20240119 emotion). 再想不到就要放首页了.

对于一个二维的 Dp 数组, 可以认为它是 $n$ 个多项式, 直接维护点值最后插值就可以求出所有 $Dp_i$ 的带权和.

## T3(partial) [分块]

期望:50 实际:50 难度:3.5 用时:2h

链的三分做法差不多想好了. 实际上可以二分. 并且与正解的思路相差很大.

对于数据结构不好维护的奇怪查询, 考虑对询问修改分块. 可以大力预处理, 但修改需要能够快速进行.

## 结算

T2 $m = 2$ 的暴力没有注意到无需枚举子序列和求 $F(T, a)$ , 感觉写不完且难调就放弃了, 遗憾少了 10pts.

# 20240123 总结

## T1(b) [多项式快速幂]
期望:100 实际:40 难度:2 用时:3h

写的 $O(q m^2 \sqrt n \log n)$ 的做法, 最后一个点稳定 1.046s . 预处理多项式的二的次幂就过了.

实际上, 若用到 $\sum m$ 为 $O(m)$ 级别的条件, 则可以消去 $O(\sqrt n)$ . 但当时感觉浪费了很多时间, 精神错乱之下没有想到这一做法.

## T2(c) [靶函数]
期望:33 实际:12 难度:5 用时:1.5h

把 $O(2^m)$ 的状态改成 $O(17 的拆分数)$ 的状态即可. 考场上估算拆分数认为是 $O(2^m)$ 级别.

对于一类求 庞大状态 简单转移 的期望问题, 考虑构造一个定义域较小的 势能函数 与 一个状态的势能, 使得当得知这个函数的点值后每个状态的势能容易计算, 且一次转移中 势能的期望变化与状态的期望变化一致, 则期望直接由势能给出.

## T3(d) [仙人掌上 Dp]
期望:30 实际:0 难度:3 用时:30min

没有时间写导致的. 难度主要集中在实现.

对于一些树上可做的搬到仙人掌上的问题, 考虑建立圆方树.

对于树上一个 $O(\sum_{x} \sum_{i \in Son_x} \min(m, nowsize_x) * \min(m, size_i))$ 的算法(带限制背包), 其均摊 $O(nm)$ . 具体证明可分类讨论 $nowsize_x$ 与 $m$ 的关系 及 $size_i$ 与 $m$ 的关系.

## 结算
T1 对于一个算法的复杂度计算错误, 并且不看模数就自信认为可以 NTT, 导致很快糊出一个优秀的假做法. 导致浪费时间心态变化精神错乱, 最终遗憾.

发现自己假了崩溃的时候, 做做别的题或者出去逛一圈清空脑子.

# 20240212 总结

## T1(nobody) [线段树]

期望:100 实际:100 难度:2 用时:2h

略.

## T2(thousand) [二分答案] [扫描线] [随机打乱]

期望:66 实际:0 难度:4 用时:2h

写了跟正解毫无联系的 $O(n^3\log^2 n)$ 做法.
由于精度误差被爆了.

对于一类求一个最小简单图形的问题, 考虑决定这个图形形状的特殊点(圆周上的点/三角形的顶点).

若一次二分会有 $O(n)$ 次独立的 Check, 则随机打乱后只需进行 $O(\log n)$ 次二分, 每次 $O(1)$ 次 Check.

## T3(christmas) [歌唱王国] [并查集] [搜索合法 Boarder]

期望:40 实际:15 难度:5 用时:1h

"数据与题面不符的, 以实际数据为准."

对于形如 $S$ 中至少出现一次 某个特定字符串 的方案数 Dp, 可以设 $f_i$ 与 $g_i$ 表示 $i$ 的前缀中恰好在结尾出现了这个字符串 与 没有出现这个字符串 的方案数.
其中包含了钦定的思想.

对于给定了若干组相等关系的序列计数问题, 使用并查集计算连通块数量.

若猜测某个集合很小但难以求出, 考虑一个每次转移较快的搜索. 可以从 如何判定某个元素是否在集合中 来推出 如何搜出这个集合.

## 结算
T1 的题面看的非常疑惑, 于是开始想 T2, 但第一步想错了方向, 没有回到最初的思路重新想.

对于看不太懂的题面, 多看几遍或手玩, 将题意形式化表述.

如果想了几步之后发现问题规约到一个简洁的难解问题, 考虑回退一步.

# 20240213 总结

## T1(string) [SAM] [线段树合并]

期望:100 实际:100 难度:3 用时:2h

一开始想的是对一个串求出它的最长 Boarder, 只能用 KMP.
事实上转换视角对于一个串求哪些串会以它作为 Boarder 之一更容易计算.
若枚举元素不好算答案, 就枚举答案反推元素.

在 SAM 上线段树合并维护 Endpos 好像还挺常见的, 之前好题宣讲讲过.

## T2(delete) [区间 DP] [拓扑序优化]

期望:80 实际:80 难度:3.5 用时:2h

对于一类转移保序的 Dp, 可以以 Dp 值为拓扑序, 类似最短路地转移(其实之前正睿也考过).
这里的保序是指, 较小的状态 所转移到的状态 都必然比 较大的状态 所转移到的状态 小.

## T3(rectangle) [容斥] [扫描线]

期望:20 实际:20 难度:4.5 用时:0.5h

想到了用 bitset 将 $O(n^3)$ 优化为 $O(\frac{n^3}{\omega})$, 但时间不够了.
也想过容斥, 但发现不会求三元环.

对于一类容斥问题, 想清楚自己可以限制什么, 对应的每项系数长什么样, 然后可以使用瞪眼法.
一般会把 "恰好" 容斥成 "至多/少" 或反向.

其中一类特殊的容斥问题是, 统计具有特殊性质的树形连通块(序列), 有 $点数 - 边数 = 1$, 则可以先统计点数次再统计边数次.

对于二维平面上的复杂偏序问题, 描述出需要统计的式子会方便思考.
~~想扫描线求度数的时候对着一张图想了很久, 下午对着一行式子马上糊出来了.~~

## 结算
开考 1h 后还没想出 T1(或者感觉自己没睡好神志不清), 这时可以先去把每道题的暴力都写了, 再回过头继续想.

# 20240215 总结

## T1(a) [矩阵快速幂] [矩乘优化]

期望:100 实际:100 难度:1 用时:0.5h

略.

## T2(b) [扫描线] [分块] [定期重构]

期望:40 实际:20 难度:4 用时:3h

第一步就跟正解不一样, 且在 $O(n\sqrt n\log n)$ 的做法中使用了常数极大的 FHQ Treap 而不是 动态开点线段树, 导致跑不过朴素暴力.

对于一类 区间修改 单点查询历史值附带属性 的问题, 考虑离线用扫描线解决.

## T3(c) [颜色段均摊] [分治] [扫描线] [李超树]

期望:30 实际:0 难度:4.5 用时:1h

线段树维护值域最近点对时, 若存在两个相等的值, 答案忘记置 0.

若给定 $O(n)$ 个带权区间, 一个区间的权值是这些区间中被包含的那些的权的 min/max, 则所有区间构成 $O(n)$ 个相同权的矩形.
使用颜色段均摊容易求出.

对于 修改较多 查询较少 的问题, 考虑对于所修改的序列进行分治.

## 结算

似乎没有只能用 Treap 做的东西.

在 T2 上浪费了较多时间卡常与优化, 事实上优化了半小时后就应果断放弃而去拼 T2 部分分 和 思考 T3, 能够节省 1h.

# 20240216 总结

## T1(factory) [树形 Dp]

期望:50 实际:20 难度:3 用时:4h

$O(n^4)$ 正解没有调出来.

对于带权的方案数背包, 考虑将权带进状态中.

一棵树的拓扑序个数是 $\frac{n!}{\prod size}$.
对于一个多带一些限制的类似问题, 可以考虑规约到平凡问题并让方案带上相关信息.

## T2(magic) [网络流]

期望:5 实际:0 难度:4 用时:0.25h

大脑短路直接输出 $0$ 导致的, 事实上贪心显然.

对于数据范围在 $[10^2, 10^3]$ 范围的, 不存在 Dp 解法的最优化问题, 考虑最大流/最小割.

建模可以先根据所设的局面表示出答案再考虑.
若最后的式子不好建模, 考虑修改局面中部分变量的定义.

## T3(set) [莫队] [分块] [并查集]

期望:12 实际:8 难度:5 用时:0.25h

暴力求 mex 的时候枚举上界小了.

对于区间查询的元素出现性问题, 都可以使用 $p_{v, i}$ 表示 $i$ 之前第一个值为 $v$ 的位置等类似的东西来转化.

带修的主席树可以用分块变成 $O(\sqrt \frac{n}{\log n})$ 棵动态开点的线段树.

## 结算

死磕 T1 老毛病了(不是)

准备死磕之前先打好暴力.

# 20240218 总结

## T1(fst) [平分权值]

(没做出来) 用时:1.5h

对于一类 左侧每一项都相似, 右侧是一个常数 的不等式限制, 考虑将这个常数分摊到每一项中, 限制变为只与某一项相关的与 $0$ 的大小关系, 但是时间多个 $\log$.

## T2(game) [树上路径拆成两条] [FWT]

(做出来了) 用时:0.5h

略.

## T3(?) [生成函数]

(不会且一眼弃) 用时:0h

不会.

## 结算

vp 场.

T1 真的不一定比 T2 简单. 用时过于长之后要果断弃掉, 尤其是在没有好的思路时.

# 20240219 总结

## T1(why) [构造]

期望:100 实际:100 难度:1 用时:1.5h

略.

## T2(noip) [分类讨论] [斜率优化] [猫树分治]

期望:30 实际:0 难度:3.5 用时:2h

考场上糊了一个 $O(n^2)$ 假做法, 没写数据分治.

强调很多遍了, 把要求的式子列出来再考虑怎么维护.
图形有的时候不能涵盖所有情况.

区间查一个难以合并的东西可以离线下来猫树合并.
若强制在线但某一端点具有单调性, 可以使用二进制分组.

斜率优化在 x坐标单调性 与 下标单调性 不同时, 凸壳的方向与二分的方向要格外注意.

## T3(noforce) [深度和转子树和] [高斯消元] [中国剩余定理]

期望:40 实际:30 难度:5 用时:1h

转移方程的小错误, $i$ 不一定会转移到 $i + a_i$, 需要拿个数组记录.

求贡献时可以转换视角(如 20240111 T3 jigsaw).

若高斯消元时有一些项不是多项式, 考虑枚举不同情况来化简这些项, 并得到若干限制条件.

若要求很大的数又不想写高精, 可以用多个模数分别算出答案再用中国剩余定理.

~~事实上题解并没有看懂.~~

## 结算

最后 20min 用来想怎么把 T3 优化一个 $\log$, 但实际上想到了也不一定写得出.
正确的策略是把数据分治写了.

# 20240221 总结

## T1(isomorphism) [树同构] [Dinic二分图匹配]

期望:100 实际:100 难度:2 用时:2.5h

Dinic 跑二分图匹配的时间复杂度为 $O(m\sqrt n)$, 具体证明可以分类讨论增广轮数与 $\sqrt n$ 的关系.

树哈希可以用来解决树同构问题(虽然这次没有用到且考场上不会), 具体哈希式子为

$$ Hash_x = Size_x \times \sum_{i = 0}^{Son_x - 1} Hash_{Son_{x, i}} \times Prime^i $$

其中 $Prime$ 为一个质数常量. 特别地,
$$ Hash_x = Prime (x \in Leaf) $$

## T2(art) [贪心] [FFT]

期望:100 实际:70 难度:1 用时:2h

当值域为 $[10^9, 10^{18}]$ 级别时, FFT 需要使用 long double. 同时, FFT 数组需要开 $4$ 倍.

IDFT 所使用的矩阵, 其每个元素都与 DFT 矩阵的对应元素 **共轭** .

## T3(path) [点分治] [分类讨论] [可持久化带权李超线段树]

期望:0 实际:0 难度:4.5 用时:0h

并没有时间想.

对于一类路径不交的问题, 可以枚举分界点.

对于一类查询 $A \times F(x) + B \times G(y)$ 的问题, 其中 $A$ 与 $B$ 为定值, 考虑计算出 $F(x)$ 与 $G(y)$ 后维护凸包.

李超线段树的下标可以不连续(带权), 使用离散化即可.

## 结算

FFT 的板子没有背好, 共轭的那里调了 1h.

# 20240226 总结

## T1(dream) [容斥] [狄利克雷差分]

期望:60 实际:60 难度:2.5 用时:3h

难点在于不去想莫比乌斯反演.
该做法需要用到魔力筛 ($O(n)$ 计算 $g = \mu * f$).

想求 $Lcm$ 恰为 $i$ 的方案数一般会先求 $Lcm | i$ 的方案数.
想求 $Gcd$ 恰为 $i$ 的方案数一般会先求 $i | Gcd$ 的方案数.
求出前者后, 可以类似地求出 $Lcm$ 恰为 $i$ 且 $Gcd = 1$ 的方案数, 其中 $Gcd = 1$ 是一个很强的性质.

## T2(wind) [逆排列] [多项式卷积] [卢卡斯定理]

期望:70 实际:50 难度:3.5 用时:1h

这道题 $O(n^4)$ 可以过 $1000$, 但没开滚动数组导致跑不了 $n > 100$.

非对合排列可以与其逆排列一一对应, 其中对合排列为 $p_{p_i} = i$ 的排列.
在模 2 意义下对对合排列计数相当于对排列计数.

排列的逆序对个数与其逆排列的逆序对个数相等 ($i < j \space \land \space p_i > p_j \Rightarrow p_j < p_i \space \land \space j > i$).

前缀和可以看作乘以 $\dfrac{1}{1-x}$, 由此可以进行快速幂或交换律.

有卢卡斯定理:

$$ {n \choose m} \equiv {\lfloor \frac{n}{p} \rfloor \choose \lfloor \frac{m}{p} \rfloor} \times {n \bmod p \choose m \bmod p} \pmod p $$

由此, 有推论:

$$ {n \choose m} \equiv [n \And m = m] \pmod 2 $$

## T3(snow) [容斥] [观察力] [合同变换]

期望:15 实际:15 难度:4.5 用时:0.5h

对于一些比较简单的限制, 考虑合法状态与非法状态的关系, 并将限制容斥掉 (考虑非法状态的总数或与合法状态的和差).

对于一些复杂的贡献计算方式, 考虑分类讨论其贡献的组成部分以得到更多性质.

## 结算

T1 依然死磕一个想法.

对于每道题都尽量不让空间成为瓶颈.

T3 的特殊性质我全程在打表找规律而没有手推式子.
以后可以先推 10min 再考虑找规律.

# 20240227 总结

## T1(can) [找规律] [圆反演]

期望:80 实际:60 难度:2(卡知识点题) 用时:2h

脑抽忘记写另外的一个 Sub.

对于有一堆相切的平面几何题, 考虑用圆反演.

一个圆反演后还是圆, 但若其过反演圆的圆心, 会变成一条直线.

## T2(circle) [观察力] [主席树二分]

期望:30 实际:30 难度:3 用时:0.5h

对于一类有以前从来没见过的没有一点想法的问题, 考虑手造手玩一些样例.

对于区间内的与值相关的问题, 考虑主席树.

## T3(adventure) [最优化 Dp] [前缀/后缀 max 优化]

期望:64 实际:100 难度:2(n^4) 3.5(n^3) 用时:2h

$O(n^4)$ 的常数过小没被卡掉. 本地 3.3s OJ 0.4s.

极好的一道 Dp 题 (赞赏).

考场上没有将方程形式化描述, 导致思维比较混乱.

由于对于 收集型 Dp 的优化方法 多于 对于 扩散型 Dp 的优化方法, 对于一类 转移到的状态 与 当前状态和转移本身 之间不可逆 (下标带有 max/min 之类), 于是看似只能使用扩散型的 Dp, 考虑在枚举完 拓扑序对应维 之后立即枚举 转移, 并利用分类讨论使转移变得可逆, 同时得到一些对其他维度的限制. 这时由于转移可逆, 可以使用收集型来进行优化.

类似地, 对于一类转移数量极多但最优转移较少的 Dp, 显然需要利用某些方法求出这些最优转移再转移, 此时同样可以先枚举转移再枚举其他维, 得到一些对其他维的限制.

## 结算

写完一道题的代码之后, 再检查一遍有没有 Sub 忘记写了.

形式化描述一个局面或者一个方程是重要的.

# 20240228 总结

## T1(blocks) [线段树]

期望:40 实际:0 难度:3.5 用时:2h

枚举值域的循环上界错误地写了 $n$.

对于一类维护区间之间的相互关联的附带信息的数据结构, 考虑使用线段树.

线段树上维护区间之间的相交相离性, 考虑维护 $nt_i$ 表示有多少个区间跨过了 $[i, i + 1]$ 间的分界线.

对于线段树结点上一些进行区间操作会被推平, 但逆操作之后又需要还原的信息, 显然不能直接维护. 考虑分别维护推平前和推平后的信息, 合并左右儿子时分类讨论即可.

## T2(reset) [期望 Dp]

期望:20 实际:20 难度:4 用时:1h

对于一类转移与集合 $S$ 中的一个特殊元素 $x$ 有关, $S$ 中插入一个元素后 $x$ 的变化方便维护, 但若把当前 $x$ 删掉其变化唯一但不好维护的 Dp, 直接做必须维护整个集合. 考虑设计状态时钦定 $x$ 之后必须一直在集合中, 则终止状态会多出一个 $x$ 被删掉, 会多一个 Dp 数组, 转移时注意即可.

事实上, 此类 Dp 可以视作后继确定前驱唯一但未知的树上 Dp. 若其方程为线性组合的形式, 对于一个集合 $S$, 若其能转移到 $T$, 必然有 $f_T = f_S * k_T + b_T$. 将这个式子代入原来的 Dp 式子即可求出 $k_T$ 和 $b_T$ 的方程, 手解即可得到递推式. 对于一个 $T$, 还原出 $f_T$ 是容易的, 可以视作不断往根上跳, 同时维护对应项系数. 两种方法分别得到的两个 Dp 状态及方程是完全一样的.

## T3(triples) [贪心] [模拟网络流]

期望:20 实际:20 难度:4.5 用时:1.5h

对于一类最优化问题, 若其有显然的上下界, 考虑利用该界得到更多性质 (如 [U369223 集卡游戏](https://www.luogu.com.cn/training/393133#problems)).

模拟网络流一般会将网络流转化为最小割, 然后考虑一组解可能的形态.

## 结算

想 T1 的时候脑子非常混乱, 一直在想按左端点排序, 应该先把 T2 和 T3 的暴力写了再回来想的.

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

# 20240330 总结

## T1(kanzenkankaku) [贪心]

期望:65 实际:50 难度:3.5 用时:2.5h

01 串的部分分没有写出来. $O(n^3)$ 的做法与正解没有一点关系.

对于一个暴力的枚举做法, 若时间复杂度已经很优 (如多项式级别), 考虑变换视角 (即更换枚举的东西) 使得最后一维可以用数据结构维护.

## T2(retribution) [观察力] [缩点]

期望:30 实际:30 难度:3 用时:1h

对于二维平面上的连通块相关问题, 考虑连通块的性质 (是否为一个矩形).

## T3(medrcy) [逻辑] [最小点覆盖]

期望:0 实际:0 难度:4 用时:1h

如之前强调的很多遍, 要将题意用式子形式化表达出来.

## 结算

T1 花费的时间太多了, 本应去想 T3 的. 30 min 没有进展时就应当换题.

# 20240401 总结

## T1([a](https://pjudge.ac/problem/21633)) [期望 Dp]

期望:0 实际:0 难度:4.5 用时:4.5h

事实上, 这道题与 20240228 T2(reset) 并不类似, 考场上以为是一样的做法. reset 的状态构成一棵树, 但这道题的状态构成一张 Dag (证明如 $\sum 3^{a_i}$ 单调递增), 且前驱有多个, 如: ![](https://cdn.luogu.com.cn/upload/image_hosting/30vgmilt.png).

考虑从初始状态开始的若干特殊状态. 如 空/满且底部为 $x$/只有一个 $x$. 状态与转移可以围绕这些特殊状态设计.

## T2([b](https://loj.ac/p/3483)) [观察力]

期望:0 实际:0 难度:4.5 用时:0.25h

并没有开.

无向图上若从 $s$ 节点走 $i$ 步能到达 $x$, 则 $i+2$ 步同样也能到达 $x$. 故这一集合可以变成两个数 (奇偶最短路).

## T3([c](https://loj.ac/p/2468)) [不会]

期望:0 实际:0 难度:5 用时:0.25h

同样没有开.

## 结算

考试策略有问题. 事实上 T1 的 60pts 是好拿的, 可以有时间开后面的题.

T1 在知道正解后仍调了 3h. 需要加强期望 Dp 的实现.

# 20240402 总结

## T1([a](https://qoj.ac/contest/1057/problem/5171)) [平衡树优化 Dp]

期望:100 实际:100 难度:2 用时:2.5h

对于最优方案的方案数统计， 考虑求出最优化属性数组后用同样的方法计算. 可以少带一个最优化属性的维度.

## T2([b](https://contest-archive.loj.ac/contest/7/problem/2)) [树链剖分] [动态 Dp]

期望:23 实际:23 难度:4 用时:1.5h

降低复杂度的一种思路是, 考虑自己的几层枚举中有哪些受输入信息影响较少. 如枚举 $\ge x$ 的数显然比枚举实际方案与输入方案的 LCP 受影响更小.

树链剖分时, 若需要更新的附带属性与所有儿子都相关, 考虑根据 BFS 序开一颗线段树来维护.

## T3([c](https://uoj.ac/contest/64/problem/656)) [Trie 树] [差分] [哈希]

期望:7 实际:7 难度:4.5 用时:1h

对于一类字符串的拼接的匹配问题, 若不好转化成只会在某一个字符串内部或至多跨过一条边界的情况, 则仍需考虑暴力匹配并维护匹配到达的结点.

如 20230112 T4(奇妙能力歌), 一条 $S$ 从 Trie 树上结点 $x$ 出发的匹配路径可以被规约到深度更浅的 $y$ 出发的路径.

## 结算
考试的最后一个多小时脑子一直不清楚. 大概率是没有睡好.

# 20240403 总结

## T1([a](https://www.luogu.com.cn/problem/P9546)) [博弈论] [线段树]

期望:100 实际:100 难度:1 用时:1h

略.

## T2([b](https://loj.ac/p/4019)) [分治] [欧拉路径]

期望:60 实际:15 难度:2.5 用时:3.5h

流的建模出现了小问题. 对于一类需要有下界的网络流, 应当将流量设为下界, 并新建一个点来吸收上下界之间的流量. 而不是简单的将流量设为上界.

对于一个长为 $2^k$ 的序列, 优先考虑分治, 其次再是多项式与倍增.

分治的过程可以理解为将一个长为 $S$ 的序列变成了 $\log_2S$ 个长为 $2$ 的序列.

对于一类要求将一些元素分为大小相差不超过 $1$ 的两部分的问题, 使用网络流是愚蠢的. 使用欧拉路径是明智的.

## T3([c](https://loj.ac/p/4018)) [转化操作] [分类讨论]

期望:10 实际:0 难度:5 用时:0.5h

事实上, 防御力有可能降到 $0$, 因此循环的下界应是 $0$.

对于一类有固定攻击力与防御力的问题, 考虑将 己方攻击力 -= 对面防御力, 则攻击时无需考虑防御力的问题, 减防操作变成加攻击操作.

## 结算

事实上想 T2 Sub2 ($S = 2$) 时想到了欧拉路径, 但是并没有意识到可以在分治过程中同样使用. 当前面的 Sub 做法在后面没有任何用处时, 不妨回过头好好想想.

# 20240404 讲[题](https://www.luogu.com.cn/paste/jxb7b3lp)总结

- 计算 $\prod (1 - a_ix)$ 或 $\sum \frac{b_i}{1 - a_ix}$ 可以用分治 NTT. $O(n\log^2n)$.

- 对于一个生成函数的单项求值可以考虑按奇偶分类并使规模减半.
  
  如给定 $a_{[1,k]}$ 与 $b_{[1,k]}$, 求 $b_n = \sum_{i = 1}^k a_i b_{n - i} \space (n > k)$, 则有 $\sum_{i = 0}^k a_i b_{n - i} = 0 \space (a_0 = -1)$.
  
  故 $A(z) * Ans(z) = B(z)$, 其中 $A(z) = \sum_{i = 0}^k a_i z^i$, $B(z) = \sum_{i = 1}^k b_iz^i$, $Ans(z) = \sum_{i = 1}^\infty b_iz^i$.

  那么 $Ans(z) = \frac{B(z)}{A(z)} = \frac{B(z) * A(-z)}{A(z) * A(-z)}$. 设 $C(z^2) = A(z) * A(-z)$, $D(z^2) + z * E(z^2) = B(z) * A(-z)$, 则 $Ans(z) = \frac{D(z^2)}{C(z^2)} + z * \frac{E(z^2)}{C(z^2)}$, 从而可以分类讨论 $n$ 的奇偶性来只考虑右侧式子的前项或后项. $O(k\log k\log n)$.

- 转置原理: 对于一个算法, 若其可以处理输入一个矩阵 $[X]$, 输出矩阵 $[Y] = [A] * [X] \space ([A]$为常量$)$, 则必然可以处理输入一个矩阵 $[Y']$, 输出矩阵 $[X'] = [A^T] * [X]$.
  
  体现在具体实现上为将所有的操作转置并将顺序反向.

- LGB Lemma: 对于两条路径 $i \rightarrow l$ 与 $j \rightarrow k$, 满足 $i$ 在 $j$ 的左侧, $k$ 在 $l$ 的左侧, 若必然有这两条路径交叉, 那么对于 $|L| = |R| = n$ 的两个点集之间对应有路径且不交的方案数为 矩阵 $A_{i, j} = (L$ 中 $i$ 号元素到 $R$ 中 $j$ 号元素的路径条数$)$ 的行列式.

- 子集卷积: 若要计算
  $$C_{S} = \sum_{I \cup J = S, I \cap J = \varnothing} A_I B_J$$

  考虑条件等价于 $I | J = S, |I| + |J| = |S|$, 故按 PopCount 将下标分为 $n$ 组, 每组之间两两进行 Or 卷积. $O(2^n n^2)$.

- 子集 Exp: 从 $1$ 到 $n$ 递推, 每次枚举一个最大值为 $i$ 的集合并与之前得到的结果做子集卷积. $O(\sum_{i = 1}^n 2^i i^2) = O(2^n n^2)$.

# 20240407 总结 & [解](https://www.luogu.com/article/ybti3sqj)

## T1([a](https://www.luogu.com.cn/problem/U415120)) [线段树] [扫描线]

期望:50 实际:50 难度:4 用时:1.5h

对于一类线段树上维护 值为某定值的位置数 的问题, 考虑该定值是否同时为可能取到的最小 (大) 值, 则可以维护 最小 (大) 值 与 数量.

## T2([b](https://www.luogu.com.cn/problem/U415121)) [计数 Dp] [容斥] [多项式]

期望:65 实际:65 难度:3 用时:2.5h

同 HNOI Day1 T3 (wormhole), Dp 方程列出来后可以考虑其的实际意义来优化.

**对于一个总和确定的序列, 本质不同的元素只有 $O(\sqrt n)$ 种. 远古时代会的东西现在不会了, 哈哈.**

### 多项式取模 
给定最高项次数分别为 $n$ 和 $m$ 的多项式 $F(z)$ 和 $G(z)$, 求最高项次数分别为 $n - m$ 与 $m - 1$ 的多项式 $Q(z)$ 与 $R(z)$, 使得

$$F(z) = Q(z) G(z) + R(z).$$

考虑定义最高项系数为 $n$ 的多项式 $F(z)$ 的转置

$$F^T(z) = z^n F(\frac{1}{z})$$

即 reverse 每一项的系数. 有

$$F(z) = Q(z) G(z) + R(z)$$

$$z^n F(z) = z^{n - m} Q(z) z^m G(z) + z^{n - m + 1} z^{m - 1} R(z)$$

$$F^T(z) = Q^T(z) G^T(z) + z^{n - m + 1} R^T(z).$$

因为 $Q^T$ 的最高项系数为 $n - m$, 则

$$F^T(z) = Q^T(z) G^T(z) \pmod {z^{n - m + 1}}.$$

$O(n \log n)$

### 多项式多点求值

给定最高项次数为 $n$ 的多项式 $F(z) = \sum_i f_i z^i$ 与长为 $m$ 的序列 $a$, 求 $F(a_i)$.

考虑 $F(z) = F_i(z) * (z - a_i) + ans_i$, 则只要对每个 $i$ 求出 $F(z) \bmod (z - a_i)$ 的值即可. 考虑分治取模, 左边每次模 $\prod_{i = l}^{mid} (z - a_i)$, 右边同理. $O(n \log^2 n)$ ~~或许可以利用 class 20240404 转置原理, 但我还不会.~~

## T3([c](https://www.luogu.com.cn/problem/U415119) 或 [月球车站](https://uoj.ac/problem/683)) [不会]

期望:30 实际:5 难度:5 用时:1h

分类讨论时漏了情况. 不收敛的情况判断错误.

对于一类分数需要取模且需要取 $\max$ 的问题, 若有关的数很小, 不用手写分数类而考虑同时维护 double 与 long long.

对于一类 DAG 博弈问题, 必胜点的后继中存在一个必败点, 必败点的后继全是必胜点, 否则是平局点. 从确定状态的非平局点开始 BFS, 队列里只放非平局点, 必胜点则判断每个前驱的后继是否都是必胜点, 必败点则将每个前驱设为必胜. 剩下的点都是平局点, 每个非平局点的步数为更新它的点的步数 + 1.

对于一类随机博弈的步数期望问题, 考虑最优博弈的决策与步数.

## 结算

~~总体上没有出现太大的失误, 但 T3 没有想到一个显然的技巧就开始写分数类有些不应当.~~

总体上出现了巨大的失误, 且 T2 没有想到一个显然的技巧极不应当, 贺知章一样.

# 20240408 总结

## T1([se](https://www.luogu.com.cn/problem/CF1610G)) [贪心] [Dp] [栈]

期望:30 实际:30 难度:1 用时:3h

若贪心想了超过 30min 且不确定是否一定是贪心, 继续想是愚蠢的. 即使对于总问题的 **部分** 情况有一定正确且优秀的做法.

若 Dp 的结果中只有最后一项会有用, 则可以只维护当前的 Dp 状态及对应的最优化属性. 用可持久化数据结构是愚蠢的.

若一个序列只用查后缀的信息, 弹出/插入 最后一个位置, 则可以用栈. 用线段树是愚蠢的. 用平衡树是更加愚蠢的.

综上, 在贪心中使用可持久化平衡树是极度愚蠢的. 尽管我仅仅是想了一个贪心做法与一个可持久化平衡树做法.

## T2([cover](https://www.luogu.com.cn/problem/CF1774G)) [奇偶分类] [区间包含关系] [倍增] [分讨]

期望:40 实际:40 难度:3 用时:1h

对于计数类似 奇数 - 偶数 的东西, 可以考虑一个元素是否有贡献来抵消. 同样可以考虑 LGV Lemma (因为里面有一个 $(-1)^{逆序对个数}$).

## T3([break](https://www.luogu.com.cn/problem/CF1842I) & [解](https://www.luogu.com.cn/api/team/downloadFile/x6u23kff)) [观察力] [分治]

期望:25 实际:25 难度:5 用时:1h

对于一类 $O(n^2)$ 状态 $O(1)$ 转移的方程, 考虑将其写成 $O(n)$ 状态 $O(n)$ 转移的形式. 即使原方程已经可以 $O(n \log n)$ 求, 后者也可能通过单调队列实现 $O(n)$.

对于一类环上问题, 若时间不允许断环成链, 则考虑随意断一条边然后调解.

调解的常用思路是考虑 两组最优解之间的关系/最优解与次优解的关系.

若有所有最优解的元素数量相等, 并且某一最优解的两元素中间有且仅有一个元素 (指数量而非特定元素) 会出现在其他最优解中. 可以考虑对最优解的第一个元素所在区间进行分治, 每次求出第一个元素固定为 mid 时的解, 则每个元素都能递归下去.

## 结算

吾有三罪:

- 先想贪心不想 Dp.

- 贪心找出所有需要的结论之后对于一个显然能 Dp 的问题 硬贪.

- 想到一个 $O(n^2)$ 做法之后无脑堆数据结构.

综上, 晚上要早睡.

# 20240409 总结

## T1([a](https://loj.ac/p/4139)) [Bitset] [倍增]

期望:30 实际:30 难度:3 用时:2h

思路与正解最偏离的一集. ~~容易转化为一个只能暴力求解的问题, 然后不会做.~~ 事实上大家都利用 ``bitset`` 将这个暴力求解的问题草过去了 (悲伤). ~~为什么我赛后还草不过去.~~

使用线段树合并/启发式合并时, 若一棵线段树/``set``会被多次合并 (即对其他多个线段树/``set``有贡献), 则复杂度是错的, 即使合并次数仍是常数. 原因是直到最后一次合并前线段树与``set``都需要复制, 会打破均摊的复杂度分析.

当想用 ``bitset`` 草题的时候, 通常空间的限制会紧于时间, 此时一种可行的策略是减少维护的状态量, 但是多做几遍 (如从 维护长度为 $n$ 的信息 & 做 $1$ 遍 变成 维护长度为 $16384$ 的信息 & 做 $\lceil\frac{n}{16384}\rceil$ 遍).

对于转化后的问题, 如果不好求解, 考虑回退一步 (如 20240119 T1 mulsign).

对于一个显然的做法, 考虑其错误 (算重) 的原因, 并尝试规避 (减) 掉.

如果一道题直接想复杂度正确的做法想不出, 考虑先想一个 **简单** 的复杂度较劣的做法. 此处的简单指可以容易形式化表述从而进行优化.

对于一类要对所有元素求相同附带属性的静态可合并 (或可分拆成多个可合并信息) 问题, 考虑使用倍增.

对于一类区间问题, 常用的两个思路是考虑左右端点能否分别处理 和 考虑具有包含/相交关系的两个区间之间的性质.

## T2([b](https://www.luogu.com.cn/problem/P9924)) [构造] [分讨]

期望:82 实际:82 难度:2 用时:2h

不难想到距离正解很近的做法.

对于一类限制了某些属性的上界的构造题, 考虑已有的构造方案在哪些情况下才会寄, 从而得到设计新方案时能用到的性质.

## T3([c](https://www.luogu.com.cn/problem/U416909)) [博弈论] [分讨]

期望:28 实际:44 难度:2.5 用时:1h

数据水了.

对于在一条链上有的结论, 务必将其扩展到树上.

对于博弈论中已经有了的必胜局面, 若 Sub 中每个都给了强烈的暗示, 则可以自信剩下的情况都必败.

## 结算

T1 卡了 45min 就去想 T2 了, 最会亡羊补牢的一集. 但应该更早的回退思路或直接开始想 ``bitset`` 做法.

# 20240427 总结

## T1(maze) [数学]

期望:60 实际:50 难度:3 用时:4h

形式化表述要求的东西. 对于一类求参数 $x$ 的最小值使得每个量 $f$ 都为整数的问题, 若每个 $f$ 都正比于 $x$, 则可以表示出 $x = 1$ 时每个 $f$ 的值并据此直接求得 $x$ 的式子.

令 $F_p(n)$ 表示 $n$ 中含有质数 $p$ 的幂数, 则 $F_p{n + m \choose n}$ 是 $p$ 进制下 $n + m$ 的进位次数.

<details>
<summary>Proof</summary>

$$F_p(n!) = \sum_{i \ge 1} \lfloor \frac{n}{p^i} \rfloor$$
$$F_p{n + m \choose n} = \sum_{i \ge 1} \lfloor \frac{n + m}{p^i} \rfloor - (\lfloor \frac{n}{p^i} \rfloor + \lfloor \frac{m}{p^i} \rfloor)$$

则第 $i$ 项只能取 $0$ 或 $1$, 取 $1$ 当且仅当第 $i - 1$ 位发生 向第 $i$ 位的进位.

</details>

当 $p = 2$ 时, 该值即为 PopCount$(n \oplus m \oplus (n + m))$ 或 PopCount$(n)$ + PopCount$(m)$ - PopCount$(n + m)$.

<details>
<summary>Proof</summary>

不进位加法与进位加法的差距 或 进位一次少一个 1.

</details>

可以用以下代码 $O(\log \log n)$ 求 PopCount. 思想为类似线段树的 Pushup.

<details>
<summary>Code</summary>

```c++
#define LL long long

int PopCount(LL x) {
  const static unsigned LL w = -1, w0 = w / 3, w1 = w / 5;
  const static unsigned LL w2 = w / 17, w3 = w / 257;
  const static unsigned LL w4 = w / 65537, w5 = w / 4294967297;
  x = (x & w0) + (x >> 1 & w0);
  x = (x & w1) + (x >> 2 & w1);
  x = (x & w2) + (x >> 4 & w2);
  x = (x & w3) + (x >> 8 & w3);
  x = (x & w4) + (x >> 16 & w4);
  x = (x & w5) + (x >> 32 & w5);
  return x;
}
```

</details>

## T2(city) [不会]

期望:0 实际:0 难度:5 用时:0.25h

## T3(color) [不会]

期望:0 实际:0 难度:5 用时:0.25h

## 结算

最后 30min 一定要把自己会的分拿完, 不要再冲正解. 不要被别人影响.

# 200240505 总结

## T1(party) [二分答案] [点分治]

期望:50 实际:50 难度:2 用时:3h

对于一类树上求距离一个点小于等于 $x$ 的点数, 考虑点分治. 其本质上是从一个点引出的 $n$ 条链.

## T2(string) [哈希] [后缀排序]

期望:60 实际:60 难度:3.5 用时:1h

对于字符间没有区分的字符串判等问题, 除 `将第一个出现的字符标 1, 第二个标 2 , 以此类推` 之外, 还可 `维护每个位置上一个同样字符的位置, 用这个数组的全等来判等`.

一个字符串的本质不同连续字串数量除几种经典的 Dp 以外, 还可由 $\frac{n(n+1)}{2} - \sum_{i = 1}^{n - 1} height_i$ 求得. 证明显然, 适用于动态且无法 DDP 的问题.

## T3(village) [观察力] [不会]

期望:5 实际:5 难度:4.5 用时:1h

一张混合图中为每条无向边定向, 保证总有方法最后得到一个 SCC, 则判断一条无向边能否朝一个方向连边的方式为 `钦定它是对应方向的有向边, 将其他无向边看作两条有向边后图是否是 SCC` .

## 结算

T1 经典想了一个显然错误的结论并进行了实现. 成功浪费 2h. 人类退化史.

真的要提升自己找反例与猜结论的能力了.

T2 考场上搓了一个跟后缀排序做的事情一模一样的 $O(n^2)$, 但是没有意识到是后缀排序. 或许以后的优化思路又多了考虑用已有算法替换一部分过程.

# 20240506 总结

## T1(soulist) [期望] [离散化]

期望:24 实际:16 难度:3.5 用时:2.5h

**我是傻逼.**

- `cout << Ask(l, r) << '\n'` 应为 
  
  `cout << Ask(l, r) % kMod << '\n'`.

- `if (n <= 19 && m <= 19 && 0) {` 应为

  `if (n <= 19 && m <= 19) {` .

对于一类修改与查询都只与相对大小关系有关的期望问题, 考虑维护 $P(a_i < a_j)$. 事实上是一种另类的离散化, 因此时间复杂度不应与 $n$ 有关.

## T2(whiteqwq) [Ex GCD] [Ex CRT] [不会]

期望:12 实际:8 难度:5 用时:1.5h

没有写完, 但神秘地得了 8pts. 事实上, 输出 $n$ 有 20pts.

一类字符串匹配算法无需一定是相同匹配. 以 Manacher 为例, 只需满足回文内部一边有回文另一边对应位置也必然回文即可. Ex KMP 则只需满足等号有传递性即可. 事实上后者用的不多.

## T3(beautiful) [观察力] [分块打表] [Min_25 筛]

期望:60 实际:60 难度:2 用时:1h

求解一个前缀有多少质数可用 Min_25 筛.

打表时为缩短代码长度有如下技巧:

- 打表的内容尽量与要求的东西相接近以减少信息量.
  
  例如, 要求前缀质数个数则打表区间质数个数比打表质数优.

- 分块使得散块的规模可直接暴力做从而减少存的内容.

- 将十进制改为更大的进制.

- 若每个元素都等长, 将数组改为字符串可以省去逗号.

- 代码长度通常为 100k.

## 结算

想 T1 的时间过于长了. 事实上这题并不是我能够初见切的题.

需要正确估计写剩下的暴力所需时间, 并计算出什么时候应当结束想题开始写暴力.

# 20240508 总结

## T1(moon) [放缩题意] [高斯消元] [反 Hall 块]

期望:45 实际:55 难度:4 用时:2.5h

数据水了. 事实上考场上我自己就造了一个 $n = 5$ 的 Hack.

对于一类 两组集合的并相等 的题目, 若不好满足则考虑将其放为 给每组中的每个集合赋正权, 对应元素的和全为 0.

求非完美匹配的二分图的任意一个连通块, 满足其不满足 Hall 定理, 则可以从一个非匹配点出发搜一棵交错树, 与根距离为奇数的点集为 $S$, 偶数为 $N(S)$.

由此, 对于题目给出的 类似 $n$ 与 $m$ 间的小于关系, 考虑建立二分图模型.

## T2(you) [数学]

期望:60 实际:70 难度:3 用时:1.5h

数据造错了.

考虑一种 "出题人意识", 若题目中给了 $\gcd(x, y, z) = 1$ 的限制, 大概率是解法依赖这个条件 (不然我加一个反演也不难) 而给我们提示.

做数学题有一种暴力的方法, 即将能换的元全部换了然后 $O{n \choose m}$ 枚举子集消元, 看有没有前途.

## T3(who) [椭圆曲线] [不会]

期望:20 实际:20 难度:5 用时:1h

在 $\bmod \space p \space (p \neq 2, p \in Prime)$ 意义下, 一个数 $x \in [1, p)$ 为二次剩余 (至少有一个数 $y \in [1, p)$ 使得 $y^2 \equiv x \pmod p$), 当且仅当 $x^{\frac{p - 1}{2}} = 1$, 且有且仅有 $y$ 与 $p - y$ 两个根.

事实上, 若忘记了这个定理, 判断一个数为二次剩余也可 $O(p)$ 预处理 $O(1)$ 判断.


## 结算

灵感浓度过高的一场 (虽然约等于只有两道题).

# 20240509 总结

## T1(pain) [搜索] [合并等价类] [狄利克雷卷积]

期望:22 实际:22 难度:2 用时:2h

如下代码:
```c++
for (int i = 1; i <= n; i++) {
  for (int j = i + i; j <= n; j += i) {
    f[j] -= f[i];
  }
}
```
其本质上为将 $f$ 卷上 $\mu$.

事实上, $n$ 以内的本质不同 质因数分解的指数集合 是极少的, 当 $n = 10^{18}$ 时为 $10^4$ 量级.

## T2(silksong) [Meet-in-the-Middle] [随机化]

期望:100 实际:30 难度:2 用时:1.5h

没有看到有自环. 随机化写的太劣了.

随机化中加入随机调整会比纯随优很多.

## T3(pantheon) [生成函数] [不会]

期望:29 实际:11 难度:5 用时:1.5h

尚且不明的原因.

Dp 时, 优化的方法为 降低转移数(同时一般会增大状态数) 或 降低状态数(增大转移数).

## 结算

T2 想到正解但不够自信直到快下考才开始写. 好在写完了.

# 20240514 总结 & [解](https://www.luogu.com.cn/api/team/downloadFile/0h39kbn0)

## T1(tree) [BDFS 序] [树链剖分]

期望:25 实际:25 难度:4 用时:2h

### BDFS 序

考虑如下事实, DFS 序能够方便地处理 子树 与 链 的问题, 而 BFS 序能处理 较近的邻域 的问题.

因此, 将两者结合, 具体而言在根上方添加长为 $k$ 的链, 从链顶开始 DFS, 每次将该结点距离为 $k$ 的后代加入序中, 得到 k-BDFS 序.

一个结点的子树内的距离 $\le k$ 的结点在序上分别构成了 $k$ 个区间. 一棵子树除深度严格前 $k$ 小外在序上为一个区间. 一条重链除深度前 $k$ 小外在序上为一个区间, 但要把 非超重儿子 (在重链上的深度为前 $k$ 小) 剔除.

## T2(snow) [观察力] [递归]

期望:30 实际:30 难度:4 用时:1.5h

对于不好描述合法条件的一类问题, 考虑采用递归的方式描述.

调试时, 若输入数据过大而不好调, 考虑简化输入使得仍然保留原来输入的性质.

## T3(halation) [观察力] [奇偶分类] [整体二分]

期望:45 实际:30 难度:4 用时:1h

数据分治写的不完全导致的.

看见有形如 $2^k$ 的式子且 $n$ 很大时, 考虑用奇偶分类将 $n$ 降为亚线性.

## 结算

数据分治还是要分开写. 使用 `if` 是不明智的.

# 20240515 总结

## T1(matrix) [最小割]

期望:100 实际:100 难度:1 用时:0.75h

最小割若要输出方案, 不能直接将边权为 0 的边当作被割的边, 但可以将边权非 0 的边当作未割的边. 原因显然.

## T2(card) [期望 Dp]

期望:100 实际:100 难度:2.5 用时:2h

20240507 讲题 讲过的东西. 具体为考虑一次有效的拿取物品. 此处略.

## T3(string) [01 串变换] [观察力]

期望:20 实际:20 难度:3 用时:2h

若对于一个 01 环, 每次将 01 变成 10, 则相当于 长度 $> 1$ 的 0 连续段每次向右移 1, 1 连续段左移 1, 相撞则均减 1.

## 结算

似乎发挥的还不错? T3 还不会, 暂且不做评价.

# 20240712 总结

## T1(ain) [包含特定子串的字符串数] [Border 等差数列]

期望:100 实际:100 难度:1 用时:1h

略.

## T2(ainsoph) [拆分贡献] [变换求和顺序] [含 0 逆元特殊处理]

期望:100 实际:100 难度:2.5 用时:2h

本来应当挂成 0 的, 数据水了.

注意到 0 没有逆元, 因此算区间连乘积时若可能出现值为 0 的项, 每个前缀应当记录 0 项的个数以及不考虑 0 项的积.

## T3(ainsophaur) [单位根反演] [式子转实际意义] [旋转坐标轴] [范德蒙德卷积]

期望:80 实际:80 难度:3.5 用时:1.5h

当一个式子长的很好看时, 考虑直接构造它的实际意义并改变计算的方法.

每次能朝四个方向走 1 单位不好处理, 可以通过旋转坐标轴 45° 并均偏移 $(1, 1)$, 即 $(x, y) \Rightarrow (\frac{x+y+1}{2}, \frac{y-x+1}{2})$ 来变成两维独立, 可以选择 $+1$ 或不变.

有如下式子 (即范德蒙德卷积)

$$\sum_{a+b=t} {x \choose a} {y \choose b} = {x+y \choose t}$$

可以用来拆形如 $\sum {n \choose a,b,c,d}$ 的东西.

## 结算

天胡开局. 但是依旧少考虑 Corner Case, 谨防 1795MiB 事故重演.

# 20240715 总结

## T1(aka) [拆分贡献] [二分图匹配]

期望:50 实际:40 难度:3 用时:4h

最小丑的一集, $O(2^n n^2)$ 没过 20. 想了 1h 发现看错题了, 再想 1h 想到了一个假做法成功浪费整场考试. 原本以为第一场考试会寄, 没想到是第二场.

对于一个元素的贡献有多种情况且情况能划分维度的问题, 考虑给每个维度赋恰当的权值使得合并后为元素本身的贡献. 事实上这点考场上应当想到的, 但因为受到错误题面的误导完全没有往这方面想.

用若干环覆盖所有元素相当于赋一个 $n$ 排列.

## T2(ao) [限制最优解形态]

期望:0 实际:0 难度:3.5 用时:0.25h

常见套路为, 当你要 删/加 某个元素时, 考虑在 头/尾 删/加 不劣的限制条件, 取反得到对最优解的限制.

一个连招为, 产生限制后用这个限制来缩减状态数量.

## T3(shiro) [李超线段树优化 Dp] [树套树]

期望:23 实际:0 难度:4.5 用时:0.25h

没有时间写朴素 Dp 导致的.

李超线段树不仅可以维护若干线段的单点最值, 事实上可以维护任意单调 (可既有增也有减) 函数 $f_i(x)$ 满足 $f_i(x)$ 与 $f_j(x)$ 只有至多一个交点.

李超线段树只能支持查询所有函数的最值, 若要查询 前缀/区间 的函数最值可以套上一个 树状数组/线段树.

动态开点李超线段树单次插入的空间花费是 $O(1)$ 的.

李超线段树上使用动态开点以扩大值域是愚蠢的. 可以直接离散化.

## 结算

成七的寄忆似乎准备复刻了. 看完题之后看样例输入, **且先不要看输出** (你的计算可能是错误的, 但看了答案后反推了过程), 算出全部答案后比对, 可以有效降低读错题的可能性.

每道题都要保证至少 0.75h 的思考时间, **且一般这也是上界**, 如果后面的题均很难则可以达到 1.25h.

# 20240717 总结

## T1(crops) [求特定转移可行性]

期望:100 实际:100 用时:1.5h

在最优化动态规划 $F$ 中若需要对每个阶段求出某一种转移的可行性, 则可以设同阶状态 $g$ 表示在该阶段内钦定其他状态都为极劣值时答案状态的值是否不变.

如树上最大带权独立集 Dp 中, 设有 $f_{i,0/1}$, 则 $g_{i,0}$ 表示钦定 $f_{i,1}$ 为 $-\infty$ 时 $f_{1,0}$ 是否不变. 转移显然.

## T2(miss) [提取定量优化 Dp]

期望:0 实际:82 用时:1h

脑抽写了一个神秘做法, 甚至不满足拓扑序, 而通过了所有样例且获得了较高分数. 戏剧性的是没过的是一个前缀且暴力容易通过.

当 Dp 中存在 $a \bmod p$ 时考虑将其变为 $a - p \lfloor \frac{a}{p} \rfloor$, 从而将 $a$ 与 $p$ 提取出来成为全局量.

## T3(biophy) [推式子] [前缀和优化]

期望:100 实际:100 用时:1.5h

略. 注意推式子时想清楚每个部分代表的含义, 减少错误.

## 结算

对于一个做法先在脑内质疑并验证. 当时间有富余时 (事实上很难有) 拼暴力.

# 20240719 [HDUACM](https://acm.hdu.edu.cn/contest/problems?cid=1124) 总结 & [Account](https://www.luogu.com.cn/paste/o08ha6jb)

## T1(循环位移) [哈希]

状态:AC(-4) 难度:2

略.

## T2(星星) [小体积背包]

状态:AC(-2) 难度:1

暴力可过.

对于小体积背包, 暴力做 $O(nmV)$, 可以将每个物品 ``shuffle`` 后看作在背包容量一维上的随机游走, 则考虑完前 $i$ 个物品后期望容量为 $\frac{im}{n}$, 当只维护这周围 $\plusmn V \sqrt m$ 的背包容量时错误的概率约为 $10^{-4}$. 故可以做到 $O(nV \sqrt m)$.

## T3(树) [线段树合并]

状态:AC(-5) 难度:1

略.

## T4(传送) [线段树分治] [可撤销并查集]

状态:AC 难度:2.5

若使用 LCT 维护的最大生成树, 其边权不作为答案的一部分贡献, 则可以使用线段树分治套并查集.

## T5(博弈) [对称]

状态:WA 难度:3

当需要求一个元素大于另一个元素的概率时, 考虑交换这两个元素其概率是否不变.

## T6(序列立方) [转次方为指针]

状态:AC 难度:2

若一个等价类的贡献为大小的 $k$ 次方, 则相当于拿 $k$ 个指针扫同一个等价类的方案数.

## T7(三元环) [竞赛图三元环] [三维偏序]

状态:AC(-1) 难度:2

竞赛图三元环见前文同标签.

## T8(位运算) [无]

状态:AC 难度:1

略.

## T9(数位的关系) [数位 Dp]

状态:N/A 难度:2.5

难度主要体现在实现. 一般可以利用差分去掉下界, 然后额外设 0/1 表示前面 $i$ 位是否都顶到上界. 无需设初始值, 在循环内加上填第一个非 0 数的转移即可. 对于题目要求的量, 注意前导 0 是否能转移的问题.

## T10(众数) [随机数据]

状态:WA 难度:3

数据随机时, 每个区间的最大值都期望很大. 一般这种题可以直接写暴力然后稍微剪枝.

实现方面的细节, 若对 最大值恰为一个数 的区间数计数, 则容易从小到大使用并查集解决, 需要从大到小枚举时, 使用 ``priority_queue`` 按段内最大值 维护每个被之前的较大值切开的段. 需要预处理最大值出现位置.

## T11(树上的 mex) [二分答案] [链转平面点] [扫描线]

状态:N/A 难度:3

通过二分答案可以将求 mex 时的 $[0, k-1]$ 出现 $k$ 不出现转为 $[0, mid-1]$ 出现. 省去了不出现的要求.

当用若干条链将树拆分时, 不经过特定链的链在 dfn 坐标系中 形成若干个矩形, 所有链的矩形个数之和为 $O(n)$ 级别.

## T12(并) [合并贡献]

状态:AC 难度:2

当矩形数量为 $10^4$ 级别时, 考虑每个切出来的小块.

# 20240722 [HDUACM](https://acm.hdu.edu.cn/contest/problems?cid=1125) 总结 & [Account](https://www.luogu.com.cn/paste/o08ha6jb)

## T1(鸡爪) [贪心] [构造]

状态:AC 难度:2

略.

## T2(梦中的地牢战斗) [最短路]

状态:AC(-1) 难度:2.5

当一个最优化问题难以找到拓扑序时, 考虑用 Dp 值本身当作拓扑序.

## T3(绝对不简单的模拟魔方) [搜索] [模拟]

状态:AC(-1) 难度:2

当一个问题过于复杂时, 考虑其中不影响答案的量将其删去. 例如, 将三阶魔方换为二阶魔方不影响角上的块.

## T4(a*b problem) [min_25 筛]

状态:TLE 难度:4

暴力做法. 与正解只差 min_25 筛.

难点主要在学会 min_25 筛, 但我不会.

## T5(小塔的养成游戏之梦) [平面几何] [直线导出所有极小凸包]

状态:N/A 难度:4

难点主要在求出所有直线围成的所有极小凸包. 考虑将两端点夹的线拆成带方向的两条, 从任意未经过的一边开始走, 每次走到旋转角尽可能大的一条边上, 走一圈就是一个极小凸包.

## T6(传奇勇士小凯) [无]

状态:AC(-3) 难度:1

值得注意的是, 使用 ``pair`` 维护一个分数时, 若重定义了 $<$ 号, 在使用 ``max`` 函数时仍会用 ``pair`` 的默认比较函数来比较. 因此最好用一个 ``struct`` / ``class`` 维护分数.

## T7(URL 划分) [模拟]

状态:AC(-1) 难度:1

略.

## T8(成长, 生命, 幸福) [树上带点权直径]

状态:AC(-1) 难度:2.5

略.

## T9(强攻计策) [区间加 拆 后缀加减]

状态:WA 难度:4

做法假了.

当要维护的东西很庞大 ($O(n)$ 级别或差不多) 时, 考虑每次操作带来的变化量.

当区间加不好考虑 (会有两次变化) 时, 考虑将其拆分成 前/后 缀的加减 (只有一次变化).

一个支持 区间 加减 1 与 查询一个后缀最靠前的 0 的位置 的数据结构的实现方法: 分块. 块内排序二分可以做到块长为 $O(\sqrt {n \log n})$ 时 $O(q \sqrt {n \log n})$ (重构时可以归并做到 $O(B)$); 也可以在每个块内维护 $\plusmn \sqrt n$ 的最靠前位置 失效后重构, 当块长为 $\sqrt n$ 时可以做到 $O(q \sqrt n)$.

## T10(女神的睿智) [无]

状态:AC(-4) 难度:1

难点主要在正确理解题意.

## T11(在 A 里找有 C 的 B) [Trie 树] [KMP]

状态:AC 难度:2

判断模式串是否在多个匹配串中出现时, 若匹配串的长度之和可以接受, 则可以使用 KMP. $O(m + \sum n)$.

## T12(图计算) [并查集] [哈希]

状态:AC(-2) 难度:3

当需要判断若干组元素对应相等时, 考虑哈希.

当这些元素的值域不够大时, 可以为每个元素的取值赋一个权.

若哈希的方式为将其合并为一个大进制数的模数, 则底数 **一定要是质数**, 否则冲突几率极大.

# 20240724 总结

## T1(string) [交换求和符号] [KMP]

期望:100 实际:100 难度:2.5 用时:2.5h

看错题浪费了很长时间. 之后又被部分分误导没有往正确方向想.

统计进行一些操作后的字符串中的模式串出现次数, 若原串可能作为贡献的模式串很少, 则对每个模式串考虑将其保留下来的操作方案数.

## T2(game) [二分图博弈]

期望:20 实际:0 难度:4 用时:1h

最后十分钟赶的暴力, 连样例都来不及测, 挂了不足为奇.

判断合法转移的 ``s >> i & 1 ^ 1`` 写成了 ``s >> i & 1``, 初始集合的 ``1 << i`` 写成了 ``0``.

[二分图博弈](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点.

## T3(sequence) [贪心] [线性规划对偶]

期望:30 实际:30 难度:4.5 用时:1h

对于一个局面的多种转移, 考虑是否有一种转移始终不劣于其他转移. 若没有, 则不断添加限制条件来分类讨论.

当有两个对答案有益的量需要减少总共 $k$, 以当前状态难以决策时, 可以将这两个量均减去 $k$ (注意特判负数) 并在之后获得 $k$ 次免费使这两个量 +1 的机会.

[线性规划对偶](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点.

## 结算

不要看错题. 部分分不一定通往正解, 当想了一段时间没有进展时及时回退.

快结束在打一道题较高的暴力时先将其他题的暴力打完.

# 20240726 [HDUACM](https://acm.hdu.edu.cn/contest/problems?cid=1126) 总结

## T1(深度自同构) [略]

状态:AC(-1) 难度:1

略.

## T2(旅行) [线段树合并]

状态:AC 难度:2.5

略.

## T3(游走) [模拟]

状态:AC(-8) 难度:3

傻逼恶心题.

## T4(游戏) [多项式]

状态:N/A 难度:4

[多项式快速幂](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点.

## T5(数论) [容斥] [Gcd 减半]

状态:N/A 难度:3.5

选取若干不交区间使得其中一个包含 $i$, 可容斥为在 $i-1$ 的前缀和在 $i+1$ 的后缀分别选取.

$\gcd$ 每次变化, 至少减半.

## T6(字符串) [字符串]

状态:N/A 难度:4

考虑一个母串 $S$ 中 $|Endpos|$ 相同的所有子串, 其左端点对于一个固定的右端点 $x$ 必然为一个区间 $[l, r]$, 且随 $x$ 的增大, $l$ 和 $r$ 都单调不降.

## T7(单峰序列) [线段树]

状态:AC(-3) 难度:2

维护一个区间内的数是否 单峰/上升/下降 这样依赖相邻两项数的信息, 考虑维护差分.

## T8(比特跳跃) [贪心]

状态:AC(-1) 难度:2.5

对于形如 $g_i = \min_j\{f_j + (i|j) \times k\}$ 的式子求值, 若 $k$ 为非负数, 则可以记 $h_i = \min_{j|i = i}\{f_j\}$, 有 $g_i = \min_{j|i = j}\{h_j + j \times k\}$. 若项数为 $2^n$, 则 $O(n2^n + 3^n)$.

## T9(圣芙蕾雅) [不会]

状态:N/A 难度:5

不会.

## T10(绘世之卷) [线段树分治] [根号分治]

状态:N/A 难度:4

维护较少元素两两之间的值的最值时, 若既有插入也有删除, 考虑使用线段树分治变成插入和撤销.

注意到, $\lfloor \frac{x}{y} \rfloor$ 与 $x \bmod y \space (x \ge y)$ 都是 $O(x-y)$ 级别的. 故当值域内有 $O(\sqrt V)$ 个数时, $\lfloor \frac{x}{y} \rfloor + x \bmod y \space$ 的最小值为 $O(\sqrt V)$ 级别.

## T11(抓拍) [三分]

状态:AC 难度:2

当需要求若干函数的和的最值, 但值不好动态维护时, 考虑函数的凸性.

## T12(死亡之组) [略]

状态:AC 难度:1

略.

# 20240806 [HDUACM](https://acm.hdu.edu.cn/contest/problems?cid=1129) 总结

## T1(造花 简单版) [略]

状态:AC(-2) 难度:2

略.

## T2(造花 困难版) [必要条件交集]

状态:AC(-3) 难度:3

对于一类求哪些单点操作可以满足条件的题目, 考虑找到原始状态下不满足条件的极小单元, 从而得到一个集合, 必须操作其中之一, 然后将所有集合求交集.

## T3(飞车狂飙) [略]

状态:AC 难度:1

略.

## T4(不醒人室) [略]

状态:AC(-1) 难度:1

略.

## T5(交通管控) [略]

状态:AC 难度:1

略.

## T6(解方程) [Lenstra-Lenstra-Lovász 算法]

状态:N/A 难度:5

不会.

## T7(树上 MEX 问题) [拆 MEX] [Dp]

状态:AC 难度:2

所有集合的 MEX 之和 等于 包含 0 的集合个数 + 包含 0 和 1 的集合个数 + ...

## T8(树形 DNA) [哈希] [查询转修改]

状态:AC 难度:2

维护集合每次判若干固定元素是否全在集合中, 可以改成枚举每个固定元素找包含这个元素的集合.

## T9(数字加减) [计算上界]

状态:N/A 难度:4.5

对于一些操作对元素总数的修改很少, 且元素会自行减少的数据结构题, 考虑元素总数的上界.

对于一些无法简单维护的特殊情况 (如两个连续段连在一起需要合并) 且数量较少, 考虑将其当作一种操作并动态维护这种操作.

## T10(Rikka 与子集 IV) [多项式] [重链剖分] [矩阵乘法] [分治]

状态:N/A 难度:4

将轻儿子合并到重儿子的过程可以考虑用矩阵来表示, 从而能够方便地合并整条重链.

对于一类复杂度与二元都有关的合并算法, 从左到右依次合并显然不优, 考虑分治.

## T11(天天爱跑步) [分类讨论] [树形 Dp]

状态:AC(-1) 难度:3

略.

# 20240807 总结

## T1(sus) [倍增]

期望:100 实际:100 难度:1 用时:0.5h

略.

## T2(usd) [扫描线] [线段树] [并查集]

期望:100 实际:100 难度:3 用时:2.5h

判断二分图除了直接染色, 还能够维护并查集. 事实上直接染色没有拓扑序, 需要快速判断时不常用.

当线段树需要 修改/查询 的不是一个区间, 但元素之间无序时, 考虑提前将元素排序.

## T3(pois) [Hall 定理] [最小割]

期望:30 实际:75 难度:4.5 用时:1.5h

数据造水了. 事实上, 按照 匹配边-非匹配边-匹配边-...-非匹配边 搜索得到的图是是一张一般有向图, 而不是无向图.

有个不应该的点在于送的 10pts 没有意识到.

当题目保证了完美匹配且需要满足一个等式时, 考虑 Hall 定理并 得到 补全另一个方向的条件.

Hall 定理可以反向, 即在有完美匹配的二分图中 $|S| \ge |M(S)|$, 其中 $|M(S)|$ 为另一侧与 $C_S$ 无边的点集.

可以通过给所有边都加上一个 $inf$ 的方式使最小割优先保证割的边数最少.

## 结算

T2 最开始没想清楚, 从手动染色到发现没有拓扑序再想到并查集花费了很久, 中途还实现了手动染色的代码.

对于一个代码预计花费较长 (> 1h) 的思路, 一定要验证可行性 (大概 5min).
