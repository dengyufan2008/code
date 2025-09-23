引理. 若 $n$ 为正整数, 则 $n < 2^n$.

Proof. 若 $n=1$, 则不等式成立. 否则 $n \ge 2$, 对 $2^n=(1+1)^n$ 进行二项式展开, 有其第一项为 1, 第二项为 $n$, 且每一项非负. $\blacksquare$

---

Lemma 1. 若 $\mathbb{F}$ 是序域, 对于任意正整数 $n$ 和非负数 $x_1, \cdots, x_n \in \mathbb{F}$, 有 $x_1 x_2 \cdots x_n \le (\frac{x_1+x_2+ \cdots +x_n}{n})^n$. 不等式取等当且仅当 $x_1=x_2= \cdots =x_n$.

Proof. 设 $z_n = \frac{x_1+x_2+ \cdots +x_n}{n}$. 不等式等价于保证 $x_1+x_2+ \cdots +x_n=nz_n$ 的情况下, $x_1 x_2 \cdots x_n \le z_n^n$, 且不等式取等当且仅当 $x_1=x_2= \cdots =x_n$.

设命题 $P(m)$ 表示保证 $x_1+x_2+ \cdots +x_m=mz_m$ 的情况下, $x_1 x_2 \cdots x_m \le z_m^m$, 且不等式取等当且仅当 $x_1=x_2= \cdots =x_m$.

设 $A= \set{n \in \N | P(2^n)}$, 显然 $0 \in A$. 试证明 $1 \in A$.

考虑 $a^2+b^2-2ab=(a-b)^2 \ge 0$, 即 $ab \le \frac{a^2+b^2}{2}$, 不等式取等当且仅当 $a=b$. 代入 $a=\sqrt x_1$, $b=\sqrt x_2$, 得 $\sqrt{x_1x_2} \le \frac{x_1+x_2}{2}=z_2$. 两侧平方得 $x_1x_2 \le z_2^2$, 不等式取等当且仅当 $x_1=x_2$. 故 $1 \in A$.

再试证明对于 $0 < d \in N$, $d \in A \rightarrow d+1 \in A$. 设 $g=2^d$, 因为 $1 \in A$, 有 $x_1x_2 \cdots x_{2g} \le (\frac{x_1+x_2}{2})^2 (\frac{x_3+x_4}{2})^2 \cdots (\frac{x_{2g-1}+x_{2g}}{2})^2 = (\frac{x_1+x_2}{2} \frac{x_3+x_4}{2} \cdots \frac{x_{2g-1}+x_{2g}}{2})^2$. 又因为 $d \in A$, 有 $(\frac{x_1+x_2}{2} \frac{x_3+x_4}{2} \cdots \frac{x_{2g-1}+x_{2g}}{2})^2 \le (\frac{\frac{x_1+x_2}{2}+\frac{x_3+x_4}{2}+\cdots+\frac{x_{2g-1}+x_{2g}}{2}}{g})^{2g}$, 故 $x_1x_2 \cdots x_{2g} \le (\frac{x_1+x_2+\cdots+x_{2g}}{2g})^{2g}$, 不等式取等当且仅当 $x_1=x_2=\cdots=x_{2g}$, $d+1 \in A$. 故 $A=\N$.

现在考虑任意正整数 $n$ 对应的 $P(n)$. 有 $n < 2^n$ 且 $P(2^n)$, 故有 $x_1x_2 \cdots x_n z_n^{2^n-n} \le (\frac{x_1+x_2+\cdots+x_n+(2^n-n)z_n}{2^n})^{2^n}$. 由于有 $\frac{x_1+x_2+\cdots+x_n+(2^n-n)z_n}{2^n}=(x_1+x_2+\cdots+x_n) \frac{1+\frac{2^n-n}{n}}{2^n}=z_n$, 故不等式化为 $x_1x_2 \cdots x_n z_n^{2^n-n} \le z_n^{2^n}$ 即 $x_1x_2 \cdots x_n \le z_n^n$. 不等式取等当且仅当 $x_1=x_2=\cdots=x_n$. $\blacksquare$
