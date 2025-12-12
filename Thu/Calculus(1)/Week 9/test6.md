记 $A > \frac{1}{2}$, $L(A)$ 为抛物线 $y=Ax^2$ 位于圆 $x^2+(y-1)^2=1$ 的内部部分的半边弧长.

Prob 1. 求 $\lim_{A \rightarrow +\infty} L(A)$.

显然交点 $x$ 坐标为 $\plusmn \frac{\sqrt{2A-1}}{A}$. 设 $t=\frac{\sqrt{2A-1}}{A}$, 弧长为 $\int_0^t \sqrt{1+4A^2x^2} \text{d}x = \int_0^t \sqrt{1+u^2} \text{d}\frac{u}{2A} = \frac{1}{2A} \int_0^{2At} \sqrt{1+u^2} \text{d}u$. 设 $B=2At=2\sqrt{2A-1}$, 则弧长为 $\frac{1}{4A}(B\sqrt{1+B^2}+\ln(B+\sqrt{B^2+1})) = 2 \frac{B\sqrt{1+B^2}+\ln(B+\sqrt{B^2+1})}{B^2+4}$. 当 $A \rightarrow +\infty$ 时, $B \rightarrow +\infty$, 显然弧长为 2.

---

Prob 2. 是否存在 $A$ 使得 $L(A)>2$?

$L(A)>2$ iff $B \sqrt{1+B^2}+\ln(B+\sqrt{B^2+1}) > B^2+4$. 当 $B \rightarrow +\infty$ 时, 左侧为 $B^2+\frac{1}{2}+\ln(2B)+o(1)$, 故当 $B$ 足够大时会有 $L(A)>2$.

---

Prob 3. 有多少个 $A$ 使得 $L(A)=2$?

$L(A)=2$ iff $B \sqrt{1+B^2}+\ln(B+\sqrt{B^2+1}) - B^2 - 4 = 0$. 当 $A=\frac{1}{2}$ 时 $B=0$, 左式小于 0.

对左式求导得 $2\sqrt{1+B^2}-2B>0$, 故左式单调递增. 故有一个 $A$ 使得 $L(A)=2$.
