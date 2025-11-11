# Week7 Homework (Textbook)

By Deng Yufan.

## P207 T1

a. The function det: $M_{2 \times 2}(F) → F$ is a linear transformation.

b. The determinant of a $2 \times 2$ matrix is a linear function of each row of the matrix when the other row is held fixed.

c. If $A \in M_{2 \times 2}(F)$ and $\det(A) = 0$, then $A$ is invertible.

d. If $u$ and $v$ are vectors in $R^2$ emanating from the origin, then the area of the parallelogram having $u$ and $v$ as adjacent sides is $\det{u \choose v}$.

a. False. b. True. c. False. d. False.

## P208 T2

Compute the determinants of the following matrices in $M_{2 \times 2}(R)$.

a. $\left[\begin{matrix}6 & -3 \\ 2 & 4\end{matrix}\right]$.

---

a. $\det\left[\begin{matrix}6 & -3 \\ 2 & 4\end{matrix}\right]=6 \times 4 - (-3) \times 2 = 30$.

## P208 T3

Compute the determinants of the following matrices in $M_{2 \times 2}(C)$.

a. $\left[\begin{matrix}-1+i & 1-4i \\ 3+2i & 2-3i\end{matrix}\right]$

---

a. $\det\left[\begin{matrix}-1+i & 1-4i \\ 3+2i & 2-3i\end{matrix}\right]=(-1+i)(2-3i)-(1-4i)(3+2i)=(1+5i)-(11-10i)=-10+15i$.

## P208 T9

Prove that $\det(AB) = \det(A) \cdot \det(B)$ for any $A, B \in M_{2 \times 2}(F)$.

---

We have $AB=\left[\begin{matrix}a_{11}b_{11}+a_{12}b_{21} & a_{11}b_{12}+a_{12}b_{22} \\ a_{21}b_{11}+a_{22}b_{21} & a_{21}b_{12}+a_{22}b_{22}\end{matrix}\right]$, $\det(AB)=(a_{11}b_{11}+a_{12}b_{21})(a_{21}b_{12}+a_{22}b_{22})-(a_{11}b_{12}+a_{12}b_{22})(a_{21}b_{11}+a_{22}b_{21})=a_{11}b_{11}a_{22}b_{22}+a_{12}b_{21}a_{21}b_{12}-a_{11}b_{12}a_{22}b_{21}-a_{12}b_{22}a_{21}b_{11}=(a_{11}a_{22}-a_{12}a_{21})(b_{11}b_{22}-b_{12}b_{21})=\det A \det B$.

## P220 T1

a. The function det: $M_{n \times n}(F) \rightarrow F$ is a linear transformation.

b. The determinant of a square matrix can be evaluated by cofactor
expansion along any row.

c. If two rows of a square matrix $A$ are identical, then $\det(A) = 0$.

d. If $B$ is a matrix obtained from a square matrix $A$ by interchanging any two rows, then $\det(B) = - \det(A)$.

e. If $B$ is a matrix obtained from a square matrix $A$ by multiplying a row of $A$ by a scalar, then $\det(B) = \det(A)$.

f. If $B$ is a matrix obtained from a square matrix $A$ by adding $k$ times row $i$ to row $j$, then $\det(B) = k \det(A)$.

g. If $A \in M_{n \times n}(F)$ has rank $n$, then $\det(A) = 0$.

h. The determinant of an upper triangular matrix equals the product
of its diagonal entries.

a. False. b. True. c. True. d. True. e. False. f. False. g. False. h. True.

## P221 T5

Evaluate the determinant of $\left[\begin{matrix}0 & 1 & 2 \\ -1 & 0 & -3 \\ 2 & 3 & 0\end{matrix}\right]$ by cofactor expansion along the first row.

---

We have $\det\left[\begin{matrix}0 & 1 & 2 \\ -1 & 0 & -3 \\ 2 & 3 & 0\end{matrix}\right]=-\det\left[\begin{matrix}-1 & -3 \\ 2 & 0\end{matrix}\right]+2\det\left[\begin{matrix}-1 & 0 \\ 2 & 3\end{matrix}\right]=6+2(-3)=0$.

## P221 T8

Evaluate the determinant of $\left[\begin{matrix}1 & 0 & 2 \\ 0 & 1 & 5 \\ -1 & 3 & 0\end{matrix}\right]$ by cofactor expansion along the third row.

---

We have $\det\left[\begin{matrix}1 & 0 & 2 \\ 0 & 1 & 5 \\ -1 & 3 & 0\end{matrix}\right]=-\det\left[\begin{matrix}0 & 2 \\ 1 & 5\end{matrix}\right]-3\det\left[\begin{matrix}1 & 2 \\ 0 & 5\end{matrix}\right]=-(-2)-3(5)=-13$.

