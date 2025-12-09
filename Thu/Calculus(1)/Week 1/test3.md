若无特殊说明, 默认所有的变量均为自然数.

---

Lemma 1. $\forall n \neq 0, m$, $\exist k, r$, $m=kn+r \land r<n$.

Proof. 设 $A_n = \{m | \exist k, r, m=kn+r \land r<n \}$.

1. 试证明 $0 \in A_n$.

   取 $k=r=0$, 有 $0=0 \cdot n+0$.

2. 假设 $d \in A_n$, 试证明 $S(d) \in A_n$.

   假设即为 $d=k'n+r'$.

   对 $r'$ 进行分类讨论, 显然有 $S(r') < S(n)$ 即 $S(r') \le n$.

   - $S(r')<n$.

     取 $k=k', r=S(r')<n$, 有 $S(d)=S(k'n+r')=k'n+S(r')=kn+r$.

   - $S(r')=n$.

     取 $k=S(k'), r=0<n$, 有 $S(d)=S(k'n+r')=k'n+S(r')=k'n+n=S(k')n=S(k')n+0=kn+r$.

综上所述, $A_n=\N$. $\blacksquare$
