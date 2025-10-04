Lemma 1. $\lim_{x \rightarrow a} \frac{\sin x - \sin a}{x-a} = \cos a$.

Proof. 根据和差化积公式, 我们有 $\lim_{x \rightarrow a} \frac{\sin x - \sin a}{x-a} = \lim_{x \rightarrow a} \frac{2 \cos \frac{x+a}{2} \sin \frac{x-a}{2}}{x-a} = \lim_{x \rightarrow a} \frac{\sin \frac{x-a}{2}}{\frac{x-a}{2}} \lim_{x \rightarrow a} \cos \frac{x+a}{2}$.

令 $y=\frac{x-a}{2}$, 有 $\lim_{x \rightarrow a} \frac{\sin \frac{x-a}{2}}{\frac{x-a}{2}} \lim_{x \rightarrow a} \cos \frac{x+a}{2} = \lim_{y \rightarrow 0} \frac{\sin y}{y} \lim_{x \rightarrow a} \cos \frac{x+a}{2} = \cos a$. $\blacksquare$

---

Lemma 2. $\lim_{x \rightarrow a} \frac{\cos x - \cos a}{x-a} = -\sin a$.

Proof. 根据和差化积公式, 我们有 $\lim_{x \rightarrow a} \frac{\cos x - \cos a}{x-a} = \lim_{x \rightarrow a} \frac{-2 \sin \frac{x+a}{2} \sin \frac{x-a}{2}}{x-a} = -\lim_{x \rightarrow a} \frac{\sin \frac{x-a}{2}}{\frac{x-a}{2}} \lim_{x \rightarrow a} \sin \frac{x+a}{2}$.

令 $y= \frac{x-a}{2}$, 有 $\lim_{x \rightarrow a} \frac{\sin \frac{x-a}{2}}{\frac{x-a}{2}} \lim_{x \rightarrow a} \sin \frac{x+a}{2} = \lim_{y \rightarrow 0} \frac{\sin y}{y} \lim_{x \rightarrow a} \sin \frac{x+a}{2} = \sin a$. $\blacksquare$

---

Lemma 3. $\lim_{x \rightarrow 0} \frac{1-\cos x \sqrt{\cos 2x} \sqrt[3]{\cos 3x}}{x^2} = 3$.

Proof (使用 deepseek). 我们有 $1-\cos x \sqrt{\cos 2x} \sqrt[3]{\cos 3x} = (1-\cos x) + \cos x(1- \sqrt{\cos 2x}) + \cos x \sqrt{\cos 2x}(1- \sqrt[3]{\cos 3x})$. 故分别计算三个极限.

根据半角原理, 我们有 $\lim_{x \rightarrow 0} \frac{1- \cos x}{x^2} = \lim_{x \rightarrow 0} \frac{2 \sin^2 \frac{x}{2}}{x^2} = \frac{1}{2} (\lim_{x \rightarrow 0} \frac{\sin \frac{x}{2}}{\frac{x}{2}})^2$. 令 $y = \frac{x}{2}$, 有 $\lim_{x \rightarrow 0} \frac{\sin \frac{x}{2}}{\frac{x}{2}} = \lim_{y \rightarrow 0} \frac{\sin y}{y} = 1$, 故 $\lim_{x \rightarrow 0} \frac{1- \cos x}{x^2} = \frac{1}{2}$.

我们有 $\lim_{x \rightarrow 0} \frac{\cos x(1- \sqrt{\cos 2x})}{x^2} = \lim_{x \rightarrow 0} \frac{1- \sqrt{\cos 2x}}{x^2} = \lim_{x \rightarrow 0} \frac{1- \cos 2x}{x^2(1+ \sqrt{\cos 2x})} = 2 \lim_{x \rightarrow 0} \frac{1- \cos 2x}{(2x)^2}$. 令 $y=2x$, 有 $\lim_{x \rightarrow 0} \frac{1- \cos 2x}{(2x)^2} = \lim_{y \rightarrow 0} \frac{1-\cos y}{y^2} = \frac{1}{2}$, 故 $\lim_{x \rightarrow 0} \frac{\cos x(1- \sqrt{\cos 2x})}{x^2} = 1$.

我们有 $\lim_{x \rightarrow 0} \frac{\cos x \sqrt{\cos 2x} (1- \sqrt[3]{\cos 3x})}{x^2} = \lim_{x \rightarrow 0} \frac{1- \sqrt[3]{\cos 3x}}{x^2} = \lim_{x \rightarrow 0} \frac{1- \cos 3x}{x^2(1+(\cos 3x)^\frac{1}{3}+(\cos 3x)^\frac{2}{3})} = 3 \lim_{x \rightarrow 0} \frac{1- \cos 3x}{(3x)^2}$. 令 $y=3x$, 有 $\lim_{x \rightarrow 0} \frac{1- \cos 3x}{(3x)^2} = \lim_{y \rightarrow 0} \frac{1-\cos y}{y^2} = \frac{1}{2}$. 故 $\lim_{x \rightarrow 0} \frac{\cos x \sqrt{\cos 2x} (1- \sqrt[3]{\cos 3x})}{x^2} = \frac{3}{2}$.

综上所述, $\lim_{x \rightarrow 0} \frac{1-\cos x \sqrt{\cos 2x} \sqrt[3]{\cos 3x}}{x^2} = 3$. $\blacksquare$