## P222 T25

Prove that $\det(kA) = k^n \det(A)$ for any $A \in M_{n \times n}(F)$.

---

Induction $n$.

As basis: When $n=1$, we have $\det(kx)=kx=k\det(x)$.

As induction: We assume $n-1$ and prove $n$. For all $A \in M_{n \times n}(F)$, we have $\det(kA)=\sum_{i=1}^n (-1)^{i+1}kA_{1i}\det(k\widetilde A_{1i})=k\sum_{i=1}^n(-1)^{i+1}A_{1i} k^{n-1} \det(\widetilde A_{1i})=k^n\sum_{i=1}^n(-1)^{i+1}\det(\widetilde A_{1i})=k^n\det(A)$.

## P228 T1

a. If $E$ is an elementary matrix, then $\det(E) = \plusmn 1$.

b. For any $A, B \in M_{n \times n}(F)$, $\det(AB) = \det(A) \cdot \det(B)$.

c. A matrix $M \in M_{n \times n}(F)$ is invertible if and only if $\det(M) = 0$.

d. A matrix $M \in M_{n \times n}(F)$ has rank $n$ if and only if $\det(M) \ne 0$.

e. For any $A \in M_{n \times n}(F)$, $\det(A^t) = - \det(A)$.

f. The determinant of a square matrix can be evaluated by cofactor expansion along any column.

g. Every system of $n$ linear equations in $n$ unknowns can be solved by Cramer's rule.

h. Let $Ax = b$ be the matrix form of a system of $n$ linear equations
in $n$ unknowns, where $x = (x_1, x_2,\cdots,x_n)^t$. If $\det(A) \ne 0$ and if $M_k$ is the $n \times n$ matrix obtained from $A$ by replacing row $k$ of $A$ by $b^t$, then the unique solution of $Ax = b$ is $x_k = \frac{\det(M_k)}{\det(A)}$ for $k = 1, 2, \cdots, n$.

a. False. b. True. c. False. d. True. e. False. f. True. g. False. h. True.

## P228 T5

Use Cramer's rule to solve $\left\{\begin{aligned}&x_1-x_2+4x_3=-4 \\ &-8x_1+3x_2+x_3=8 \\ & 2x_1-x_2+x_3=0\end{aligned}\right.$.

---

Write the system into matrix form, we have

$$
\left[\begin{matrix}
1 & -1 & 4
\\
-8 & 3 & 1
\\
2 & -1 & 1
\end{matrix}\right] x = \left[\begin{matrix}
-4
\\
8
\\
0
\end{matrix}\right].
$$

We have $\det\left[\begin{matrix}
1 & -1 & 4
\\
-8 & 3 & 1
\\
2 & -1 & 1
\end{matrix}\right]=2$, $\det\left[\begin{matrix}
-4 & -1 & 4
\\
8 & 3 & 1
\\
0 & -1 & 1
\end{matrix}\right]=-40$, $\det\left[\begin{matrix}
1 & -4 & 4
\\
-8 & 8 & 1
\\
2 & 0 & 1
\end{matrix}\right]=-96$, $\det\left[\begin{matrix}
1 & -1 & -4
\\
-8 & 3 & 8
\\
2 & -1 & 0
\end{matrix}\right]=-16$.

So $x_1=-20$, $x_2=-48$, $x_3=-8$.

## P229 T13

For $M \in M_{n \times n}(C)$, let $\overline M$ be the matrix such that $(\overline M)ij = \overline {M_{ij}}$ for all $i$, $j$, where $\overline {M_{ij}}$ is the complex conjugate of $M_{ij}$.

a. Prove that $\det(\overline M) = \overline {\det(M)}$.

b. A matrix $Q \in M_{n \times n}(C)$ is called unitary if $QQ^* = I$, where $Q^* = \overline {Q^t}$. Prove that if $Q$ is a unitary matrix, then $|\det(Q)|=1$.

---

a. Induction $n$.

As basis: When $n=1$, we have $\det(\overline x)=\overline x = \overline {\det(x)}$.

As induction: We assume $n-1$ and prove $n$. For all $A \in M_{n \times n}(C)$, $\det(\overline A)=\sum_{i=1}^n (-1)^{i+1} \overline {A_{1i}} \det(\overline {\widetilde A_{1i}})=\sum_{i=1}^n (-1)^{i+1} \overline {A_{1i}} \overline {\det(\widetilde A_{1i})}=\sum_{i=1}^n (-1)^{i+1} \overline {A_{1i}\det(\widetilde A_{1i})}=\overline {\sum_{i=1}^n (-1)^{i+1} A_{1i}\det(\widetilde A_{1i})}=\overline {\det A}$.

