若无特殊说明, 默认所有的变量均为自然数.

---

Lemma 1. $\forall m, n$, $\exist k$, $m=n+k \lor n=m+k$.

Proof. 设 $A_m = \{n | \exist k, n=m+k \lor m=n+k\}$.

1. 试证明 $0 \in A_m$.

   $\exist k, 0=m+k \lor m=0+k$. 取 $k=m$ 即可.

2. 若 $d \in A_m$, 则 $S(d) \in A_m$.

   归纳假设即为 $\exist k, d=m+k \lor m=d+k$.

   分类讨论归纳假设.

   - $d=m+k'$.

     取 $k=S(k')$, 有 $d=m+k' \rightarrow S(d)=S(m+k')=m+S(k')=m+k$.
   
   - $m=d+k'$.

     对 $k'$ 进行分类讨论.

     - $k'=0$, $m=d$.

       取 $k=1$, 有 $S(d)=S(m)=m+1=m+k$.

     - $k'=S(w)$, $m=d+S(w)$.

       取 $k=w$, 有 $m=d+S(w) \rightarrow m=S(d+w) \rightarrow m=S(d)+w$.

   综上所述, 若 $d \in A_m$, 则 $S(d) \in A_m$.

故 $A_m=\N$. $\blacksquare$

---

Lemma 2. $\forall A \subseteq \N \land A \neq \varnothing$, $\exist m \in A$, $\forall n \in A$, $m \le n$.

Proof. 对 $x \in A$ 定义 $f_A(x)=\sum_{y \in A} [y < x]$. 由于 $x \le y \lor y < x$ 恒为真, 故原命题等价于 $\forall A \subseteq \N \land A \neq \varnothing, \exist m \in A, f_A(x)=0$.

由于 $A$ 非空, 故可以任取一个元素 $x \in A$, 并进行以下过程.

- 若 $f_A(x)=0$, 则取 $m=x$ 即可.

- 若 $f_A(x) \neq 0$, 则取任意一个 $y<x$. 若有一个 $z \in A, x \le z$, 则有 $y < x \le z \rightarrow y \le z$. 又有 $y<x \land \lnot (y<y)$, 故 $f_A(y) < f_A(x)$. 重新令 $x=y$, 重复刚刚的过程.

试证明上述过程只会进行有限次. 我们有 $f_A(x)=\sum_{y \in A} [y<x]=\sum_{y<x} [y \in A] \le \sum_{y<x} 1=x$, 而有 $f_A(x) < f_A(x)$, 故上述过程至多只会进行 $x$ 次. $\blacksquare$
