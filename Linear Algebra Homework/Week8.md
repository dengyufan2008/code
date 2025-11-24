# Week8 Homework (Textbook)

By Deng Yufan.

## P236 T1

a. The determinant of a square matrix may be computed by expanding the matrix along any row or column.

b. In evaluating the determinant of a matrix, it is wise to expand along a row or column containing the largest number of zero entries.

c. If two rows or columns of $A$ are identical, then $\det(A) = 0$.

d. If $B$ is a matrix obtained by interchanging two rows or two columns of $A$, then $\det(B) = \det(A)$.

e. If $B$ is a matrix obtained by multiplying each entry of some row or column of $A$ by a scalar, then $\det(B) = \det(A)$.

f. If $B$ is a matrix obtained from $A$ by adding a multiple of some row to a different row, then $\det(B) = \det(A)$.

g. The determinant of an upper triangular $n \times n$ matrix is the product of its diagonal entries.

h. For every $A \in M_{n \times n}(F)$, $\det(A^t) = -\det(A)$.

i. If $A, B \in M_{n \times n}(F)$, then $\det(AB) = \det(A) \cdot \det(B)$.

j. If $Q$ is an invertible matrix, then $\det(Q^{-1}) = [\det(Q)]^{-1}$.

k. A matrix $Q$ is invertible if and only if $\det(Q) \ne 0$.

a. True. b. True. c. True. d. False. e. False. f. True. g. True. h. False. i. True. j. True. k. True.

## P256 T1

a. Every linear operator on an $n$-dimensional vector space has $n$ distinct eigenvalues.

b. If a real matrix has one eigenvector, then it has an infinite number of eigenvectors.

c. There exists a square matrix with no eigenvectors.

d. Eigenvalues must be nonzero scalars.

e. Any two eigenvectors are linearly independent.

f. The sum of two eigenvalues of a linear operator $T$ is also an eigenvalue of $T$.

g. Linear operators on infinite-dimensional vector spaces never have
eigenvalues.

h. An $n \times n$ matrix $A$ with entries from a field $F$ is similar to a diagonal matrix if and only if there is a basis for $F^n$ consisting of eigenvectors of $A$.

i. Similar matrices always have the same eigenvalues.

j. Similar matrices always have the same eigenvectors.

k. The sum of two eigenvectors of an operator $T$ is always an eigenvector of $T$.

a. False. b. True. c. True. d. False. e. False. f. False. g. False. h. True. i. True. j. False. k. False.

## P256 T2

For each of the following linear operators $T$ on a vector space $V$ and ordered bases $\beta$, compute $[T]_\beta$, and determine whether $\beta$ is a basis consisting of eigenvectors of $T$.

b. $V=P_1(R)$, $T(a+bx)=(6a-6b)+(12a-11b)x$, and $\beta=\{3+4x, 2+3x\}$.

c. $V=R^3$, $T\left[\begin{matrix}a \\ b \\ c\end{matrix}\right] = \left[\begin{matrix}3a+2b-2c \\ -4a-3b+2c \\ -c\end{matrix}\right]$, and $\beta=\left\{\left[\begin{matrix}0 \\ 1 \\ 1\end{matrix}\right], \left[\begin{matrix}1 \\ -1 \\ 0\end{matrix}\right], \left[\begin{matrix}1 \\ 0 \\ 2\end{matrix}\right]\right\}$.

---

b. $T(\beta_1)=-6-8x=-2\beta_1$, $T(\beta_2)=-6-9x=-3\beta_2$. So $[T]_\beta = \left[\begin{matrix}-2 & 0 \\ 0 & -3\end{matrix}\right]$. Since $[T]_\beta$ is a diagonal matrix, so $\beta$ consists only eigenvectors.

c. $T(\beta_1)=\left[\begin{matrix}0 \\ -1 \\ -1\end{matrix}\right]=-\beta_1$, $T(\beta_2)=\left[\begin{matrix}1 \\ -1 \\ 0\end{matrix}\right]=\beta_2$, $T(\beta_3)=\left[\begin{matrix}-1 \\ 0 \\ -2\end{matrix}\right]=-\beta_3$. So $[T]_\beta=\left[\begin{matrix}-1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & -1\end{matrix}\right]$. Since $[T]_\beta$ is a diagonal matrix, so $\beta$ consists only eigenvectors.

