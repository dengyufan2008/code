Lemma 1. 当 $a \in \N^*$ 时, $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = a$.

Proof. 我们有 $x^a-1=(x-1)(x^{a-1}+x^{a-2}+\cdots+1)$. 故 $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = \lim_{x \rightarrow 1} (x^{a-1}+x^{a-2}+\cdots+1)=\lim_{x \rightarrow 1} x^{a-1} + \lim_{x \rightarrow 1} x^{a-2} + \cdots + \lim_{x \rightarrow 1} 1$.

由于幂函数是连续函数, 我们有 $\lim_{x \rightarrow 1} x^a = x^a = 1$. 故 $\lim_{x \rightarrow 1} x^{a-1} + \lim_{x \rightarrow 1} x^{a-2} + \cdots + \lim_{x \rightarrow 1} 1 = a$. $\blacksquare$

---

Lemma 2. 当 $a > 0 \land a \in \mathbb{Q}$ 时, $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = a$.

Proof. 设 $n, m \in \N^*$, 命题即为 $\lim_{x \rightarrow 1} \frac{x^\frac{n}{m}-1}{x-1} = \frac{n}{m}$. 我们有 $\lim_{x \rightarrow 1} \frac{x^n-1}{x-1} = n$ 和 $\lim_{x \rightarrow 1} \frac{x^m-1}{x-1} = m$. 故 $\lim_{x \rightarrow 1} \frac{x^n-1}{x^m-1} = \frac{n}{m}$.

令 $f(x) = \frac{x^n-1}{x^m-1}$, $g(x) = x^\frac{1}{m}$. 由于 $g(x)$ 在 $x>0$ 时单调递减且连续, 我们有 $\lim_{x \rightarrow 1} g(x) = g(1) = 1$, $\lim_{x \rightarrow 1} f(g(x)) = \lim_{x \rightarrow 1} f(x)$. 也即 $\lim_{x \rightarrow 1} \frac{x^\frac{n}{m}-1}{x-1} = \lim_{x \rightarrow 1} \frac{x^n-1}{x^m-1} = \frac{n}{m}$. $\blacksquare$

---

引理 1. 若 $a > 0 \land a \in \R$, $\sup S = p$, 定义 $T = \set{ax | x \in S}$, 则 $\sup T = ap$.

Proof. 对于任意 $x \in S$, 有 $x \le p$, 故 $ax \le ap$, 故 $ap$ 是 $T$ 的一个上界. 假设 $T$ 存在一个上界 $h < ap$, 即对于任意 $y \in T$, 有 $y \le h$, 则有 $\frac{y}{a} \le \frac{h}{a}$, 有 $\frac{h}{a}$ 是 $S$ 的一个上界, 又有 $\frac{h}{a} < p$, 矛盾. 故 $ap$ 是 $T$ 的上确界. $\blacksquare$

---

引理 2. 若 $S = \set{f_1(x), f_2(x), \cdots}$ 非空且在 $a \in \R$ 附近有上界且 $f(x) \in S$ 有在 $a$ 处的极限, 设 $T = \set{\lim_{x \rightarrow a} f_1(x), \cdots}$, 有 $\lim_{x \rightarrow a} \sup S = \sup T$.

Proof. 设 $A=\lim_{x \rightarrow a} \sup S$, 则对于任意 $\epsilon > 0$ 存在 $\delta > 0$, 使得对于所有的 $0 < |x-a| < \delta$, 有 $\sup S < A + \epsilon$ 即 $f(x) < A + \epsilon$. 故 $\lim_{x \rightarrow a} f(x) \le A$, $A$ 是 $T$ 的一个上界.

假设有 $B<A$ 是 $T$ 的上界. 则有 $\lim_{x \rightarrow a} f(x) \le B$. 故对于任意 $\epsilon > 0$ 存在 $\delta > 0$, 使得对于所有的 $0 < |x-a| < \delta$, 有 $f(x) < B + \epsilon$. 取 $\epsilon = \frac{A-B}{2}$, 则存在 $\delta > 0$ 使得对于所有的 $0 < |x-a| < \delta$, 有 $f(x) < \frac{A+B}{2}$. 也即存在 $\delta > 0$ 使得对于所有的 $0 < |x-a| < \delta$, 有 $\sup S \le \frac{A+B}{2}$. 这与 $A=\lim_{x \rightarrow a} \sup S$ 矛盾. 故 $A$ 是 $T$ 的上确界. $\blacksquare$

---

Lemma 3. 当 $a > 0 \land a \in \R$ 时, $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = a$.

