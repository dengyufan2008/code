# Week6 Homework (Textbook)

By Deng Yufan.

## P123 T1

a. Every linear transformation is a linear functional.

b. A linear functional defined on a field may be represented as a $1 \times 1$ matrix.

c. Every vector space is isomorphic to its dual space.

d. Every vector space is isomorphic to the dual of some other vector space.

e. If $T$ is an isomorphism from $V$ onto $V^*$ and $\beta$ is a finite ordered basis for $V$, then $T(\beta)$ = $\beta^*$.

f. If $T$ is a linear transformation from $V$ to $W$, then the domain of $(T^t)^t$ is $V^{**}$.

g. If $V$ is isomorphic to $W$, then $V^*$ is isomorphic to $W^*$.

h. The derivative of a function may be considered as a linear functional on the vector space of differentiable functions.

a. False. b. True. c. True. d. True. e. False. f. True. g. True. h. False.

## P124 T6

Define $f \in (R^2)^*$ by $f(x, y)=2x + y$ and $T: R^2 \rightarrow R^2$ by $T(x, y) = (3x + 2y, x)$.

a. Compute $T^t(f)$.

b. Compute $[T^t]_{\beta^*}$, where $\beta$ is the standard ordered basis for $R^2$ and $\beta^* = \{f_1, f_2\}$ is the dual basis, by finding scalars $a$, $b$, $c$, and $d$ such that $T^t(f_1) = af_1 + cf_2$ and $T^t(f_2) = bf_1 + df_2$.

c. Compute $[T]_\beta$ and $([T]_\beta)^t$, and compare your results with (b).

---

a. We have $T^t(f)(x, y)=f(T(x, y))=f(3x+2y,x)=7x+4y$.

b. We have $f_1(x, y)=x$ and $f_2(x, y)=y$. And $T^t(f_1)(x, y)=f_1(T(x, y))=3x+2y$, $T^t(f_2)(x, y)=f_2(T(x, y))=x$. So $T^t(f_1)=3f_1+2f_2$, $T^t(f_2)=f_1$. So $[T^t]_{\beta^*}=\left[\begin{matrix}3 & 1 \\ 2 & 0\end{matrix}\right]$.

c. We have $T(1, 0)=(3, 1)$ and $T(0, 1)=(2, 0)$, so $[T]_\beta=\left[\begin{matrix}3 & 2 \\ 1 & 0\end{matrix}\right]$, $([T]_\beta)^t=\left[\begin{matrix}3 & 1 \\ 2 & 0\end{matrix}\right]=[T^t]_{\beta^*}$.

## P124 T7

