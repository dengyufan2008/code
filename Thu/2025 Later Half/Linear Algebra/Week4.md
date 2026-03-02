# Week4 Homework (Textbook)

By Deng Yufan.

## P84 T1

Assume that $V$ and $W$ are finite-dimensional vector spaces with ordered bases $\beta$ and $\gamma$, respectively, and $T,U: V \rightarrow W$ are linear transformations.

a. For any scalar $a$, $aT + U$ is a linear transformation from $V$ to $W$.

b. $[T]^\gamma_\beta=[U]^\gamma_\beta$ implies that $T = U$.

c. If $m = \dim(V)$ and $n = \dim(W)$, then $[T]^\gamma_\beta$ is an $m \times n$ matrix.

d. $[T + U]^\gamma_\beta=[T]^\gamma_\beta+[U]^\gamma_\beta$.

e. $\mathcal L(V, W)$ is a vector space.

f. $\mathcal L(V, W) = \mathcal L(W,V)$.

a. True. b. True. c. True. d. True. e. True. f. False.

## P84 T2

Let $\beta$ and $\gamma$ be the standard ordered bases for $R^n$ and $R^m$, respectively. For each linear transformation $T: R^n \rightarrow R^m$, compute $[T]^\gamma_\beta$.

a. $T: R^2 \rightarrow R^3$ defined by $T(a_1, a_2) = (2a_1 - a_2, 3a_1 + 4a_2, a_1)$.

b. $T: R^3 \rightarrow R^2$ defined by $T(a_1, a_2, a_3) = (2a_1 + 3a_2 - a_3, a_1 + a_3)$.

c. $T: R^3 \rightarrow R$ defined by $T(a_1, a_2, a_3) = 2a_1 + a_2 - 3a_3$.

---

a. $T(\beta_1)=T(1, 0)=(2, 3, 1)=2\gamma_1+3\gamma_2+\gamma_3$, $T(\beta_2)=T(0, 1)=(-1, 4, 0)=-\gamma_1+4\gamma_2$.

So $[T(\beta_1)]_\gamma=\left[
\begin{matrix}
2
\\
3
\\
1
\end{matrix}
\right]$, $[T(\beta_2)]_\gamma=\left[
\begin{matrix}
-1
\\
4
\\
0
\end{matrix}
\right]$.

Then $[T]^\gamma_\beta=\left[
\begin{matrix}
2 & -1
\\
3 & 4
\\
1 & 0
\end{matrix}
\right]$.

b. Likewise, we have $[T]^\gamma_\beta=\left[
\begin{matrix}
2 & 3 & -1
\\
1 & 0 & 1
\end{matrix}
\right]$.

c. Likewise, we have $[T]^\gamma_\beta=\left[
\begin{matrix}
2 & 1 & -3
\end{matrix}
\right]$.

## P84 T4

Define $T: M_{2 \times 2}(R) \rightarrow P_2(R)$ by $T \left(
\begin{matrix}
a & b
\\
c & d	
\end{matrix}
\right) = (a + b) + (2d)x + bx^2$.

Let $\beta = \left\{
\left[
\begin{matrix}
1 & 0
\\
0 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 1
\\
0 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 0
\\
1 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 0
\\
0 & 1
\end{matrix}
\right] \right\}$ and $\gamma = \{1, x, x^2\}$.

Compute $[T]^\gamma_\beta$.

---

We have $T(\beta_1)=1=\gamma_1$, $T(\beta_2)=1+x^2=\gamma_1+\gamma_3$, $T(\beta_3)=0$, $T(\beta_4)=2x=2\gamma_2$.

So $[T]^\gamma_\beta=\left[
\begin{matrix}
1 & 1 & 0 & 0
\\
0 & 0 & 0 & 2
\\
0 & 1 & 0 & 0
\end{matrix}
\right]$.

## P84 T5

Let $\alpha = \left\{ \left[
\begin{matrix}
1 & 0
\\
0 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 1
\\
0 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 0
\\
1 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 0
\\
0 & 1
\end{matrix}
\right] \right\}$, $\beta = \{1, x, x^2\}$.

Define $T: P_2(R) \rightarrow M_{2 \times 2}(R)$ by $T(f(x)) = \left[
\begin{matrix}
f'(0) & 2f(1)
\\
0 & f''(3)
\end{matrix}
\right]
$. Compute $[T]^\alpha_\beta$.

