# WeekD Homework (Textbook)

By Deng Yufan.

## P403 T1

a. All projections are self-adjoint.

b. An orthogonal projection is uniquely determined by its range.

c. Every self-adjoint operator is a linear combination of orthogonal projections.

d. If $T$ is a projection on $W$, then $T(x)$ is the vector in $W$ that is closest to $x$.

e. Every orthogonal projection is a unitary operator.

a. False. b. True. c. True. d. False. e. False.

## P404 T6

Let $T$ be a normal operator on a finite-dimensional inner product space. Prove that if $T$ is a projection, then $T$ is also an orthogonal projection.

---

For all $x \in R(T)^\perp$ and $y \in V$, we can have $y=y_1+y_2$, where $y_1 \in R(T)$, $y_2 \in R(T)^\perp$.

Then we have $\langle T(x), y \rangle = \langle T(x), y_1+y_2 \rangle = \langle T(x), y_1 \rangle$ since $\langle T(x), y_2 \rangle = 0$.

Since $T$ is a projection, then $T(y_1)=y_1$, we have $\langle T(x), y \rangle = \langle T(x), T(y_1) \rangle = \langle x, T^*T(y_1) \rangle$. Since $T$ is normal, we have $\langle T(x), y \rangle = \langle x, TT^*(y_1) \rangle = 0$.

So $T(x)=0$, thus $R(T)^\perp \subseteq N(T)$. Since $\dim(R(T))+\dim(N(T))=\dim(V)=\dim(R(T))+\dim(R(T)^\perp)$, then $R(T)^\perp=N(T)$, thus $R(T)={R(T)^\perp}^\perp = N(T)^\perp$. So $T$ is orthogonal projection.

## P404 T7

Let $T$ be a normal operator on a finite-dimensional complex inner product space $V$. Use the spectral decomposition $\lambda_1T_1 + \lambda_2T_2 + \cdots + \lambda_kT_k$ of $T$ to prove the following results.

a. If $g$ is a polynomial, then $g(T)=\sum_{i=1}^k g(\lambda_i)T_i$.

b. If $T^n = T_0$ for some $n$, then $T = T_0$.

c. Let $U$ be a linear operator on $V$. Then $U$ commutes with $T$ if and only if $U$ commutes with each $T_i$.

d. There exists a normal operator $U$ on $V$ such that $U^2 = T$.

e. $T$ is invertible if and only if $\lambda_i \ne 0$ for $1 \le i \le k$.

f. $T$ is a projection if and only if every eigenvalue of $T$ is 1 or 0.

g. $T = -T^*$ if and only if every $\lambda_i$ is an imaginary number.

---

a. If $g(x)=\sum_{i=0}^n a_ix^i$, then $g(T)=\sum_{i=0}^n a_i (\sum_{j=1}^k \lambda_j T_j)^i=\sum_{i=0}^n a_i \sum_{j=1}^k \lambda_j^i T_j = \sum_{j=1}^k T_j \sum_{i=0}^n a_i \lambda_j^i = \sum_{j=1}^k g(\lambda_j) T_j$, since $T_iT_j = 0$ for $i \ne j$, and $T_i^j = T_i$ for $j \ge 1$.

b. We have $\sum_{i=1}^k \lambda_i^n T_i(x) = 0$. Then $0=T_j(\sum_{i=1}^k \lambda_i^n T_i(x)) = \lambda_j^n T_j(x)$. So $T_i=0$ for all $\lambda_i \ne 0$. Then $T=0$.

c. If: $UT=U(\sum_{i=1}^k \lambda_i T_i)=(\sum_{i=1}^k \lambda_i T_i)U=TU$.

Only if: We have $\lambda_jT_iUT_j=T_iU(\sum_{p=1}^k \lambda_p T_p)T_j=T_iUTT_j=T_iTUT_j=T_i(\sum_{p=1}^k \lambda_p T_p)UT_j=\lambda_i T_iUT_j$. So if $i \ne j$, then $T_iUT_j=0$. Thus $T_iU=T_iUT_i$, $UT_j=T_jUT_j$. So $T_iU=UT_i$.

d. Let $U=\sum_{i=1}^k \sqrt \lambda_i T_i$, then $U^2=\sum_{i=1}^k \sqrt \lambda_i T_i \sum_{j=1}^k \sqrt \lambda_j T_j = \sum_{i=1}^k \lambda_i T_i = T$. We have $U^*=\sum_{i=1}^k \overline{\sqrt \lambda_i} T_i^*=\sum_{i=1}^k \overline{\sqrt \lambda_i} T_i$. Easy to see $UU^*=\sum_{i=1}^k |\lambda_i| T_i=U^*U$.

