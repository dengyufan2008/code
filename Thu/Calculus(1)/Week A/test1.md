Lemma 1. 设 $f \in \mathscr C^1[a, b]$, $f(a)=f(b)$, $\int_a^b f(x) \text{d}x=0$. 则 $\int_a^b f^2(x) \text{d}x \le \frac{(b-a)^2}{4\pi^2} \int_a^b f'^2(x) \text{d}x$, 取等 iff $f(x)=A\cos(\frac{2\pi(x-a)}{b-a}+\theta)$.

Proof. 设 $g(x)=f(a+\frac{b-a}{2\pi}x)$, 则 $f(x)=g(\frac{2\pi}{b-a}(x-a))$, $f'(x)=\frac{2\pi}{b-a}g'(\frac{2\pi}{b-a}(x-a))$. 有 $g(0)=g(2\pi)$, $\int_0^{2\pi} g(x) \text{d}x=\frac{2\pi}{b-a}\int_a^b f(x) \text{d}x=0$. 只需证明 $\int_0^{2\pi}g^2(x)\text{d}x \le \int_0^{2\pi} g'^2(x) \text{d}x$, 取等 iff $g(x)=A\cos(x+\theta)=B\sin(x)+C\cos(x)$.

根据 deepseek, 使用傅里叶级数和 Parseval 恒等式不难证明.

---

Lemma 2. 若 $\Omega$ 是平面上有界区域, 边界为长度为 $L$ 的 $\mathscr C^1$ 简单封闭曲线. 则 $\Omega$ 的面积 $S$ 有 $S \le \frac{L^2}{4\pi}$, 取等 iff $\Omega$ 是圆盘.

设曲线为 $(x(l), y(l)) \space (0 \le l \le L)$, 且曲线正则, $\int_0^L x(l) \text{d}l=\int_0^L y(l) \text{d}l=0$, 则曲线面积为 $\frac{1}{2}\int_0^L [x(l)y'(l)-x'(l)y(l)] \text{d}l=S$.

我们有 $x'^2(l)+y'^2(l)=1$, $\int_0^L [x^2(l)+y^2(l)] \text{d}l \le \frac{L^2}{4\pi^2} \int_0^L [x'^2(l)+y'^2(l)] \text{d}l=\frac{L^3}{4\pi^2}$, 取等 iff $x(l)$ 和 $y(l)$ 都是 $\sin(\frac{2\pi}{L}l)$ 和 $\cos(\frac{2\pi}{L}l)$ 的线性组合.

设 $u(l)=(x(l),y(l))$, $v(l)=(y'(l),-x'(l))$, 则 $4S^2=(\int_0^L [x(l)y'(l)-x'(l)y(l)] \text{d}l)^2=|\langle u, v \rangle|^2 \le \langle u, u \rangle \langle v, v \rangle = \int_0^L [x^2(l)+y^2(l)]\text{d}l \cdot \int_0^L [x'^2(l)+y'^2(l)] \text{d}l \le \frac{L^3}{4\pi^2} \cdot L$, 取等 iff $u=kv$.

故 $S \le \frac{L^2}{4\pi}$. 设 $t=\frac{2\pi}{L}$, 取等 iff $x(l)=A\sin(tl)+B\cos(tl)$ 或表示为 $(A, B)$, $y(l)=(C, D)$, $x'(l)=(-Bt, At)$, $y'(l)=(-Dt, Ct)$, 且有 $(A,B)=k(-Dt,Ct)$, $(C,D)=k(Bt,-At)$. 解得 $k=\plusmn 1$, 不难验证两种情况下曲线都是圆, 且圆满足不等式取等. $\blacksquare$
