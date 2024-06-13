见区间思考有包含关系的区间能否去掉其一.(考过三次还不会的套路)

同余最短路数组居然还能换模数. [例](https://www.luogu.com.cn/problem/P4156)

搜连通块: Dfs 时维护可扩展的格子序列, 保证每次选的是递增的.

判断最小割中一条边是否被割掉: 从源点开始搜, 只走非满的边.

Dfn 求 LCA: 令 Dfn 数组为 $r_i$, ST 表数组为 $st_i$, 可以令 $st_{r_i} = r_{f_i}$, 维护区间 min. 有 $r_{LCA(x, y)} = \min_{i = r_x + 1}^{r_y} st_i$, 维护 Dfn 的逆数组即可.

树形 Dp 的另一种方式: 按 Dfs 序 Dp, 维护到根的路径上点的状态. 需要深度较小, 且转移只与祖先有关. [例](https://www.luogu.com.cn/problem/P3577)

DAG 上生成外向树的个数只有 $O(2^{m - n + 1})$ 个. [例](https://qoj.ac/problem/6406)

[一道数学题](https://www.luogu.com.cn/article/ueohh8lt)

[又一道数学题](https://www.luogu.com.cn/article/7d3j944s)

[一道 OI 题](https://www.luogu.com.cn/article/xr76q3sa)

----

[我准 **备** 用来 **忘** 记的 **箓**](https://www.luogu.com.cn/paste/lvmrhjxm)

[考逝总结](https://www.luogu.com.cn/article/sd8bpaa1)

[讲氪总结](https://www.luogu.com.cn/article/bn0cnhaw)

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

## *Last Update : 2024.5.31*
