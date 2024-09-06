# 20240903 [梦熊题单](https://www.luogu.com.cn/paste/3uzzihcg)

- 对于一类求与凸包类似的东西的问题, 考虑用类似的算法, 只需要保证每次转移最近的点一定最优, 且一个元素其后面不合法的元素构成一个后缀即可. [例](https://qoj.ac/problem/8556)

- 判断一个序列是否是等差序列可以用 ``set`` 维护数集, ``multiset`` 维护相邻两项的差值. 支持动态增删. [例](https://www.luogu.com.cn/problem/P7205)

- 对于一类每个元素的贡献都为一个凸壳且贡献方式为加法的问题, 若元素之间的限制仅有偏序关系, 则寻找贡献的最值可以使用整体二分. 具体参考 [保序回归](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点. [例](https://loj.ac/p/6518)

- 对于一类形如 "所有在范围内的数 +1/-1" 的表述, 考虑差分.
  
  对于一类求每种方案的贡献和的计数题, 若一种方案的贡献不好求, 考虑构造一种 "维护一个 (几个) 变量并进行操作贡献答案" 的类自动机算法, 从而可以 Dp 转移.
  
  比如, 例题中的类自动机算法为 $s \leftarrow \max(s + a_i, i)$, $ans \leftarrow ans + s - (n + i - 1)$, $s \leftarrow \min(s, n + i - 1)$. [例](https://qoj.ac/problem/8820) & [解](https://www.cnblogs.com/275307894a/p/18267708)
