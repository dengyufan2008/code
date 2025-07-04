> "你的留恋是什么呢?"
> 
> "拯救地球."
> 
> "地球, 也包括我吗?"

见区间思考有包含关系的区间能否去掉其一. (考过三次还不会的套路)

同余最短路数组居然还能换模数. [例](https://www.luogu.com.cn/problem/P4156)

搜连通块: Dfs 时维护可扩展的格子序列, 保证每次选的是递增的.

判断最小割中一条边是否被割掉: 从源点开始搜, 只走非满的边.

Dfn 求 LCA: 令 Dfn 数组为 $r_i$, ST 表数组为 $st_i$, 可以令 $st_{r_i} = r_{f_i}$, 维护区间 min. 有 $r_{LCA(x, y)} = \min_{r_x < i \le r_y} st_i$, 维护 Dfn 的逆数组即可.

树形 Dp 的另一种方式: 按 Dfs 序 Dp, 维护到根的路径上点的状态. 需要深度较小, 且转移只与祖先有关. [例](https://www.luogu.com.cn/problem/P3577)

DAG 上生成外向树的个数只有 $O(2^{m - n + 1})$ 个. [例](https://qoj.ac/problem/6406)

用 LCT 维护树时若树一定为小根堆则可以维护子树相关信息. [例](https://qoj.ac/problem/7760)

$$d(ij) = \sum_{x|i}\sum_{y|j}[\gcd(x, y)=1]$$
对每个质因数独立, 分解后易证.

对若干个排列取出 $O(n)$ 个极大复合无关组, 可以 ``shuffle`` $O(n)$ 次每次依次全部复合起来.

对于一个数集选两个数和 $\ge m$, 则可按 $\min(a_i, m - a_i)$ 升序排序, 靠前的需 $\ge \frac{m}{2}$.

对于一类最优化问题, 若在没有限制的情况下直接排序即可得到最优方案, 但题目中给了一个树形拓扑序的限制, 则可以将相邻逆序对绑在一起. [例](https://acm.hdu.edu.cn/contest/problem?cid=1131&pid=1001) & [Account](https://www.luogu.com.cn/paste/o08ha6jb)

在计数问题中, 离散化的方式为将 Dp 状态的值域一维缩减到 $O(n)$ 级别, 并禁止空集的转移. 20240818 T3 & [例](https://qoj.ac/problem/1084)

$n$ 个点边数为奇数的有标号无向连通图个数 $F_1(n)$ 和边数为偶数 $F_0(n)$ 的差值为 $(-1)^n(n-1)!$. 归纳证明, 考虑 $n$ 连接的点数, 分 1 个和多个考虑, 发现多个对二者的贡献相等故舍去, 剩余部分自证不难.

最优化将序列划分成若干段的权值和问题中, 若一段的权值的计算方式与值域相关 (如与值域上连续的三个元素有关的某个函数), 则考虑 CDQ 分治优化 Dp. 例: Resources/建筑游戏.zip

对底栈的复杂度居然是均摊 $O(1)$ 的. [例](https://www.luogu.com.cn/problem/CF2026F)

$O(\log n)$ 地用一个栈模拟队列: 考虑将对顶栈中的元素放在一个栈里, 设 pop 端的元素数量为 $t$, 则每次 pop 时找到 pop 端的前 $\text{lowbit}(t)$ 个元素, 将从这里到栈顶的每一个元素全都移出栈, 先加入刚刚被移出栈的 push 端元素, 再加入 pop 端元素. 若 $t=0$ 则将栈全部弹出并翻转后再插入, 则所有的 push 端元素变为 pop 端元素. 使用 $\text{lowbit}$ 可以看作将 pop 端元素二进制分组.

对于形如大量种类的颜色匹配是否合法的判定, 可以对每种颜色赋一个随机的权值 $v$ 并生成矩阵

$$
A = \left[
\begin{matrix}
v & 1
\\
1-v^2 & -v
\end{matrix}
\right]
$$

显然有 $A^2 = I$, 则只需判断整个序列的乘积是否为单位矩阵即可. 注意到 $B * B^{-1} = B^{-1} * B = I$, 故无法使用这种方式判断括号匹配.

树剖+线段树维护 SG 函数时, 线段树每个叶子只需记录 重儿子 SG 值为 $x$ 时本结点 SG 值为 $y$ 否则为 $z$ 即可, 而无需对重儿子每个可能的 SG 值分别记转移. 容易合并.

有

$$\sum_{i=0}^{+\infty} {n+i \choose n} a^i = \frac{1}{(1-a)^{n+1}}.$$

二分图最大匹配 = n - 最大独立集. 最小点覆盖构造方案考虑网络流最小割, 选左部的 T 和右部的 S.

对所有数 $a_i$ 变为 $\lfloor \frac{a_i+x}{2} \rfloor$ 的操作, 如果维护排序后的 $a_i$, 每次把所有相等的数合并则可以暴力做. 势能分析考虑 $\sum_i \lceil \log_2(a_i-a_{i-1}) \rceil$, 两项差每次会除以二上取整或下取整, 则差只要大于 1 取对数后就会减少 1, 差是 1 的连续段每次长度 $l$ 会变为 $\lceil \frac{l+1}{2} \rceil$, 则只要长度大于 2 就会减半, 小于等于 2 时只花费了 $O(1)$ 的代价就能让本段和右侧的段之间的势能减少. 故复杂度 $O(n \log V)$.

进行操作使方差最小考虑枚举平均数. [例](https://www.luogu.com.cn/problem/CF2029I)

求序列 $a_i$ 与 $b_j$ 的加法笛卡尔积的前 $k$ 小, 可以考虑先排序两个序列, 将 $a_1 + b_1$ 加入不可重集, 随后每次取出一个最小值 $a_i + b_j$, 则将 $a_{i+1} + b_j$ 与 $a_i + b_{j+1}$ 加入优先队列. 需要去重. 本质上是维护平面直角坐标系中被 ban 掉的坐标的外包络.

$F^p(x) \equiv F(x^p) \pmod p$, 证明考虑将左式拆成 $p$ 个 $\sum$ 的形式, 若这 $p$ 个循环变量中有一对不同, 则重排的方案数为 $p$ 的倍数 (拆开组合数, 上面的 $p!$ 中的 $p$ 消不掉), 故只需考虑 $p$ 个循环变量全部相同.

给定树上三点则唯一确定了三条路径, 注意到只有它们的重心被三条路径经过奇数次, 而重心是三个点分别到另外两点路径的最近点, 对于一类树上求路径最近点权值的异或和问题好用. [例](https://atcoder.jp/contests/pakencamp-2024-day2/tasks/pakencamp_2024_day2_c?lang=en)

$n$ 错排的限制可以用 $n$ 个点的有向图来描述. 不完整的错排只有孤立点, 链, 非自环的环; 完整的错排只有非自环的环. [例](https://www.luogu.com.cn/problem/CF1085G)

描述一个 $n$ 边形的剖分可以用栈. 将环平铺成链, 从 $1$ 到 $n$, 若加边 $(i, j) \space (i + 1 < j)$ 则在 $i$ 处弹栈到栈顶为 $j$ 为止, 加完边后把 $i$ 加入栈. 最后加入边 $(1, n)$, 显然它不能作为多边形的剖分, 故没有影响; 并且不把 $n$ 加入栈. 那么栈的限制为 1 始终不能弹出 (即大小始终非 0) 且最终只剩 1. [例](https://www.luogu.com.cn/problem/AT_agc065_d)

加边使 DAG 变 SCC 的最小数量是 $\max(入度为 0 的点数, 出度为 0 的点数)$, 构造考虑先变成弱联通图, 然后做一个入度为 0 的点与出度为 0 的点的匹配.

求最小曼哈顿生成树只需保留每个点的 8 向最小边即可. 证明考虑转切比雪夫距离.

下降幂满足二项式定理, 即 $(x+y)^{\underline k} = \sum_{i=0}^k {k \choose i} x^{\underline i} y^{\underline {k-i}}$. 证明考虑范德蒙德卷积.

$\bmod \space 2^{64}$ 的多项式题目可以考虑下降幂多项式, 只用保留前不超过 70 项.

对于一类问题, 若不考虑插入操作, 元素在操作序列上满足单调性, 那么有插入操作时可以考虑二进制分组. [例](https://loj.ac/p/3273)

可持久化数据结构可以通过询问分块, 块长 ${q \over \log n}$, 重构 $O(\log n)$ 次来使空间不带 $\log$, 时间复杂度不变.

树套树可以 pushup, 可持久化即可. [例](https://darkbzoj.cc/problem/3946) 兔队线段树本质上是每个结点维护了一个可持久化平衡树.

强连通竞赛图中一定分别存在大小在 $[3, n]$ 内的简单环. 竞赛图强连通的充要条件为任意大小为 $m$ 的点集 (事实上只需考虑度数前 $m$ 小的点), 其在整张图的出度 (或入度) 之和大于 $m(m-1) \over 2$. [例](https://www.luogu.com.cn/problem/CF1268D)

[一道数学题](https://www.luogu.com.cn/article/ueohh8lt)

[又一道数学题](https://www.luogu.com.cn/article/7d3j944s)

[双一道数学题](https://www.luogu.com.cn/article/lc9tfr5v)

[一道计数题](https://www.luogu.com.cn/article/qpk41kv1)

[又一道计数题](https://www.luogu.com.cn/article/6bpx8onp)

[一道 OI 题](https://www.luogu.com.cn/article/xr76q3sa)

史诗级没什么用的发现: $\gcd(a,c) \gcd(b,c) = \gcd(ab,c \gcd(a,b,c))$, 或言 $\gcd$ 也可以整式乘法.

----

[我准 **备** 用来 **忘** 记的 **箓**](https://www.luogu.com.cn/paste/lvmrhjxm)

[考逝总结](https://www.luogu.com.cn/article/sd8bpaa1)

[讲氪总结](https://www.luogu.com.cn/article/bn0cnhaw)

[最腥知识](https://www.luogu.com.cn/article/ft3tx54e)

[To Do Lists](https://www.luogu.com.cn/paste/lcysbo18)

[Files](https://www.luogu.com.cn/team/33225#file)

[Sharing](https://www.luogu.com.cn/paste/frklj4he)

---

![](https://moe.jitsu.top/img)

# *DengYufan's Introduction*

## *Accounts*
- Luogu : 1795MiB

- Codeforces : dengyufan

- Atcoder : dengyufan2009

- Github : dengyufan2008

## *Websites*
- [cppreference](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)

## *Code*
- [Fast IO For Interger](https://www.luogu.com.cn/paste/a6g4tzxa)

- [Poly Calculator](https://www.luogu.com.cn/paste/otlhoocq)

- [Pair Hash](https://www.luogu.com.cn/paste/bwkr5zb3)

- [Treap](https://www.luogu.com.cn/paste/201bgmoy)

- [Splay](https://www.luogu.com.cn/paste/t1c5l25d)

- [HLPP](https://www.luogu.com.cn/paste/1ltjkyl7)

- [EK](https://www.luogu.com.cn/paste/clkjej7u)

- [Primal Duel](https://www.luogu.com.cn/paste/s1nawmeh)

- [Fast Mul](https://www.luogu.com.cn/paste/bmjrtlws)

## *Last Update : 2025.6.25*

> "对我来说, 你就是地球的中心."
