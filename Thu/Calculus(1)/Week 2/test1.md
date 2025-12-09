引理. 若 $\mathbb{F}$ 是一个域, $x \in \mathbb{F}$, 则 $(-x) \cdot (-x)=x \cdot x$.

Proof. 先证加法消去律, 即 $a+c=b+c \rightarrow a=b$. 我们有 $a+c=b+c \rightarrow a+c+(-c)=b+c+(-c) \rightarrow a+[c+(-c)]=b+[c+(-c)] \rightarrow a+0_\mathbb{F}=b+0_\mathbb{F} \rightarrow a=b$.

再证 $0_\mathbb{F} \cdot x=0_\mathbb{F}$. 显然有 $0_\mathbb{F}=0_\mathbb{F}+0_\mathbb{F}$, 则 $0_\mathbb{F} \cdot x=0_\mathbb{F} \cdot x+0_\mathbb{F} \cdot x$, $0_\mathbb{F} \cdot x+[-(0_\mathbb{F} \cdot x)]=0_\mathbb{F} \cdot x+0_\mathbb{F} \cdot x+[-(0_\mathbb{F} \cdot x)]$, $0_\mathbb{F}=0_\mathbb{F} \cdot x+0_\mathbb{F}=0_\mathbb{F} \cdot x$.

故由加法消去律得, $(-x) \cdot (-x)=x \cdot x \leftrightarrow (-x) \cdot (-x)+x \cdot (-x)=x \cdot x+x \cdot (-x)$. 进而上式 $\leftrightarrow [(-x)+x] \cdot (-x)=x \cdot [x+(-x)] \leftrightarrow 0_\mathbb{F} \cdot (-x)=x \cdot 0_\mathbb{F} \leftrightarrow 0_\mathbb{F}=0_\mathbb{F}$. $\blacksquare$

---

Lemma 1. 若 $\mathbb{F}$ 是一个序域, $x \in \mathbb{F}$, 则 $x^2 \ge 0_\mathbb{F}$ 且 $x^2=0_\mathbb{F} \leftrightarrow x=0_\mathbb{F}$.

Proof. 对 $x$ 进行分类讨论.

- $x \in \mathbb{F}^+$.

  显然有 $x \cdot x \in \mathbb{F}^+$, 也即 $x \cdot x > 0$.

- $-x \in \mathbb{F}^+$.

  根据引理有 $x \cdot x=(-x) \cdot (-x)$, 故同上一种情况有 $x \cdot x > 0$.

- $x=0_\mathbb{F}$.

  根据引理有 $x \cdot x=0_\mathbb{F}$.

综上所述, 只有 $x=0_\mathbb{F}$ 时才有 $x^2=0_\mathbb{F}$, 其他情况下 $x^2>0_\mathbb{F}$. $\blacksquare$

---

Lemma 2. 复数集 $\Complex$ 不是序域.

Proof. 假设 $\Complex$ 是序域, 显然 $\Complex^+$ 非空.

任取 $x \in \Complex^+$, 令 $i$ 满足 $i^2=-1$, 显然 $x \cdot i \ne 0$, 故 $(x \cdot i)^2 \in \Complex^+$ 即 $-x^2 \in \Complex^+$. 又有 $x^2 \in \Complex^+$, 与序域定义矛盾. $\blacksquare$
