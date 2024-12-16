# 20240912 [梦熊题单](https://www.luogu.com.cn/paste/c7xke3op)

- 对于一类期望的题目, 变换钦定的顺序再求概率可能会降低难度. 如本题先钦定最开始选择的点再钦定逆序对 比 先钦定逆序对再钦定最开始选择的点 容易. [例](https://www.luogu.com.cn/problem/CF1540B)

- 当数据范围只有 $10^5$ 且 $O(n^2)$ 做法显然时, 考虑使用 ``bitset``. [例](https://loj.ac/p/6499)

- 计算平面上欧几里得距离的近似值的一种方法为, 考虑一个极小的角 $\theta$ 满足 $k \theta = 2\pi \space (k \in \N)$, 每次将点绕原点旋转 $\theta$ 并求和 $x$ 坐标之差, 和除以 $(1, 0)$ 每次旋转后到原点的 $x$ 轴无符号距离和即为距离的近似值. 需要注意的是这种方法误差较大, 当 $\theta = \frac{2\pi}{1024}$ 时才能获得 $10^{-6}$ 的绝对误差精度. [例](https://qoj.ac/problem/9289)

- 最优化问题中, 若贡献的计算方式与区间高度相关, 考虑四边形不等式. [例](https://www.luogu.com.cn/problem/P9732)

- 对于 删除若干元素 使得 剩下元素两两之间都需满足某个限制 的题目, 考虑将不满足限制的元素连边, 则成为最小点覆盖问题. [例](https://www.luogu.com.cn/problem/CF164D) & 20240323 T3

- [杨表](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点. [例](https://www.luogu.com.cn/problem/P3774)