e. Let $\beta$ be orthonormal basis consist only eigenvectors. Then $[T]_\beta$ is diagonal, so $\text{rank}([T]_\beta)=\sum_{i=1}^n [{[T]_\beta}_{ii} \ne 0]$. So $T$ invertible iff $\text{rank}(T)=n$ iff ${[T]_\beta}_{ii} \ne 0$.

f. $T$ is projection iff $T^2=T$. That is $\sum_{i=1}^k \lambda_i^2 T_i = (\sum_{i=1}^k \lambda_i T_i)^2 = T^2 = T = \sum_{i=1}^k \lambda_i T_i$. Which iff $\lambda_i^2=\lambda_i$ (like b., apply $T_j$ to both side to prove only if), that is $\lambda_i \in \{0, 1\}$.

g. We have $\sum_{i=1}^k \lambda_i T_i=T=-T^*=\sum_{i=1}^k -\overline{\lambda_i} T_i^* = \sum_{i=1}^k -\overline{\lambda_i} T_i$, then $\lambda_i = -\overline{\lambda_i}$, $\lambda_i$ is imaginary.

## P405 T10

*Simultaneous diagonalization.* Let $U$ and $T$ be normal operators on a finite-dimensional complex inner product space $V$ such that $TU = UT$. Prove that there exists an orthonormal basis for $V$ consisting of vectors that are eigenvectors of both $T$ and $U$.

---

Let $\lambda$ be a eigenvalue of $T$. For all $x \in E_\lambda$, $TU(x)=UT(x)=\lambda U(x)$, then $E_\lambda$ is $T$ and $U$-invariant.

Since $U$ is normal, and $[U]_\beta = \bigoplus [U_{\lambda_i}]_{\beta_i}$, so $U_{\lambda}$ is normal. Then we can have orthonormal basis $\beta_\lambda$ for $E_\lambda$ consist only eigenvectors of $U_\lambda$. Obviously $\beta_i$ consist only eigenvectors of $T_\lambda$. Then $\bigcup \beta_\lambda$ is orthonormal basis of $V$ consist only eigenvectors of $T$ and $U$.

## P447 T1

a. Every quadratic form is a bilinear form.

b. If two matrices are congruent, they have the same eigenvalues.

c. Symmetric bilinear forms have symmetric matrix representations.

d. Any symmetric matrix is congruent to a diagonal matrix.

e. The sum of two symmetric bilinear forms is a symmetric bilinear form.

f. Two symmetric matrices with the same characteristic polynomial are matrix representations of the same bilinear form.

g. There exists a bilinear form $H$ such that $H(x, y) \ne 0$ for all $x$ and $y$.

h. If $V$ is a vector space of dimension $n$, then $\dim(\mathcal B(V)) = 2n$.

i. Let $H$ be a bilinear form on a finite-dimensional vector space $V$ with $\dim(V) > 1$. For any $x \in V$, there exists $y \in V$ such that $y \ne 0$, but $H(x, y) = 0$.

j. If $H$ is any bilinear form on a finite-dimensional real inner product space $V$, then there exists an ordered basis $\beta$ for $V$ such that $\psi_\beta(H)$ is a diagonal matrix.

a. False. b. False. c. True. d. False. e. True. f. False. g. False. h. False. i. True. j. False.

## P447 T4

Determine which of the mappings that follow are bilinear forms. Justify your answers.

a. Let $V = C[0, 1]$ be the space of continuous real-valued functions on the closed interval $[0, 1]$. For $f,g \in V$, define $H(f, g)=\int_0^1 f(t)g(t) \text{d}t$.

f. Let V be a complex inner product space, and let $H : V \times V \rightarrow C$ be the function defined by $H(x, y) = \langle x, y \rangle$ for $x, y \in V$.

---

a. Easy to see $H(f, g)=H(g, f)$, and $H(cf+g, h)=\int_0^1 (cf+g)(t)h(t) \text{d}t = cH(f, h)+H(g, h)$. So $H$ is bilinear form.

f. We have $H(x, cy)=\langle x, cy \rangle = \overline{c} \langle x, y \rangle = \overline{c} H(x, y) \ne cH(x, y)$ if $c$ is not real. So $H$ is not bilinear form.

## P448 T5

Verify that each of the given mappings is a bilinear form. Then compute its matrix representation with respect to the given ordered basis $β$.

c. Let $\beta = \{\cos t, \sin t, \cos 2t, \sin 2t\}$. Then $\beta$ is an ordered basis for $V = \text{span}(\beta)$, a four-dimensional subspace of the space of all continuous functions on $R$. Let $H : V \times V \rightarrow R$ be the function defined by $H(f,g) = f'(0) \cdot g''(0)$.

