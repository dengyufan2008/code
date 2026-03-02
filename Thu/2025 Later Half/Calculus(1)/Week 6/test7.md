Lemma 1. 若二阶可微函数 $f$ 是 $y''+y=0$ 的解, 则 $f^2(x)+f'^2(x)$ 为常值函数.

Proof. 我们有 $f''+f=0$, 则 $2f'(f''+f)=0$, 也即 $(f^2+f'^2)'=0$. $\blacksquare$

---

Lemma 2. 上述微分方程的解都可写为 $y=A \cos x + B \sin x$, 其中 $A$ 和 $B$ 是常数.

Proof. 我们有 $(\frac{\text{d}}{\text{d}x}-i)(\frac{\text{d}}{\text{d}x}+i)f=0$, 故 $f$ 是且仅是 $e^{ix}$ 和 $e^{-ix}$ 的线性组合. 我们有 $e^{ix}=\cos x+i\sin x$, $e^{-ix}=\cos x-i\sin x$. 且 $(a+bi)e^{ix}+(c+di)e^{-ix}=((a+c)\cos x+(d-b)\sin x)+i((b+d)\cos x+(a-c)\sin x)$. 由于 $f$ 的值域是实数, 故 $f$ 至多是 $\cos x$ 和 $\sin x$ 的线性组合. 容易验证 $\cos x$ 和 $\sin x$ 都是解, 故得证. $\blacksquare$
