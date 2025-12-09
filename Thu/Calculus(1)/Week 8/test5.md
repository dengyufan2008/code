Prob 1. 求 $[0, 1]$ 上的可积函数 $f$ 使得 $\forall x \in [0, 1]$ 有 $f(x)=1 + (1-x) \int_0^x y f(y) \text{d}y + x \int_x^1 (1-y) f(y) \text{d}y$.

对条件求两次导数, 不难发现 $f''(x)=-f(x)$. 故 $f(x)=A\sin x+B \cos x$. 代入得 $(A \sin 1 + B \cos 1 - B)x = 1 - B$, 则 $A=\frac{1-\cos 1}{\sin 1} = \tan \frac{1}{2}$, $B=1$. 故 $f(x)=\tan \frac{1}{2} \sin x + \cos x$.