---

We have $T(\beta_1) = \left[
\begin{matrix}
0 & 2
\\
0 & 0
\end{matrix}
\right] = 2\alpha_2$, $T(\beta_2) = \left[
\begin{matrix}
1 & 2
\\
0 & 0
\end{matrix}
\right] = \alpha_1+2\alpha_2$, $T(\beta_3) = \left[
\begin{matrix}
0 & 2
\\
0 & 2
\end{matrix}
\right] = 2\alpha_2+2\alpha_4$.

So $[T]^\alpha_\beta = \left[
\begin{matrix}
0 & 1 & 0
\\
2 & 2 & 2
\\
0 & 0 & 0
\\
0 & 0 & 2
\end{matrix}
\right]$.

## P85 T8

Let $V$ be an $n$-dimensional vector space with an ordered basis $\beta$. Define $T: V \rightarrow F^n$ by $T(x)=[x]_\beta$. Prove that T is linear.

---

We have $T(x)+T(y)=[x]_\beta+[y]_\beta=\left[
\begin{matrix}
a_1
\\
a_2
\\
\vdots
\\
a_n
\end{matrix}
\right] + \left[
\begin{matrix}
b_1
\\
b_2
\\
\vdots
\\
b_n
\end{matrix}
\right] = \left[
\begin{matrix}
a_1+b_1
\\
a_2+b_2
\\
\vdots
\\
a_n+b_n
\end{matrix}
\right]$, where $\sum_{i=1}^n a_i\beta_i = x$, $\sum_{i=1}^n b_i\beta_i = y$.

So $\sum_{i=1}^n (a_i+b_i)\beta_i = x+y$, that is $\left[
\begin{matrix}
a_1+b_1
\\
a_2+b_2
\\
\vdots
\\
a_n+b_n
\end{matrix}
\right] = [x+y]_\beta = T(x+y)$. So $T(x)+T(y)=T(x+y)$.

Likewise, we have $cT(x) = c[x]_\beta = c\left[
\begin{matrix}
a_1
\\
a_2
\\
\vdots
\\
a_n
\end{matrix}
\right] = \left[
\begin{matrix}
ca_1
\\
ca_2
\\
\vdots
\\
ca_n
\end{matrix}
\right] = [cx]_\beta = T(cx)$.

## P85 T11

Let $V$ be an $n$-dimensional vector space, and let $T: V \rightarrow V$ be a linear transformation. Suppose that $W$ is a $T$-invariant subspace of V having dimension $k$. Show that there is a basis $\beta$ for $V$ such that $[T]_\beta$ has the form $\left[
\begin{matrix}
A & B
\\
O & C
\end{matrix}
\right]$, where $A$ is a $k \times k$ matrix and $O$ is the $(n - k) \times k$ zero matrix.

---

Let $\{\beta_1, \beta_2, \cdots, \beta_n\}$ be a basis of $V$, and $\{\beta_1, \beta_2, \cdots, \beta_k\}$ be a basis of $W$. Now we prove $[T]_\beta$ has the form mentioned.

We have $[T]_\beta = [[T(\beta_1)]_\beta, [T(\beta_2)]_\beta, \cdots, [T(\beta_n)]_\beta]$, then we only have to prove for $1 \le i \le k, k+1 \le j \le n$, $j$th element in $[T(\beta_i)]_\beta$ is 0.

We have for $1 \le i \le k$, $\beta_i \in W$. So $T(\beta_i) \in W$, that is $T(\beta_i) = \sum_{t=1}^k a_t\beta_t$. So $T(\beta_i) = \left[
\begin{matrix}
a_1
\\
a_2
\\
\vdots
\\
a_k
\\
0
\\
\vdots
\\
0
\end{matrix}
\right]$. So obviously for $k+1 \le j \le n$, $j$th element in $[T(\beta_i)]_\beta$ is 0.

## P86 T13

Let $V$ and $W$ be vector spaces, and let $T$ and $U$ be nonzero linear transformations from $V$ into $W$. If $R(T) \cap R(U) = \{0\}$, prove that $\{T,U\}$ is a linearly independent subset of $\mathcal L(V, W)$.

