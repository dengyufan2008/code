Lemma 1. 若 $f$ 在 $(a, b)$ 可微, $a_n, b_n \in (a, b)$ 满足 $n \rightarrow +\infty$ 时, $a_n \rightarrow a$, $b_n \rightarrow b$, $f(a_n) \rightarrow A$, $f(b_n) \rightarrow A$. 则存在 $\xi \in (a, b)$ 使得 $f'(\xi)=0$.

Proof. 反证法. 不妨设 $f'>0$, 则 $f$ 在 $(a, b)$ 上单调递增.

假设存在一个 $x_0 \in (a, b)$ 使得 $A>f(x_0)$. 由于 $a_n \rightarrow a$, 则存在 $n_0$ 使得 $n > n_0 \rightarrow a_n < x_0$. 故 $f(a_n)<f(x_0)$, $\lim_{n \rightarrow+\infty} f(a_n)\le f(x_0)<A$, 矛盾.

假设存在一个 $x_0 \in (a, b)$ 使得 $A<f(x_0)$. 由于 $b_n \rightarrow b$, 则存在 $n_0$ 使得 $n > n_0 \rightarrow b_n > x_0$. 故 $f(b_n)>f(x_0)$, $\lim_{n \rightarrow+\infty} f(b_n)\ge f(x_0)>A$, 矛盾.

假设对于所有 $x \in (a, b)$ 有 $f(x)=A$. 但我们知道 $f$ 单调递增, 矛盾. $\blacksquare$