b. We have $|\det(Q)| = \det(Q) \overline{\det(Q)} = \det(Q) \overline{\det(Q^t)} = \det(Q) \det(Q^*) = \det(QQ^*) = \det(I) = 1$.

## P229 T20

Suppose that $M \in M_{n \times n}(F)$ can be written in the form $M = \left[\begin{matrix}A & B \\ O & I\end{matrix}\right]$, where $A$ is a square matrix. Prove that $\det(M) = \det(A)$.

---

Let $I$ be a $m \times m$ identical matrix. Induction $m$.

As basis: When $m=0$, then $M=A$. So $\det(M)=\det(A)$.

As induction: We assume $m-1$ and prove $m$. We have $\det(M)=\sum_{i=1}^n (-1)^{n+i} M_{ni} \det(\widetilde M_{ni})=\det(\widetilde M_{nn})=\det(A)$.

## P229 T21

Prove that if $M \in M_{n \times n}(F)$ can be written in the form $M = \left[\begin{matrix}A & B \\ O & C\end{matrix}\right]$, where $A$ and $C$ are square matrices, then $\det(M) = \det(A) \cdot \det(C)$.

---

Let $C$ be a $m \times m$ matrix. Induction $m$.

As basis: When $m=1$, then $M=\left[\begin{matrix}A & B \\ O & x\end{matrix}\right]$. If $x=0$ then $\det(M)=0=\det(A) \cdot \det(C)$. Else multiply row $n$ by $\frac{1}{x}$ and use P229 T20, we have $\frac{1}{x}\det(M)=\det(A)$, which is $\det(M)=\det(A) \cdot \det(C)$.

As induction: We assume $m-1$ and prove $m$. We have $\det(M)=\sum_{i=1}^n (-1)^{n+i} M_{ni} \det(\widetilde M_{ni})=\sum_{i=1}^m (-1)^{2n-m+i} C_{mi} (\det(A) \cdot \det(\widetilde C_{mi}))=\det(A)\sum_{i=1}^m (-1)^{m+i}C_{mi}\det(\widetilde C_{mi})=\det(A) \cdot \det(C)$.

## P230 T22

Let $T: P_n(F) \rightarrow F^{n+1}$ be the linear transformation defined by $T(f)=(f(c_0), f(c_1),\cdots,f(c_n))$, where $c_0, c_1,\cdots, c_n$ are distinct scalars in an infinite field $F$. Let $\beta$ be the standard ordered basis for $P_n(F)$ and $\gamma$ be the standard ordered basis for $F^{n+1}$.

a. Show that $M = [T]^\gamma_\beta$ has the form $\left[\begin{matrix}1 & c_0 & c_0^2 & \cdots & c_0^n \\ 1 & c_1 & c_1^2 & \cdots & c_1^n \\ \vdots & \vdots & \vdots & & \vdots \\ 1 & c_n & c_n^2 & \cdots & c_n^n\end{matrix}\right]$.

c. Prove that $\det(M) = \prod_{0 \le i < j \le n} (c_j − c_i)$.

---

a. Since $T(\beta_i)=(c_0^i, c_1^i, \cdots, c_n^i)=c_0^i\gamma_0+\cdots+c_n^i\gamma_n$. So obviously $M$ has the form.

c. Induction $n$.

As basis, when $n=0$, we have $\det(1)=1$.

