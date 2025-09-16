若无特殊说明, 默认所有的变量均为自然数.

---

Lemma 1. $\forall m, n, k$, $m+k=n+k \rightarrow m=n$.

Proof. 设 $A = \{k | m+k=n+k \rightarrow m=n\}$. 由加法定义可知 $0 \in A$. 假设有 $d \in A$, 试证明 $S(d) \in A$.

由加法定义可知 $m+S(d)=n+S(d) \rightarrow S(m+d)=S(n+d)$.

由于 $S(n)$ 是一个单射, 则 $S(m+d)=S(n+d) \rightarrow m+d=n+d$.

由归纳假设得 $m+d=n+d \rightarrow m=n$. 故 $m+S(d)=n+S(d) \rightarrow m=n$. 故 $A = \N$. $\blacksquare$

---

引理. $m \cdot n=0 \rightarrow m=0 \lor n=0$.

Proof. 考虑其逆否命题, 即 $m \neq 0 \land n \neq 0 \rightarrow m \cdot n \neq 0$.

由于 $m, n \neq 0$, 故令 $x, y$ 满足 $S(x)=m, S(y)=n$.

$S(x) \cdot S(y)=(x+1) \cdot (y+1)=(x+1) \cdot y+(x+1)=(x+1) \cdot y+x+1$.

由于 $[(x+1) \cdot y+x]$ 是自然数, 则 $1 \le S(x) \cdot S(y)$. 我们有 $0 < 1$, 故 $S(x) \cdot S(y) \neq 0$. $\blacksquare$

---

Lemma 2. $\forall m, n, k$, $k \neq 0 \land m \cdot k=n \cdot k \rightarrow m=n$.

Proof. 设 $A = \{n | \forall k, k \neq 0 \land m \cdot k=n \cdot k \rightarrow m=n\}$.

1. 先试证明 $0 \in A$.

   $m \cdot k = 0 \cdot k \rightarrow m \cdot k = 0 \rightarrow m = 0 \lor k = 0$.

   因为有 $k \neq 0$, 故 $m=0=n$.

2. 再假设 $d \in A$, 试证明 $S(d) \in A$.

   对 $m$ 继续进行分类讨论.

   - $m=0$.

     $m \cdot k = S(d) \cdot k \rightarrow S(d) \cdot k = 0 \rightarrow S(d) = 0 \lor k = 0$.

     因为有 $S(d) \neq 0$, 故 $k=0$. 又有 $k \neq 0$, 故矛盾.

   - $m=S(y)$.

     $m \cdot k = S(d) \cdot k \rightarrow S(y) \cdot k = S(d) \cdot k \rightarrow y \cdot k + k = d \cdot k + k \rightarrow y \cdot k = d \cdot k \rightarrow y = d \rightarrow S(y) = S(d) \rightarrow m = S(d)$.

综上所述, $A = \N$. $\blacksquare$
