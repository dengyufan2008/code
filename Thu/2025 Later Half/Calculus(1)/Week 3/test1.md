设 $A$, $B$ 是 $\R$ 的非空子集, 且有上界. 设 $\sup A=p$, $\sup B=q$.

---

Lemma 1. $A+B$ 非空且有上界, 且 $\sup(A+B)=p+q$.

Proof. 任取 $x \in A$ 和 $y \in B$, 有 $x+y \in A+B$, 故 $A+B$ 非空. 又有对于任意 $a \in A$ 和 $b \in B$, $a \le p \land b \le q$. 故 $a+b \le p+q$, $p+q$ 是 $A+B$ 的上界.

假设 $p+q$ 不是 $A+B$ 的上确界, 则有 $h < p+q$ 是 $A+B$ 的上界. 设 $f=\frac{p-q+h}{2}$, $g=\frac{q-p+h}{2}$, 有 $f+g=h$, $f < p$, $g < q$. 故可以取 $s \in A$ 使得 $s > f$, 取 $t \in B$ 使得 $t > g$, 有 $s+t > f+g=h$, 且 $s+t \in A+B$, 矛盾. 故 $p+q$ 是 $A+B$ 的上确界. $\blacksquare$

---

Lemma 2. $A \cup B$ 非空且有上界, 且 $\sup(A \cup B)=\max(p,q)$.

Proof. 由于 $A \ne \varnothing$, 故 $A \cup B \ne \varnothing$. 对于任意 $a \in A$, 有 $a \le p \le \max(p,q)$, 同理有 $b \in B \rightarrow b \le \max(p, q)$. 故 $\max(p,q)$ 是 $A \cup B$ 的上界.

假设 $\max(p,q)$ 不是 $A \cup B$ 的上确界, 则有 $h < \max(p, q)$ 是 $A \cup B$ 的上界. 我们有 $h < p \lor h < q$, 则不妨设 $h < p$, 另一种情况对称. 取 $s \in A$ 且 $s > h$, 则 $s \in A \cup B$ 且 $s > h$, 矛盾. 故 $\max(p,q)$ 是 $A+B$ 的上确界. $\blacksquare$

---

Lemma 3. 若 $A \cap B \ne \varnothing$, 则 $\sup(A \cap B) \le \min(p,q)$.

对于任意 $x \in A \cap B$, 有 $x \in A \land x \in B$, 故 $x \le p \land x \le q$, 也即 $x \le \min(p,q)$. 故 $\min(p,q)$ 是 $A \cap B$ 的一个上界, 故有上确界不超过 $\min(p,q)$. $\blacksquare$

---

Lemma 4. 存在一组 $A$ 和 $B$, 有 $\sup(A \cap B) < \min(p,q)$.

考虑 $A=\set{0,1}$, $B=\set{0,2}$, 有 $\sup(A \cap B)=0$, 但 $p=1$, $q=2$. $\blacksquare$
