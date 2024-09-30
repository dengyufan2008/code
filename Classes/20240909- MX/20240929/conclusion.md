# 20240929 [梦熊题单](https://www.luogu.com.cn/paste/od08eg6w)

- 对于一类指数级做法的题目, $q$ 次询问一般是没有意义的, 需要对于每个集合都求出答案.
  
  类似 20240228 T2 地, 若一个状态 $P$ 能够转移到若干状态 $Q_i$, 而取其中一个转移 $\mathcal F: P \rightarrow R$, 对所有 $Q_i \neq R$ 有 $\mathcal F(Q_i) = P$, 则可以将每个状态 $P$ 的期望 $E(P)$ 用 $A_P + B_P E(\mathcal F(P))$ 表示, 由于 $E(Q_i) = A_{Q_i} + B_{Q_i} E(P)$ , 可以分别得到 $A_P$ 和 $B_P$ 的递推式. 例如树上转移到每个邻点的问题可以用父亲的期望来表示. [例](https://www.luogu.com.cn/problem/P5643)

- 当最小化问题的答案存在明显上界时, 考虑其是否同时也是下界. [例](https://www.luogu.com.cn/problem/CF2B)

- 当题目只需要求生成树时, 同样也应当使用生成树算法, 且此时可以自行添加边权. [例](https://www.luogu.com.cn/problem/CF653E)

- 当存在两种元素, 其中只有第一种元素有限制时, 考虑先将第一种元素满足限制地排列好, 再将第二种元素插进去. [例](https://www.luogu.com.cn/problem/CF316D3)

- 找到规律后一定要验证. 验证之后考虑规律能否化简 (比如白色的连续段奇偶交替出现且两侧恰好有一个奇段 $\Leftrightarrow$ 白色个数为奇数). [例](https://www.luogu.com.cn/problem/AT_arc143_e)

- 当问题涉及到的元素过多时, 考虑将元素划分等价类使得不同等价类之间的元素无关.
  
  对于两维长度差异较大的数组, 要么将较大一维放在前面, 要么使用滚动或类似背包的处理方式消去一维, 可以大大降低常数. [未使用滚动数组, >8s](https://atcoder.jp/contests/arc184/submissions/58274623) & [使用滚动数组, <5s](https://atcoder.jp/contests/arc184/submissions/58274888). [例](https://www.luogu.com.cn/problem/AT_arc184_b)

- 将二维状态的 Dp 优化到 $< O(n^2)$ 时, 不仅需要考虑类似重链剖分中的第二维不超过子树大小, 同样需要考虑有无更加紧的限制.
  
  对于一类分数规划的二分答案解法, 判断完后用 ``mid`` 来更新左右端点是不优的, 应当用本次求解出的答案来更新. [例](https://www.luogu.com.cn/problem/P3319)

- 对于一类字符串题目, 寻找性质时不要在 SAM 上找, 而应当在字符串上找并将其映射至 SAM 上. [例 (线性做法)](https://qoj.ac/problem/562)

- 回文串需要考虑回文中心的每个可能出现的位置, 尤其是当回文串长度为偶数时. [例](https://www.luogu.com.cn/problem/P4324)