---

Proof by contradiction. Assume that there exists $a, b \in F$ that $a^2+b^2>0$ and $aT+bU=0$. We can assume that $a \ne 0$, otherwise we can swap $T$ and $U$.

So let $c = -\frac{b}{a} \in F$, we have $T=cU$. Since $T$ is nonzero, we can find $x \in V$ that $T(x) \ne 0$. Then we have $T(x)=cU(x)=U(cx) \ne 0$. So $0 \ne T(x) \in R(T) \cap R(U)$, contradiction.

## P86 T15

Let $V$ and $W$ be vector spaces, and let $S$ be a subset of $V$. Define $S^0 = \{T \in \mathcal L(V, W): T(x) = 0 \text{ for all } x \in S\}$. Prove the following statements.

a. $S^0$ is a subspace of $\mathcal L(V, W)$.

b. If $S_1$ and $S_2$ are subsets of $V$ and $S_1 \subseteq S_2$, then $S^0_2 \subseteq S^0_1$.

c. If $V_1$ and $V_2$ are subspaces of $V$, then $(V_1 + V_2)^0 = V^0
_1 \cap V^0_2$.

---

a. Obviously the zero transformation is in $S^0$. For all $T, U \in S^0$, $a, b \in F$, for all $x \in S$, $(aT+bU)(x)=aT(x)+bU(x)=0$, so $aT+bU \in S^0$.

b. For all $T \in S^0_2$, we have for all $x \in S_2$, $T(x)=0$. Since $S_1 \subseteq S_2$, for all $x \in S_1 \subseteq S_2$, $T(x)=0$. So $T \in S^0_1$, that is $S^0_2 \subseteq S^0_1$.

c. For all $T \in (V_1+V_2)^0$, we have for all $x \in V_1+V_2$, $T(x)=0$. Since $V_1 \in V_1+V_2$, $V_2 \in V_1+V_2$, we have $T \in V_1^0$, $T \in V_2^0$, so $T \in V_1^0 \cap V_2^0$.

For all $T \in V_1^0 \cap V_2^0$, we have $T \in V_1^0$ and $T \in V_2^0$. So for all $x \in V_1$ or $x \in V_2$, $T(x)=0$. So for all $y \in V_1+V_2$, we can rewrite $y$ as $y_1+y_2$, where $y_1 \in V_1$ and $y_2 \in V_2$. We have $T(y_1)=T(y_2)=0$, so $T(y)=T(y_1+y_2)=0$. So $T \in (V_1+V_2)^0$.

In conlusion, $(V_1+V_2)^0 = V_1^0 \cap V_2^0$.

## P86 T16

Let $V$ and $W$ be vector spaces such that $\dim(V) = \dim(W)$, and let $T: V \rightarrow W$ be linear. Show that there exist ordered bases $\beta$ and $\gamma$ for $V$ and $W$, respectively, such that $[T]^\gamma_\beta$ is a diagonal matrix.

---

Let $n$ be $\dim(V)$, $m$ be $\text{nullity}(T)$. Consider $\{\beta_1, \beta_2, \cdots, \beta_m\}$ as a basis of $N(T)$, then we can have $\{\beta_1, \beta_2, \cdots, \beta_n\}$ as a basis of $V$.

We are about to prove $\{T(\beta_{m+1}), T(\beta_{m+1}), \cdots, T(\beta_n)\}$ is independent. If there exists $\vec a \ne 0$, $\sum_{i=m+1}^n a_iT(\beta_i)=0$. Then $T(\sum_{i=m+1}^n a_i\beta_i)=0$, $\sum_{i=m+1}^n a_i\beta_i \in N(T)$. But we know $\{\beta_1, \beta_2, \cdots, \beta_m\}$ is a basis of $N(T)$, and $\{\beta_1, \beta_2, \cdots, \beta_n\}$ is independent, so there is a contradiction.

Thus, we can have $\gamma = \{\gamma_1, \gamma_2, \cdots, \gamma_m, T(\beta_{m+1}), T(\beta_{m+2}), \cdots, T(\beta_n)\}$ is a basis of $W$. Consider $[T]^\gamma_\beta$, for $1 \le i \le m$, $[T(\beta_i)]_\gamma = \vec 0$, and for $m+1 \le i \le n$, $[T(\beta_i)]_\gamma$ is the $i$th standard ordered basis of $F^n$. So obviously $[T]^\gamma_\beta$ is a diagonal matrix.

