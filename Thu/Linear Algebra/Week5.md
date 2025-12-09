# Week5 Homework (Textbook)

By Deng Yufan.

## P107 T13

Let $\sim$ mean "is isomorphic to". Prove that $\sim$ is an equivalence relation on the class of vector spaces over $F$.

---

Reflexivity: Consider $I_V$, then $I_VI_V=I_V$, so $V \sim V$.

Symmetry: If $V \sim W$, then there is $T:V \rightarrow W$ is invertible. So $T^{-1}:W \rightarrow V$ is invertible, so $W \sim V$.

Transitivity: If $V \sim W$, $W \sim R$, then there is $T:V \rightarrow W$, $U:W \rightarrow R$ is invertible. Consider $UT:V \rightarrow R$, we show it has inverse $T^{-1}U^{-1}$.

We have $T^{-1}U^{-1}UT=T^{-1}(U^{-1}U)T=T^{-1}I_WT=T^{-1}T=I_V$ and $UTT^{-1}U^{-1}=U(TT^{-1})U^{-1}=UI_WU^{-1}=UU^{-1}=I_R$. So $V \sim R$.

## P108 T15

Let $V$ and $W$ be finite-dimensional vector spaces, and let $T: V \rightarrow W$ be a linear transformation. Suppose that $\beta$ is a basis for $V$. Prove that $T$ is an isomorphism if and only if $T(\beta)$ is a basis for $W$.

---

Let $n$ be $\dim(V)$.

Only if: We have $T^{-1}T=I_V$ and $TT^{-1}=I_V$. According to P97 T12, since $I_V$ is one-to-one, then $T$ is one-to-one; since $I_V$ is onto, then $T$ is onto.

For all $x \in V$, we have $x=\sum_{i=1}^na_i\beta_i$, then $T(x)=\sum_{i=1}^na_iT(\beta_i)$, so $T(x) \in \text{span}(T(\beta))$. Since $T$ is onto, then $\text{span}(T(\beta))=W$.

Since $T$ is one-to-one, $T(x)=0$ only if $x=0$. So for all $a_1, a_2, \cdots, a_n$, $\sum_{i=1}^na_iT(\beta_i)=T(\sum_{i=1}^na_i\beta_i)$. So $LHS=0$ only if $\sum_{i=1}^na_i\beta_i=0$, so $T(\beta)$ is independent. So $T(\beta)$ is a basis for $W$.

If: For all $a_1, a_2, \cdots, a_n$, $\sum_{i=1}^na_iT(\beta_i)=T(\sum_{i=1}^na_i\beta_i)$. So for all $w \in \text{span}(T(\beta))$, we can find a $x \in V$ that $T(x)=w$. Since $\text{span}(T(\beta))=W$, so $T$ is onto.

For all $x \in V$, we have $x=\sum_{i=1}^na_i\beta_i$, then $T(x)=\sum_{i=1}^na_iT(\beta_i)$. Since $T(\beta)$ is independent, $T(x)=0$ only if $a_i=0$, then $x=0$. So $T$ is one-to-one.

So $T$ is one-to-one and onto, we can have $U:W \rightarrow V$ that $U(x)$ is the only $y$ satisfying $T(y)=x$. So $U(T(x))=x$, $T(U(x))=x$. So $T$ is invertible, then $T$ is an isomorphism.

## P108 T17

Let $V$ and $W$ be finite-dimensional vector spaces and $T: V \rightarrow W$ be an isomorphism. Let $V_0$ be a subspace of $V$.

a. Prove that $T(V_0)$ is a subspace of $W$.

b. Prove that $\dim(V_0) = \dim(T(V_0))$.

---

Let $n=\dim(V)$, $m=\dim(V_0)$. Let $\beta_1, \beta_2, \cdots, \beta_m$ be a basis of $V_0$. Since $V_0$ is a subspace of $V$, we can have $\beta_1, \beta_2, \cdots, \beta_n$ be a basis of $V$. Since $T$ is an isomorphism, according to P108 T15, $T(\beta)$ is a basis of $W$. So $T(\beta_1), T(\beta_2), \cdots, T(\beta_m)$ is independent. Then $T(V_0)=T(\text{span}\{\beta_1, \beta_2, \cdots, \beta_m\})=\text{span}\{T(\beta_1), T(\beta_2), \cdots, T(\beta_m)\}$ is a subspace of $W$, and $T(\beta_1), T(\beta_2), \cdots, T(\beta_m)$ is a basis of $T(V_0)$. So $\dim(V_0)=m=\dim(T(V_0))$.

<!--
Holy shit, I did an extra prob!

## P117 T5

