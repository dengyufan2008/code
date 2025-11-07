Lemma 1. 对于任意 $a>b>0$ 有 $\frac{a-b}{\sqrt{(1+a^2)(1+b^2)}}<\arctan a - \arctan b < a-b$.

Proof. 显然有 $(\arctan x)' = \frac{1}{1+x^2}$. 由于 $1+x^2$ 单调递增, $\frac{1}{1+x^2}$ 单调递减, 故 $\arctan x$ 严格凹. 则对于任意 $b>0$ 有对于任意 $a>b$, $\arctan a < \frac{1}{1+b^2} a - \frac{b}{1+b^2} + \arctan b$, 即 $\arctan a - \arctan b < \frac{a-b}{1+b^2} < a-b$.

对于任意 $b>0$, 设 $f(a)=\arctan a - \arctan b - \frac{a-b}{\sqrt{(1+a^2)(1+b^2)}}$. 我们需要证明 $a > b \rightarrow f(a)>0$. 显然有 $f(b)=0$. 又有 $f'(a)=\frac{1}{1+a^2}(1-\frac{1+ab}{\sqrt{(1+a^2)(1+b^2)}})$. 故我们只需要证明 $f'(a)>0$, 也即 $(1+ab)^2 < (1+a^2)(1+b^2)$. 化简得 $2ab < a^2+b^2$ 即 $(a+b)^2 > 0$. 由于 $a>b>0$, 显然成立. $\blacksquare$