Let $V = P_1(R)$ and $W = R^2$ with respective standard ordered bases $\beta$ and $\gamma$. Define $T: V \rightarrow W$ by $T(p(x))=(p(0)-2p(1), p(0)+p'(0))$.

a. For $f \in W^*$ defined by $f(a, b) = a − 2b$, compute $T^t(f)$.

b. Compute $[T^t]^{\beta^*}_{\gamma^*}$ without appealing to Theorem 2.25.

c. Compute $[T]^\gamma_\beta$ and its transpose, and compare your results with (b).

---

a. We have $T^t(f)(p(x))=f(T(p(x)))=f(p(0)-2p(1), p(0)+p'(0))=-p(0)-2p(1)-2p'(0)$.

b. Let $\beta^*=\{f_1, f_2\}$, $\gamma^*=\{g_1, g_2\}$.

We have $T^t(g_1)(p(x))=g_1(T(p(x)))=g_1(p(0)-2p(1), p(0)+p'(0))=p(0)-2p(1)=f_1(p)-2(f_1(p)+f_2(p))=-f_1(p)-2f_2(p)$.

And $T^t(g_2)(p(x))=g_2(T(p(x)))=g_2(p(0)-2p(1), p(0)+p'(0))=p(0)+p'(0)=f_1(p)+f_2(p)$.

So $[T^t]^{\beta^*}_{\gamma^*}=\left[\begin{matrix}-1 & 1 \\ -2 & 1\end{matrix}\right]$.

c. We have $T(1)=(-1, 1)$ and $T(x)=(-2, 1)$. So $[T]^\gamma_\beta=\left[\begin{matrix}-1 & -2 \\ 1 & 1\end{matrix}\right]$, $([T]^\gamma_\beta)^t=\left[\begin{matrix}-1 & 1 \\ -2 & 1\end{matrix}\right]=[T^t]^{\beta^*}_{\gamma^*}$.

## P125 T9

Prove that a function $T: F^n \rightarrow F^m$ is linear if and only if there exist $f_1, f_2,\cdots, f_m \in (F^n)^*$ such that $T(x)=(f_1(x), f_2(x),\cdots, f_m(x))$ for all $x \in F^n$.

---

If: We have $T(cx+y)=(f_1(cx+y), f_2(cx+y),\cdots, f_m(cx+y))=(cf_1(x)+f_1(y), cf_2(x)+f_2(y),\cdots, cf_m(x)+f_m(y))=c(f_1(x), f_2(x),\cdots, f_m(x))+(f_1(y), f_2(y),\cdots, f_m(y))=cT(x)+T(y)$.

Only if: Consider $f_i=T^t(g_i)=g_iT$, where $g_i$ is the $i$th dual basis of standard ordered basis of $F^m$. So $(f_1(x), f_2(x), \cdots, f_m(x))=(g_1(T(x)), g_2(T(x)), \cdots, g_m(T(x)))=T(x)$.

## P126 T13

$V$ denotes a finite-dimensional vector space over $F$. For every subset $S$ of $V$, define the annihilator $S^0$ of $S$ as $S^0=\{f \in V^*:f(x)=0 \text{ for all } x \in S\}$.

a. Prove that $S^0$ is a subspace of $V^*$.

b. If $W$ is a subspace of $V$ and $x \notin W$, prove that there exists $f \in W^0$ such that $f(x) \ne 0$.

c. Prove that $(S^0)^0 = \text{span}(\psi(S))$, where $\psi$ is defined as in Theorem 2.26, $\psi(x)=\hat x$.

d. For subspaces $W_1$ and $W_2$, prove that $W_1 = W_2$ if and only if $W^0_1 = W^0_2$.

e. For subspaces $W_1$ and $W_2$, show that $(W_1 + W_2)^0 = W^0_1 \cap W^0_2$.

---

a. We have $0(x) \in S^0$. And if $f \in S^0$, $g \in S^0$, then for all $x \in S$, $cf(x)+g(x)=0$. So $cf+g \in S^0$.

b. Let $n=\dim(V)$, $m=\dim(W)$, $\{\beta_1, \beta_2, \cdots, \beta_m\}$ is a basis of $W$. Since $x \notin W$, so we can have $\{\beta_1, \beta_2, \cdots, \beta_n\}$ is a basis of $V$, and $\beta_{m+1}=x$. We can have $f \in V^*$ that $f(\beta_i)=[i > m]$. So $f(\beta_i)=0 \space (i \le m)$, then $f(w)=0$ for all $w \in W$, $f \in W^0$. And $f(x)=f(\beta_{m+1})=1$.

c. If $x \in \text{span}(S)$, then for all $f \in S^0$, $\hat x(f)=f(x)=0$, since for all $y \in S$ we have $f(y)=0$ and $f$ is linear, and $x$ is a finite linear combination of $S$, so $f(x)=0$. So $\hat x \in (S^0)^0$, which means $\text{span}(\psi(S))=\psi(\text{span}(S)) \subseteq (S^0)^0$.

If $\hat x$ satisfy that for all $f \in S^0$, $f(x)=\hat x(f)=0$. Let $n=\dim(V)$, $m=\dim(\text{span}(S))$, and $\{\beta_1, \beta_2, \cdots, \beta_m\}$ be a ordered basis of $\text{span}(S)$. We can have $\{\beta_1, \beta_2, \cdots, \beta_n\}$ be a ordered basis of $V$. Consider $f_i(\beta_j)=\delta_{i, j} \space (i > m)$. Obviously $f_i(x)=0$ iff $i$th entry of $[x]_\beta$ is zero, and $f_i \in S^0$. So the $(m+1)$th to $n$th entry of $x$ should be zero if $\hat x(f_i)=0$. Then $x \in \text{span}(S)$. So $(S^0)^0 \subseteq \psi(\text{span}(S))=\text{span}(\psi(S))$.

So $(S^0)^0 = \text{span}(\psi(S))$.

d. If: We have for all $f \in V^*$, $f(x)=0 \forall x \in W_1 \Leftrightarrow f(x)=0 \forall x \in W_2$. If $W_1 \ne W_2$, let $n=\dim(V)$, $m_1=\dim(W_1)$, $m_2=\dim(W_2)$, $m=\dim(W_1 \cap W_2)<m_2$. We can have $\{\beta_1, \beta_2, \cdots, \beta_m\}$ be a basis of $W_1 \cap W_2$, then we can have $\{\beta_1, \beta_2, \cdots, \beta_{m_1+m_2-m}\}$, which satisfy $\{\beta_1, \beta_2, \cdots, \beta_{m_1}\}$ is a basis of $W_1$ and $\{\beta_1, \beta_2, \cdots, \beta_m, \beta_{m_1+1}, \beta_{m_1+2}, \cdots, \beta_{m_1+m_2-m}\}$ is a basis of $W_2$. So $\{\beta_1, \beta_2, \cdots, \beta_{m_1+m_2-m}\}$ is a basis of $W_1+W_2$, we can have $\{\beta_1, \beta_2, \cdots, \beta_n\}$ be a basis of $V$.

Consider $f_i(\beta_j)=\delta_{i, j}$. Obviously $f_i(x)=0$ iff $i$th entry of $[x]_\beta$ is zero. For $x \in W_1$, we have $f_{m_1+m_2-m}(x)=0$ since $m_1+m_2-m>m_1$, but we have $y=\beta_{m_1+m_2-m} \in W_2$ and $f_{m_1+m_2-m}(y) = 1 \ne 0$. Contradiction. So $W_1=W_2$.

Only if: Obvious.

e. If $f$ satisfy for all $x \in W_1+W_2$, $f(x)=0$. Then for all $x \in W_1 \subseteq W_1+W_2$, $f(x)=0$. So $f \in W_1^0$. Likewise, $f \in W_2^0$. So $f \in W_1^0 \cap W_2^0$, which is $(W_1+W_2)^0 \subseteq W_1^0 \cap W_2^0$.

If $f$ satisfy for all $x \in W_1$ or $x \in W_2$, $f(x)=0$. Then for all $y=y_1+y_2$, where $y_1 \in W_1$, $y_2 \in W_2$, we have $f(y)=f(y_1+y_2)=f(y_1)+f(y_2)=0$. So $f \in (W_1+W_2)^0$, which is $W_1^0 \cap W_2^0 \subseteq (W_1+W_2)^0$.

So $(W_1 + W_2)^0 = W^0_1 \cap W^0_2$.

## P126 T14

Prove that if $W$ is a subspace of $V$, then $\dim(W) + \dim(W^0) = \dim(V)$.

---

Let $m=\dim(W)$, $n=\dim(V)$. We can have $\{\beta_1, \beta_2, \cdots, \beta_m\}$ is a basis of $W$. And we can have $\{\beta_1, \beta_2, \cdots, \beta_n\}$ is a basis of $V$. Consider $\beta^*=\{f_1, f_2, \cdots, f_n\}$. We are about to prove $\{f_{m+1}, f_{m+2}, \cdots, f_n\}$ is a basis of $W^0$. This ends the proof.

Since $\beta^*$ is a basis of $V^*$, $\{f_{m+1}, f_{m+2}, \cdots, f_n\}$ is independent. For all $f \in W^0$, we have for all $i \le m$, $f(\beta_i)=0$. Let $a_{m+1}, a_{m+2}, \cdots, a_n$ satisfy $f(\beta_i)=a_i$. Then $\{a_i\}$ uniquely forms $f$, and $f=\sum_{i=m+1}^n a_if_i$. So $W^0 \subseteq \text{span}(\{f_{m+1}, f_{m+2}, \cdots, f_n\})$.

For all $a_{m+1}, a_{m+2}, \cdots, a_n$ satisfy $f=\sum_{i=m+1}^na_if_i$, since we have $f_i(\beta_j)=0 \space (i > m, j \le m)$, so for all $i > m, x \in W$, $f_i(x)=0$. So for all $x \in W$, $f(x)=(\sum_{i=m+1}^na_if_i)(x)=\sum_{i=m+1}^na_if_i(x)=0$. Then $f \in W^0$, which is $\text{span}(\{f_{m+1}, f_{m+2}, \cdots, f_n\}) \subseteq W^0$.

So $\{f_{m+1}, f_{m+2}, \cdots, f_n\}$ is independent and $\text{span}(\{f_{m+1}, f_{m+2}, \cdots, f_n\})=W^0$, then $\{f_{m+1}, f_{m+2}, \cdots, f_n\}$ is a basis of $W^0$.

## P165 T1

a. The rank of a matrix is equal to the number of its nonzero columns.

b. The product of two matrices always has rank equal to the lesser of
the ranks of the two matrices.

c. The $m \times n$ zero matrix is the only $m \times n$ matrix having rank 0.

d. Elementary row operations preserve rank.

e. Elementary column operations do not necessarily preserve rank.

f. The rank of a matrix is equal to the maximum number of linearly
independent rows in the matrix.

g. The inverse of a matrix can be computed exclusively by means of
elementary row operations.

h. The rank of an $n \times n$ matrix is at most $n$.

i. An $n \times n$ matrix having rank $n$ is invertible.

a. False. b. False. c. True. d. True. e. False. f. True. g. True. h. True. i. True.

## P165 T2

Find the rank of the following matrices.

a. $\left[\begin{matrix}1 & 1 & 0 \\ 0 & 1 & 1 \\ 1 & 1 & 0\end{matrix}\right]$.

b. $\left[\begin{matrix}1 & 1 & 0 \\ 2 & 1 & 1 \\ 1 & 1 & 1\end{matrix}\right]$.

c. $\left[\begin{matrix}1 & 0 & 2 \\ 1 & 1 & 4\end{matrix}\right]$.

---

a. Add -1 times of row 1 to row 3, we have

$$
\left[
\begin{matrix}
1 & 1 & 0
\\
0 & 1 & 1
\\
0 & 0 & 0
\end{matrix}
\right].
$$

So there is 2 pivot in the matrix, and the rank of the matrix is 2.

b. Add -2 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 1 & 0
\\
0 & -1 & 1
\\
1 & 1 & 1
\end{matrix}
\right].
$$

Add -1 times of row 1 to row 3, we have

$$
\left[
\begin{matrix}
1 & 1 & 0
\\
0 & -1 & 1
\\
0 & 0 & 1
\end{matrix}
\right].
$$

So there is 3 pivot in the matrix, and the rank of the matrix is 3.

c. Add -1 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 0 & 2
\\
0 & 1 & 2
\end{matrix}
\right].
$$

So there is 2 pivot in the matrix, and the rank of the matrix is 2.

## P166 T5

For each of the following matrices, compute the rank and the inverse if it exists.

b. $\left[\begin{matrix}1 & 2 \\ 2 & 4\end{matrix}\right]$.

e. $\left[\begin{matrix}1 & 2 & 1\\-1 & 1 & 2\\1 & 0 & 1\end{matrix}\right]$.

---

b. Add -2 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 2
\\
0 & 0
\end{matrix}
\right].
$$

So there is 1 pivot in the matrix, and the rank of the matrix is 1.

Since the matrix is $2 \times 2$, but rank is only 1, so it don't have inverse.

e. Add row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 2 & 1
\\
0 & 3 & 3
\\
1 & 0 & 1
\end{matrix}
\right].
$$

