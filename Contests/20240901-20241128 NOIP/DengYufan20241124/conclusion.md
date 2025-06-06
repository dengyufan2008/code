# 20241124 总结

## T1(sort) [逐位考虑] [贪心]

期望:100 实际:100 难度:1 用时:0.5h

``builtin_clz`` (count leading zero) 可以计算一个 ``unsigned`` 变量的前导零个数, 则可以使用它来计算 highbit.

## T2(swap) [复合排列] [快速幂]

期望:100 实际:100 难度:2 用时:0.5h

排列的快速幂是可以做到线性的. 具体地, 将每个置换环求出来, 直接取模即可.

## T3(calc) [实数期望] [二项式定理]

期望:100 实际:100 难度:3 用时:**2h**

当期望中出现非线性函数时 ($\max$ 和 $\min$ 可以简单地用 min/max 容斥解决), 若在期望的式子中仅出现了一个非线性函数, 且其外部仅有 $k$ 次方, 则可以考虑使用二项式定理. 如 $E(\lfloor x \rfloor ^k)$ 可以用 $E(x^p)$ 和 $E((x \bmod 1)^p)$ 来表示.

有一个在区间 $[l, r)$ 均匀随机的实数变量 $x$ 和一个函数 $F:\R \rightarrow \R$, 则 $E(F(x)) = \frac{1}{r-l} \int_{l}^{r} F(x) \, \text{d}x$.

期望具有可乘性. 具体地, $E(xy) = \sum_w w \sum_{xy=w} P(x) Q(y) = (\sum_x x P(x))(\sum_y yQ(y)) = E(x)E(y)$.

期望满足二项式定理. 具体地, $E((x+y)^k) = \sum_{i=0}^k {k \choose i} E(x^i) E(y^{k-i})$.

等概率地取模卷积的结果也是等概率的. 具体地, $n$ 个 $[0, 1)$ 范围内均匀随机的变量的加和的小数部分是在 $[0, 1)$ 范围内均匀随机的.

## T4(mo) [转化贡献] [转化操作] [观察力] [ODT]

期望:25 实际:25 难度:4 用时:1.5h

对于一类求区间内颜色数的问题, 若同一种颜色只会形成至多一个连续段, 则可以维护相邻两个元素是否相等, 并转化操作的意义. 如对于一个 $a_i = i$ 的序列, 每次将 $[l, r]$ 都赋为 $a_l$, 则可以维护 $b_i = [a_i \neq a_{i+1}]$, 一次操作相当于 $b_r \leftarrow \text{Or}_{i=l}^r b_i, \forall l \le i < r, b_i \leftarrow 0$.

对于一类维护 $n$ 个 01 变量并进行 $m$ 次操作的问题, 常用的套路是考虑每个 01 变量是否只会从 $0$ 变成 $1$ 或反之.

## 结算

最刺激的一场. 花费了 1.5h 通过 T1 T2 后, 在 T3 上卡了 1h 想到了一个维护分段函数并支持卷积+积分的 $O(n^3)$ 做法, 明智地没有写这个做法转而去思考 T4. 在思考了 0.5h 后想到了一个假做法并花了 0.5h 实现出来, 发现 **连最小的样例都过不去**, 遂开始想部分分, 想了一会之后不甘心地回去继续想 T3. 在最后的 1h 内得出了正解, 手玩样例并经历了一系列计算错误后证实了正确性, 顺利切掉并写完了 T4 的暴力.

被一道题卡住时想别的题换脑子是极其有效的.

在得到了一个做法后一定要使用这个做法来计算样例, 以一定程度保证做法的正确性.
