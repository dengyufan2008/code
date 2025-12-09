Lemma 1. $e^{\lambda x}$ 是 $y'+5y=0$ 的解 iff $\lambda=-5$.

Proof. 我们有 $(e^{\lambda x})'=\lambda e^{\lambda x}$. 代入得 $(\lambda+5)e^{\lambda x}=0$. 由于 $e^{\lambda x} > 0$, 故 $\lambda=-5$. $\blacksquare$

---

Lemma 2. $C(x)e^{-5x}$ 是 $y'+5y=0$ 的解 iff $C(x)$ 是常值.

Proof. 我们有 $(C(x)e^{-5x})'=C'(x)e^{5x}-5C(x)e^{-5x}$. 代入得 $C'(x)e^{-5x}=0$. 由于 $e^{-5x}>0$, 故 $C'(x)=0 \Leftrightarrow C(x)$ 是常值.

---

Lemma 3. $\left\{\begin{aligned}&y'+5y=0\\&y(0)=8\end{aligned}\right.$ 有唯一解.

Proof. 任意函数 $f(x)$ 可以被写成 $\frac{f(x)}{e^{-5x}}e^{-5x}$, 即 $C(x)e^{-5x}$ 的形式. 则解满足 $C(x)$ 是常值. 设 $f(x)=Ce^{-5x}$, 有 $f(0)=C=8$. 故 $f(x)=8e^{-5x}$ 是唯一解.