Add -1 times of row 1 to row 3, we have

$$
\left[
\begin{matrix}
1 & 2 & 1
\\
0 & 3 & 3
\\
0 & -2 & 0
\end{matrix}
\right].
$$

Multiply row 2 by $\frac{1}{3}$, we have

$$
\left[
\begin{matrix}
1 & 2 & 1
\\
0 & 1 & 1
\\
0 & -2 & 0
\end{matrix}
\right].
$$

Add 2 times of row 2 to row 3, we have

$$
\left[
\begin{matrix}
1 & 2 & 1
\\
0 & 1 & 1
\\
0 & 0 & 2
\end{matrix}
\right].
$$

Multiply row 3 by $\frac{1}{2}$, we have

$$
\left[
\begin{matrix}
1 & 2 & 1
\\
0 & 1 & 1
\\
0 & 0 & 1
\end{matrix}
\right].
$$

Add -1 times of row 3 to row 1 and row 2, we have

$$
\left[
\begin{matrix}
1 & 2 & 0
\\
0 & 1 & 0
\\
0 & 0 & 1
\end{matrix}
\right].
$$

Add -2 times of row 2 to row 1, we have

$$
\left[
\begin{matrix}
1 & 0 & 0
\\
0 & 1 & 0
\\
0 & 0 & 1
\end{matrix}
\right].
$$