Let $T$ be the linear operator on $P_1(R)$ defined by $T(p(x)) = p'(x)$, the derivative of $p(x)$. Let $\beta = \{1, x\}$ and $\beta' = \{1 + x, 1 − x\}$. Use Theorem 2.23 and the fact that $
\left[
\begin{matrix}
1 & 1
\\
1 & -1
\end{matrix}
\right]^{-1} = \left[
\begin{matrix}
\frac{1}{2} & \frac{1}{2}
\\
\frac{1}{2} & -\frac{1}{2}
\end{matrix}
\right]
$ to find $[T]_\beta'$.

---

We have $Q$ changes $\beta'$ coor into $\beta$ coor, and $Q=\left[
\begin{matrix}
1 & 1
\\
1 & -1
\end{matrix}
\right]$, $Q^{-1}=\left[
\begin{matrix}
\frac{1}{2} & \frac{1}{2}
\\
\frac{1}{2} & -\frac{1}{2}
\end{matrix}
\right]$. We also have $[T]_\beta=\left[
\begin{matrix}
0 & 1
\\
0 & 0
\end{matrix}
\right]$.

Using Thm 2.23, $[T]_{\beta'}=Q^{-1}[T]_\beta Q=\left[
\begin{matrix}
\frac{1}{2} & -\frac{1}{2}
\\
\frac{1}{2} & -\frac{1}{2}
\end{matrix}
\right]$.
-->

## P116 T1

a. Suppose that $\beta = \{x_1, x_2,\cdots,x_n\}$ and $\beta' = \{x_1', x_2',\cdots,x_n'\}$ are ordered bases for a vector space and $Q$ is the change of coordinate matrix that changes $\beta'$-coordinates into $\beta$-coordinates. Then the $j$th column of Q is $[x_j]_{\beta'}$.

b. Every change of coordinate matrix is invertible.

c. Let $T$ be a linear operator on a finite-dimensional vector space $V$, let $\beta$ and $\beta'$ be ordered bases for $V$, and let $Q$ be the change of coordinate matrix that changes $\beta'$-coordinates into $\beta$-coordinates. Then $[T]_\beta = Q[T]_{\beta'}Q^{−1}$.

d. The matrices $A, B \in M_{n \times n}(F)$ are called similar if $B = Q^tAQ$ for some $Q \in M_{n \times n}(F)$.

e. Let $T$ be a linear operator on a finite-dimensional vector space $V$. Then for any ordered bases $\beta$ and $\gamma$ for $V$, $[T]_\beta$ is similar to $[T]_\gamma$.

a. False. b. True. c. True. d. False. e. True.

## P116 T2

For each of the following pairs of ordered bases $\beta$ and $\beta'$ for $R^2$, find the change of coordinate matrix that changes $\beta'$-coordinates into $\beta$-coordinates.

a. $\beta = \{e_1, e_2\}$ and $\beta' = \{(a_1, a_2),(b_1, b_2)\}$.

b. $\beta = \{(−1, 3),(2, −1)\}$ and $\beta' = \{(0, 10),(5, 0)\}$

---

a. We have $[\beta'_1]_\beta=\left[
\begin{matrix}
a_1
\\
a_2
\end{matrix}
\right]$, $[\beta'_2]_\beta=\left[
\begin{matrix}
b_1
\\
b_2
\end{matrix}
\right]$, so $Q$ changes $\beta'$-coor to $\beta$-coor and $Q=\left[
\begin{matrix}
a_1 & b_1
\\
a_2 & b_2
\end{matrix}
\right]$.

b. We have $[\beta'_1]_\beta=\left[
\begin{matrix}
4
\\
2
\end{matrix}
\right]$, $[\beta'_2]_\beta=\left[
\begin{matrix}
1
\\
3
\end{matrix}
\right]$, so $Q$ changes $\beta'$-coor to $\beta$-coor and $Q=\left[
\begin{matrix}
4 & 1
\\
2 & 3
\end{matrix}
\right]$.

## P116 T3

For each of the following pairs of ordered bases $\beta$ and $\beta'$ for $P_2(R)$, find the change of coordinate matrix that changes $\beta'$-coordinates into $\beta$-coordinates.

a. $\beta = \{x^2, x, 1\}$ and $\beta' = \{a_2x^2 + a_1x + a_0, b_2x^2 + b_1x + b_0, c_2x^2 + c_1x + c_0\}$.

---

