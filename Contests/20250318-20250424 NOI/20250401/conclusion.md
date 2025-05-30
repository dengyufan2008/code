# 20250401 总结

## T1(a) [DDp] [并查集]

应得:100 实得:100 难度:2.5 用时:1.5h

动态维护每个阶段的 Dp 值并不一定需要将 Dp 写成矩阵乘法的形式, 若 Dp 方程较简单, 仅有线性变换和与常数取 max/min, 则可以直接考虑增量带来的变化. 如动态维护 $f_x = a_x + \sum_{i \in Son_x} \max(f_i, 0)$, 当 $a_x$ 只会增加时, 并不需要树剖加线段树维护矩乘, 只需要把小于 0 和大于等于 0 的分开, 并写一个支持树上链加单点查的数据结构即可.

## T2(b) [观察力] [重标号] [DDp]

应得:75 实得:75 难度:3.5 用时:1.5h

对于一类形如在序列 $a$ 上选择两个下标 $i$ 和 $j$ 要满足 $i$ 和 $j$ 都在各自限制的范围中 (如 $i$ 在前一半, $j$ 在后一半) 且 $j-i \le m$ 的限制, 若一个元素的贡献只与和 $i$ 以及 $j$ 的相对位置有关, 则可以将 $a$ 复制一份 $b$, 平移下标直到 $a_1$ 与 $b_{m+2}$ 对齐, 则若钦定 $i$ 在 $a$ 中选, $j$ 在 $b$ 中选, 限制变为 $i$ 要在 $j$ 之后选, 则容易满足.

对于一类能够写出 答案的贡献简单但限制条件较多的式子 的计数问题, 考虑将式子用 Dp 实现而不是直接维护式子. 在需要动态维护答案时尤其有用.

## T3([c](https://codeforces.com/gym/105755/problem/B)) [观察力] [Exgcd] [构造]

应得:35 实得:35 难度:4.5 用时:2h

对于一类将 01 序列进行线性变换的神秘操作 (比如每次用 "001" 替换 0, 用 "01" 替换 1), 考虑将变化前后的 01 序列画成一条格路, 并观察两条格路 (变化前后的格路, 或题目中给出的两个 01 序列分别的格路) 围出的小格子. 如 [QOJ3040 Container](https://qoj.ac/problem/3040).

对于给定一些小格子的集合, 求两条格路恰好包络了这些小格子的问题, 若值域较小则可以分别求出右下轮廓线和左上轮廓线, 而不用真的用两条格路来包这些小格子.

## 结算

做构造题不能过于自信. T3 暴搜写到一半突然想到了一个做法, 便不加验证的转而写构造做法了, 最终不出所料的假了.
