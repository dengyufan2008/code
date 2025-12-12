Lemma 1. 设 $f \in \mathscr C^1[0, 1]$, $f(0)=f(1)=0$. 则 $|\int_0^1 f(x) \text{d}x| \le \frac{1}{4} \max_{x \in [0, 1]} |f'(x)|$.

Proof. 设 $t=\max_{x \in [0, 1]} |f'(x)|$. 显然 $f(x) \le tx$ 且 $f(x) \le -tx+t$. 故 $|\int_0^1 f(x) \text{d}x| \le |\int_0^\frac{1}{2} f(x) \text{d}x| + |\int_\frac{1}{2}^1 f(x) \text{d}x| \le |\int_0^\frac{1}{2} tx \text{d}x| + |\int_\frac{1}{2}^1 -tx+t \text{d}x| = \frac{1}{4}t$. $\blacksquare$

---

Lemma 2. 设 $f \in \mathscr C^1[a, b]$, $f(a)=0$. 则 $\max_{x \in [a, b]} f^2(x) \le (b-a)\int_a^b f'^2(x) \text{d}x$, $\int_a^b f^2(x) \text{d}x \le \frac{(b-a)^2}{2} \int_a^b f'^2(x) \text{d}x$.

Proof. 先证第一个不等式. 设 $g(x)=f'(x)$, $t=\max_{x \in [a, b]} f(x)$, $p \in [a, b]$ 为任意一个位置使得 $f(p)=t$. 只需证明 $(b-a)\int_a^b g^2(x) \text{d}x \ge (\int_a^p g(x) \text{d}x)^2$. 进一步, 只需证明 $(p-a)\int_a^p g^2(x) \text{d}x \ge (\int_a^p g(x) \text{d}x)^2$.

根据 Cauchy 不等式, 有 $|\langle x, y \rangle| \le ||x|| \cdot ||y||$, 故 $(\int_a^p g(x) \text{d}x)^2 \le \int_a^p g(x)^2 \text{d}x \int_a^p 1 \text{d}x = (p-a)\int_a^p g(x)^2 \text{d}x$.

再证第二个不等式. 显然当 $b=a$ 时不等式成立. 只需证明对 $b$ 求导得 $f^2(b) \le \frac{(b-a)^2}{2} f'^2(b) + (b-a)\int_a^b f'^2(x) \text{d}x$.

我们有 $f^2(b) \le \max_{x \in [a, b]} f^2(x) \le (b-a)\int_a^bf'^2(x) \text{d}x$. $\blacksquare$