## P257 T3

For each of the following matrices $A \in M_{n \times n}(F)$,

- Determine all the eigenvalues of $A$.

- For each eigenvalue $\lambda$ of $A$, find the set of eigenvectors corresponding to $\lambda$.

- If possible, find a basis for $F^n$ consisting of eigenvectors of $A$.

- If successful in finding such a basis, determine an invertible matrix $Q$ and a diagonal matrix $D$ such that $Q^{-1}AQ = D$.

b. $A=\left[\begin{matrix}0 & -2 & -3 \\ -1 & 1 & -1 \\ 2 & 2 & 5\end{matrix}\right]$ for $F=R$.

c. $A=\left[\begin{matrix}i & 1 \\ 2 & -i\end{matrix}\right]$ for $F=C$.

---

b. We have $\det(A-tI)=-(t-1)(t-2)(t-3)$. So eigenvalues are $1, 2, 3$.

Solve $(A-\lambda I)x=0$ for each eigenvalue, we have $1$ correspond to $k\left[\begin{matrix}1 \\ 1 \\ -1\end{matrix}\right]$, $2$ correspond to $k\left[\begin{matrix}1 \\ -1 \\ 0\end{matrix}\right]$, $3$ correspond to $k\left[\begin{matrix}1 \\ 0 \\ -1\end{matrix}\right]$.

Obviously $\beta=\left\{\left[\begin{matrix}1 \\ 1 \\ -1\end{matrix}\right], \left[\begin{matrix}1 \\ -1 \\ 0\end{matrix}\right], \left[\begin{matrix}1 \\ 0 \\ -1\end{matrix}\right]\right\}$ is a basis of $F^3$, and it consist only eigenvectors.

Let $Q$ changes $\beta'$-coor into $\beta$-coor, where $\beta'$ is the standard ordered basis of $R^3$, then $Q=\left[\begin{matrix}1 & 1 & 1 \\ 1 & 0 & 1 \\ -1 & -1 & -2\end{matrix}\right]$ and is invertible. We can find that $Q^{-1}AQ=D=\left[\begin{matrix}1 & 0 & 0 \\ 0 & 2 & 0 \\ 0 & 0 & 3\end{matrix}\right]$.

c. We have $\det(A-tI)=(t+1)(t-1)$. So eigenvalues are $-1, 1$.

Solve $(A-\lambda I)x=0$ for each eigenvalue, we have $-1$ correspond to $k\left[\begin{matrix}-1+i \\ 2\end{matrix}\right]$, $1$ correspond to $k\left[\begin{matrix}1+i \\ 2\end{matrix}\right]$.

Obviously $\beta=\left\{\left[\begin{matrix}-1+i \\ 2\end{matrix}\right], \left[\begin{matrix}1+i \\ 2\end{matrix}\right]\right\}$ is a basis of $C^2$, and it consist only eigenvectors.

Let $Q$ changes $\beta'$-coor into $\beta$-coor, where $\beta'$ is the standard ordered basis of $C^2$, then $Q=\left[\begin{matrix}-\frac{1}{2} & \frac{1}{2} \\ \frac{1+i}{4} & \frac{1-i}{4}\end{matrix}\right]$ and is invertible. We can find that $Q^{-1}AQ=D=\left[\begin{matrix}-1 & 0\\ 0 & 1\end{matrix}\right]$.

## P257 T4

For each linear operator $T$ on $V$, find the eigenvalues of $T$ and an ordered basis $\beta$ for $V$ such that $[T]_\beta$ is a diagonal matrix.

g. $V = P_3(R)$ and $T(f(x)) = xf'(x) + f''(x) − f(2)$.

---

g. We have $\det(T-tI)=(t+1)(t-1)(t-2)(t-3)$. So eigenvalues are $-1, 1, 2, 3$.