## P96 T1

$V$, $W$, and $Z$ denote vector spaces with ordered (finite) bases $\alpha$, $\beta$, and $\gamma$, respectively; $T: V \rightarrow W$ and $U: W \rightarrow Z$ denote linear transformations; and $A$ and $B$ denote matrices.

a. $[UT]^\gamma_\alpha = [T]^\beta_\alpha[U]^\gamma_\beta$.

b. $[T(v)]_\beta = [T]^\beta_\alpha[v]_\alpha$ for all $v \in V$.

c. $[U(w)]_\beta = [U]^\beta_\alpha[w]_β$ for all $w ∈ W$.

d. $[I_V]_\alpha = I$.

e. $[T^2]^\beta_\alpha = ([T]^\beta_\alpha)^2$.

f. $A^2 = I$ implies that $A = I$ or $A = -I$.

g. $T = L_A$ for some matrix $A$.

h. $A^2 = O$ implies that $A = O$, where $O$ denotes the zero matrix.

i. $L_{A+B} = L_A + L_B$.

j. If $A$ is square and $A_{ij} = \delta_{ij}$ for all $i$ and $j$, then $A = I$.

a. False. b. True. c. False. d. True. e. False. f. False. g. False. h. False. i. True. j. True.

## P96 T2

a. Let $A = \left[
\begin{matrix}
1 & 3
\\
2 & -1
\end{matrix}
\right]$, $B = \left[
\begin{matrix}
1 & 0 & -3
\\
4 & 1 & 2	
\end{matrix}
\right]$, $C = \left[
\begin{matrix}
1 & 1 & 4
\\
-1 & -2 & 0
\end{matrix}
\right]$, and $D = \left[
\begin{matrix}
2
\\
-2
\\
3
\end{matrix}
\right]$. Compute $A(2B + 3C)$, $(AB)D$, and $A(BD)$.

b. Let $A = \left[
\begin{matrix}
2 & 5
\\
-3 & 1
\\
4 & 2
\end{matrix}
\right]$, $B = \left[
\begin{matrix}
3 & -2 & 0
\\
1 & -1 & 4
\\
5 & 5 & 3
\end{matrix}
\right]$, and $C = \left[
\begin{matrix}
4 & 0 & 3
\end{matrix}
\right]$. Compute $A^t$, $A^tB$, $BC^t$, $CB$, and $CA$.

---

a. $A(2B+3C)= \left[
\begin{matrix}
20 & -9 & 18
\\
5 & 10 & 8
\end{matrix}
\right]$, $(AB)D=A(BD)= \left[
\begin{matrix}
29
\\
-26
\end{matrix}
\right]$.

b. $A^t= \left[
\begin{matrix}
2 & -3 & 4
\\
5 & 1 & 2
\end{matrix}
\right]$, $A^tB= \left[
\begin{matrix}
23 & 19 & 0
\\
26 & -1 & 10
\end{matrix}
\right]$, $BC^t= \left[
\begin{matrix}
12
\\
16
\\
29
\end{matrix}
\right]$, $CB= \left[
\begin{matrix}
27 & 7 & 9
\end{matrix}
\right]$, $CA= \left[
\begin{matrix}
20 & 26
\end{matrix}
\right]$.

## P96 T3

Let $g(x)=3+x$. Let $T:P_2(R) \rightarrow P_2(R)$ and $U: P_2(R) \rightarrow R^3$ be the linear transformations respectively defined by $T(f(x)) = f'(x)g(x)+2f(x)$ and $U(a + bx + cx^2)=(a + b, c, a - b)$.

Let $\beta$ and $\gamma$ be the standard ordered bases of $P_2(R)$ and $R^3$, respectively.

a. Compute $[U]^\gamma_\beta$, $[T]_\beta$, and $[UT]^\gamma_\beta$ directly. Then use Theorem 2.11 to verify your result.

b. Let $h(x)=3 - 2x + x^2$. Compute $[h(x)]_\beta$ and $[U(h(x))]_\gamma$. Then use $[U]^\gamma_\beta$ from (a) and Theorem 2.14 to verify your result.

