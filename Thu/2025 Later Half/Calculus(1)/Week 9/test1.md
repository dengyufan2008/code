求以下曲线的弧长和曲率.

Prob 1. $y=f(x)$, $a \le x \le b$, $f \in \mathscr C^2$.

我们有弧长为 $\int_a^b \sqrt{1+f'(x)^2} \text{d}x$, 即 $l(x)= \int_a^x \sqrt{1+f'(t)^2} \text{d}t$.

故 $\frac{\text{d}l}{\text{d}x}=\sqrt{1+f'(x)^2}$, $\frac{\text{d}x}{\text{d}l}=\frac{1}{\sqrt{1+f'(x)^2}}$, $\frac{\text{d}y}{\text{d}l} = \frac{f'(x)}{\sqrt{1+f'(x)^2}}$.

故 $\frac{\text{d}^2x}{\text{d}l^2}=-\frac{f'(x)f''(x)}{(1+f'(x)^2)^2}$, $\frac{\text{d}^2y}{\text{d}l^2}=\frac{f''(x)}{(1+f'(x)^2)^2}$.

故 $\kappa(x) = ||(\frac{\text{d}x^2}{\text{d}^2l}, \frac{\text{d}y^2}{\text{d}^2l})|| = \frac{|f''(x)|}{(1+f'(x)^2)^\frac{3}{2}}$.

---

Prob 2. 极坐标下 $r=r(\theta)$, $\alpha \le \theta \le \beta$, $r \in \mathscr C^2$.

考虑 $R^2$ 的标准正交基 $\vec {e_r}(\theta) = (\cos \theta, \sin \theta)$ 和 $\vec {e_\theta}(\theta) = (-\sin \theta, \cos \theta)$. 有 $\vec {e_r}'(\theta) = \vec {e_\theta}(\theta)$, $\vec {e_\theta}'(\theta) = -\vec {e_r}(\theta)$.

故 $\vec x(\theta) = r(\theta)\vec {e_r}(\theta)$, $\frac{\text{d} \vec x}{\text{d} \theta} = r'(\theta)\vec {e_r}(\theta) + r(\theta)\vec {e_\theta}(\theta)$.

我们有弧长为 $\int_\alpha^\beta \sqrt{r(\theta)^2 + r'(\theta)^2}\text{d}\theta$, 即 $l(\theta)=\int_\alpha^\theta \sqrt{r(t)^2 + r'(t)^2}\text{d}t$.

故 $\frac{\text{d}l}{\text{d}\theta} = \sqrt{r(\theta)^2 + r'(\theta)^2}$, $\frac{\text{d}\theta}{\text{d}l}=\frac{1}{\sqrt{r(\theta)^2 + r'(\theta)^2}}$, $\frac{\text{d}\vec x}{\text{d}l}=\frac{r'(\theta)}{\sqrt{r(\theta)^2 + r'(\theta)^2}}\vec {e_r}(\theta) + \frac{r(\theta)}{\sqrt{r(\theta)^2 + r'(\theta)^2}} \vec {e_\theta}(\theta)$.

故 $\frac{\text{d}^2 \vec x}{\text{d}l^2} = \frac{r(\theta)(r(\theta)r''(\theta) - 2r'(\theta)^2 - r(\theta)^2)}{(r(\theta)^2 + r'(\theta)^2)^2} \vec {e_r}(\theta) - \frac{r'(\theta)(r(\theta)r''(\theta) - 2r'(\theta)^2 - r(\theta)^2)}{(r(\theta)^2 + r'(\theta)^2)^2} \vec {e_\theta}(\theta)$.

故 $\kappa(\theta)=||\frac{\text{d}^2 \vec x}{\text{d}l^2}||=\frac{|r(\theta)r''(\theta) - 2r'(\theta)^2 - r(\theta)^2|}{(r(\theta)^2 + r'(\theta)^2)^\frac{3}{2}}$.
