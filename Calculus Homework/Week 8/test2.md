设 $f \in \mathscr C^1 [a, b]$.

Lemma 1. $\int_a^b \sqrt{1+f'(x)^2} \text{d}x \ge \sqrt{(b-a)^2+(f(b)-f(a))^2}$, 等号成立 iff $f'$ 为常值函数.

Proof. 对于标准平面内点, 我们有 $\langle x, y \rangle^2 \le \langle x, x \rangle \langle y, y \rangle$, 即 $\langle x, y \rangle + \langle y, x \rangle \le 2 \sqrt{\langle x, x \rangle \langle y, y \rangle}$, $\langle x+y, x+y \rangle \le (\sqrt{\langle x, x \rangle} + \sqrt{\langle y, y \rangle})^2$, $||x+y|| \le ||x||+||y||$. 不等式取等 iff $x$ 和 $y$ 线性相关.

进一步运用数学归纳法容易得到, $||x_1+x_2+\cdots+x_n|| \le ||x_1|| + ||x_2|| + \cdots + ||x_n||$, 不等式取等 iff $x_i$ 和 $x_j$ 两两线性相关.

故 $\sum_{i=1}^n \sqrt{1+f'(x_i)^2} \ge \sqrt{n^2 + (\sum_{i=1}^n f'(x_i))^2}$, 不等式取等 iff $(1, f'(x_i))$ 两两线性相关, 即 $f'(x_i)$ 为定值.

故 $\sum_{i=1}^n \frac{b-a}{n} \sqrt{1+f'(x_i)^2} \ge \sqrt{(b-a)^2 + (\sum_{i=1}^n \frac{b-a}{n} f'(x_i))^2}$. 取 $x_i \in [(i-1)\frac{b-a}{n}, i\frac{b-a}{n}]$, 则得到 $[a, b]$ 的一组划分. 令 $n \rightarrow +\infty$, 则有 $\int_a^b \sqrt{1+f'(x)^2} \text{d}x \ge \sqrt{(b-a)^2+(f(b)-f(a))^2}$, 不等式取等 iff $f'$ 为常值函数. $\blacksquare$