So the rank of the matrix is 3, and it has inverse. Apply the same row operation to $I$, we have the inverse is

$$
\left[
\begin{matrix}
1 & 0 & 0
\\
0 & 1 & 0
\\
0 & 0 & 1
\end{matrix}
\right] \Rightarrow \left[
\begin{matrix}
1 & 0 & 0
\\
1 & 1 & 0
\\
0 & 0 & 1
\end{matrix}
\right] \Rightarrow \left[
\begin{matrix}
1 & 0 & 0
\\
1 & 1 & 0
\\
-1 & 0 & 1
\end{matrix}
\right] \Rightarrow \left[
\begin{matrix}
1 & 0 & 0
\\
\frac{1}{3} & \frac{1}{3} & 0
\\
-1 & 0 & 1
\end{matrix}
\right]
\\
\Rightarrow \left[
\begin{matrix}
1 & 0 & 0
\\
\frac{1}{3} & \frac{1}{3} & 0
\\
-\frac{1}{3} & \frac{2}{3} & 1
\end{matrix}
\right] \Rightarrow \left[
\begin{matrix}
1 & 0 & 0
\\
\frac{1}{3} & \frac{1}{3} & 0
\\
-\frac{1}{6} & \frac{1}{3} & \frac{1}{2}
\end{matrix}
\right] \Rightarrow \left[
\begin{matrix}
\frac{7}{6} & -\frac{1}{3} & -\frac{1}{2}
\\
\frac{1}{2} & 0 & -\frac{1}{2}
\\
-\frac{1}{6} & \frac{1}{3} & \frac{1}{2}
\end{matrix}
\right] \Rightarrow \left[
\begin{matrix}
\frac{1}{6} & -\frac{1}{3} & \frac{1}{2}
\\
\frac{1}{2} & 0 & -\frac{1}{2}
\\
-\frac{1}{6} & \frac{1}{3} & \frac{1}{2}
\end{matrix}
\right].
$$

