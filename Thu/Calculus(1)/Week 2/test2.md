Lemma 1. 设 $\mathbb{F}$ 是一个序域, $a_1, \cdots, a_n, b_1, \cdots, b_n \in \mathbb{F}$, 则 $(a_1b_1+ \cdots +a_nb_n)^2 \le (a_1^2+ \cdots +a_n^2)(b_1^2+ \cdots +b_n^2)$, 且不等式取等 iff 存在 $\lambda \in \mathbb{F}$ 使得 $a_k=\lambda b_k (k=1,2, \cdots ,n)$ 或 $b_k=\lambda a_k (k=1,2, \cdots ,n)$.

Proof. 设 $n$ 维向量 $\vec{a}$ 各维坐标分别为 $a_1, \cdots, a_n$, 同理设 $\vec{b}$ 各维坐标为 $b_1, \cdots, b_n$. 假设 $\vec{a}$ 与 $\vec{b}$ 均不是零向量, 否则容易验证命题成立.

不等式等价于 $(\vec{a} \cdot \vec{b})^2 \le |\vec{a}|^2|\vec{b}|^2$. 我们有 $\vec{a} \cdot \vec{b}=|\vec{a}||\vec{b}| \cos \theta$, 其中 $\theta$ 为 $\vec{a}$ 与 $\vec{b}$ 的夹角. 故不等式等价于 $|\vec{a}|^2|\vec{b}|^2 \cos^2 \theta \le |\vec{a}|^2|\vec{b}|^2$. 消去 $|\vec{a}|^2|\vec{b}|^2$ 得 $\cos^2 \theta \le 1$.

上式显然成立. 不等式取等时显然为 $\theta=0$ 时, 此时 $\vec{a}$ 与 $\vec{b}$ 同向, 自然满足命题中所述条件. $\blacksquare$

Proof2 (使用 deepseek). 设 $S(t)=\sum_{i=1}^n(a_kt+b_k)^2, t \in \mathbb{F}$, 有 $S(t) \ge 0$.

展开 $S(t)$, 有 $S(t)=(\sum_{i=1}^na_k^2)t^2+2(\sum_{i=1}^na_kb_k)t+(\sum_{i=1}^nb_k^2)$. 记 $A=\sum_{i=1}^na_k^2$, $B=\sum_{i=1}^na_kb_k$, $C=\sum_{i=1}^nb_k^2$, 有 $S(t)=At^2+2Bt+C \ge 0$. 对 $A \ge 0$ 进行分类讨论, 有

- $A=0$.

  若 $B \ne 0$, 取 $t=-\frac{C+1}{2B}$, 有 $S(t)<0$, 矛盾. 故 $B=0$, 进而有 $B^2 \le AC$.

- $A>0$.

  有 $S(t)=A(t+\frac{B}{A})^2-\frac{B^2}{A}+C$. 取 $t=-\frac{B}{A}$ 有 $-\frac{B^2}{A}+C \ge 0$, 即 $B^2 \le AC$. 不等式取等当且仅当 $S(-\frac{B}{A})=0$.

综上所述, 有 $B^2 \le AC$, 不等式取等当且仅当 $A=0$ 或 $S(-\frac{B}{A})=0$. 注意到 $B^2 \le AC$ 即命题中不等式, 下考虑取等条件.

显然 $A=0$ 即 $a_i=0$, 又即 $a_i=0b_i$, $S(-\frac{B}{A})=0$ 即 $a_kt+b_k=0$, 又即 $b_k=(-t)a_k$. 显然等价于命题中描述的条件. $\blacksquare$