Solve $(T-\lambda I)x=0$ for each eigenvalue, we have $-1$ correspond to $k(1)$, $1$ correspond to $k(1-x)$, $2$ correspond to $k(2-3x^2)$, $3$ correspond to $k(7-6x-2x^3)$. So we have $\beta=\{1, 1-x, 2-3x^2, 7-6x-2x^3\}$ is a basis of $P_3(R)$ and consist only eigenvectors.

Obviously $[T]_\beta=\left[\begin{matrix}-1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 2 & 0 \\ 0 & 0 & 0 & 3\end{matrix}\right]$.

## P258 T8

a. Prove that a linear operator $T$ on a finite-dimensional vector space is invertible if and only if zero is not an eigenvalue of $T$.

b. Let $T$ be an invertible linear operator. Prove that a scalar $\lambda$ is an eigenvalue of $T$ if and only if $\lambda^{-1}$ is an eigenvalue of $T^{-1}$.

---

a. Let $T:V \rightarrow V$ and $n=\dim(V)$. We have zero is not an eigenvalue of $T$ iff $Tx=0$ only have zero solution iff $\text{nullity}(T)=0$ iff $\text{rank}(T)=n$ iff $T$ is invertible.

b. Since $T$ is invertible, then $\lambda \ne 0$, $\det(T) \ne 0$, thus $\det(-\lambda^{-1}T^{-1}) \ne 0$. So $\lambda$ is an eigenvalue of $T$ iff $\det(T-\lambda I)=0$ iff $\det(T-\lambda I) \det (-\lambda^{-1} T^{-1})=0$ iff $\det(T^{-1}-\lambda^{-1}I)=0$ iff $\lambda^{-1}$ is an eigenvalue of $T^{-1}$.

## P259 T14

For any square matrix $A$, prove that $A$ and $A^t$ have the same characteristic polynomial (and hence the same eigenvalues).

---

We have $\det(A-tI)=\det((A-tI)^t)=\det(A^t-(tI)^t)=\det(A^t-tI)$.

## P259 T17

Let $T$ be the linear operator on $M_{n \times n}(R)$ defined by $T(A) = A^t$.

a. Show that $\plusmn 1$ are the only eigenvalues of $T$.

b. Describe the eigenvectors corresponding to each eigenvalue of $T$.

c. Find an ordered basis $\beta$ for $M_{2 \times 2}(R)$ such that $[T]_\beta$ is a diagonal matrix.

d. Find an ordered basis $\beta$ for $M_{n \times n}(R)$ such that $[T]_\beta$ is a diagonal matrix for $n > 2$.

---

a. If $A \ne 0, TA=\lambda A$, then $(T-\lambda I)A=0$. Let $U=T-\lambda I$, $U(A)_{ij}=A_{ij}-\lambda A_{ji}$. So if $U(A)=0$, then $A_{ij}=\lambda A_{ji}=\lambda^2 A_{ij}$, which is $A=\lambda^2 A$. Then $\lambda=\plusmn 1$.

b. Solve $(T+I)A=0$, we have $-1$ correspond to $A$ satisfy $A_{ij}=-A_{ji}$ and $A_{ii}=0$. Solve $(T-I)A=0$, we have $1$ correspond to $A$ satisfy $A_{ij}=A_{ji}$.

c. Let $\beta=\left\{\left[\begin{matrix}0 & 1 \\ -1 & 0\end{matrix}\right], \left[\begin{matrix}1 & 0 \\ 0 & 0\end{matrix}\right], \left[\begin{matrix}0 & 0 \\ 0 & 1\end{matrix}\right], \left[\begin{matrix}0 & 1 \\ 1 & 0\end{matrix}\right]\right\}$ is a basis for $M_{2 \times 2}(R)$, then $[T]_\beta$ is a diagonal matrix.

