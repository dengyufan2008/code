Lemma 1. 若 $f \in \mathscr C^1[0, a]$, $f(0)=0$, $f'(x) \le 1+f(x)$, 则 $f'(x) \le e^x$.

Proof. 设 $g(x)=\frac{f(x)+1}{e^x}$, 则 $f(x)=g(x)e^x-1$, $f'(x)=g(x)e^x+g'(x)e^x$. 故我们有 $g(0)=1$ 和 $g(x)e^x+g'(x)e^x \le g(x)e^x$ 即 $g'(x) \le 0$. 我们只需证明 $g(x)e^x + g'(x)e^x \le e^x \leftarrow g(x)+g'(x) \le 1 \leftarrow g(x) \le 1$ 即可. 显然有 $g$ 单调不增, 故 $g(x) \le g(0) = 1$. $\blacksquare$
