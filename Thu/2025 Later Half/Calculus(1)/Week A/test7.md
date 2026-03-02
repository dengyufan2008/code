讨论以下积分的收敛性.

Prob 1. $\int_0^{+\infty} \frac{\arctan x}{x^\alpha} \text{d}x$.

当 $x \rightarrow 0$ 时, $\arctan x = x+o(x)$, 故收敛当且仅当 $x^{1-\alpha}$ 收敛, 即 $\alpha < 2$.

当 $x \rightarrow +\infty$ 时, $\arctan x = \frac{\pi}{2}+o(1)$, 故收敛当且仅当 $x^{-\alpha}$ 收敛, 即 $\alpha > 1$.

故收敛当且仅当 $\alpha \in (1,2)$.

---

Prob 2. $\int_0^{+\infty} \frac{\ln(1+x)}{x^\alpha} \text{d}x$.

当 $x \rightarrow 0$ 时, $\ln(1+x)=x+o(x)$, 故收敛当且仅当 $x^{1-\alpha}$ 收敛, 即 $\alpha < 2$.

当 $x \rightarrow +\infty$ 时, $\ln(1+x)=\ln x + o(1)$, 故收敛当且仅当 $\frac{\ln x}{x^\alpha}$ 收敛, 即 $\alpha > 1$.

故收敛当且仅当 $\alpha \in (1,2)$.

---

Prob 3. $\int_3^{+\infty} \frac{1}{\sqrt{x(x-1)(x-2)}} \text{d}x$.

当 $x \rightarrow +\infty$ 时 $\frac{1}{\sqrt{x(x-1)(x-2)}} = x^{-\frac{3}{2}} + o(x^{-\frac{3}{2}})$, 故收敛.

---

Prob 4. $\int_0^{+\infty} \frac{x}{\sqrt{e^x-1}} \text{d}x$.

当 $x \rightarrow 0$ 时, $(e^x-1)^{-\frac{1}{2}} = x^{-\frac{1}{2}}+o(x^{-\frac{1}{2}})$, 故收敛.

当 $x \rightarrow +\infty$ 时, $x=o(\sqrt[3] {e^x-1})$, 故收敛.

故收敛.

---

Prob 5. $\int_0^1 \frac{1}{\ln x} \text{d}x$.

有 $\int_0^1 \frac{1}{\ln x} \text{d}x = \int_0^1 \frac{1}{\ln (1-x)} \text{d}x$.

当 $x \rightarrow 0$ 时, $\ln(1-x) = -x+o(x)$, 故发散.

---

Prob 6. $\int_0^1 \frac{x^{\beta - 1}-x^{\alpha - 1}}{\ln x} \text{d}x$.

不妨设 $\alpha > \beta$, 否则 $\alpha = \beta$ 时收敛, $\alpha < \beta$ 时取相反数.

有 $\int_0^1 \frac{x^{\beta - 1}-x^{\alpha - 1}}{\ln x} \text{d}x = \int_{-\infty}^0 \frac{e^{\beta x}-e^{\alpha x}}{x} \text{d}x$.

当 $x \rightarrow 0$ 时, $\frac{e^{\beta x}-e^{\alpha x}}{x} \rightarrow \beta-\alpha$, 故收敛.

当 $x \rightarrow -\infty$ 时, $\frac{e^{\beta x}-e^{\alpha x}}{x} = \frac{e^{\beta x}}{x} + o(\frac{e^{\beta x}}{x})$, 故收敛当且仅当 $\frac{e^{\beta x}}{x}$ 收敛. 若 $\beta < 0$, 则 $x=o(e^{\frac{1}{2} \beta x})$, 显然发散. 若 $\beta = 0$, 则 $\frac{1}{x}$ 积分发散. 若 $\beta > 0$, 则 $e^{\beta x}=o(\frac{1}{x})$, 显然收敛.

故收敛当且仅当 $\alpha=\beta$ 或 $\min(\alpha, \beta)>0$.

---

Prob 7. $\int_0^\frac{\pi}{2} \ln \sin x \text{d}x$, 若收敛则求值.

我们有 $\int_0^\frac{\pi}{2} \ln \sin x \text{d}x = \int_0^1 \frac{\ln x}{\sqrt{1-x^2}} \text{d}x = \int_{-\infty}^0 \frac{xe^x}{\sqrt{1-e^{2x}}} \text{d}x = -\int_0^{+\infty} \frac{xe^{-x}}{\sqrt{1-e^{-2x}}} \text{d}x = -\int_0^{+\infty} \frac{x}{\sqrt{e^{2x}-1}} \text{d}x = -\frac{1}{4} \int_0^{+\infty} \frac{x}{\sqrt{e^x-1}} \text{d}x$.

当 $x \rightarrow 0$ 时, $\frac{x}{\sqrt{e^x-1}} = \sqrt{x} + o(\sqrt x)$, 故收敛.

当 $x \rightarrow +\infty$ 时, $\frac{x}{\sqrt{e^x-1}} \rightarrow 0$, 故收敛.

故收敛.

由于 $\int_0^\frac{\pi}{2} \ln \sin x \text{d}x = \int_0^{\frac{\pi}{2}} \ln \cos x \text{d}x$, 有

$$
\begin{aligned}
\int_0^\frac{\pi}{2} \ln \sin x \text{d}x &= \frac{1}{2} \int_0^\frac{\pi}{2} \ln (\sin x \cos x) \text{d}x
\\
&= -\frac{\pi}{4} \ln 2 + \frac{1}{2} \int_0^\frac{\pi}{2} \ln (\sin 2x) \text{d}x
\\
&= -\frac{\pi}{4} \ln 2 + \frac{1}{4} \int_0^\pi \ln \sin x \text{d}x
\\
&= -\frac{\pi}{4} \ln 2 + \frac{1}{2} \int_0^\frac{\pi}{2} \ln \sin x \text{d}x.
\end{aligned}
$$

故 $\int_0^\frac{\pi}{2} \ln \sin x \text{d}x = -\frac{\pi}{2} \ln 2$.
