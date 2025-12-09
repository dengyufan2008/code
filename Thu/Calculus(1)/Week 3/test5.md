设 $f: \mathbb{Q} \rightarrow \R$ 是单调不减函数, 且 $f(\mathbb{Q})$ 在 $\R$ 上稠密.

---

Lemma 1. 对于任意 $x \in \R$, 设 $S(x) = \set{f(r) | r \le x}$, $g(x) = \sup S(x)$, 则 $\lim_{r \rightarrow x} f(r)$ 存在, 且为 $g(x)$.

Proof. 对于任意 $\epsilon > 0$, 可以取一个 $x_1 \in \mathbb{Q}$ 满足 $g(x) - \epsilon < f(x_1) < g(x)$, 和一个 $x_2 \in \mathbb{Q}$ 满足 $g(x) < f(x_2) < g(x) + \epsilon$.

由于 $f(x_1) < g(x)$, 则存在一个 $x_1' \le x \in \mathbb{Q}$, 使得 $f(x_1) < f(x_1')$. 由于 $f$ 单调不减, 则 $x_1 < x_1' \le x$. 进一步地, 对于任意 $x_0 \in \mathbb{Q}, x_1 < x_0 < x$, 有 $g(x) - \epsilon < f(x_1) \le f(x_0)$.

由于 $g(x) < f(x_2)$, 则对于任意 $x_2' \le x \in \mathbb{Q}$ 有 $f(x_2') < f(x_2)$, 故 $x_2' < x_2$, 也即 $x_2 > \sup \set{x_2' \in \mathbb{Q} | x_2' \le x} = x$. 由于 $f$ 单调不减, 则对于任意 $x_0 \in \mathbb{Q}, x < x_0 < x_2$, 有 $f(x_0) \le f(x_2) < g(x) + \epsilon$.

综上所述, 有对于任意 $x_0 \in \mathbb{Q}, x_1 < x_0 < x_2$, 有 $g(x) - \epsilon < f(x_0) < g(x) + \epsilon$. 故取 $\delta = \min(x-x_1, x_2-x) > 0$, 根据极限定义有 $\lim_{r \rightarrow x} f(r) = g(x)$. $\blacksquare$

---

Lemma 2. 对于任意 $x \in \mathbb{Q}$, $g(x) = f(x)$.

Proof. 由于 $f$ 单调不减, 则有 $f(x)$ 是 $S(x)$ 的最大值. 故 $g(x) = f(x)$. $\blacksquare$

---

Lemma 3. $g : \R \rightarrow \R$ 单调不减, 且若 $f$ 严格增, 则 $g$ 严格增.

Proof. 假设有 $x_1, x_2 \in \R$, $x_1 < x_2$, 则有 $S(x_1) \subset S(x_2)$, 故 $g(x_1) \le g(x_2)$.

若 $f$ 严格增, 则取 $x_3, x_4 \in \mathbb{Q}$, $x_1 < x_3 < x_4 < x_2$, 则 $g(x_1) \le f(x_3) < f(x_4) \le g(x_2)$. $\blacksquare$

---

Lemma 4. $g$ 是连续函数.

Proof. 由于 $f:\mathbb{Q}\rightarrow\R$ 在 $\R$ 上稠密, 且对于 $x \in \mathbb{Q}$ 有 $f(x)=g(x)$, 则 $g$ 在 $\R$ 上稠密.

对于任意 $x \in \R$ 和 $\epsilon > 0$, 存在一个 $x_1$ 满足 $g(x) - \epsilon < g(x_1) < g(x)$, 存在一个 $x_2$ 满足 $g(x) < g(x_2) < g(x) + \epsilon$. 由于 $g$ 单调不减, 则 $x_1 < x < x_2$. 考虑任意一个 $x_1 < x_0 < x_2$, 我们有 $g(x) - \epsilon < g(x_1) \le g(x_0) \le g(x_2) < g(x) + \epsilon$. 故取 $\delta = \min(x-x_1,x_2-x)>0$, 根据连续定义有 $g$ 在 $x$ 连续. $\blacksquare$
