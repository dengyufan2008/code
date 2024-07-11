# 又一道计数[题](https://www.luogu.com.cn/problem/AT_agc021_f)

定义一个 $n$ 行 $m$ 列的 01 矩阵的 $a_j$ 数组为第 $j$ 行第一个 1 的列, $b_i$ 为 $i$ 列第一个的行, $c_i$ 为最后一个的行, 若没有 1 则为 0. 求本质不同的 01 矩阵数量, 本质不同定义为 $(a_j, b_i, c_i)$ 不同.

$1 \le n \le 8000$, $1 \le m \le 200$.

---

不妨假设矩阵内只有对 $a_j$, $b_i$, $c_i$ 有贡献的位置才会是 1, 则要统计合法的矩阵数量.

显然以行作为拓扑序很愚蠢, 考虑从第 $i-1$ 列转移到第 $i$ 列.

然后是计数题的一个经典套路, 如果 要统计的东西有至少两维 且 限制不足以使得每个元素的这两维有较好的关系, 则可以 每次插入 拓扑序维 值为当前枚举的值 的元素.

故设 $f_{i,j}$ 表示考虑了前 $i$ 列, 有 $j$ 行已经确定了第一个 1 的位置, 的合法矩阵数量.

考虑转移, 每次可以插入若干行并将这些行的 $a_j$ 设为 $i$. 同时可以在这些插入的行两边各选一个已经存在的行将这一列的 $b_i$ 和 $c_i$ 设为选定值, 当然也可以不选. 需要特判一行都不插的情况, 此时选的是左端点还是右端点没有区别, 需要减去部分系数. 故有

$$f_{i,j} = f_{i-1,j}(-j) + \sum_{k=0}^j f_{i-1,j-k} (\sum_{1 \le l \le r \le j} {r-l-1 \choose k} + 2 \sum_{x=1}^j {j-x \choose k} + {j \choose k})$$

考虑化简这坨很丑的系数. 这部分可以跳过.

$$\sum_{1 \le l \le r \le j} {r-l-1 \choose k} + 2 \sum_{x=1}^j {j-x \choose k} + {j \choose k}$$

$$\sum_{x=0}^{j-2} {x \choose k} (j-x-1) + 2 \sum_{x=0}^{j-1} {x \choose k} + {j \choose k}$$

$$\sum_{x=0}^j {x \choose k} (j-x+1)$$

$$(j+2) \sum_{x=0}^j {x \choose k} - \sum_{x=0}^j {x \choose k} (x+1)$$

$$(j+2) {j+1 \choose k+1} - (k+1) \sum_{x=0}^j {x+1 \choose k+1}$$

$$(j+2) {j+1 \choose k+1} - (k+1) {j+2 \choose k+2}$$

$$(k+2) {j+2 \choose k+2} - (k+1) {j+2 \choose k+2}$$

$${j+2 \choose k+2}$$

故

$$f_{i,j} + f_{i-1,j}j = \sum_{k=0}^j f_{i-1,j-k} {j+2 \choose k+2}$$

现在我们能够 $O(n^2 m)$ 了, 考虑优化转移.

$$\frac{f_{i,j} + f_{i-1,j}j}{(j+2)!} = \sum_{k=0}^j \frac{f_{i-1,j-k}}{(j-k)!} \frac{1}{(k+2)!}$$

NTT 即可. $O(nm \log n)$.
