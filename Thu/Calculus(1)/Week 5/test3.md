Lemma 1. 设 $f \in \mathscr C^\infty$, $g(x)=f(\ln x)$. 则对于任意 $n \in \N^*$, $x^n \frac{\text{d}^n g}{\text{d} x^n}=(\frac{\text{d}}{\text{d} t} - (n-1)) \cdots (\frac{\text{d}}{\text{d} t} - 1) \frac{\text{d}}{\text{d} t} f(t)$, 其中 $t=\ln x$.

Proof. 使用数学归纳法. 显然 $n=1$ 时有 $\frac{\text{d} g}{\text{d} x}=\frac{f'(t)}{x}$. 下假设 $n$ 成立而证明 $n+1$ 成立.

我们有

$$
\begin{aligned}
\frac{\text{d} g}{\text{d} x^{n+1}} &= \frac{\text{d}}{\text{d} x} \frac{(\frac{\text{d}}{\text{d} t} - (n-1)) \cdots \frac{\text{d}}{\text{d} t} f(t)}{x^n}
\\
&= \frac{1}{x} \frac{\text{d}}{\text{d} t} \frac{(\frac{\text{d}}{\text{d} t} - (n-1)) \cdots \frac{\text{d}}{\text{d} t} f(t)}{e^{nt}}
\\
&= \frac{1}{x} \frac{e^{nt} \frac{\text{d}}{\text{d} t} (\frac{\text{d}}{\text{d} t} - (n-1)) \cdots \frac{\text{d}}{\text{d} t} f(t) - ne^{nt} (\frac{\text{d}}{\text{d} t} - (n-1)) \cdots \frac{\text{d}}{\text{d} t} f(t)}{e^{2nt}}
\\
&= \frac{(\frac{\text{d}}{\text{d} t} - n) (\frac{\text{d}}{\text{d} t} - (n-1)) \cdots \frac{\text{d}}{\text{d} t} f(t)}{x^{n+1}}.
\end{aligned}
$$

故命题得证. $\blacksquare$
