# 二分图博弈

给定一张二分图, 有一枚棋子在一个左部点上. A 和 B 依次行动, 每次将棋子移到有边相连的另一点, 不能移动至之前到过的点, 无法移动者输. 对每个初始结点 $v$ 计算 $f(v)$ 表示 A 必胜 (1) 或必败 (0).

$1 \le n \le 10^5$, $1 \le m \le 4 \times 10^5$.

---

设 $W$ 表示 **所有** 最大匹配方案构成的集合, $M$ 表示一个最大匹配方案, $M(v)$ 表示 $v$ 所匹配的点.

对于一个初始结点 $v$, $M \in W \Rightarrow v \in M \Leftrightarrow f(v)=1$.

  <details><summary>Proof</summary>

  >  - 充分性
  >
  >    任取一个最大匹配 $M$, A 将棋子从 $v$ 移至 $M(v), 则 B 无法移动 或 只能沿非匹配边移动至 $u$. 假设 $u \notin M$, 则可以将 $M$ 中的匹配 $(v, M(v))$ 改为 $(u, M(v))$ 得到最大匹配 $M'$ 且 $v \notin M'$. 故 $u \in M$, A 可以继续移动至 $M(u)$, 故 A 必胜.
  >  - 必要性
  >
  >    假设有 $M \in W$ 且 $v \notin M$, 则 A 无法移动 或 只能沿非匹配边移动至 $u$, 由于不存在增广路, 有 $u \in M$, 则 B 可以移动至 $M(u)$. 故 A 必败.
  </details>

建立经典的网络流求最大匹配模型, 边权全为 1. 考虑任意一个最大流 $F$ 与其残量网络 $G$ (有流量的边反向).

对于源点 $s$ 能到达的左部点集 $S$, 有 $v \in S \Leftrightarrow f(v)=0$, 即 $v \in S \Leftrightarrow \exist M \in W, v \notin M$.

  <details><summary>Proof</summary>

  >  - 充分性
  >
  >    假设有一最大匹配 $M$ 使得 $v \in M$, 则必然存在一条简单路径 $P$ 从 $s$ 到 $v$ 和 $G$ 中的一条边 $(v, s)$. 则 $P + (v, s)$ 形成环流, 可以构造 $M'$ 使得 $v \notin M'$.
  >  - 必要性
  >
  >    假设 $\forall M \in W, v \in M$, 则对于残量网络 $G$ 中不存在环流同时经过 $s$ 和 $v$. 又有 $G$ 中存在边 $(v, s)$, 则不存在简单路径 $P$ 从 $s$ 到 $v$, 则 $v \notin S$.
  </details>

故直接做即可, $O(m \sqrt n)$.

# 线性规划对偶

给定一个序列 $a_i$, 要求用两种形式的串覆盖每个位置 $a_i$ 次. 一种为覆盖一个区间, 一种为在一个区间内覆盖一个跳过一个. 问最少用的串个数.

$1 \le n \le 10^6$, $1 \le a_i \le 10^9$.

---

设一个串能覆盖到的点集为 $S_j$, 则 $\{2, 4, 6\}$ 为一个合法的 $S_j$, 设合法的 $S_j$ 总数为 $m$.

设 $m$ 维向量 $z$ 表示每种串使用的数量, 需满足 $z_i \ge 0$.

则需满足 $\forall i, \sum_j z_j [i \in S_j] = a_i$, 变形为 $\forall i, \sum_j z_j [i \in S_j] \ge a_i$ 且 $\forall i, \sum_j -z_j [i \in S_j] \ge -a_i$.

设 $2n$ 维向量 $t$ 满足 $t_i = a_i (-1)^{[n + 1 \le i \le 2n]}$.

设 $2n \times m$ 的矩阵 $A$ 满足 $A_{i,j} = [i \in S_j] (-1)^{[n + 1 \le i \le 2n]} \space (1 \le i \le 2n)$.

设单位 $m$ 维向量 $i$ 满足 $i_i = 1$.

则可将限制条件改写为 $Az \ge t$, $z \ge 0$, 需要最小化 $z \cdot i$.

其答案等于 $A^Tz' \le i, z \ge 0$, 最大化 $z' \cdot t$, 其中 $z'$ 为一 $2n$ 维向量.

  <details><summary>Proof</summary>

  >  不会.
  </details>

即需满足 $\forall j, \sum_i [i \in S_j] (-1)^{[n + 1 \le i \le 2n]} z'_i \le 1, z'_i \ge 0$, 最大化 $\sum_i z'_i a_i (-1)^{[n + 1 \le i \le 2n]}$.

设 $n$ 维向量 $x$ 与 $y$ 满足 $z' = [x \space y]$.

条件改写为 $\forall j, \sum_i [i \in S_j] (x_i - y_i) \le 1, x_i \ge 0, y_i \ge 0$, 最大化 $\sum_i a_i (x_i - y_i)$.

设 $n$ 维向量 $d$ 满足 $d = x - y$.

条件继续改写为 $\forall j, \sum_i [i \in S_j] d_i \le 1$, 最大化 $\sum_i a_i d_i$.

由于对于所有 $1 \le i \le n$, 有 $\{i\}$ 为合法的 $S_j$, 则 $d_i \le 1$.

考虑 $\max_j \sum_i [i \in S_j] d_i$ 事实上为 3 种最大子段和 (全局, 奇数位, 偶数位), 则当 $d_i = -1$ 时只要前面的部分合法 (最大子段和 $\le 1$), $i$ 这段前缀必然被舍弃. 故 $d_i \ge -1$. 故 $d_i \in \{-1, 0, 1\}$.

因此设 $f_{i, s0, s1, s2}$ 表示考虑了前 $i$ 位, 3 种最大子段和分别为 $s0$, $s1$, $s2$ ($0 \le s0$, $s1$, $s2 \le 1$) 的最大 $\sum_i a_i d_i$, 转移考虑 $d_{i+1}$ 的三种取值.

$O(n)$.

# 多项式快速幂

给定 $k$ 项的多项式 $F$ 和 $m$, 求 $G = F^m$ 的前 $n$ 项系数, 对 $10^9 + 7$ 取模.

$1 \le n \le 5 \times 10^6$, $1 \le m \le 10^{18}$, $1 \le k \le 5$

---

两边求导,
$$G' = mF^{m-1}F'$$

同乘 $F$,
$$G'F = mGF'$$

取第 $n$ 项系数
$$\sum_{i=0}^{k-1} (n-i+1)g_{n-i+1}f_i = m \sum_{i=0}^{k-1} ig_{n-i+1}f_i$$

$$\sum_{i=0}^{k-1} (mi+i-n-1)g_{n-i+1}f_i = 0$$

$$\sum_{i=1}^{k-1} (mi+i-n-1)g_{n-i+1}f_i = (n+1)g_{n+1}f_0$$

$$g_{n+1} = \frac{\sum_{i=1}^{k-1} (mi+i-n-1)g_{n-i+1}f_i}{(n+1)f_0}$$

特别地, $g_0 = f_0^m$, 其余项均可递推得到.

$O(nk)$.
