# Week9 Homework (Textbook)

By Deng Yufan.

## P279 T1

a. Any linear operator on an $n$-dimensional vector space that has fewer than $n$ distinct eigenvalues is not diagonalizable.

b. Two distinct eigenvectors corresponding to the same eigenvalue are always linearly dependent.

c. If $\lambda$ is an eigenvalue of a linear operator $T$, then each vector in $E_\lambda$ is an eigenvector of $T$.

d. If $\lambda_1$ and $\lambda_2$ are distinct eigenvalues of a linear operator $T$, then $E_{\lambda_1} \cap E_{\lambda_2} = \{0\}$.

e. Let $A \in M_{n \times n}(F)$ and $\beta = \{v_1, v_2,\cdots,v_n\}$ be an ordered basis for $F^n$ consisting of eigenvectors of $A$. If $Q$ is the $n \times n$ matrix whose $j$th column is $v_j \space (1 
\le j \le n)$, then $Q^{-1}AQ$ is a diagonal matrix.

f. A linear operator $T$ on a finite-dimensional vector space is diagonalizable if and only if the multiplicity of each eigenvalue $\lambda$ equals the dimension of $E_\lambda$.

g. Every diagonalizable linear operator on a nonzero vector space has
at least one eigenvalue.

h. If a vector space is the direct sum of subspaces $W_1, W_2,\cdots, W_k$, then $W_i \cap W_j = \{0\}$ for $i \ne j$.

i. If $V=\sum_{i=1}^k W_i$ and $W_i \cap W_j = \{0\} \space (i \ne j)$, then $V=W_1 \oplus W_2 \oplus \cdots \oplus W_k$.

a. False. b. False. c. False. d. True. e. True. f. True. g. True. h. True. i. True.

## P279 T2

For each of the following matrices $A \in M_{n \times n}(R)$, test $A$ for diagonalizability, and if $A$ is diagonalizable, find an invertible matrix $Q$ and a diagonal matrix $D$ such that $Q^{-1}AQ = D$.

f. $\left[\begin{matrix}1 & 1 & 0 \\ 0 & 1 & 2 \\ 0 & 0 & 3\end{matrix}\right]$.

g. $\left[\begin{matrix}3 & 1 & 1 \\ 2 & 4 & 2 \\ -1 & -1 & 1\end{matrix}\right]$.

---

f. We have $\det(A-tI)=(1-t)^2(3-t)$, so eigenvalues are 1 and 3. Solve $(A-I)x=0$, we have $x=k \left[\begin{matrix}1 \\ 0 \\ 0\end{matrix}\right]$. Solve $(A-3I)x=0$, we have $x=k \left[\begin{matrix}1 \\ 2 \\ 2\end{matrix}\right]$. Since $\dim(E_1) = 1 < 2$, $A$ is not diagonalizable.

g. We have $\det(A-tI)=(2-t)^2(4-t)$, so eigenvalues are 2 and 4. Solve $(A-2I)x=0$, we have $x=k_1\left[\begin{matrix}1 \\ 0 \\ -1\end{matrix}\right]+k_2\left[\begin{matrix}0 \\ 1 \\ -1\end{matrix}\right]$. Solve $(A-4I)x=0$, we have $x=k\left[\begin{matrix}1 \\ 2 \\ -1\end{matrix}\right]$. Since $\beta=\left\{\left[\begin{matrix}1 \\ 0 \\ -1\end{matrix}\right], \left[\begin{matrix}0 \\ 1 \\ -1\end{matrix}\right], \left[\begin{matrix}1 \\ 2 \\ -1\end{matrix}\right]\right\}$ is a basis consist only eigenvector, so $A$ is diagonalizable, and $Q=\left[\begin{matrix}1 & 0 & 1 \\ 0 & 1 & 2 \\ -1 & -1 & -1\end{matrix}\right]$, $Q^{-1}AQ=D=\left[\begin{matrix}2 & 0 & 0 \\ 0 & 2 & 0 \\ 0 & 0 & 4\end{matrix}\right]$.

## P280 T3

