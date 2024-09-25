# 20240504 讲[题](https://www.luogu.com.cn/api/team/downloadFile/5n4g6qh1)总结

- 对于一类贪心问题, 找到对贡献影响很大的关键点, 据此来调整非关键点从而得到特殊性质.
  
  若要查是否存在一个任意的元素满足其附带属性恰好为 $k$, 若有存在 $k$ 则必存在 $k - 2$, 则可以分奇偶维护 $k$ 的最大值. [例](https://www.luogu.com.cn/problem/AT_agc028_e)

- 对于一类排序后两两对应需满足同一类不等关系的限制, 考虑一个值域上的前缀/后缀和数组, 限制变为任意一个位置都 $\ge 0$. [例](https://www.luogu.com.cn/problem/CF533A)

- 对于一类贡献形如 $\max(a_i, a_{i + 1})$, 考虑将其变形为 $a_i + max(a_{i + 1} - a_i, 0)$, 则只需考虑上升部分的距离. [例](https://www.luogu.com.cn/problem/P10197)

- 对于一类确定树的形态的问题, 只需考虑一个点的邻点集合与邻点中哪个是父亲. [例](https://www.luogu.com.cn/problem/CF1129E)

- 对于一类限定某些元素要在两个元素之间的问题, 考虑从两边往中间构造. [例](https://www.luogu.com.cn/problem/P7056)

附: 讲[课](https://www.luogu.com.cn/api/team/downloadFile/byor0cng)内容