---

a. $[U]^\gamma_\beta= \left[
\begin{matrix}
1 & 1 & 0
\\
0 & 0 & 1
\\
1 & -1 & 0
\end{matrix}
\right]$, $[T]_\beta= \left[
\begin{matrix}
2 & 3 & 0
\\
0 & 3 & 6
\\
0 & 0 & 4
\end{matrix}
\right]$, $[UT]^\gamma_\beta= \left[
\begin{matrix}
2 & 6 & 6
\\
0 & 0 & 4
\\
2 & 0 & -6
\end{matrix}
\right]$.

Obviously $[UT]^\gamma_\beta=[U]^\gamma_\beta[T]_\beta$.

b. $[h(x)]_\beta= \left[
\begin{matrix}
3
\\
-2
\\
1
\end{matrix}
\right]$, $[U(h(x))]_\gamma= \left[
\begin{matrix}
1 & 1 & 5
\end{matrix}
\right]$.

Obviously $[U(h(x))]_\gamma=[U]^\gamma_\beta[h(x)]_\beta$.

## P97 T4

Let $\alpha = \left\{ \left[
\begin{matrix}
1 & 0
\\
0 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 1
\\
0 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 0
\\
1 & 0	
\end{matrix}
\right], \left[
\begin{matrix}
0 & 0
\\
0 & 1
\end{matrix}
\right] \right\}$, $\beta = \{1, x, x^2\}$, $\gamma = \{1\}$. Use Theorem 2.14 to compute the following vectors.

a. Define $T: M_{2 \times 2}(F) \rightarrow M_{2 \times 2}(F)$ by $T(A) = A^t$. Calculate $[T(A)]_\alpha$, where $A = \left[
\begin{matrix}
1 & 4
\\
-1 & 6
\end{matrix}
\right]$.

b. Define $T: P_2(R) \rightarrow M_{2 \times 2}(R)$ by $T(f(x)) = \left[
\begin{matrix}
f'(0) & 2f(1)
\\
0 & f''(3)
\end{matrix}
\right]
$. Calculate $[T(f(x))]_\alpha$, where $f(x)=4 - 6x + 3x^2$.

---

a. $T(A) = \left[
\begin{matrix}
1 & -1
\\
4 & 6
\end{matrix}
\right] = \alpha_1-\alpha_2+4\alpha_3+6\alpha_4$, then $[T(A)]_\alpha = \left[
\begin{matrix}
1
\\
-1
\\
4
\\
6
\end{matrix}
\right]$.

b. $T(f(x))=\left[
\begin{matrix}
-6 & 2
\\
0 & 6
\end{matrix}
\right]=-6\alpha_1+2\alpha_2+6\alpha_4$, then $[T(f(x))]_\alpha=\left[
\begin{matrix}
-6
\\
2
\\
0
\\
6
\end{matrix}
\right]$.

## P97 T9

Find linear transformations $U,T: F^2 \rightarrow F^2$ such that $UT = T_0$ (the zero transformation) but $TU \ne T_0$. Use your answer to find matrices $A$ and $B$ such that $AB = O$ but $BA \ne O$.

---

Consider $T(x, y)=(x+y, 0)$, $U(x, y)=(0, y)$. Obviously $T, U$ are linear transformations, and $U(T(x, y))=U(x+y, 0)=(0, 0)$, $T(U(x, y))=T(0, y)=(y, 0)$. So $UT=T_0$ but $TU \ne T_0$.

Let $\beta$ be the standard ordered basis of $F^2$, consider $A=[U]_\beta=\left[
\begin{matrix}
0 & 0
\\
0 & 1
\end{matrix}
\right]$, $B=[T]_\beta=\left[
\begin{matrix}
1 & 1
\\
0 & 0
\end{matrix}
\right]$, we have $AB=O$ but $BA=\left[
\begin{matrix}
0 & 1
\\
0 & 0
\end{matrix}
\right]$.

## P97 T12

Let $V$, $W$, and $Z$ be vector spaces, and let $T: V \rightarrow W$ and $U: W \rightarrow Z$ be linear.

a. Prove that if $UT$ is one-to-one, then $T$ is one-to-one. Must $U$ also be one-to-one?