---

c. Since derivative is linear, then $H$ is linear for both side, and $H$ is bilinear form. We have $\psi_\beta(H)=\left[\begin{matrix}0 & 0 & 0 & 0 \\ -1 & 0 & -4 & 0 \\ 0 & 0 & 0 & 0 \\ -2 & 0 & -8 & 0\end{matrix}\right]$.

## P448 T6

Let $H : R^2 \rightarrow R$ be the function defined by $H((a_1, a_2)^t, (b_1, b_2)^t)=a_1b_2+a_2b_1$.

a. Prove that $H$ is a bilinear form.

b. Find the $2 \times 2$ matrix $A$ such that $H(x, y) = x^tAy$ for all $x, y \in R^2$.

---

a. We have $H((a_1, a_2)^t, (b_1, b_2)^t) = \det \left[\begin{matrix}a_1 & -b_1 \\ a_2 & b_2\end{matrix}\right] = \det \left[\begin{matrix}a_1 & b_1 \\ -a_2 & b_2\end{matrix}\right]$. So $H$ is linear for $\left[\begin{matrix}a_1 \\ a_2\end{matrix}\right]$ and $\left[\begin{matrix}b_1 \\ b_2\end{matrix}\right]$. Then $H$ is bilinear form.

b. Let $\beta$ be standard ordered basis for $R^2$. Then $A=\psi_\beta(H)=\left[\begin{matrix}0 & 1 \\ 1 & 0\end{matrix}\right]$.

## P450 T21

Let $A$ and $E$ be in $M_{n \times n}(F)$, with $E$ an elementary matrix. Prove that $E^tA$ can be obtained by means of the same elementary operation performed on the rows rather than on the columns of $A$.

---

Since $E^tA=(A^tE)^t$, then we perform elementary operation on $A^t$, then transpose back. So it's just perform transposed elementary operation on $A$.

## P451 T22

For each of the following matrices $A$ with entries from $R$, find a diagonal matrix $D$ and an invertible matrix $Q$ such that $Q^tAQ = D$.

a. $\left[\begin{matrix}1 & 3 \\ 3 & 2\end{matrix}\right]$.

b. $\left[\begin{matrix}0 & 1 \\ 1 & 0\end{matrix}\right]$.

c. $\left[\begin{matrix}3 & 1 & 2 \\ 1 & 4 & 0 \\ 2 & 0 & -1\end{matrix}\right]$.

---

a. We have $\left[\begin{matrix}1 & 3 \\ 3 & 2\end{matrix} \mid \begin{matrix}1 & 0 \\ 0 & 1\end{matrix}\right]$.

Add -3 times of row 1 to row 2, -3 times of column 1 to column 2, we have

$$\left[\begin{matrix}1 & 0 \\ 0 & -7\end{matrix} \mid \begin{matrix}1 & 0 \\ -3 & 1\end{matrix}\right].$$

So $D=\left[\begin{matrix}1 & 0 \\ 0 & -7\end{matrix}\right]$, $Q=\left[\begin{matrix}1 & -3 \\ 0 & 1\end{matrix}\right]$.

b. We have $\left[\begin{matrix}0 & 1 \\ 1 & 0\end{matrix} \mid \begin{matrix}1 & 0 \\ 0 & 1\end{matrix}\right]$.

Add row 2 to row 1, column 2 to column 1, we have

$$\left[\begin{matrix}2 & 1 \\ 1 & 0\end{matrix} \mid \begin{matrix}1 & 1 \\ 0 & 1\end{matrix}\right].$$

Add $-\frac{1}{2}$ times of row 1 to row 2, $-\frac{1}{2}$ times of column 1 to column 2, we have

$$\left[\begin{matrix}2 & 0 \\ 0 & -\frac{1}{2}\end{matrix} \mid \begin{matrix}1 & 1 \\ -\frac{1}{2} & \frac{1}{2}\end{matrix}\right].$$

So $D=\left[\begin{matrix}2 & 0 \\ 0 & -\frac{1}{2}\end{matrix}\right]$, $Q=\left[\begin{matrix}1 & -\frac{1}{2} \\ 1 & \frac{1}{2}\end{matrix}\right]$.

c. We have $\left[\begin{matrix}3 & 1 & 2 \\ 1 & 4 & 0 \\ 2 & 0 & -1\end{matrix} \mid \begin{matrix}1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1\end{matrix}\right]$.

