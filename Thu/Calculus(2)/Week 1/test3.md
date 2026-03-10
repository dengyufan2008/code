Prob 1. 给定 $n$ 阶方阵 $A$, $\lVert A \rVert = \max_{\lVert v \rVert = 1} \lVert Av \rVert$. 求 $A=\left[\begin{matrix}1 & 2 \\ 3 & 4\end{matrix}\right]$ 的范数.

$\lVert A \rVert^2 = \max \lVert Av \rVert^2 = \max v^t A^t A v$.

令 $B$ 为 $A^tA$ 对应的二次型, 由于 $B$ 实对称, 则可以正交对角化. $\lVert A \rVert^2 = \max B(v) = \max \sum_i \lambda_i a_i^2$, 其中 $\lambda_i$ 为 $A^tA$ 的正交特征值, $a_i$ 为 $v$ 的正交特征向量分解.

则 $\lVert v \rVert = \sqrt{\sum_i a_i^2}$. 故要保证 $\sum_i a_i^2$ 恒定. 令 $b_i = a_i^2$, 则要保证 $\sum b_i$ 恒定的情况下最大化 $\sum \lambda_i b_i$. 由于 $B$ 半正定, 则 $\lambda_i \ge 0$, 故最优解为 $b_i$ 在除了 $\lambda_i$ 最大值的位置都为 0.

故 $\lVert A \rVert^2 = \max_i \lambda_i$, $A$ 的范数为 $A^tA$ 最大特征值的平方根.

故 $\lVert A \rVert = \sqrt{15 + \sqrt{221}}$.