b. Prove that if $UT$ is onto, then $U$ is onto. Must $T$ also be onto?

c. Prove that if $U$ and $T$ are one-to-one and onto, then $UT$ is also.

---

a. Assume $x \ne y$ and $T(x)=T(y)$. We have $U(T(x))=U(T(y))$, so $UT$ is not one-to-one. Contradiction.

Consider $T(x, y)=(x, y, 0)$ and $U(x, y, z)=(x, y)$. Obviously $T$ and $U$ is linear transformations, and $UT$ is one-to-one, but $U$ is not one-to-one.

b. For all $z$, exists $x$ that $U(T(x))=z$. Then for all $z$, consider $y=T(x)$, $U(y)=z$. So $U$ is onto.

Also consider $T(x, y)=(x, y, 0)$ and $U(x, y, z)=(x, y)$. Obviously $UT$ is onto, but $T$ is not onto.

c. For all $x \ne y$, we have $T(x) \ne T(y)$, so $U(T(x)) \ne U(T(y))$. Thus $UT$ is one-to-one.

For all $z$, there exists a $y$ that $U(y)=z$. And there exists a $x$ that $T(x)=y$. So $U(T(x))=z$, $UT$ is onto.

## P98 T16

Let $V$ be a finite-dimensional vector space, and let $T: V \rightarrow V$ be linear.

a. If $\text{rank}(T) = \text{rank}(T^2)$, prove that $R(T) \cap N(T) = \{0\}$. Deduce that $V = R(T) \oplus N(T)$.

b. Prove that $V = R(T^k) \oplus N(T^k)$ for some positive integer $k$.

---

a. Obviously $R(T^2) \subseteq R(T)$, so if $\dim(R(T^2))=\dim(R(T))$, $R(T^2)=R(T)$. Let $S=R(T)$, consider $U:S \rightarrow S$ that $U(x)=T(x)$. we have $R(U)=\{T(x) | x \in S\}=\{T^2(x) | x \in V\} = R(T^2) = S$. So $\dim(S)=\text{rank}(U)$, then $\text{nullity}(U)=0$, that is $x \in S \land x \ne 0 \rightarrow U(x) \ne 0$.

So $x \ne 0 \land x \in R(T) \rightarrow x \notin N(T)$, that is $R(T) \cap N(T) \subseteq \{0\}$. And we have $T(0)=0$, so $R(T) \cap N(T) = \{0\}$.

If $x \in R(T)$ and $y \in N(T)$, we have $x \in V$ and $y \in V$, so $x+y \in V$. Thus $R(T)+N(T) \subseteq V$.

If $x \in V$, let $y=T(x) \in S$. Since $\dim(S)=\text{rank}(U)$, $U$ is onto. So there exists $z \in S$ that $T(z)=y$. Let $u=x-z$, we have $T(u)=T(x)-T(z)=0$, So we have $z \in R(T)$ and $u \in N(T)$, $z+u=x$. Thus $V \subseteq R(T)+N(T)$. Totally, $V=R(T)+N(T)$. And $R(T) \cap N(T)=\{0\}$, so $V=R(T) \oplus N(T)$.

b. Induction to prove $R(U^k)=S$, we have $R(U^k)=\{T(x) | x \in R(U^{k-1})\}=\{T(x) | x \in S\}=S$, so $U^k$ is onto. Like we did in (a), $N(U^k)=\{0\}$, so $R(U^k) \cap N(U^k) = \{0\}$.

Also like we did in (a), $R(T^k)+N(T^k) \subseteq V$. If $x \in V$, let $y=T^k(x) \in S$, and $z \in S$ that $T^k(z)=y$, $u=x-z$. Then $T^k(u)=T^{k-1}(T(x)-T(z))=T^{k-2}(T^2(x)-T^2(z))=\cdots=T^k(x)-T^k(z)=0$. Thus $z \in R(T^k)$ and $u \in N(T^k)$, $z+u=x$. So $V=R(T^k) \oplus N(T^k)$.

## P106 T1

$V$ and $W$ are vector spaces with ordered (finite) bases $\alpha$ and $\beta$, respectively, $T: V \rightarrow W$ is linear, and $A$ and $B$ are matrices.

