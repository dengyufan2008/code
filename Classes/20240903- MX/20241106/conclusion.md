# 20241106 [梦熊题单](https://www.luogu.com.cn/paste/ft9nu2ko)

- 对于 2048 游戏, 若其局面上的数列具有单调性, 则可以看作一个二进制数. [例](https://www.luogu.com.cn/problem/P7093)

- 一个数的前驱更大值为大根笛卡尔树上对应子树对应区间的左侧一个位置, 后继同理.
  
  $\sum \min(i-p_i, s_i-i)$ 为 $O(n \log n)$ 级别. 证明考虑笛卡尔树上启发式合并. [例](https://www.luogu.com.cn/problem/AT_joi2020ho_e)

- 当有一个 $O(n)$ 和一个对称的 $O(m)$ 做法时, 若 $O(nmk)$ 较小, 则考虑一个 $O(k)$ 做法. 即三次根号分治. [例](https://www.luogu.com.cn/problem/AT_joi2018ho_e)

- 对于一类计数合法的排列问题, 若以排列的值为拓扑序不好考虑, 则考虑题目所给的拓扑序, 并将有限制的元素对应排列的值放进状态中. [例](https://www.luogu.com.cn/problem/AT_joisc2016_c) & 20241110 T2 gravekeeper

- 给定若干区间, 使得每个位置被覆盖至少 $a_i$ 次 这一问题是板的, 可以直接贪心. [例](https://www.luogu.com.cn/problem/AT_joisc2017_d) & 20241110 T1 tracy

byd 在做完这两道题后这天考的两个 Trick 怎么一个想了 1h 一个直接不会.
