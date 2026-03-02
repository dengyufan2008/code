Lemma 1. 对 $x \in [0, \pi]$, $t \in [0, 1]$ 有 $\sin(tx) \ge t\sin x$.

Proof. 显然 $\sin''(x) = -\sin(x) \le 0 \space (x \in [0, \pi])$, 故 $\sin$ 在 $[0, \pi]$ 凹. 故 $\sin(tx) \ge (1-t)\sin(0)+t\sin(x)=t\sin(x)$. $\blacksquare$

---

Lemma 2. 对 $p > 0$ 有 $\int_0^\frac{\pi}{2} |\sin u|^p \text{d}u \ge \frac{\pi}{2(p+1)}$.

Proof (使用 chatgpt). 由于 $\sin$ 在 $[0, \pi]$ 凹, 我们有 $\sin u \ge \frac{2}{\pi} u$. 则 $\sin^p u \ge \frac{2^p}{\pi^p} u^p$, $\int_0^\frac{\pi}{2} \sin^p u \text{d}u \ge \frac{2^p}{\pi^p} \int_0^\frac{\pi}{2} u^p \text{d}u = \frac{\pi}{2(p+1)}$. $\blacksquare$

---

Lemma 3. 对 $x \ge 0$, $p > 0$ 有 $\int_0^x |\sin u|^p \text{d}u \ge \frac{x|\sin x|^p}{p+1}$.

Proof. 若 $x \le \pi$, 由于 $\sin$ 在 $[0, \pi]$ 凹, 有 $\sin u \ge \frac{\sin x}{x} u$. 则 $\int_0^x \sin^p u \text{d}u \ge \frac{\sin^p x}{x^p} \int_0^x u^p \text{d}u = \frac{x\sin^p x}{p+1}$.

若 $x > \pi$, 将 $x$ 写作 $k\pi + y$, 其中 $k \in \N, y \in [0, \pi]$. 有 $\int_0^x |\sin u|^p \text{d}u = k\int_0^\pi \sin^p u \text{d}u + \int_0^y \sin^p u \text{d}u \ge k\frac{\pi}{p+1} + \frac{y|\sin y|^p}{p+1} \ge \frac{(k\pi + y)|\sin y|^p}{p+1} = \frac{x|\sin x|^p}{p+1}$. $\blacksquare$
