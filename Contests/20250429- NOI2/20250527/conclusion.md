# 20250527 总结

## T1([a](https://qoj.ac/problem/10871)) [观察力]

应得:100 实得:100 难度:2.5 用时:2h

对于一类有将序列循环位移的操作, 若事实上并不关心每个元素的绝对下标而只关心元素间的相对下标, 则可以在循环位移上做手脚, 让元素不移动或移动量较少.

## T2(b) [构造]

应得:42 实得:42 难度:3.5 用时:1.5h

对于一类构造题, 若前面的特殊性质是容易做的, 则可以考虑将没有特殊性质的情况归约至有特殊性质的情况. 比如本题所有树的根都相同时容易做, 则对于树的根只有 1 和 $n$ 的情况, 只需选择一些边来将 1 和 $n$ 合并成一个连通块即可.

## T3(c) [多项式] [线性代数] [组合意义] [树链剖分]

应得:12 实得:12 难度:5 用时:0.5h

[一类特殊格路计数问题](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点.

有 $A^{-1} = {\text{adj}(A) \over \det(A)}$. 其中 $\text{adj}(A)_{i, j} = (-1)^{i+j} M_{j, i}$, 其中 $M_{i, j}$ 为 $A$ 去掉第 $i$ 行第 $j$ 列的行列式.

快速求解特殊矩阵的行列式可以考虑矩阵中一个 环 可能的形态. 则行列式中枚举的排列一定是若干个环的并. 比如求无向树上随机游走的邻接矩阵的行列式, 则环只可能是对于一条边 $(x, y)$ 来说从 $x$ 到 $y$ 再回到 $x$, 显然排列的逆序对数就是选取的边数, 则求行列式变为了求完美匹配方案数.

## 结算

T2 两个特殊性质使用的做法完全无交, 导致做出了特殊性质也对正解没有帮助. 事实上有很多人使用 ``shuffle`` 草过了 T2.
