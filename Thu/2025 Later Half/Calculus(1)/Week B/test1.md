Prob 1. 求 $[0, +\infty)$ 上的连续函数 $f$ 使得 $\ln |f(x)|+\int_0^x f(t) \text{d}t = 0$.

显然有 $f(x) \ne 0$.

求导得 $\frac{f'(x)}{f(x)} + f(x)=0$, 即 $f'(x)+f^2(x)=0$. 还需保证 $\ln |f(0)| = 0$, 即 $f(0)=\plusmn 1$.

设 $f(x)=\frac{1}{g(x)}$, 则 $\frac{1-g'(x)}{g^2(x)}=0$, $g'(x)=1$, $g(x)=x+C$, $f(x)=\frac{1}{x+C}$.

当 $f(0)=\frac{1}{C}=1$ 时, $C=1$, 故 $f(x)=\frac{1}{x+1}$.