Proof. 根据 $x^a$ 的定义有 $x^a = \sup \set{x^b | b \in \mathbb{Q}, b \le a}$. 故根据第一问和引理 1 得, $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = \lim_{x \rightarrow 1} \sup \set{\frac{x^b-1}{x-1} | b \in \mathbb{Q}, b \le a}$. 根据引理 2 得, $\lim_{x \rightarrow 1} \sup \set{\frac{x^b-1}{x-1} | b \in \mathbb{Q}, b \le a} = \sup \set{\lim_{x \rightarrow 1} \frac{x^b-1}{x-1} | b \in \mathbb{Q}, b \le a} = \sup \set{b | b \in \mathbb{Q}, b \le a} = a$. $\blacksquare$

---

Lemma 4. 当 $a \in \R$ 时, $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = a$.

Proof. 当 $a=0$ 时, 有 $\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} = \lim_{x \rightarrow 1} \frac{1-1}{x-1} = 0 = a$. 当 $a>0$ 时 Lemma 3 已证. 故下文考虑在 $a>0$ 时证明 $\lim_{x \rightarrow 1} \frac{x^{-a}-1}{x-1} = -a$.

我们有 $\lim_{x \rightarrow 1} \frac{x^{-a}-1}{x-1} = -\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} x^{-a} = -\lim_{x \rightarrow 1} \frac{x^a-1}{x-1} \lim_{x \rightarrow 1} x^{-a} = -a \cdot 1^{-a} = -a$. $\blacksquare$

---

Lemma 5.1. $\lim_{x \rightarrow 0} \frac{\sqrt{1+x}-\sqrt[3]{1-x}}{x} = \frac{5}{6}$.

Proof. 我们有 $\lim_{x \rightarrow 0} \frac{\sqrt{1+x}-\sqrt[3]{1-x}}{x} = \lim_{x \rightarrow 0} \frac{\sqrt{1+x}}{x} - \lim_{x \rightarrow 0} \frac{\sqrt[3]{1-x}}{x}$. 故分别考虑两项极限的值.

令 $y=1+x$, 有 $\lim_{x \rightarrow 0} \frac{\sqrt{1+x}}{x} = \lim_{y \rightarrow 1} \frac{y^\frac{1}{2}}{y-1} = \lim_{y \rightarrow 1} \frac{y^\frac{1}{2}-1}{y-1} + \lim_{x \rightarrow 0} \frac{1}{x} = \frac{1}{2}$.

令 $z=1-x$, 有 $\lim_{x \rightarrow 0} \frac{\sqrt[3]{1-x}}{x} = \lim_{z \rightarrow 1} \frac{z^\frac{1}{3}}{1-z} = -\lim_{z \rightarrow 1} \frac{z^\frac{1}{3}-1}{z-1} - \lim_{x \rightarrow 0} \frac{1}{x} = -\frac{1}{3}$.

故 $\lim_{x \rightarrow 0} \frac{\sqrt{1+x}-\sqrt[3]{1-x}}{x} = \frac{5}{6}$. $\blacksquare$

---

Lemma 5.2. $\lim_{x \rightarrow 4} \frac{\sqrt[3]{3+6x}-3}{\sqrt x-2}= \frac{8}{9}$.

Proof. 我们有 $\lim_{x \rightarrow 4} \frac{\sqrt[3]{3+6x}-3}{\sqrt x-2} = \lim_{x \rightarrow 4} \frac{\frac{\sqrt[3]{3+6x}-3}{6x-24}}{\frac{\sqrt x-2}{6x-24}} = \frac{\lim_{x \rightarrow 4} \frac{\sqrt[3]{3+6x}-3}{6x-24}}{\lim_{x \rightarrow 4} \frac{\sqrt x-2}{6x-24}} = \lim_{x \rightarrow 4} \frac{\sqrt[3]{3+6x}-3}{6x-24} \lim_{x \rightarrow 4} \frac{6x-24}{\sqrt x-2}$. 故分别考虑两部分极限.

令 $y=\frac{3+6x}{27}$, 有 $\lim_{x \rightarrow 4} \frac{\sqrt[3]{3+6x}-3}{6x-24} = \lim_{y \rightarrow 1} \frac{\sqrt[3]{27y}-3}{27y-27} = \frac{1}{9} \lim_{y \rightarrow 1} \frac{y^\frac{1}{3}-1}{y-1} = \frac{1}{27}$.

令 $z=\frac{1}{2} \sqrt x$, 有 $\lim_{x \rightarrow 4} \frac{6x-24}{\sqrt x-2} = \lim_{z \rightarrow 1} \frac{24z^2-24}{2z-2} = 12 \lim_{z \rightarrow 1} \frac{z^2-1}{z-1} = 24$.

故 $\lim_{x \rightarrow 4} \frac{\sqrt[3]{3+6x}-3}{\sqrt x-2}= \frac{8}{9}$. $\blacksquare$