a. We have $[\beta'_1]_\beta=\left[
\begin{matrix}
a_2
\\
a_1
\\
a_0
\end{matrix}
\right]$, $[\beta'_2]_\beta=\left[
\begin{matrix}
b_2
\\
b_1
\\
b_0
\end{matrix}
\right]$, $[\beta'_3]_\beta=\left[
\begin{matrix}
c_2
\\
c_1
\\
c_0
\end{matrix}
\right]$, so $Q$ changes $\beta'$-coor to $\beta$-coor and $Q=\left[
\begin{matrix}
a_2 & b_2 & c_2
\\
a_1 & b_1 & c_1
\\
a_0 & b_0 & c_0
\end{matrix}
\right]$.

## P116 T4

Let $T$ be the linear operator on $R^2$ defined by $T\left(
\begin{matrix}
a
\\
b
\end{matrix}
\right)=\left(
\begin{matrix}
2a+b
\\
a-3b
\end{matrix}
\right)$, let $\beta$ be the standard ordered basis for $R^2$, and let $\beta'=\left\{\left[
\begin{matrix}
1
\\
1
\end{matrix}
\right], \left[
\begin{matrix}
1
\\
2
\end{matrix}
\right]\right\}$. Use Theorem 2.23 and the fact that $\left[
\begin{matrix}
1 & 1
\\
1 & 2
\end{matrix}
\right]^{-1}=\left[
\begin{matrix}
2 & -1
\\
-1 & 1
\end{matrix}
\right]$ to find $[T]_{\beta'}$.

---

We have $Q$ changes $\beta'$ coor into $\beta$ coor, and $Q=\left[
\begin{matrix}
1 & 1
\\
1 & 2
\end{matrix}
\right]$, $Q^{-1}=\left[
\begin{matrix}
2 & -1
\\
-1 & 1
\end{matrix}
\right]$. We also have $[T]_\beta=\left[
\begin{matrix}
2 & 1
\\
1 & -3
\end{matrix}
\right]$.

Using Thm 2.23, $[T]_{\beta'}=Q^{-1}[T]_\beta Q=\left[
\begin{matrix}
8 & 13
\\
-5 & -9
\end{matrix}
\right]$.

## P117 T6

For each matrix $A$ and ordered basis $\beta$, find $[L_A]_\beta$. Also, find an invertible matrix $Q$ such that $[L_A]_\beta = Q^{−1}AQ$.

a. $A=\left[
\begin{matrix}
1 & 3
\\
1 & 1
\end{matrix}
\right]$ and $\beta=\left\{\left[
\begin{matrix}
1
\\
1
\end{matrix}
\right], \left[
\begin{matrix}
1
\\
2
\end{matrix}
\right]\right\}$.

---

a. We have $L_A(\beta_1)=\left[
\begin{matrix}
4
\\
2
\end{matrix}
\right]=6\beta_1-2\beta_2$, and $L_A(\beta_2)=\left[
\begin{matrix}
7
\\
3
\end{matrix}
\right]=11\beta_1-4\beta_2$. So $[L_A(\beta_1)]_\beta=\left[
\begin{matrix}
6
\\
-2
\end{matrix}
\right]$, $[L_A(\beta_2)]_\beta=\left[
\begin{matrix}
11
\\
-4
\end{matrix}
\right]$. So $[L_A]_\beta=\left[
\begin{matrix}
6 & 11
\\
-2 & -4
\end{matrix}
\right]$.

We found that when $Q=\left[
\begin{matrix}
1 & 1
\\
1 & 2
\end{matrix}
\right]$, $[L_A]_\beta=Q^{-1}AQ$.

## P117 T8

Prove the following generalization of Theorem 2.23. Let $T: V \rightarrow W$ be a linear transformation from a finite-dimensional vector space $V$ to a finite-dimensional vector space $W$. Let $\beta$ and $\beta'$ be ordered bases for $V$, and let $\gamma$ and $\gamma'$ be ordered bases for $W$. Then $[T]^{\gamma'}_{\beta'} = P^{−1}[T]^\gamma_\beta Q$, where $Q$ is the matrix that changes $\beta'$-coordinates into $\beta$-coordinates and $P$ is the matrix that changes $\gamma'$-coordinates into $\gamma$-coordinates.

---

For all $x \in V$, we have $[T]^{\gamma'}_{\beta'}[x]_{\beta'}=[T(x)]_{\gamma'}$, so $P[T]^{\gamma'}_{\beta'}[x]_{\beta'}=P[T(x)]_{\gamma'}=[T(x)]_\gamma$.

And we have $Q[x]_{\beta'}=[x]_\beta$, so $[T]^\gamma_\beta Q[x]_{\beta'}=[T]^\gamma_\beta[x]_\beta=[T(x)]_\gamma$. So $P[T]^{\gamma'}_{\beta'}[x]_{\beta'}=[T]^\gamma_\beta Q[x]_{\beta'}$.

