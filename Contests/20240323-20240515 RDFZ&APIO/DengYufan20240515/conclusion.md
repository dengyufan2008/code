# 20240515 总结

## T1(matrix) [最小割]

期望:100 实际:100 难度:1 用时:0.75h

最小割若要输出方案, 不能直接将边权为 0 的边当作被割的边, 但可以将边权非 0 的边当作未割的边. 原因显然.

## T2(card) [期望 Dp]

期望:100 实际:100 难度:2.5 用时:2h

20240507 讲题 讲过的东西. 具体为考虑一次有效的拿取物品. 此处略.

## T3(string) [01 串变换] [观察力]

期望:20 实际:20 难度:3 用时:2h

若对于一个 01 环, 每次将 01 变成 10, 则相当于 长度 $> 1$ 的 0 连续段每次向右移 1, 1 连续段左移 1, 相撞则均减 1.

## 结算

似乎发挥的还不错? T3 还不会, 暂且不做评价.