For each of the following linear operators $T$ on a vector space $V$, test $T$ for diagonalizability, and if $T$ is diagonalizable, find a basis $\beta$ for $V$ such that $[T]_\beta$ is a diagonal matrix.

b. $V = P_2(R)$ and $T$ is defined by $T(ax^2 + bx + c) = cx^2 + bx + a$.

c. $V = R^3$ and $T$ is defined by $T(a_1, a_2, a_3)=(a_2, -a_1, 2a_3)$.

---

b. We have $\det(T-tI)=(-1-t)(1-t)^2$, so eigenvalues are -1 and 1. Solve $(T+I)x=0$, we have $x=kx^2-k$. Solve $(T-I)x=0$, we have $x=k_1x^2+k_2x+k_1$. So $\beta=\{x^2-1, x^2+1, x\}$ is a basis consist only eigenvector, so $T$ is diagonalizable, $[T]_\beta=\left[\begin{matrix}-1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1\end{matrix}\right]$.

c. We have $\det(T-tI)=(t^2+1)(2-t)$, so $T$ is not diagonalizable.

## P280 T9

Let $T$ be a linear operator on a finite-dimensional vector space $V$, and suppose there exists an ordered basis $\beta$ for $V$ such that $[T]_\beta$ is an upper triangular matrix.

a. Prove that the characteristic polynomial for $T$ splits.

---

a. Let $n=\dim(V)$. We have $\det(T-tI)=\det([T]_\beta-tI)=\prod_{i=1}^n ({[T]_\beta}_{ii}-t)$, so the poly splits.

## P281 T10

Let $T$ be a linear operator on a finite-dimensional vector space $V$ with the distinct eigenvalues $\lambda_1, \lambda_2,\cdots,\lambda_k$ and corresponding multiplicities $m_1, m_2,\cdots,m_k$. Suppose that $\beta$ is a basis for $V$ such that $[T]_\beta$ is an upper triangular matrix. Prove that the diagonal entries of $[T]_\beta$ are $\lambda_1, \lambda_2,\cdots,\lambda_k$ and that each $\lambda_i$ occurs $m_i$ times ($1 \le i \le k$).

---

Let $n=\dim(V)$. We have $c \prod_{i=1}^k (t-\lambda_i)^{m_i}=\det(T-tI)=\prod_{i=1}^n ({[T]_\beta}_{ii}-t)$. So $\lambda_i$ occurs $m_i$ times.

## P281 T13

Let $A \in M_{n \times n}(F)$. For any eigenvalue $\lambda$ of $A$ and $A^t$, let $E_\lambda$ and $E_\lambda'$ denote the corresponding eigenspaces for $A$ and $A^t$, respectively.

a. Show by way of example that for a given common eigenvalue, these two eigenspaces need not be the same.