As induction, we assume $n-1$ and prove $n$. Add -1 times of row 1 to other rows, we have $M'=\left[\begin{matrix}1 & c_0 & c_0^2 & \cdots & c_0^n \\ 0 & c_1-c_0 & c_1^2-c_0^2 & \cdots & c_1^n-c_0^n \\ \vdots & \vdots & \vdots & & \vdots \\ 0 & c_n-c_0 & c_n^2-c_0^2 & \cdots & c_n^n-c_0^n\end{matrix}\right]$. Obviously $\det(M)=\det(M')=\det(\widetilde M'_{11})$. Multiply row $i$ ($1 \le i \le n$) by $\frac{1}{c_i-c_0}$, we have $M''=\left[\begin{matrix}1 & c_0+c_1 & \cdots & c_0^n+c_0^{n-1}c_1+\cdots+c_1^n \\ \vdots & \vdots & & \vdots \\ 1 & c_0+c_n & \cdots & c_0^n+c_0^{n-1}c_n+\cdots+c_n^n\end{matrix}\right]$. Add $c_0^{j-i}$ times of row $i$ to row $j$ ($i < j$, operate in ascend order of $i$), we have $M'''=\left[\begin{matrix}1 & c_1 & \cdots & c_1^n \\ \vdots & \vdots & & \vdots \\ 1 & c_n & \cdots & c_n^n\end{matrix}\right]$. Obviously $\det(M)=\det(M'')\prod_{i=1}^n (c_i-c_0)=\det(M''')\prod_{i=1}^n (c_i-c_0)=\prod_{1 \le i < j \le n} (c_j-c_i) \cdot \prod_{i=1}^n (c_i-c_0)=\prod_{0 \le i < j \le n}(c_j-c_i)$.

## P230 T24

Let $A \in M_{n \times n}(F)$ have the form $A=\left[\begin{matrix}0 & 0 & \cdots & a_0 \\ -1 & 0 & \cdots & a_1 \\ 0 & -1 & \cdots & a_2 \\ \vdots & \vdots & & \vdots \\ 0 & 0 & \cdots & a_{n-1}\end{matrix}\right]$. Compute $\det(A + tI)$, where $I$ is the $n \times n$ identity matrix.

---

We prove $\det(A+tI)=\sum_{i=0}^na_it^i$, where $a_n=1$.

Induction $n$. As basis: When $n=1$, $\det(A+tI)=a_0+t$.

As induction: We assume $n-1$ and prove $n$. Since $\widetilde {(A+tI)}_{1n}$ is a upper triangle matrix, $\det(\widetilde {(A+tI)}_{1n})=(-1)^{n-1}$. So $\det(A+tI)=t\det(\widetilde {(A+tI)}_{11})+(-1)^{n+1}a_0\det(\widetilde {(A+tI)}_{1n})=t\sum_{i=1}^n a_it^{i-1} + (-1)^{2n} a_0=\sum_{i=0}^n a_it^i$.

## P231 T25

Let $c_{jk}$ denote the cofactor of the row $j$, column $k$ entry of the matrix $A \in M_{n \times n}(F)$, or $(-1)^{j+k} \det(\widetilde A_{jk})$.

a. Prove that if $B$ is the matrix obtained from $A$ by replacing column $k$ by $e_j$, then $\det(B) = c_{jk}$.

b. Show that for $1 \le j \le n$, we have $A\left[\begin{matrix}c_{j1} \\ c_{j2} \\ \vdots \\ c_{jn}\end{matrix}\right]=\det(A) \cdot e_j$.

c. Deduce that if $C$ is the $n \times n$ matrix such that $C_{ij} = c_{ji}$, then $AC = [\det(A)]I$.

d. Show that if $\det(A) \ne 0$, then $A^{-1} = [\det(A)]^{-1}C$.

---

a. $\det(B)=\det(B^t)=\sum_{i=1}^n (-1)^{k+i} B_{ik} \det(\widetilde {B^t}_{ki})=(-1)^{j+k}\det(\widetilde B_{jk})=(-1)^{j+k}\det(\widetilde A_{jk})=c_{jk}$.

b. For all $1 \le j \le n$, let $A^{(i)}$ be $A$ replacing row $j$ by row $i$. We have $\sum_{k=1}^n A_{ik} c_{jk}=\sum_{k=1}^n A_{ik} (-1)^{j+k} \det(\widetilde A_{jk})=\sum_{k=1}^n A^{(i)}_{jk} (-1)^{j+k} \det(\widetilde {A^{(i)}}_{jk})=\det(A^{(i)})$. So for $i \ne j$, row $i$ and row $j$ of $A^{(i)}$ is identical, so $\det(A^{(i)})=0$. And since $A^{(j)}=A$, $\det(A^{(j)})=\det(A)$. So $A\left[\begin{matrix}c_{j1} \\ c_{j2} \\ \vdots \\ c_{jn}\end{matrix}\right]=\det(A) \cdot e_j$.

c. We have $C=[C'_1, C'_2, \cdots, C'_n]$, where $C'_i = \left[\begin{matrix}c_{i1} \\ c_{i2} \\ \vdots \\ c_{in}\end{matrix}\right]$. So $AC=[AC'_1, AC'_2, \cdots, AC'_n]=[\det(A) \cdot e_1, \det(A) \cdot e_2, \cdots, \det(A) \cdot e_n]=\det(A)I$.

d. We have $A (\det^{-1}(A)C) = \det^{-1}(A)(AC) = I$. And we have when $A$ and $B$ are square, $AB=I$, then $BA=I$ according to P107 T9. So $(\det^{-1}(A)C) A = I$, thus $A^{-1}=\det^{-1}(A)C$.
