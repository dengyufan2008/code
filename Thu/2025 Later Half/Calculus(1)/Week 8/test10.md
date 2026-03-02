Lemma 1. 若 $f$ 在 $[a, b]$ 上连续且非负, $\int_a^b f(x) \text{d}x=0$, 则 $f(x)=0$.

Proof. 假设存在一个 $x \in [a, b]$ 使得 $f(x) > 0$, 则存在 $(x_1, x_2)$ 使得 $x \in (x_1, x_2) \rightarrow f(x)>0$. 则 $\int_a^b f(x) \text{d}x \ge \int_{x_1}^{x_2} f(x) \text{d}x > 0$. $\blacksquare$

---

Lemma 2. 不存在 $[a, b]$ 上的非负连续函数使得 $\int_a^b f(x) \text{d}x = 1$, $\int_a^b xf(x) \text{d}x = \alpha$, $\int_a^b x^2f(x) \text{d}x = \alpha^2$.

Proof. 假设存在这样的 $f$. 则 $\int_a^b (x-\alpha)^2f(x) \text{d}x = \int_a^b (x^2-2 \alpha x+ \alpha^2)f(x) \text{d}x=0$. 故 $(x-\alpha)^2f(x)=0$, 则对于所有 $x \ne \alpha$, $f(x)=0$. 则 $\int_a^b f(x) \text{d}x=0$, 矛盾. $\blacksquare$