b. Prove that for any eigenvalue $\lambda$, $\dim(E_\lambda) = \dim(E_\lambda')$.

c. Prove that if $A$ is diagonalizable, then $A^t$ is also diagonalizable.

---

a. When $A=\left[\begin{matrix}1 & 4 \\ 1 & 1\end{matrix}\right]$, $E_3 = \left\{k\left[\begin{matrix}2 \\ 1\end{matrix}\right]\right\}$, $E_3' = \left\{k\left[\begin{matrix}1 \\ 2\end{matrix}\right]\right\}$.

b. We have $\dim(E_\lambda)=\text{nullity}(L_A-\lambda I)=n - \text{rank}(L_A- \lambda I) = n - \text{rank}(A- \lambda I) = n - \text{rank}((A- \lambda I)^t)= n - \text{rank}(A^t- \lambda I) = n - \text{rank}(L_{A^t}- \lambda I) = \text{nullity}(L_{A^t}- \lambda I) = \dim(E_\lambda')$.

c. If $A$ diagonalizable, then $\text{multiplicity}'(\lambda_i)=\text{multiplicity}(\lambda_i)=\dim(E_{\lambda_i})=\dim(E_{\lambda_i}')$, so $A^t$ diagonalizable.

## P282 T18

Two linear operators $T$ and $U$ on a finite-dimensional vector space $V$ are called simultaneously diagonalizable if there exists an ordered basis $\beta$ for $V$ such that both $[T]_\beta$ and $[U]_\beta$ are diagonal matrices. Similarly, $A, B \in M_{n \times n}(F)$ are called simultaneously diagonalizable if there exists an invertible matrix $Q \in M_{n \times n}(F)$ such that both $Q^{-1}AQ$ and $Q^{-1}BQ$ are diagonal matrices.

a. Prove that if $T$ and $U$ are simultaneously diagonalizable operators, then $T$ and $U$ commute (i.e., $TU = UT$).

---

a. For all $x \in V$, we have $[TUx]_\beta=[T]_\beta [Ux]_\beta=[T]_\beta [U]_\beta [x]_\beta$. Since $[T]_\beta$ and $[U]_\beta$ is diagonal matrix, then $[T]_\beta [U]_\beta = [U]_\beta [T]_\beta$. So $[T]_\beta [U]_\beta [x]_\beta = [U]_\beta [T]_\beta [x]_\beta = [UTx]_\beta$. So $TUx=UTx$, thus $TU=UT$.

## P283 T20

Let $W_1, W_2,\cdots, W_k$ be subspaces of a finite-dimensional vector space $V$ such that $\sum_{i=1}^k W_i = V$. Prove that $V$ is the direct sum of $W_1, W_2,\cdots, W_k$ if and only if $\dim(V)=\sum_{i=1}^k \dim(W_i)$.

---

Induction $k$ to prove $\dim(\sum_{i=1}^k W_i) \le \sum_{i=1}^k \dim(W_i)$, and equal iff for all $1 \le i < j \le k$, $W_i \cap W_j = \{0\}$.

As basis, when $k=1$ and $k=2$ it's obvious.

As induction, we assume $k-1$ and prove $k$. We have $\sum_{i=1}^k \dim(W_i) \le \dim(\sum_{i=1}^{k-1} W_i)+\dim(W_k)$, and equal iff for all $1 \le i < j < k$, $W_i \cap W_j = \{0\}$. And we have $\dim(\sum_{i=1}^{k-1} W_i)+\dim(W_k) \le \dim(\sum_{i=1}^k W_i)$, and equal iff $\sum_{i=1}^{k-1} W_i \cap W_k = \{0\}$ iff for all $1 \le i < k$, $W_i \cap W_k = \{0\}$. So $\sum_{i=1}^k \dim(W_i) \le \dim(\sum_{i=1}^k W_i)$, and equal iff for all $1 \le i < j \le k$, $W_i \cap W_j = \{0\}$.

## P283 T23

Let $W_1, W_2,K_1,K_2,\cdots,K_p, M_1, M_2,\cdots, M_q$ be subspaces of a vector space $V$ such that $W_1 = K_1 \oplus K_2 \oplus \cdots \oplus K_p$ and $W_2 = M_1 \oplus M_2 \oplus \cdots \oplus M_q$. Prove that if $W_1 \cap W_2 = \{0\}$, then $W_1 + W_2 = W_1 \oplus W_2 = K_1 \oplus K_2 \oplus \cdots \oplus K_p \oplus M_1 \oplus M_2 \oplus \cdots \oplus M_q$.

---

Obviously if $W_1 \cap W_2 = \{0\}$, $W_1+W_2=W_1 \oplus W_2 = (K_1 \oplus K_2 \oplus \cdots \oplus K_p) \oplus (M_1 \oplus M_2 \oplus \cdots \oplus M_q)$. If $A \oplus (B \oplus C) = D \Leftrightarrow (A \oplus B) \oplus C = D$, then we can apply the rule finite times to prove $(K_1 \oplus K_2 \oplus \cdots \oplus K_p) \oplus (M_1 \oplus M_2 \oplus \cdots \oplus M_q)=K_1 \oplus K_2 \oplus \cdots \oplus K_p \oplus M_1 \oplus M_2 \oplus \cdots \oplus M_q$ and complete the proof.

If $B \cap C = \{0\}$, $A \cap (B \oplus C) = \{0\}$, then $A \cap B = A \cap C = B \cap C = \{0\}$, then $(A \oplus B) \cap C = \{0\}$. So $A \oplus (B \oplus C) = A+(B+C)=(A+B)+C=(A \oplus B) \oplus C$.

And we have $(A \oplus B) \oplus C = C \oplus (B \oplus A) = (C \oplus B) \oplus A = A \oplus (B \oplus C)$. So we complete the proof.

## P323 T13

Let $T$ be a linear operator on a vector space $V$, let $v$ be a nonzero vector in $V$, and let $W$ be the $T$-cyclic subspace of $V$ generated by $v$. For any $w \in V$, prove that $w \in W$ if and only if there exists a polynomial $g(t)$ such that $w = g(T)(v)$.

---

If: For all $n \in \N$, we have $T^n(v) \in W$. So $g(T)(v) \in W$.

Only if: Let $k = \dim(W)$. For all $w \in W$, then we have $w=\sum_{i=0}^{k-1} a_iT^i(v)$, so let $g(x)=\sum_{i=0}^{k-1} a_ix^i$, then $w=g(T)(v)$.

## P324 T20

Let $T$ be a linear operator on a vector space $V$, and suppose that $V$ is a $T$-cyclic subspace of itself. Prove that if $U$ is a linear operator on $V$, then $UT = TU$ if and only if $U = g(T)$ for some polynomial $g(t)$.

---

Let $k=\dim(V)$, $V$ is generated by $v$.

If: $U=\sum_{i=0}^{m-1} a_iT^i$, then $UT = \sum_{i=0}^{m-1} a_iT^{i+1}=TU$.

Only if: Since $U(v) \in V$, then we can have $U(v)=g(T)(v)$. Then we have $U(T^n(v))=g(T)(T^n(v))=T^n(g(T)(v))=T^nU(v)$. For all $x \in V$, we can have $x=\sum_{i=0}^{k-1} a_iT^i(v)$, so $U(T(x))=U(\sum_{i=0}^{k-1} a_iT^{i+1}(v))=\sum_{i=0}^{k-1} a_iT^{i+1}(U(v))=T(U(x))$. So $UT=TU$.

## Extra

Prove the following statements.

a. If $A^2=I_n$, then $A$ is diagonalizable (here $A$ is a real square matrix).

b. If $A$ is a nonzero square matrix such that $A^k=0 \space (k>1)$, then $A$ is not diagonalizable.

c. If $A$ is a real square matrix such that $A^2+A+I_n=0$, then $A$ is not diagonalizable over $R$.

---

a. For all $x \ne 0$, $Ax=\lambda x$, we have $x=A^2 x=\lambda Ax=\lambda^2 x$, so $\lambda=\plusmn 1$. For all $x \in F^n$, let $x_1=\frac{1}{2}(x+Ax)$, $x_2=\frac{1}{2}(x-Ax)$. We have $Ax_1=\frac{1}{2}(Ax+A^2x)=x_1$, $Ax_2=\frac{1}{2}(Ax-A^2x)=-x_2$, $x_1+x_2=x$. Since $x_1 \in E_1$, $x_2 \in E_{-1}$, then $F^n=E_1+E_{-1}$. Since $E_1 \cap E_{-1} = \{0\}$, then $F^n=E_1 \oplus E_{-1}$. So $A$ is diagonalizable.

b. If $A \ne 0$ is diagonalizable, then $A=QDQ^{-1}$, where $D \ne 0$ is diagonal matrix. So $0=A^k=QD^kQ^{-1}$, $D^k=Q^{-1}0Q=0$, but $D^k \ne 0$, contradiction.

c. If $A$ is diagonalizable, then $A=QDQ^{-1}$, where $D$ is diagonal matrix. So $0=A^2+A+I=QD^2Q^{-1}+QDQ^{-1}+QQ^{-1}=Q(D^2+D+I)Q^{-1}$, then $D^2+D+I=0$, which is $D_{ii}^2+D_{ii}+1=0$ for all $i$. But $x^2+x+1=0$ have no real solution, contradiction.
