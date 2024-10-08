# 20240729 [HDUACM (vp)](https://acm.hdu.edu.cn/contest/problems?cid=1127) 总结

## T1(超维攻坚) [三维凸包]

难度:3.5

难度主要集中在实现.

两个三维向量的叉乘即为这个面的法向量, 三点共线时叉乘为 0.

三个向量的行列式即为平行四面体的体积, 四点共面时行列式为 0.

## T2(黑白边游戏) [简化状态]

难度:3

对于编号不影响的有编号图, 考虑将其同构的缩成一个等价类从而压缩状态.

## T3(最优 k 子段) [二分答案] [贪心]

难度:3

求解最大子段和除了朴素的 Dp 外, 还能够枚举右端点维护左端点最小的前缀和.

当数据随机且题面中有质数的限制时, 考虑 Prime Gap = log.

## T4(分组) [Meet in the Middle] [前缀和优化]

难度:3

对于每个元素带权且贡献与权的最值有关, 考虑将所有元素按权排序. 此时下标与权单调, 则对于下标的取值范围的限制可以转化为对于权的最终取值添加一个上下界.

## T5(多层血条) [模拟]

难度:2

略.

## T6(延时操控) [简化状态]

难度:2

考虑一个状态的合法条件, 从而反向限制状态的范围. 事实上可以不用考虑, 使用记忆化搜索实现即可, 但强制需要写收集型.

## T7(序列更新) [根号分治]

难度:3

对于一类 checkmax 的操作, 考虑序列中的前 $B$ 大. 由于值是单调的, 同样可以考虑势能分析.

## T8(魔法卡牌) [搜索优化]

难度:4

对于一类 NPC 问题, 考虑简化状态并预先 Dp 出一类状态的时间复杂度上界, 每次取最优的转移. 如果上界过于大, 则多分几类讨论.

## T9(昵称检索) [略]

难度:1

值得一提的是, 将所有合法的月份+日期 (如 0715, 0229) 反着插入字典树, 那么得到的结点数恰好是 715.

## T10(矩阵的周期) [转化实际意义]

难度:3.5

一个 01 正方形矩阵可以视为邻接矩阵. 取若干次方就是走若干条边.

## T11(找环) [最小均值回路]

难度:3

[最小均值回路](https://www.luogu.com.cn/article/ft3tx54e) 相关知识点.

## T12(寻找宝藏) [分类讨论] [扫描线]

难度:2

对于给定的限制较弱的情况 (即与无限制相比差距不大), 考虑直接分类讨论并使用类似无限制的方式解决.