d. Let $\beta=\{\{P^{ij} \space (i < j)\}, \{Q^{ij} \space (i < j)\}, \{R^i\}\}$, where $P^{ij} \space (i < j)$ is a $n \times n$ matrix satisfy $P^{ij}_{ij}=P^{ij}_{ji}=1$, other entry is 0; $Q^{ij} \space (i < j)$ is a $n \times n$ matrix satisfy $Q^{ij}_{ij}=1$, $Q^{ij}_{ji}=-1$, other entry is 0; $R^i$ is a $n \times n$ matrix satisfy $R^{i}_{ii}=1$, other entry is 0.

## P260 T22

a. Let $T$ be a linear operator on a vector space $V$ over the field $F$, and let $g(t)$ be a polynomial with coefficients from $F$. Prove that if $x$ is an eigenvector of $T$ with corresponding eigenvalue $\lambda$, then $g(T)(x) = g(\lambda)x$. That is, $x$ is an eigenvector of $g(T)$ with corresponding eigenvalue $g(\lambda)$.

---

We first prove if $Tx=\lambda x$, then $T^nx=\lambda^n x$ using induction $n$. As basis, when $n=0$ it is just $x=x$. As induction, we assume $n$ and prove $n+1$. We have $T^{n+1}x=T(T^n x)=T(\lambda^n x)=\lambda^n T(x)=\lambda^{n+1}x$.

For $g(t)=\sum_{i=0}^n a_it^i$, $g(T)(x)=\sum_{i=0}^n a_iT^i(x)=\sum_{i=0}^n a_i \lambda^i x = (\sum_{i=0}^n a_i \lambda^i) x = g(\lambda)x$.

## Extra 1

Let $A=\left[\begin{matrix}I_r & B \\ 0 & -I_{n-r}\end{matrix}\right]$ be an $n \times n$ matrix. Prove that $A$ is diagonalizable.

---

We have $\det(A-tI)=(1-t)^r(-1-t)^{n-r}$, so eigenvalues are $-1, 1$.

Solve $(A+I)x=0$, we have $x_{r+1}, x_{r+2}, \cdots, x_n$ are free and $x_i=\sum_{j=r+1}^{n} -A_{ij}x_j \space (i \le r)$. So $\dim(E_{-1})=n-r$.

Likewise, solve $(A-I)x=0$, we have $x_1, x_2, \cdots, x_r$ are free and $x_i=0 \space (i>r)$. So $\dim(E_1)=r$.

Obviously for $-1$ and $1$ we have $\dim(E_\lambda)+\text{multiplicity}=n$. So $A$ is diagonalizable.

## Extra 2

Let $\alpha=\left[\begin{matrix}a_1 \\ a_2 \\ \vdots \\ a_n\end{matrix}\right]$ and $\beta=\left[\begin{matrix}b_1 \\ b_2 \\ \vdots \\ b_n\end{matrix}\right]$ be nonzero column vectors satisfying $\alpha^t \beta=0$. Let $A=\alpha \beta^t$. Determine $A^2$ and eigenvalues and eigenvectors of $A$.

---

We have $(A^2)^t=(\alpha \beta^t \alpha \beta^t)^t = \beta (\alpha^t \beta) \alpha^t=0$. So $A^2=0$.

For all $x \ne 0$, $Ax=\lambda x$, we have $\lambda Ax=A^2x=0$. If $\lambda \ne 0$, then $\lambda x=Ax=0$, thus $x=0$, contradiction. So $\lambda=0$, or say eigenvalues only consist 0.

We have $Ax=0$ iff for all $i$, $\sum_{j=1}^n a_ib_j x_j=0$, which is $a_i = 0$ or $\sum_{j=1}^n b_jx_j=0$. Since $\alpha \ne 0$, then $Ax=0$ iff $\sum_{j=1}^n b_jx_j=0$.

Since $\beta \ne 0$, let $p$ satisfy $b_i = 0 \space (i<p)$ and $b_p \ne 0$. Then we solve $Ax=0$, we have $x_i \space (i \ne p)$ is free, $x_p=\sum_{i=p+1}^n -\frac{b_i}{b_p}x_i$.

As conclusion, $A^2=0$, eigenvalues are only 0, eigenvectors are $x$ satisfy $x_p=\sum_{i=p+1}^n -\frac{b_i}{b_p}x_i$ and $x \ne 0$.
