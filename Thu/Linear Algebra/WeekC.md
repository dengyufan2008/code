# WeekC Homework (Textbook)

By Deng Yufan.

## P368 T22

Find the minimal solution to each of the following systems of linear equations.

b. $\left\{\begin{aligned}&x+2y-z=1 \\ &2x+3y+z=2 \\ &4x+7y-z=4\end{aligned}\right.$.

d. $\left\{\begin{aligned}&x+y+z-w=1 \\ &2x-y+w=1\end{aligned}\right.$.

---

b. $A=\left[\begin{matrix}1 & 2 & -1 \\ 2 & 3 & 1 \\ 4 & 7 & -1\end{matrix}\right]$, $b=\left[\begin{matrix}1 \\ 2 \\ 4\end{matrix}\right]$.

$AA^*=\left[\begin{matrix}6 & 7 & 19 \\ 7 & 14 & 28 \\ 19 & 28 & 66\end{matrix}\right]$. $x_0= \left[\begin{matrix}0 \\ \frac{1}{7} \\ 0\end{matrix}\right]$ is a solution of $AA^*x=b$, so $s = A^*x_0=\left[\begin{matrix}\frac{2}{7} \\ \frac{3}{7} \\ \frac{1}{7}\end{matrix}\right]$.

d. $A=\left[\begin{matrix}1 & 1 & 1 & -1 \\ 2 & -1 & 0 & 1\end{matrix}\right]$, $b=\left[\begin{matrix}1 \\ 1\end{matrix}\right]$.

$AA^*=\left[\begin{matrix}4 & 0 \\ 0 & 6\end{matrix}\right]$. $x_0=\left[\begin{matrix}\frac{1}{4} \\ \frac{1}{6}\end{matrix}\right]$ is a solution of $AA^*x=b$, so $s=A^*x=\left[\begin{matrix}\frac{7}{12} \\ \frac{1}{12} \\ \frac{1}{4} \\ -\frac{1}{12}\end{matrix}\right]$.

## P374 T1

a. Every self-adjoint operator is normal.

b. Operators and their adjoints have the same eigenvectors.

c. If $T$ is an operator on an inner product space $V$, then $T$ is normal if and only if $[T]_\beta$ is normal, where $\beta$ is any ordered basis for $V$.

d. A real or complex matrix $A$ is normal if and only if $L_A$ is normal.

e. The eigenvalues of a self-adjoint operator must all be real.

f. The identity and zero operators are self-adjoint.

g. Every normal operator is diagonalizable.

h. Every self-adjoint operator is diagonalizable.

a. True. b. False. c. False. d. True. e. True. f. True. g. False. h. True.

## P375 T2

For each linear operator $T$ on an inner product space $V$, determine whether $T$ is normal, self-adjoint, or neither. If possible, produce an orthonormal basis of eigenvectors of $T$ for $V$ and list the corresponding eigenvalues.

a. $V = R^2$ and $T$ is defined by $T(a, b) = (2a − 2b, −2a + 5b)$.

c. $V = C^2$ and $T$ is defined by $T(a, b) = (2a + ib, a + 2b)$.

e. $V = M_{2 \times 2}(R)$ and $T$ is defined by $T(A) = A^t$.

---

a. Let $\beta$ be the standard ordered basis. $A=[T]_\beta=\left[\begin{matrix}2 & -2 \\ -2 & 5\end{matrix}\right]$. Easy to see $A=A^*$, so $T$ is self-adjoint. We have $\beta'=\{(\frac{2}{\sqrt 5},\frac{1}{\sqrt 5}),(-\frac{1}{\sqrt 5},\frac{2}{\sqrt 5})\}$, eigenvalues are 1 and 6.

c. $A=[T]_\beta=\left[\begin{matrix}2 & i \\ 1 & 2\end{matrix}\right]$. Easy to see $AA^*=A^*A=\left[\begin{matrix}5 & 2+2i \\2-2i & 5\end{matrix}\right]$, so $T$ is normal. We have $\beta'=\{(\frac{1}{\sqrt 2} i, \frac{1}{2}+\frac{1}{2}i), (-\frac{1}{\sqrt 2} i, \frac{1}{2}+\frac{1}{2}i)\}$, eigenvalues are $2+\frac{1+i}{\sqrt 2}$ and $2-\frac{1+i}{\sqrt 2}$.

e. $A=[T]_\beta=\left[\begin{matrix}1 & 0 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 0 & 1\end{matrix}\right]$. Easy to see $A=A^*$, so $T$ is self-adjoint. We have $\beta'=\left\{\left[\begin{matrix}1 & 0 \\ 0 & 0\end{matrix}\right], \left[\begin{matrix}0 & 0 \\ 0 & 1\end{matrix}\right], \left[\begin{matrix}0 & 1 \\ 1 & 0\end{matrix}\right], \left[\begin{matrix}0 & 1 \\ -1 & 0\end{matrix}\right]\right\}$, eigenvalues are 1, 1, 1, -1.

## P375 T3

Give an example of a linear operator $T$ on $R^2$ and an ordered basis for $R^2$ that provides a counterexample to the statement in T1 c.

---

Let $T(a,b)=(2a-2b,-2a+5b)$, then $T$ is normal. Consider $\beta=\{(1,0),(1,1)\}$, then $[T]_\beta=\left[\begin{matrix}4 & -3 \\ -2 & 3\end{matrix}\right]$, and $[T]_\beta$ is not normal.

## P375 T7

Let $T$ be a linear operator on an inner product space $V$, and let $W$ be a $T$-invariant subspace of $V$. Prove the following results.

a. If $T$ is self-adjoint, then $T_W$ is self-adjoint.

b. $W^\perp$ is $T^*$-invariant.

c. If $W$ is both $T$ and $T^*$-invariant, then $(T_W)^* = (T^*)_W$.

d. If $W$ is both $T$ and $T^*$-invariant and $T$ is normal, then $T_W$ is normal.

---

a. Since $\langle T(x), y \rangle = \langle x, T(y) \rangle$ for $x, y \in V$, then $\langle T(x), y \rangle = \langle x, T(y) \rangle$ for $x, y \in W$. So $T_W$ is adjoint of $T_W$.

b. For all $x \in W^\perp$, $y \in W$, we have $\langle T^*(x), y \rangle = \langle x, T(y) \rangle = 0$, so $T^*(x) \in W^\perp$.

c. We have $\langle T(x), y \rangle = \langle x, T^*(y) \rangle$ for all $x, y \in V$, so $\langle T(x), y \rangle = \langle x, T^*(y) \rangle$ for $x, y \in W$, so $(T_W)^*=(T^*)_W$.

d. We have $TT^*(x)=T^*T(x)$ for all $x \in V$, so $TT^*(x)=T^*T(x)$ for $x \in W$. Then $T_W(T_W)^*(x)=T_W(T^*)_W(x) = (T^*)_WT_W(x)=(T_W)^*T_W(x)$.

## P376 T9

Let $T$ be a normal operator on a finite-dimensional inner product space $V$. Prove that $N(T) = N(T^*)$ and $R(T) = R(T^*)$.

---

Let $\beta$ be a orthonormal basis consist only eigenvectors. Then $\overline {[T]_\beta}=[T^*]_\beta$, and $N(T)=E_0=N(T^*)$, $R(T)=\bigoplus_{\lambda \ne 0} E_\lambda=R(T^*)$.

## P376 T14

*Simultaneous Diagonalization.* Let $V$ be a finite-dimensional real inner product space, and let $U$ and $T$ be self-adjoint linear operators on $V$ such that $UT = TU$. Prove that there exists an orthonormal basis for $V$ consisting of vectors that are eigenvectors of both $U$ and $T$.

---

Let $\lambda$ be a eigenvalue of $T$. For all $x \in E_\lambda$, we have $T(U(x))=U(T(x))=U(\lambda x)=\lambda U(x)$, so $U(x) \in E_\lambda$. So $E_\lambda$ is $T$ and $U$-invariant.

Since $U$ is self-adjoint, we can have orthonormal basis $\beta_\lambda$ of $E_\lambda$ that $[U_{E_\lambda}]_{\beta_\lambda}$ is diagonal. Obviously $[T_{E_\lambda}]_{\beta_\lambda}$ is diagonal.

Let $\beta=\bigcup_{\lambda} \beta_\lambda$, since $T$ is self-adjoint, then $\beta$ is orthonormal. And $[T]_\beta$ and $[U]_\beta$ is diagonal.

## P377 T17

A linear operator $T$ on a finite-dimensional inner productspace is called positive definite [positive semidefinite] if $T$ is self-adjoint and $\langle T(x), x \rangle > 0 [\langle T(x), x \rangle \ge 0]$ for all $x \ne 0$.

An $n \times n$ matrix $A$ with entries from $R$ or $C$ is called positive definite [positive semidefinite] if $L_A$ is positive definite [positive semidefinite].

Let $T$ and $U$ be a self-adjoint linear operators on an $n$-dimensional inner product space $V$, and let $A = [T]_\beta$, where $\beta$ is an orthonormal basis for $V$. Prove the following results.

a. T is positive definite [semidefinite] if and only if all of its eigenvalues are positive [nonnegative].

b. T is positive definite if and only if $\sum_{i,j} A_{ij}a_j \overline{a_i} > 0$ for all nonzero $n$-tuples $(a_1, a_2, \cdots, a_n)$.

c. $T$ is positive semidefinite if and only if $A = B^*B$ for some square matrix $B$.

---

a. Let $\beta$ be a orthonormal basis consist only eigenvectors.

If: Then $\langle T(\beta_i), \beta_i \rangle > 0 [\ge 0]$. So $\langle T(x), x \rangle = \sum_{i=1}^n \langle x, \beta_i \rangle \overline{\langle x, \beta_i \rangle} \langle T(\beta_i), \beta_i \rangle > 0 [\ge 0]$.

Only if: $\langle T(\beta_i), \beta_i \rangle = \lambda \langle \beta_i, \beta_i \rangle > 0 [\ge 0]$, so $\lambda > 0 [\ge 0]$.

b. Let $a$ be column vector corresponding to $n$-tuple. Then $\langle T(x), x \rangle = \sum_{i, j} \langle x, \beta_j \rangle \overline{\langle x, \beta_i \rangle} \langle T(\beta_j), \beta_i \rangle = \sum_{i, j} a_j \overline{a_i} A_{ij} = \langle Aa, a \rangle$, where $x=\sum_{i=1}^n a_i \beta_i$. So easy to see $T$ positive definite iff $A$ positive definite.

c. If: $\langle T(x), x \rangle = \langle Aa, a \rangle = \langle B^*Ba, a \rangle = \langle Ba,Ba \rangle \ge 0$.

Only if: $A$ is positive semidefinite. So $Q^*AQ=D$, where $Q^{-1}=Q^*$, $D$ diagonal, $D_{ij} \ge 0$. So let $D'_{ij} = \sqrt{D_{ij}}$, We have $Q^*AQ=D'D'^*$, $A=QD'D'^*Q^*=(QD')(QD')^*$.

## P379 T24

Let $T$ be a linear operator on a finite dimensional inner product space $V$.

a. Suppose that $\beta$ is an ordered basis for $V$ such that $[T]_\beta$ is an upper triangular matrix. Let $\gamma$ be the orthonormal basis for $V$ obtained by applying the Gram–Schmidt orthogonalization process to $\beta$ and then normalizing the resulting vectors. Prove that $[T]_\gamma$ is an upper triangular matrix.

b. Use Exercise 32 of Section 5.4 and (a) to obtain an alternate proof of Schur's theorem.

---

a. Let $W_i = \text{span} \{\beta_1, \beta_2, \cdots, \beta_i\}$. Since $[T]_\beta$ is upper triangle, $W_i$ is $T$-invariant. Easy to see $W_i = \text{span} \{\gamma_1, \gamma_2, \cdots, \gamma_i\}$ by definition, so $[T]_\gamma$ is upper triangle.

b. If $\det(T-tI)$ splits, then we can have $[T]_\beta$ is upper triangle, then $[T]_\gamma$ is upper triangle.

## P392 T1

a. Every unitary operator is normal.

b. Every orthogonal operator is diagonalizable.

c. A matrix is unitary if and only if it is invertible.

d. If two matrices are unitarily equivalent, then they are also similar.

e. The sum of unitary matrices is unitary.

f. The adjoint of a unitary operator is unitary.

g. If $T$ is an orthogonal operator on $V$, then $[T]_\beta$ is an orthogonal matrix for any ordered basis $\beta$ for $V$.

h. If all the eigenvalues of a linear operator are 1, then the operator must be unitary or orthogonal.

i. A linear operator may preserve the norm, but not the inner product.

a. True. b. False. c. False. d. True. e. False. f. True. g. False. h. False. i. False.

## P392 T2

For each of the following matrices $A$, find an orthogonal or unitary matrix $P$ and a diagonal matrix $D$ such that $P^*AP = D$.

e. $\left[\begin{matrix}2 & 1 & 1 \\ 1 & 2 & 1 \\ 1 & 1 & 2\end{matrix}\right]$.

---

e. $\det(A-tI)=(1-t)^2(4-t)$. We have 1 correspond to $k_1\left[\begin{matrix}1 \\ 0 \\ -1\end{matrix}\right]+k_2\left[\begin{matrix}0 \\ 1 \\ -1\end{matrix}\right]$, 4 correspond to $k\left[\begin{matrix}1 \\ 1 \\ 1\end{matrix}\right]$. So we can have $\beta=\left\{\left[\begin{matrix}\frac{1}{\sqrt 6} \\ \frac{1}{\sqrt 6} \\ -\frac{2}{\sqrt 6}\end{matrix}\right], \left[\begin{matrix}\frac{1}{\sqrt 2} \\ -\frac{1}{\sqrt 2} \\ 0\end{matrix}\right], \left[\begin{matrix}\frac{1}{\sqrt 3} \\ \frac{1}{\sqrt 3} \\ \frac{1}{\sqrt 3}\end{matrix}\right]\right\}$.

Let $P$ change $\beta$-coor into $\gamma$-coor, where $\gamma$ is standard ordered basis. We have $P=\left[\begin{matrix}\frac{1}{\sqrt 6} & \frac{1}{\sqrt 2} & \frac{1}{\sqrt 3} \\ \frac{1}{\sqrt 6} & -\frac{1}{\sqrt 2} & \frac{1}{\sqrt 3} \\ -\frac{2}{\sqrt 6} & 0 & \frac{1}{\sqrt 3}\end{matrix}\right]$, $D=\left[\begin{matrix}1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 4\end{matrix}\right]$. Easy to see $P^*AP=D$.

## P393 T5

Which of the following pairs of matrices are unitarily equivalent?

d. $\left[\begin{matrix}0 & 1 & 0 \\ -1 & 0 & 0 \\ 0 & 0 & 1\end{matrix}\right]$ and $\left[\begin{matrix}1 & 0 & 0 \\ 0 & i & 0 \\ 0 & 0 & -i\end{matrix}\right]$.

e. $\left[\begin{matrix}1 & 1 & 0 \\ 0 & 2 & 2 \\ 0 & 0 & 3\end{matrix}\right]$ and $\left[\begin{matrix}1 & 0 & 0 \\ 0 & 2 & 0 \\ 0 & 0 & 3\end{matrix}\right]$.

---

d. Lhs is normal. And eigenvalues are $1$, $i$, $-i$, so they are unitarily equivalent.

e. Lsh is upper triangle but not diagonal, so it is not normal, then they are not unitarily equivalent.

## P393 T7

Prove that if $T$ is a unitary operator on a finite-dimensional inner product space $V$, then $T$ has a unitary square root; that is, there exists a unitary operator $U$ such that $T = U^2$.

---

We can have $[T]_\beta$ is diagonal and the norm of eigenvalues are 1, where $\beta$ is orthonormal basis. Let $[U]_\beta = \sqrt {[T]_\beta}$, then $[U]_\beta$ is diagonal and the norm of eigenvalues are 1.

## P394 T14

Prove that if $A$ and $B$ are unitarily equivalent matrices, then $A$ is positive definite [semidefinite] if and only if $B$ is positive definite [semidefinite].

---

We have $B=P^*AP$, where $P$ is unitary.

If $A$ is positive definite [semidefinite], then $A=A^*$, and $B^*=P^*A^*P=P^*AP=B$. We have $\langle Ax, x \rangle > 0 [\ge 0]$, then $\langle Bx, x \rangle = \langle P^*APx, x \rangle = \langle APx, Px \rangle > 0 [\ge 0]$. So $B$ is positive definite [semidefinite].

## P394 T15

Let $U$ be a unitary operator on an inner product space $V$, and let $W$ be a finite-dimensional $U$-invariant subspace of $V$. Prove that

a. $U(W)=W$.

b. $W^\perp$ is $U$-invariant.

---

a. Since $U$ is unitary, then $U^{-1}=U^*$, so $U$ is one-to-one. Then $U_W$ is one-to-one, so $U_W$ is onto, thus $U(W)=W$.

b. For all $x$ that for all $y \in W$, $\langle x, y \rangle = 0$. We have for all $y \in W$, $\langle U(x), y \rangle = \langle x, U^{-1}(y) \rangle$. Since $U(W)=W$, then $U^{-1}(y) \in W$. Then $\langle U(x), y \rangle = 0$. So $U(x) \in W^\perp$.

## P394 T16

Find an example of a unitary operator $U$ on an inner product space and a $U$-invariant subspace $W$ such that $W^\perp$ is not $U$-invariant.

---

In $H$, $U(f)=e^{it}f$, $W=\text{span}\{e^{0it}, e^{1it}, e^{2it}, \cdots\}$.

Then $W^\perp=\text{span}\{e^{-1it}, e^{-2it}, \cdots\}$, but $U(e^{-it})=e^0 \notin W^\perp$.

## Extra

Let $V$ be an inner product space over $R$ and let $T:V \rightarrow V$ be a function (not assumed to be linear) such that $T(0)=0$ and $\lVert T(v)-T(w) \rVert = \lVert v-w \rVert$ for all $v, w \in V$. Let $\dim(V)=n$.

a. Show that $\lVert T(v) \rVert = \lVert v \rVert$ for all $v \in V$.

b. Show that $\langle T(v), T(w) \rangle = \langle v, w \rangle$ for all $v, w \in V$.

c. If $\{e_1, e_2, \cdots, e_n\}$ is an orthonormal basis for $V$, show that $\{T(e_1), T(e_2), \cdots, T(e_n)\}$ is an orthonormal basis, too.

d. Show that $T$ is linear.

---

a. We have $\lVert T(v)-T(0) \rVert = \lVert v-0 \rVert$.

b. We have $\langle T(v)-T(w), T(v)-T(w) \rangle = \langle v-w, v-w \rangle$, that is $\langle T(v), T(v) \rangle + \langle T(w), T(w) \rangle - 2\langle T(v), T(w) \rangle = \langle v, v \rangle + \langle w, w \rangle - 2\langle v, w \rangle$, that is $\langle T(v), T(w) \rangle = \langle v, w \rangle$.

c. We have $\langle T(e_i), T(e_j) \rangle = \langle e_i, e_j \rangle = \delta_{ij}$.

d. We have $\langle T(cv+w), T(e_i) \rangle = \langle cv+w, e_i \rangle = c\langle v, e_i \rangle + \langle w, e_i \rangle = c\langle T(v), T(e_i) \rangle + \langle T(w), T(e_i) \rangle = \langle cT(v)+T(w), T(e_i) \rangle$. Since $\{T(e_i)\}$ is orthonormal basis, we have $T(cv+w)=cT(v)+T(w)$.