So $L_{P[T]^{\gamma'}_{\beta'}}=L_{[T]^\gamma_\beta Q}$, thus $P[T]^{\gamma'}_{\beta'}=[T]^\gamma_\beta Q$. Which is $P^{-1}P[T]^{\gamma'}_{\beta'}=P^{-1}[T]^\gamma_\beta Q$, $[T]^{\gamma'}_{\beta'}=P^{-1}[T]^\gamma_\beta Q$.

## P118 T10

Prove that if $A$ and $B$ are similar $n \times n$ matrices, then $\text{tr}(A) = \text{tr}(B)$.

---

For all $P, Q \in M_{n \times n}(F)$, we have $\text{tr}(PQ)=\sum_{i=1}^n\sum_{j=1}^n p_{i, j}q_{j, i}=\sum_{j=1}^n\sum_{i=1}^n q_{j, i}p_{i, j}=\text{tr}(QP)$.

Since $A$ and $B$ are similar, then $\exist Q \in M_{n \times n}(F)$, $A=Q^{-1}BQ$. So $\text{tr}(A)=\text{tr}((Q^{-1}B)Q)=\text{tr}(Q(Q^{-1}B))=\text{tr}(B)$.

## P118 T13

Let $V$ be a finite-dimensional vector space over a field $F$, and let $\beta = \{x_1, x_2,\cdots,x_n\}$ be an ordered basis for $V$. Let $Q$ be an $n \times n$ invertible matrix with entries from $F$. Define $x'_j=\sum_{i=1}^n Q_{i, j}x_i \space (1 \le j \le n)$ and set $\beta'=\{x'_1, x'_2, \cdots, x'_n\}$. Prove that $\beta'$ is a basis for $V$ and hence that $Q$ is the change of coordinate matrix changing $\beta'$-coordinates into $\beta$-coordinates.

---

Let $A=[x_1, x_2, \cdots, x_n]$, $B=[x'_1, x'_2, \cdots, x'_n]$ such that $A,B \in M_{n \times n}(F)$. By definition, we have $B=AQ$.

If there is a $w \in F^n$ such that $Bw=0$, which is $\sum_{i=1}^n w_ix'_i=0$. Then we have $A(Qw)=0$, which is $\sum_{i=1}^n (Qw)_ix_i=0$. Since $\beta$ is independent, We have $Qw=0$. So $Q^{-1}Qw=Q^{-1}0$, that is $w=0$. So $\beta'$ is independent. Since $|\beta'|=n=\dim(V)$, $\beta'$ is a basis of $V$.

Since $x'_j=\sum_{i=1}^n Q_{i, j}x_i \space (1 \le j \le n)$, $Q$ changes $\beta'$-coor into $\beta$-coor.

## P118 T14

Prove the converse of Exercise 8: If $A$ and $B$ are each $m \times n$ matrices with entries from a field $F$, and if there exist invertible $m \times m$ and $n \times n$ matrices $P$ and $Q$, respectively, such that $B = P^{-1}AQ$, then there exist an $n$-dimensional vector space $V$ and an $m$-dimensional vector space $W$ (both over $F$), ordered bases $\beta$ and $\beta'$ for $V$ and $\gamma$ and $\gamma'$ for $W$, and a linear transformation $T: V \rightarrow W$ such that $A=[T]^\gamma_\beta$ and $B=[T]^{\gamma'}_{\beta'}$.

---

Consider $V=F^n$, $W=F^m$, $T=L_A$. Consider $\beta$ and $\gamma$ are the standard ordered bases for $V$ and $W$, respectively.

Consider $\beta'_j=\sum_{i=1}^n Q_{i, j}\beta_i \space (1 \le j \le n)$, $\gamma'_j=\sum_{i=1}^m P_{i, j}\gamma_i \space (1 \le j \le m)$, so $\beta'$ and $\gamma'$ are bases for $V$ and $W$, respectively; and $Q$ changes $\beta'$-coor into $\beta$-coor, $P$ changes $\gamma'$-coor into $\gamma$-coor, according to P118 T13.

Since $\beta$ and $\gamma$ are standard, so $A=[L_A]^\gamma_\beta=[T]^\gamma_\beta$. Since $B=P^{-1}AQ$, so $B=[T]^{\gamma'}_{\beta'}$.

## P124 T5

Let $V = P_1(R)$, and for $p(x) \in V$, define $f_1, f_2 \in V^*$ by $f_1(p(x))=\int_0^1 p(t)dt$ and $f_2(p(x))=\int_0^2 p(t)dt$. Prove that $\{f_1, f_2\}$ is a basis for $V^*$, and find a basis for $V$ for which it is the dual basis.

---

Let $\beta$ be the standard ordered basis of $P_1(R)$, $\gamma=\{1\}$. We have $[f_1]_\beta^\gamma=[1, \frac{1}{2}]$ and $[f_2]_\beta^\gamma=[2, 2]$. By solving the augmented matrix, we can find out that $\{[f_1]_\beta^\gamma, [f_2]_\beta^\gamma\}$ is independent, thus $\{f_1, f_2\}$ is independent. Since $|\{f_1, f_2\}|=2=\dim(V^*)$, $\{f_1, f_2\}$ is a basis for $V^*$.

We found that $\{\beta_1=2-2x, \beta_2=-\frac{1}{2}+x\}$, and $\{f_1, f_2\}$ is the dual basis of $\{\beta_1, \beta_2\}$. It's easy to verify that $f_1(\beta_1)=f_2(\beta_2)=1$, $f_1(\beta_2)=f_2(\beta_1)=0$.

## P125 T10

Let $V = P_n(F)$, and let $c_0, c_1,\cdots,c_n$ be distinct scalars in $F$.

a. For $0 \le i \le n$, define $f_i \in V^*$ by $f_i(p(x)) = p(c_i)$. Prove that $\{f_0, f_1,\cdots, f_n\}$ is a basis for $V^*$.

---

a. If there is $a_0, a_2, \cdots, a_n$ such that $\sum_{i=0}^na_if_i=0$. Then consider $p_i(x)=\prod_{0 \le j \le n, j \ne i} (x-c_j) \in P_n(F)$. We have for all $j \ne i$, $p_i(c_j)=0$, and $p_i(c_i) \ne 0$. So $\sum_{i=0}^na_if_i(p_j)=0$ only if $a_j = 0$. So for all $j$, $a_j=0$. Thus $\{f_i\}$ is independent. And since $|\{f_i\}|=n+1=\dim(V^*)$, $\{f_i\}$ is a basis of $V^*$.

## Extra 1

Let $A \stackrel S \rightarrow B \stackrel T \rightarrow C$ be linear maps between vector spaces. We say that the composition is *exact* if $N(T)=R(S)$.

a. Suppose $A=0$ is the zero vector space and $S:A \rightarrow B$ is the zero map. Translate what is means for the composition $0 \rightarrow B \rightarrow C$ to be exact into more familiar terminology.

b. Suppose instead that $C=0$ and $T:B \rightarrow C$ is the zero map. Translate what it means for the composition $A \rightarrow B \rightarrow 0$ to be exact into more familiar terminology.

c. Observe that if $A \stackrel S \rightarrow B \stackrel T \rightarrow C$ is exact, then $TS=0$. Give an example of linear maps $S:R \rightarrow R^2$ and $T:R^2 \rightarrow R$ such that $TS=0$ but the composition $R \stackrel S \rightarrow R^2 \stackrel T \rightarrow R$ is not exact.

---

a. We have $N(T)=R(S)=\{0\}$, which iff $T$ is one-to-one.

b. We have $R(S)=N(T)=B$, which iff $S$ is onto.

c. Notice that when $S(x)=(x, x)$ and $T(x, y)=0$, we have $\text{nullity}(T)=2$ and $\text{rank}(S)=1$, so $N(T) \ne R(S)$. And we obviously have $T(S(x))=0$ since $T(x, y)=0$.

## Extra 2

Given a sequence $V_n \stackrel{T_n} \rightarrow V_{n-1} \stackrel{T_{n-1}} \rightarrow \cdots \stackrel{T_2} \rightarrow V_1 \stackrel{T_1} \rightarrow V_0$ of vector spaces $V_0, \cdots, V_n$ with linear maps $T_i:V_i \rightarrow V_{i-1}$, we say this sequence is *exact* if $N(T_i)=R(T_{i+1})$ for every $i$.

Let $V$ be a vector space with subspace $W \subset V$. Consider the sequence $0 \stackrel P \rightarrow W \stackrel S \rightarrow V \stackrel T \rightarrow V/W \stackrel Q \rightarrow 0$, where $S$ is the inclusion map ($S(x)=x$), $T$ is the quotient map ($T(v)=v+W$), and $P, Q$ are zero maps. Show that this sequence is exact.

---

We have $N(S)=\{0\}=R(P)$ by definition.

We have $R(S)=W$, and $N(T)=W$ proved in P79 T40. So $N(T)=R(S)$.

We have $T$ is onto by definition of $V/W$, so $R(T)=V/W=N(Q)$.