a. $([T]^\beta_\alpha)^{-1}=[T^{-1}]^\beta_\alpha$.

b. $T$ is invertible if and only if $T$ is one-to-one and onto.

c. $T = L_A$, where $A = [T]^\beta_\alpha$.

d. $M_{2 \times 3}(F)$ is isomorphic to $F^5$.

e. $P_n(F)$ is isomorphic to $P_m(F)$ if and only if $n = m$.

f. $AB = I$ implies that $A$ and $B$ are invertible.

g. If $A$ is invertible, then $(A^{-1})^{-1} = A$.

h. $A$ is invertible if and only if $L_A$ is invertible.

i. $A$ must be square in order to possess an inverse.

a. False. b. True. c. True. d. False. e. True. f. False. g. True. h. True. i. True.

## P106 T2

Determine whether $T$ is invertible and justify your answer.

a. $T: R^2 \rightarrow R^3$ defined by $T(a_1, a_2)=(a_1 - 2a_2, a_2, 3a_1 + 4a_2)$.

c. $T: R^3 \rightarrow R^3$ defined by $T(a_1, a_2, a_3) = (3a_1 - 2a_3, a_2, 3a_1 + 4a_2)$.

e. $T: M_{2 \times 2}(R) \rightarrow P_2(R)$ defined by $T \left(
\begin{matrix}
a & b
\\
c & d	
\end{matrix}
\right) = a + 2bx + (c + d)x^2$.

---

a. Since $\dim(R^2) = 2 \ne 3 = \dim(R^3)$, $T$ has no inverse.

b. $T^{-1}(a_1, a_2, a_3)=(-\frac{4}{3}a_2+\frac{1}{3}a_3, a_2, -\frac{1}{2}a_1-2a_2+\frac{1}{2}a_3)$. Obviously $T(T^{-1}(a_1, a_2, a_3))=T(-\frac{4}{3}a_2+\frac{1}{3}a_3, a_2, -\frac{1}{2}a_1-2a_2+\frac{1}{2}a_3)=(a_1, a_2, a_3)$, $T^{-1}(T(a_1, a_2, a_3))=T^{-1}(3a_1 - 2a_3, a_2, 3a_1 + 4a_2)=(a_1, a_2, a_3)$.

c. Since $\dim(M_{2 \times 2}(R)) = 4 \ne 3 = \dim(P_2(R))$, $T$ has no inverse.

## P107 T5

Let $A$ be invertible. Prove that $A^t$ is invertible and $(A^t)^{−1} = (A^{−1})^t$.

---

Let $B$ satisfy $AB=BA=I$. Then $A^tB^t=(BA)^t=I$, $B^tA^t=(AB)^t=I$.

So $(A^t)^{-1}=(A^{-1})^t$.

## P107 T9

Let $A$ and $B$ be $n \times n$ matrices such that $AB$ is invertible. Prove that $A$ and $B$ are invertible. Give an example to show that arbitrary matrices $A$ and $B$ need not be invertible if $AB$ is invertible.

---

Let $C$ satisfy $(AB)C=C(AB)=I$. Obviously $A(BC)=I$ and $(CA)B=I$. We are about to prove when $A$ and $B$ are $n \times n$ matrices, $AB=I \rightarrow BA=I$. Then $A^{-1}=BC$ and $B^{-1}=CA$.

Let $T=L_A$, $U=L_B$, we have $TU=I$. According to P97 T12 (a), $TU$ is one-to-one, so $U$ is one-to-one. Since $U:F^n \rightarrow F^n$, and $\dim(F^n)=\dim(F^n)$, so $U$ is onto.

We have $UTU=UI=U$. For all $x$, we can find $U(y)=x$, and $U(T(U(y)))=U(y)$. So $U(T(x))=x$, $UT=I$. Thus $BA=I$.

When $A=\left[
\begin{matrix}
0 & 1
\end{matrix}
\right]$, $B=\left[
\begin{matrix}
0
\\
1
\end{matrix}
\right]$, we have $AB=[1]$, which is invertible, but $A$ and $B$ are not.

## Extra 1

For an arbitrary $n \times n$ matrix $A \in M_{n \times n}(R)$ with all entries smaller than 1 for their absolute values, can we have $\lim_{m \rightarrow \infty}⁡ A^m = 0$. Justify your answer.

