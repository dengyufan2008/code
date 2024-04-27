# 20240427 总结

## T1(maze) [数学]

期望:60 实际:50 难度:3 用时:4h

形式化表述要求的东西. 对于一类求参数 $x$ 的最小值使得每个量 $f$ 都为整数的问题, 若每个 $f$ 都正比于 $x$, 则可以表示出 $x = 1$ 时每个 $f$ 的值并据此直接求得 $x$ 的式子.

令 $F_p(n)$ 表示 $n$ 中含有质数 $p$ 的幂数, 则 $F_p{n + m \choose n}$ 是 $p$ 进制下 $n + m$ 的进位次数.

<details>
<summary>Proof</summary>

$$F_p(n!) = \sum_{i \ge 1} \lfloor \frac{n}{p^i} \rfloor$$
$$F_p{n + m \choose n} = \sum_{i \ge 1} \lfloor \frac{n + m}{p^i} \rfloor - (\lfloor \frac{n}{p^i} \rfloor + \lfloor \frac{m}{p^i} \rfloor)$$

则第 $i$ 项只能取 $0$ 或 $1$, 取 $1$ 当且仅当第 $i - 1$ 位发生 向第 $i$ 位的进位.

</details>

当 $p = 2$ 时, 该值即为 PopCount$(n \oplus m \oplus (n + m))$ 或 PopCount$(n)$ + PopCount$(m)$ - PopCount$(n + m)$.

<details>
<summary>Proof</summary>

不进位加法与进位加法的差距 或 进位一次少一个 1.

</details>

可以用以下代码 $O(\log \log n)$ 求 PopCount. 思想为类似线段树的 Pushup.

<details>
<summary>Code</summary>

```c++
#define LL long long

int PopCount(LL x) {
  const static unsigned LL w = -1, w0 = w / 3, w1 = w / 5;
  const static unsigned LL w2 = w / 17, w3 = w / 257;
  const static unsigned LL w4 = w / 65537, w5 = w / 4294967297;
  x = (x & w0) + (x >> 1 & w0);
  x = (x & w1) + (x >> 2 & w1);
  x = (x & w2) + (x >> 4 & w2);
  x = (x & w3) + (x >> 8 & w3);
  x = (x & w4) + (x >> 16 & w4);
  x = (x & w5) + (x >> 32 & w5);
  return x;
}
```

</details>

## T2(city) [不会]

期望:0 实际:0 难度:5 用时:0.25h

## T3(color) [不会]

期望:0 实际:0 难度:5 用时:0.25h

## 结算

最后 30min 一定要把自己会的分拿完, 不要再冲正解. 不要被别人影响.
