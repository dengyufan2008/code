# 又一道数学[题](https://community.topcoder.com/stat?c=problem_statement&pm=11351)

给定集合 $S=\{x \mid 0 \le x \le n - 1\}$. 求在 $S$ 中恰好选 $k$ 个数使得总和为 $n$ 的倍数的方案数.

$1 \le k \le 1000$, $1 \le n \le 10^9$, $1 \le k \le n$.

答案即为

$$\sum_i [n \mid i] [x^i y^k] \prod_{j=0}^{n-1} (x^jy+1)$$

我们有

$$[n \mid i] = \frac{1}{n} \sum_{j=0}^{n-1} \omega_n^{ij}$$

<details>
<summary>Proof</summary>

- $n \mid i$

  显然成立.

- $n \nmid i$

  根据等比数列求和, 有

  $$\sum_{j=0}^{n-1} \omega_n^{ij} = \frac{1-\omega_n^{in}}{1 - \omega_n^i}$$
  
  因为 $\omega_n^i \neq 1$, $\omega_n^{in} = 1$, 故成立.
</details>

因此当 $x = \omega_n$ 即 $x^j = \omega_n^j$ 时, $\frac{1}{n} \sum_{i=0}^{n-1} x^{ij} = [n \mid j]$.

原式化为

$$\frac{1}{n} \sum_{i=0}^{n-1} [y^k] \prod_{j=0}^{n-1} (\omega_n^{ij}y+1)$$

<details>
<summary>Explanation</summary>

考虑固定一个 $\sum j = s$, 则有 $\frac{1}{n} \sum_{i=0}^{n-1} \omega_n^{is} = [n \mid s]$ 的贡献.
</details>

发现 prod 项的 $i$ 与 $n$ 事实上只会通过 $\gcd(i,n) = d$ 来决定式子的值. 具体而言, 编号为 $[0,n)$ 的环上 $d$ 的倍数会出现 $\frac{n}{d}$ 次.

枚举 $d$ 有

$$\frac{1}{n} \sum_{d \mid n} [y^k] \prod_{j=0}^{\frac{n}{d}-1} (\omega_n^{dj}y+1)^d \sum_{i=0}^{n-1} [\gcd(i,n)=d]$$

$$\frac{1}{n} \sum_{d \mid n} [y^k] \prod_{j=0}^{d-1} (\omega_n^{\frac{n}{d}j}y+1)^\frac{n}{d} \sum_{i=0}^{n-1} [\gcd(i,n)=\frac{n}{d}]$$

因为

$$\omega_n^\frac{n}{d} = \omega_d \space (d \mid n)$$

<details>
<summary>Proof</summary>

左侧转 $d$ 次恰好转完一圈, 右侧同理, 故得证.
</details>

且因为

$$\sum_{i=0}^{n-1} [\gcd(i,n)=\frac{n}{d}] = \varphi(d)$$

<details>
<summary>Proof</summary>

$i = \frac{n}{d}$ 时显然有 $1$ 的贡献, 且是最小的有贡献的数. 考虑将其扩倍, 但不能将分母上的 $d$ 约分掉, 故能有 $\varphi(d)$ 种扩倍的方式.
</details>

有

$$\frac{1}{n} \sum_{d \mid n} \varphi(d) [y^k] \prod_{j=0}^{d-1} (\omega_d^jy+1)^\frac{n}{d}$$

考虑

$$\prod_{j=0}^{d-1} (\omega_d^jy+1) = (-1)^{d+1}y^d+1$$

<details>
<summary>Proof</summary>

左式关于 $y$ 的方程的解集为 $T = \{\frac{-1}{\omega_d^j} \mid 0 \le j \le d-1 \}$.
- $2 \mid d$

  $T = \{\omega_d^j \mid 0 \le j \le d-1 \}$. 由代数基本定理得其与 $y^d-1$ 成倍数关系. 代入 $y = 0$ 发现其等于 $1-y^d$, 即右式.

- $2 \nmid d$

  $T = \{-\omega_d^j \mid 0 \le j \le d-1 \}$. 同理等于 $y^d+1$ 即右式.
</details>

故原式即

$$\frac{1}{n} \sum_{d \mid n} \varphi(d) [y^k] [(-1)^{d+1}y^d+1]^\frac{n}{d}$$

则 $d$ 显然需要是 $k$ 的因数

$$\frac{1}{n} \sum_{d \mid n,d \mid k} \varphi(d) [y^\frac{k}{d}] [(-1)^{d+1}y+1]^\frac{n}{d}$$

$$\frac{1}{n} \sum_{d \mid n,d \mid k} \varphi(d) {\frac{n}{d} \choose \frac{k}{d}} [(-1)^{d+1}]^\frac{n}{d}$$

$$\frac{(-1)^n}{n} \sum_{d \mid n,d \mid k} \varphi(d) {\frac{n}{d} \choose \frac{k}{d}} (-1)^\frac{n}{d}$$

于是筛出 $\varphi(d)$ 后枚举 $d$ 暴力算组合数可以做到 $O(k^\frac{4}{3})$.