So the inverse is $\left[
\begin{matrix}
\frac{1}{6} & -\frac{1}{3} & \frac{1}{2}
\\
\frac{1}{2} & 0 & -\frac{1}{2}
\\
-\frac{1}{6} & \frac{1}{3} & \frac{1}{2}
\end{matrix}
\right]$.

## P166 T6

For each of the following linear transformations $T$, determine whether $T$ is invertible, and compute $T^{-1}$ if it exists.

b. $T: P_2(R) \rightarrow P_2(R)$ defined by $T(f(x)) = (x + 1)f'(x)$.

c. $T: R^3 \rightarrow R^3$ defined by $T(a_1, a_2, a_3)=(a_1 + 2a_2 + a_3, -a_1 + a_2 + 2a_3, a_1 + a_3)$.

---

b. Let $\beta$ be standard ordered basis of $P_2(R)$. We have $[T]_\beta=\left[
\begin{matrix}
0 & 1
\\
0 & 1
\end{matrix}
\right]$. Since $\text{rank}([T]_\beta)=1 \ne \dim(P_2(R))$, so $[T]_\beta$ is not invertible, $T$ is not invertible.

c. Let $\beta$ be standard ordered basis of $R^3$. We have $[T]_\beta=\left[
\begin{matrix}
1 & 2 & 1
\\
-1 & 1 & 2
\\
1 & 0 & 1
\end{matrix}
\right]$. Since $\text{rank}([T]_\beta)=3=\dim(R^3)$, and $[T]_\beta^{-1}=\left[
\begin{matrix}
\frac{1}{6} & -\frac{1}{3} & \frac{1}{2}
\\
\frac{1}{2} & 0 & -\frac{1}{2}
\\
-\frac{1}{6} & \frac{1}{3} & \frac{1}{2}
\end{matrix}
\right]$ calculated in P166 T5 e., so $T^{-1}=L_{[T]_\beta^{-1}}$, we have $T^{-1}(a_1, a_2, a_3)=(\frac{1}{6}a_1-\frac{1}{3}a_2+\frac{1}{2}a_3, \frac{1}{2}a_1-\frac{1}{2}a_3, -\frac{1}{6}a_1+\frac{1}{3}a_2+\frac{1}{2}a_3)$.

