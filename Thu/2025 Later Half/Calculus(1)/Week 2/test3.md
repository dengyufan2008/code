本题会用到第四题所证结论, 即均值不等式.

---

Lemma 1. 设 $x_1, \cdots, x_n>-1$ 且 $x_ix_j \ge 0 \space (\forall i, j \in \set{1, 2, \cdots, n})$, 则 $(1+x_1) \cdots (1+x_n) \ge 1+(x_1+ \cdots + x_n)$. 其中不等式取等 iff $x_1, \cdots, x_n$ 中至多一个非零.

Proof. 注意到, 交换 $x_i$ 和 $x_j$ 的值不影响不等式两侧各自的值, 且当 $x_n=0$ 时删去 $x_n$ 并令 $n \leftarrow n-1$ 不影响不等式两侧各自的值. 故下假设 $x_i \ne 0$, 不等式取等条件变为 $n \le 1$.

设 $A = \{n | \forall x_1, \cdots, x_n>-1 \land x_i \ne 0 \land x_ix_j \ge 0 \space (\forall i, j \in \set{1, 2, \cdots, n}) \rightarrow (1+x_1) \cdots (1+x_n) > 1+(x_1+ \cdots + x_n)\}$.

下证 $2 \in A$. 有 $(1+x_1)(1+x_2)=1+(x_1+x_2)+x_1x_2$. 由于 $x_1x_2 \ge 0$, 且 $x_1, x_2 \ne 0$, 故 $x_1x_2>0$, $1+(x_1+x_2)+x_1x_2 > 1+(x_1+x_2)$.

现假设 $n \in A$, 试证明 $S(n)=n+1 \in A$. 考虑任意一个 $x_1, \cdots, x_{n+1}>-1 \land x_i \ne 0 \land x_ix_j \ge 0 \space (\forall i, j \in \set{1, 2, \cdots, n})$, 不失一般性地, 设 $x_{n+1} \le x_i$.

当 $x_1+ \cdots +x_{n+1} \le -1$ 时, 有不等式左侧为正, 右侧非正, 故命题成立.

当 $x_1+ \cdots +x_{n+1} > -1$ 时, 此时有 $x_{n+1} \le \frac{1}{n+1} (x_1+ \cdots +x_{n+1})$, $x_1+ \cdots +x_n \ge \frac{n}{n+1} (x_1+ \cdots +x_{n+1}) > -\frac{n}{n+1} > -1$. 又有 $(x_1+ \cdots x_n)x_{n+1}=x_1x_{n+1}+ \cdots +x_nx_{n+1} \ge 0$.

运用归纳假设, 得 $(1+x_1) \cdots (1+x_n) > 1+(x1+ \cdots +x_n)$, 故 $(1+x_1) \cdots (1+x_{n+1}) > [1+(x_1+ \cdots +x_n)](1+x_{n+1}) > 1+(x_1+ \cdots +x_{n+1})$.

故 $A=\N \setminus \set{0, 1}$. 当 $n \le 1$ 时, 显然有不等式取等. $\blacksquare$

---

Lemma 2. 设 $x>-1$, $n \in \N$, 则 $(1+x)^n \ge 1+nx$, 不等式取等当且仅当 $n \in \set{0, 1} \lor x=0$.

Proof. 将 $x_i=x$ 代入 Lemma 1 可得自然推论.

---

Lemma 3. $\forall n \in \N^*$, $a, b>0$, 有 $ab^n \le (\frac{a+nb}{n+1})^{n+1}$, 且不等式取等 iff $a=b$.

Proof. 取 $x_1=a$, $x_2=x_3=\cdots=x_{n+1}=b$, 有 $ab^n=x_1x_2 \cdots x_{n+1} \le (\frac{x_1+x_2+\cdots+x_{n+1}}{n+1})^{n+1}=(\frac{a+nb}{n+1})^{n+1}$, 且不等式取等当且仅当 $x_1=x_2=\cdots=x_{n+1}$, 即 $a=b$. $\blacksquare$

---

引理. 若 $n > 1$ 且 $x > 0$, 则 $(1+x)^n > 1+nx$.

Proof. 令 $y=nx>0$. 不等式化为 $1+y < (1+\frac{y}{n})^n$. 取 $a=1+y$, $b=1$, $n'=n-1$, 根据 Lemma 3 有 $1+y \le (\frac{y}{n}+1)^n$. 显然 $a \ne b$, 故不等式永不取等. $\blacksquare$

---

Lemma 4. 数列 $\set{(1+ \frac{1}{n})^n}$ 单调递增, 且数列 $\set{(1+ \frac{1}{n})^{n+1}}$ 单调递减.

Proof. 先证数列 $\set{(1+ \frac{1}{n})^n}$ 单调递增.

也即对于 $n \in \N$, $(1+ \frac{1}{n})^n < (1+ \frac{1}{n+1})^{n+1}$, 不等式化为 $(1+ \frac{1}{n+1})^\frac{n+1}{n} > 1+ \frac{1}{n}$.

显然 $\frac{n+1}{n}>1$, $\frac{1}{n+1}>0$, 根据引理, $(1+ \frac{1}{n+1})^\frac{n+1}{n} > 1 + \frac{1}{n}$. $\blacksquare$

再证数列 $\set{(1+ \frac{1}{n})^{n+1}}$ 单调递减.

也即对于 $n \in \N$, $(1+\frac{1}{n})^{n+1} > (1+\frac{1}{n+1})^{n+2}$, 不等式化为 $(1+\frac{1}{n})^\frac{n+1}{n+2} > 1+\frac{1}{n+1}$. 同样地根据引理, 有 $(1+\frac{1}{n})^\frac{n+1}{n+2} > 1+\frac{n+1}{n(n+2)}=1+\frac{n+1}{(n+1)^2-1}>1+\frac{n+1}{(n+1)^2}=1+\frac{1}{n+1}$. $\blacksquare$