---

Consider when $A=\left[
\begin{matrix}
\frac{\sqrt 2}{2} & \frac{\sqrt 2}{2}
\\
\frac{\sqrt 2}{2} & \frac{\sqrt 2}{2}
\end{matrix}
\right]$, $A^2=\left[
\begin{matrix}
1 & 1
\\
1 & 1
\end{matrix}
\right]$, $A^{2^n}=\left[
\begin{matrix}
2^{2^{n-1}-1} & 2^{2^{n-1}-1}
\\
2^{2^{n-1}-1} & 2^{2^{n-1}-1}
\end{matrix}
\right]$. So $\lim_{m \rightarrow +\infty}⁡ A^m = \left[
\begin{matrix}
+\infty & +\infty
\\
+\infty & +\infty
\end{matrix}
\right]$.

## Extra 2

Let $U$ be a subspace of a finite-dimensional vector space $V$. Let $T:V \rightarrow V$ be a linear transformation. Prove $\dim⁡(U)-\dim⁡(N(T)) \le \dim⁡(T(U)) \le \dim⁡(U)$.

---

Consider $W: U \rightarrow U$ that $W(x)=T(x)$. We have $\dim(U)=\dim(R(W))+\dim(N(W))=\dim(T(U))+\dim(N(W))$.

Since $W(x)=0 \rightarrow T(x)=0$, so $N(W) \subseteq N(T)$, $\dim(N(W)) \le \dim(N(T))$. So $\dim(U)-\dim(T(U))=\dim(N(W)) \le \dim(N(T))$, that is $\dim(U)-\dim(N(T)) \le \dim(T(U))$.

And we have $\dim(N(W)) \ge 0$, so $\dim(U)-\dim(T(U))=\dim(N(W)) \ge 0$, that is $\dim(T(U)) \le \dim(U)$.

In conclusion, $\dim⁡(U)-\dim⁡(N(T)) \le \dim⁡(T(U)) \le \dim⁡(U)$.

## Extra 3

Prove $\text{rank}(L_A)+\text{rank}(L_B)-n \le \text{rank}(L_{AB}) \le \min⁡(\text{rank}(L_A),\text{rank}(L_B))$, where $A$ and $B$ are $n \times n$ matrices.

---

Let $V=R(L_B)$. Since $V$ is a vector space using definition of add and scarlar multiple in $F^n$, and $V \subseteq F^n$, then $V$ is a subspace of $F^n$. We have $L_A:F^n \rightarrow F^n$.

According to Extra 2, we have $\text{rank}(L_B)-\text{nullity}(L_A) \le \dim(L_AV) \le \text{rank}(L_B)$. Since $L_AV=R(L_{AB})$ and $-\text{nullity}(L_A)=\text{rank}(L_A)-\dim(F^n)=\text{rank}(L_A)-n$, we have $\text{rank}(L_B)+\text{rank}(L_A)-n \le \text{rank}(L_{AB}) \le \text{rank}(L_B)$.

We also have $R(L_{AB}) \subseteq R(L_A)$, then $\text{rank}(L_{AB}) \le \text{rank}(L_A)$.

In conclusion, $\text{rank}(L_A)+\text{rank}(L_B)-n \le \text{rank}(L_{AB}) \le \min⁡(\text{rank}(L_A),\text{rank}(L_B))$.

## Extra 4

Prove $\text{rank}(L_{A+B}) \le \text{rank}(L_A)+\text{rank}(L_B)$ where $A$ and $B$ are $n \times m$ matrices.

---

We have $R(L_{A+B})=\{(A+B)x | x \in F^m\} \subseteq \{Ax+By|x, y \in F^m\}=\{Ax|x \in F^m\}+\{Bx|x \in F^m\}=R(L_A)+R(L_B)$.

So $\text{rank}(L_{A+B}) \le \dim(R(L_A)+R(L_B))$. Since $\dim(R(L_A)+R(L_B))=\text{rank}(L_A)+\text{rank}(L_B)-\dim(R(L_A) \cap R(L_B))$ proved in last week, $\text{rank}(L_{A+B}) \le \dim(R(L_A)+R(L_B)) \le \text{rank}(L_A)+\text{rank}(L_B)$.