## P168 T14

Let $T,U: V \rightarrow W$ be linear transformations.

a. Prove that $R(T+U) \subseteq R(T)+R(U)$.

b. Prove that if $W$ is finite-dimensional, then $\text{rank}(T+U) \le \text{rank}(T)+\text{rank}(U)$.

c. Deduce from (b) that $\text{rank}(A + B) \le \text{rank}(A) + \text{rank}(B)$ for any $m \times n$ matrices $A$ and $B$.

---

a. For all $x \in V$, we have $(T+U)(x) \in R(T+U)$. And we have $(T+U)(x)=T(x)+U(x) \in R(T)+R(U)$. So $R(T+U) \subseteq R(T)+R(U)$.

b. We have $\text{rank}(T+U) \le \dim(R(T)+R(U))=\dim(R(T))+\dim(R(U))-\dim(R(T) \cap R(U)) \le \text{rank}(T)+\text{rank}(U)$.

c. We have $\text{rank}(A+B)=\text{rank}(L_{A+B})=\text{rank}(L_A+L_B) \le \text{rank}(L_A)+\text{rank}(L_B)=\text{rank(A)}+\text{rank}(B)$.

## P168 T17

Prove that if B is a $3 \times 1$ matrix and C is a $1 \times 3$ matrix, then the $3 \times 3$ matrix $BC$ has rank at most 1. Conversely, show that if $A$ is any $3 \times 3$ matrix having rank 1, then there exist a $3 \times 1$ matrix $B$ and a $1 \times 3$
matrix $C$ such that $A = BC$.

---

We have $BC=\left[\begin{matrix}B_1C \\ B_2C \\ B_3C\end{matrix}\right]$, where $B_i$ denotes $i$th entry of $B$.

So $\text{rank}(BC)=\text{rank}(\left[\begin{matrix}B_1C \\ B_2C \\ B_3C\end{matrix}\right])$. If $B_1=B_2=B_3=0$, we have $\text{rank}(BC)=0 \le 1$. Otherwise we can assume $B_p \ne 0$, then $\text{rank}(BC)=\text{rank}(\left[\begin{matrix}B_pC \\ 0 \\ 0\end{matrix}\right])$. If $C_1=C_2=C_3=0$, we have $\text{rank}(BC)=0 \le 1$. Otherwise $\text{rank}(\left[\begin{matrix}B_pC \\ 0 \\ 0\end{matrix}\right])=1$. So $\text{rank}(BC) \le 1$.

Conversely, if $\text{rank}(A)=1$, then $\text{rank}(L_A)=1$, $\dim(R(L_A))=1$. Let $\{x\}$ be a basis of $R(L_A)$. Consider $A\left[\begin{matrix}1\\0\\0\end{matrix}\right]=k_1x$, so the first column of $A$ is $k_1x$. Likewise, we have the second and third column of $A$ is $k_2x$ and $k_3x$. Let $B=x$, $C=[k_1, k_2, k_3]$, then $BC=[k_1x, k_2x, k_3x]=A$.

## P168 T21

Let $A$ be an $m \times n$ matrix with rank $m$. Prove that there exists an $n \times m$ matrix $B$ such that $AB = I_m$.

---