Add $-\frac{1}{3}$ times of row 1 to row 2, $-\frac{1}{3}$ times of column 1 to column 2, we have

$$\left[\begin{matrix}3 & 0 & 2 \\ 0 & \frac{11}{3} & -\frac{2}{3} \\ 2 & -\frac{2}{3} & -1\end{matrix} \mid \begin{matrix}1 & 0 & 0 \\ -\frac{1}{3} & 1 & 0 \\ 0 & 0 & 1\end{matrix}\right].$$

Add $-\frac{2}{3}$ times of row 1 to row 3, $-\frac{2}{3}$ times of column 1 to column 3, we have

$$\left[\begin{matrix}3 & 0 & 0 \\ 0 & \frac{11}{3} & -\frac{2}{3} \\ 0 & -\frac{2}{3} & -\frac{7}{3}\end{matrix} \mid \begin{matrix}1 & 0 & 0 \\ -\frac{1}{3} & 1 & 0 \\ -\frac{2}{3} & 0 & 1\end{matrix}\right].$$

Add $\frac{2}{11}$ times of row 2 to row 3, $\frac{2}{11}$ times of column 2 to column 3, we have

$$\left[\begin{matrix}3 & 0 & 0 \\ 0 & \frac{11}{3} & 0 \\ 0 & 0 & -\frac{27}{11}\end{matrix} \mid \begin{matrix}1 & 0 & 0 \\ -\frac{1}{3} & 1 & 0 \\ -\frac{8}{11} & \frac{2}{11} & 1\end{matrix}\right].$$

So $D=\left[\begin{matrix}3 & 0 & 0 \\ 0 & \frac{11}{3} & 0 \\ 0 & 0 & -\frac{27}{11}\end{matrix}\right]$, $Q=\left[\begin{matrix}1 & -\frac{1}{3} & -\frac{8}{11} \\ 0 & 1 & \frac{2}{11} \\ 0 & 0 & 1\end{matrix}\right]$.

## P451 T24

Let $T$ be a linear operator on a real inner product space $V$, and define $H : V \times V \rightarrow R$ by $H(x, y) = \langle x,T(y) \rangle$ for all $x, y \in V$.

a. Prove that $H$ is a bilinear form.

b. Prove that $H$ is symmetric if and only if $T$ is self-adjoint.

c. What properties must $T$ have for $H$ to be an inner product on $V$?

d. Explain why $H$ may fail to be a bilinear form if $V$ is a complex inner product space.

---

a. Since inner product is linear for both side on $R$, and linear operator is linear, $H(x, y)$ is linear for $x$ and $y$. Then $H$ is bilinear.

b. $H$ symmetric iff $H(x, y)=H(y, x)$ iff $\langle x, T(y) \rangle = \langle y, T(x) \rangle$ iff $\langle x, T(y) \rangle = \langle x, T^*(y) \rangle$ iff $T=T^*$ iff $T$ is self-adjoint.

c. Since $H$ symmetric iff $T$ self-adjoint, then $T$ must be self-adjoint.

For all $x \ne 0$, $H(x, x) > 0$ iff $\langle x, T(x) \rangle > 0$ iff eigenvalues of $T$ are positive.

So $H$ is inner product iff $T$ is self-adjoint and all eigenvalues are positive.

d. When $T=I$, we have $H(x, cy) = \overline{c}\langle x, y \rangle = \overline{c} H(x, y) \ne cH(x, y)$ if $c$ is not real.

## P451 T25

Let $V$ be a finite-dimensional real inner product space, and let $H$ be a bilinear form on V. Then there exists a unique linear operator $T$ on $V$ such that $H(x, y) = \langle x,T(y) \rangle$ for all $x, y \in V$.

---

Let $\beta$ be orthonormal basis of $V$. We can have unique $z \in V$ that $[z]_\beta = \psi_\beta(H) [y]_\beta$, let $T(y)=z$, obviously $T$ is linear.

We have $H(x, y)=[x]_\beta^t \psi_\beta(H) [y]_\beta = \sum_{i, j} H(\beta_i, \beta_j) \langle x, \beta_i \rangle \langle y, \beta_j \rangle = \sum_{i=1}^n \langle x, \beta_i \rangle \sum_{j=1}^n H(\beta_i, \beta_j) \langle y, \beta_j \rangle = \sum_{i=1}^n \langle x, \beta_i \rangle \langle T(y), \beta_i \rangle = \langle x, T(y) \rangle$.

So $T$ is exist. If we have $T_1$ and $T_2$, then $\langle x, T_1(y) \rangle = \langle x, T_2(y) \rangle$, so $T_1(y)=T_2(y)$, thus $T_1=T_2$.
