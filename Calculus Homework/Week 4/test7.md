设 $I$ 是区间, $f_n$ 是 $I$ 上的连续函数, 且对于任意 $x \in I$, $f_{n+1}(x) \le f_n(x)$ 且数列 $\{f_n(x)\}$ 有下界. 设 $f(x)=\lim_{n \rightarrow +\infty}f_n(x)$.

---

Lemma 1. $f$ 在 $I$ 上上半连续. 即 $\forall x_0 \in I, \epsilon>0, \exist \delta>0, \forall x \in I, |x-x_0|<\delta \rightarrow f(x)<f(x_0)+\epsilon$.

Proof. 任取一个 $x_0 \in I$ 和 $\epsilon>0$. 存在一个 $m \ge 1$ 使得 $n\ge m \rightarrow |f_n(x_0)-f(x_0)|<\frac{1}{2}\epsilon$. 存在一个 $\delta>0$ 使得 $|x-x_0|<\delta \rightarrow |f_m(x)-f_m(x_0)|<\frac{1}{2}\epsilon$. 故 $\forall |x-x_0|<\delta, |f(x_0)-f_m(x)|\le|f(x_0)-f_m(x_0)|+|f_m(x_0)-f_m(x)|<\epsilon$. 由于我们有 $f_n(x)$ 关于 $n$ 单调且有下界, 则 $f(x)=\inf_n\{f_n(x)\} \le f_m(x)$. 故 $\forall|x-x_0|<\delta, f(x)-f(x_0)\le f_m(x)-f(x_0)\le|f_m(x)-f(x_0)|<\epsilon$, 即 $f(x)<f(x_0)+\epsilon$. $\blacksquare$

---

Lemma 2. 若 $I$ 是有界闭集, 则 $f$ 在 $I$ 上有最大值.

Proof (使用 deepseek). 显然 $f_n(x)$ 有最大值, 任取一个 $x_n$ 满足 $f_n(x_n)$ 为最大值. 显然有 $f_{n+1}(x_{n+1}) \le f_n(x_n)$ (否则 $f_{n+1}(x_{n+1}) > f_n(x_n) \ge f_n(x_{n+1})$, 矛盾), 且 $\{x_n\}$ 存在收敛子列 $\{x_{n_k}\}$ 使得 $\lim_{k \rightarrow +\infty} x_{n_k}=x_0 \in I$. 显然有 $f_{n_k}(x) \le f_{n_k}(x_{n_k})$. 令 $k \rightarrow +\infty$, 有 $f(x) \le \inf_k f_{n_k}(x_{n_k})$.

对于任意 $m$, 有当 $k \ge m$ 时 $n_k \ge m$, $f_{n_k}(x_{n_k}) \le f_m(x_{n_k})$. 令 $k \rightarrow +\infty$, 有 $\inf_k f_{n_k}(x_{n_k}) \le f_m(x_0)$. 再令 $m \rightarrow +\infty$, 有 $\inf_k f_{n_k}(x_{n_k}) \le f(x_0)$.

故 $f(x) \le \inf_k f_{n_k}(x_{n_k}) \le f(x_0)$, $f(x_0)$ 为 $f$ 的最大值. $\blacksquare$

---

Lemma 3. 存在上半连续函数 $f$ 不连续.

Proof. 考虑 $f(x)=\left\{
\begin{aligned}
& 0 & (x < 0)
\\
& 1 & (x \ge 0)
\end{aligned}
\right.$, 显然 $f$ 在 0 处不连续.

对于任意 $x_0<0$, 取 $\delta=-x_0$, 则 $|x-x_0|<\delta \rightarrow x<0 \rightarrow f(x)=0=f(x_0)$. 对于任意 $x_0 \ge 0$, 显然有对于任意 $x$, $f(x_0) \ge f(x)$. 故 $f$ 上半连续. $\blacksquare$