We can find invertible matrix $Q$ that $AQ=\left[\begin{matrix}I_m & O_{m, n-m}\end{matrix}\right]$, since $\text{rank}(A)=m$ and we don't have to use row operation.

Consider $C=\left[\begin{matrix}I_m \\ O_{n-m, m}\end{matrix}\right]$. We have $AQC=\left[\begin{matrix}I_m \times I_m+O_{m, n-m} \times O_{n-m, m}\end{matrix}\right]=I_m$. Let $B=QC$, we have $AB=I_m$.

## Extra 1

Let $A=\left[\begin{matrix}
1 & 1 & 0 & 0
\\
1 & 0 & 1 & 1
\\
2 & 1 & 0 & 0
\end{matrix}\right]$, $b_1=\left[\begin{matrix}
1
\\
2
\\
3
\end{matrix}\right]$, $b_2=\left[\begin{matrix}
0
\\
1
\\
2
\end{matrix}\right]$ and $b_3=\left[\begin{matrix}
1
\\
1
\\
1
\end{matrix}\right]$. Solve the systems of linear equations $Ax=b_1$, $Ax=b_2$ and $Ax=b_3$ using LU decomposition.

---

Consider $B=\left[\begin{matrix}
1 & 0 & 0
\\
0 & 1 & 0
\\
0 & 0 & 1
\end{matrix}\right]$. Do inverse column operation on B when do row operation on A.

Add -1 times of row 1 to row 2 (inverse: Add column 2 to column 1), we have

$$
\left[
\begin{matrix}
1 & 1 & 0 & 0
\\
0 & -1 & 1 & 1
\\
2 & 1 & 0 & 0
\end{matrix}
\right], \left[
\begin{matrix}
1 & 0 & 0
\\
1 & 1 & 0
\\
0 & 0 & 1
\end{matrix}
\right].
$$

Add -2 times of row 1 to row 3 (inverse: Add 2 times of column 3 to column 1), we have

$$
\left[
\begin{matrix}
1 & 1 & 0 & 0
\\
0 & -1 & 1 & 1
\\
0 & -1 & 0 & 0
\end{matrix}
\right], \left[
\begin{matrix}
1 & 0 & 0
\\
1 & 1 & 0
\\
2 & 0 & 1
\end{matrix}
\right].
$$

Add -1 times of row 2 to row 3 (inverse: Add column 3 to column 2), we have

$$
\left[
\begin{matrix}
1 & 1 & 0 & 0
\\
0 & -1 & 1 & 1
\\
0 & 0 & -1 & -1
\end{matrix}
\right], \left[
\begin{matrix}
1 & 0 & 0
\\
1 & 1 & 0
\\
2 & 1 & 1
\end{matrix}
\right].
$$

Let $U=\left[
\begin{matrix}
1 & 1 & 0 & 0
\\
0 & -1 & 1 & 1
\\
0 & 0 & -1 & -1
\end{matrix}
\right], L=\left[
\begin{matrix}
1 & 0 & 0
\\
1 & 1 & 0
\\
2 & 1 & 1
\end{matrix}
\right]$, we have $LU=A$.

a. Solve $Ly=b_1$, we have $y_1=1$, $y_2=1$, $y_3=0$.

Solve $Ux=y$, we have $x_3$ is free, $x_4=-x_3$, $x_2=-1$, $x_1=2$.

