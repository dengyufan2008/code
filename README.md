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

[一道数学题](https://www.luogu.com.cn/article/ueohh8lt)

[又一道数学题](https://www.luogu.com.cn/article/7d3j944s)

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

![](https://luogu.wao3.cn/api/practice?id=250810&dark_mode=true)

# *DengYufan's Introduction*

## *Accounts*
- Luogu : dengyufan

- USACO : dengyuf1

- Codeforces : dengyufan

- Atcoder : dengyufan2008

- Github : dengyufan2008

## *Websites*
- [Luogu](http://www.luogu.com.cn)

- [USACO](https://train.usaco.org)

- [Codeforces](https://codeforces.com)

- [AtCoder](https://atcoder.jp)

- [C++Info](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)

- [Github](https://github.com)

- [OI-Wiki](https://oiwiki.com)

## *Code*
- [Fast IO For Interger](https://www.luogu.com.cn/paste/a6g4tzxa)

- [Poly Calculator](https://www.luogu.com.cn/paste/otlhoocq)

- [Pair Hash](https://www.luogu.com.cn/paste/bwkr5zb3)

- [Treap](https://www.luogu.com.cn/paste/201bgmoy)

- [Splay](https://www.luogu.com.cn/paste/t1c5l25d)

- [HLPP](https://www.luogu.com.cn/paste/1ltjkyl7)

- [Fast Mul](https://www.luogu.com.cn/paste/bmjrtlws)

## *Last Update : 2024.7.25*