So $\left\{\begin{aligned}
& x_1=2
\\
& x_2=-1
\\
& x_3 \text{ is free}
\\
& x_4=-x_3
\end{aligned}\right.$.

b. Solve $Ly=b_2$, we have $y_1=0$, $y_2=1$, $y_3=1$.

Solve $Ux=y$, we have $x_3$ is free, $x_4=-x_3-1$, $x_2=-2$, $x_1=2$.

So $\left\{\begin{aligned}
& x_1=2
\\
& x_2=-2
\\
& x_3 \text{ is free}
\\
& x_4=-x_3-1
\end{aligned}\right.$.

c. Solve $Ly=b_3$, we have $y_1=1$, $y_2=0$, $y_3=-1$.

Solve $Ux=y$, we have $x_3$ is free, $x_4=1$, $x_2=1$, $x_1=0$.

So $\left\{\begin{aligned}
& x_1=0
\\
& x_2=1
\\
& x_3 \text{ is free}
\\
& x_4=1
\end{aligned}\right.$.

## Extra 2

Consider the 2D graph with $m$ chains each containing $n$ nodes as discussed in the class. Besides the connections present as discussed in the class, suppose that there also exist oriented connections connecting next nearest neighboring nodes in each chain (e.g., $A_{13}=A_{31}=1$). Write down the connection matrix in a partitioned matrix form.

---

For single chain, we have $C=\left[\begin{matrix}
0 & 1 & 1 & 0 & 0 & 0 & \cdots & 0 & 0 & 0
\\
1 & 0 & 1 & 1 & 0 & 0 & \cdots & 0 & 0 & 0
\\
1 & 1 & 0 & 1 & 1 & 0 & \cdots & 0 & 0 & 0
\\
0 & 1 & 1 & 0 & 1 & 1 & \cdots & 0 & 0 & 0
\\
  &   &   & \vdots
\\
0 & 0 & 0 & 0 & 0 & 0 & \cdots & 1 & 1 & 0
\end{matrix}\right]$.

For the graph, we have $G=\left[\begin{matrix}
C & O & O & \cdots & O
\\
O & C & O & \cdots & O
\\
  &   & \vdots
\\
O & O & O & \cdots & C
\end{matrix}\right]$.

## Extra 3

Let $A,B \in M_{n \times n}(R)$. Suppose $AB=BA=0$ and $\text{rank}(A^2)=\text{rank}(A)$. Prove that $\text{rank}(A+B)=\text{rank}(A)+\text{rank}(B)$.

---

Let $T:R(L_A) \rightarrow R(L_A)$ that $T(x)=Ax$.

Lemma 1. $T$ is one-to-one.

> Proof. We have $R(T)=T(R(L_A))=L_A(R(L_A))=R(L_AL_A)=R(L_{A^2})$. And we have $R(T)=R(L_AL_A) \subseteq R(L_A)$, $\dim(R(T))=\dim(R(L_{A^2}))=\text{rank}(A^2)=\text{rank}(A)=\dim(R(L_A))$. So $R(T)=R(L_A)$. So $T$ is onto, and thus $T$ is one-to-one.

Lemma 2. $R(L_A) \cap R(L_B) = \{0\}$.

> Proof. If there exists $x$ that $Bx \in R(L_A)$ and $Bx \ne 0$. We have $T(Bx) \ne 0$, that is $ABx \ne 0$. But we know $AB=0$, contradiction.

Lemma 3. $N(L_A)+N(L_B)=R^n$.

> Proof. For all $x \in R(L_A)$, we have $Ax=0 \Leftrightarrow x=0$, so $R(L_A) \cap N(L_A) = \{0\}$. Since $\text{rank}(L_A)+\text{nullity}(L_A)=n$, we have $R(L_A) + N(L_A) = R^n$.
>
> And we know for all $x$, $BAx=0$, so for all $y \in R(L_A)$, $By=0$. Thus $R(L_A) \subseteq N(L_B)$. So $N(L_A) + N(L_B) \supseteq N(L_A) + R(L_A) = R^n$. So $N(L_A)+N(L_B)=R^n$.

Lemma 4. $R(L_{A+B})=R(L_A)+R(L_B)$.

> Proof. Obviously $R(L_{A+B}) \subseteq R(L_A)+R(L_B)$, so we only have to prove for all $x$ and $y$, we can find a $z$ that $Ax+By=(A+B)z$.
>
> Since $N(L_A)+N(L_B)=R^n$, we can find $s$ and $t$ that $s+t=x-y$, $As=Bt=0$. Let $z=x-s$, we have $x=s+z$ and $y=z-t$ by definition. So $Ax+By=A(s+z)+B(z-t)=Az+Bz+As-Bt=(A+B)z$.

Now we can prove the thm. We have $\text{rank}(A+B)=\dim(R(L_{A+B}))=\dim(R(L_A)+R(L_B))=\dim(R(L_A))+\dim(R(L_B))=\text{rank}(A)+\text{rank}(B)$.
