# Week2 Homework (Textbook)

By Deng Yufan.

## P12 T1

a. Every vector space contains a zero vector.

b. A vector space may have more than one zero vector.

c. In any vector space, $ax = bx$ implies that $a = b$.

d. In any vector space, $ax = ay$ implies that $x = y$.

e. A vector in $\text{F}^n$ may be regarded as a matrix in $\text{M}_{n \times 1}(F)$.

f. An $m \times n$ matrix has $m$ columns and $n$ rows.

g. In $\text{P}(F)$, only polynomials of the same degree may be added.

h. If $f$ and $g$ are polynomials of degree $n$, then $f + g$ is a polynomial of degree $n$.

i. If $f$ is a polynomial of degree $n$ and $c$ is a nonzero scalar, then $cf$ is a polynomial of degree $n$.

j. A nonzero scalar of $F$ may be considered to be a polynomial in
$\text{P}(F)$ having degree zero.

k. Two functions in $\mathcal{F}(S, F)$ are equal if and only if they have the same value at each element of $S$.

a. True. b. False. c. True. d. False. e. True. f. False. g. False. h. True. i. True. j. True. k. True.

## P13 T2

Write the zero vector of $\text{M}_{3 \times 4}(F)$.

---

$$
\left[
\begin{matrix}
0 & 0 & 0 & 0
\\
0 & 0 & 0 & 0
\\
0 & 0 & 0 & 0
\end{matrix}
\right].
$$

## P14 T8

In any vector space $\text{V}$, show that $(a + b)(x + y) = ax + ay + bx + by$ for any $x, y \in \text{V}$ and any $a, b \in F$.

---

We have

$$
\begin{aligned}
(a+b)(x+y) &= (a+b)x+(a+b)y
\\
&= (ax+bx)+(ay+by)
\\
&= ax+ay+bx+by.
\end{aligned}
$$

## P15 T13

Let $\text{V}$ denote the set of ordered pairs of real numbers. If $(a_1, a_2)$ and $(b_1, b_2)$ are elements of $\text{V}$ and $c \in \R$, define $(a_1, a_2)+(b_1, b_2)=(a_1 + b_1, a_2b_2)$ and $c(a_1, a_2)=(ca_1, a_2)$. Is $\text{V}$ a vector space over $\R$ with these operations? Justify your answer.

---

$\text{V}$ is not a vector space over $\R$ with these operations, since $(0, 0)$ have no additive inverse.

Further saying, if there exists $(b_1, b_2)$ satisfy $(a_1, a_2) + (0, 0) + (b_1, b_2) = (a_1, a_2)$, that is $(a_1+0+b_1, a_2 \cdot 0 \cdot b_2)=(a_1+b_1, 0)=(a_1, a_2)$, which when $a_2 \ne 0$ it is impossible.

## P16 T21

Let $\text{V}$ and $\text{W}$ be vector spaces over a field $F$. Let $\text{Z} = \{(v, w): v \in \text{V}, w \in \text{W}\}$. Prove that $\text{Z}$ is a vector space over $F$ with the operations $(v_1, w_1)+(v_2, w_2)=(v_1 + v_2, w_1 + w_2)$ and $c(v_1, w_1)=(cv_1, cw_1)$.

---

Let $v_0$ and $w_0$ be the additive identity of $\text{V}$ and $\text{W}$, and $-v$ and $-w$ be the additive inverse of $v \in \text{V}$ and $w \in \text{W}$, respectively.

1. $\text{Z}$ have an additive identity $(v_0, w_0)$.
2. $(v, w) \in \text{Z}$ have an additive inverse $(-v, -w)$.
3. $\text{Z}$ have a scalar multiplicative identity $1$.
4. $(v_1, w_1)+(v_2, w_2)=(v_1+v_2, w_1+w_2)=(v_2+v_1, w_2+w_1)=(v_2, w_2)+(v_1, w_1)$.
5. $(v_1, w_1)+(v_2, w_2)+(v_3, w_3)=(v_1+v_2+v_3, w_1+w_2+w_3)=(v_1+(v_2+v_3), w_1+(w_2+w_3))=(v_1, w_1)+((v_2, w_2)+(v_3, w_3))$.
6. $(c_1c_2)(v, w)=((c_1c_2)v, (c_1c_2)w)=(c_1(c_2v), c_1(c_2w))=c_1(c_2(v, w))$.
7. $c((v_1, w_1)+(v_2, w_2))=c(v_1+v_2, w_1+w_2)=(c(v_1+v_2), c(w_1+w_2))=(cv_1+cv_2,cw_1+cw_2)=(cv_1, cw_1)+(cv_2, cw_2)=c(v_1, w_1)+c(v_2, w_2)$.
8. $(c_1+c_2)(v, w)=((c_1+c_2)v, (c_1+c_2)w)=(c_1v+c_2v, c_1w+c_2w)=(c_1v, c_1w)+(c_2v, c_2w)=c_1(v, w)+c_2(v, w)$.

## P19 T1

a. If $\text{V}$ is a vector space and $\text{W}$ is a subset of $\text{V}$ that is a vector space, then $\text{W}$ is a subspace of $\text{V}$.

b. The empty set is a subspace of every vector space.

c. If $\text{V}$ is a vector space other than the zero vector space, then $\text{V}$ contains a subspace $\text{W}$ such that $\text{W} \ne \text{V}$.

d. The intersection of any two subsets of $\text{V}$ is a subspace of $\text{V}$.

e. An $n \times n$ diagonal matrix can never have more than $n$ nonzero entries.

f. The trace of a square matrix is the product of its diagonal entries.

g. Let $\text{W}$ be the xy-plane in $\text{R}^3$; that is, $\text{W} = {(a_1, a_2, 0): a_1, a_2 \in R}$. Then $\text{W} = \text{R}^2$.

a. True. b. False. c. True. d. True. e. True. f. False. g. True.

## P20 T8

Determine whether the following sets are subspaces of $\text{R}^3$ under the operations of addition and scalar multiplication defined on $\text{R}^3$. Justify your answers.

a. $\text{W}_1 = \{(a_1, a_2, a_3) \in \text{R}^3 : a_1 = 3a_2, a_3 = −a_2\}$.

b. $\text{W}_2 = \{(a_1, a_2, a_3) \in \text{R}^3 : a_1 = a_3 + 2\}$.

---

a. $\text{W}_1$ is a subspace of $\text{R}^3$, since

  1. For all $(a_1, a_2, a_3), (b_1, b_2, b_3) \in \text{W}_1$, $(a_1, a_2, a_3)+(b_1, b_2, b_3)=(a_1+b_1, a_2+b_2, a_3+b_3)$, and $(a_1+b_1)=3(a_2+b_2)$, $(a_3+b_3)=-(a_2+b_2)$, so $(a_1, a_2, a_3)+(b_1, b_2, b_3) \in \text{W}_1$.
  2. For all $c \in \text{R}$, $(a_1, a_2, a_3) \in \text{W}_1$, $c(a_1, a_2, a_3)=(ca_1, ca_2, ca_3)$, and $ca_1=3(ca_2)$, $ca_3=-(ca_2)$, so $c(a_1, a_2, a_3) \in \text{W}_1$.
  3. We have the additive identity $(0, 0, 0) \in \text{W}_1$.

b. $\text{W}_2$ is not a subspace of $\text{R}^3$, since the additive identity $(0, 0, 0) \notin \text{W}_2$.

## P21 T10

Prove that $\text{W}_1 = \{(a_1, a_2,\cdots,a_n) \in \text{F}^n : a_1 + a_2 + \cdots + a_n = 0\}$ is a subspace of $\text{F}^n$, but $\text{W}_2 = \{(a_1, a_2,\cdots,a_n) \in \text{F}^n : a_1 +a_2 +\cdots+a_n = 1\}$ is not.

---

We have

1. For all $(a_1, a_2, \cdots, a_n), (b_1, b_2, \cdots, b_n) \in \text{W}_1$, $(a_1, a_2, \cdots, a_n)+(b_1, b_2, \cdots, b_n)=(a_1+b_1, a_2+b_2, \cdots, a_n+b_n)$, and $a_1+b_1+a_2+b_2+\cdots+a_n+b_n=0$, so $(a_1, a_2, \cdots, a_n)+(b_1, b_2, \cdots, b_n) \in \text{W}_1$.
2. For all $c \in \text{F}$, $(a_1, a_2, \cdots, a_n) \in \text{W}_1$, $c(a_1, a_2, \cdots, a_n)=(ca_1, ca_2, \cdots, ca_n)$, and $ca_1+ca_2+\cdots+ca_n=0$, so $c(a_1, a_2, \cdots, a_n) \in \text{W}_1$.
3. We have the additive identity $(0, 0, \cdots, 0) \in \text{W}_1$.

But the additive identity $(0, 0, \cdots, 0) \notin \text{W}_2$.

## P21 T19

Let $\text{W}_1$ and $\text{W}_2$ be subspaces of a vector space $\text{V}$. Prove that $\text{W}_1 \cup \text{W}_2$ is a subspace of $\text{V}$ if and only if $\text{W}_1 \subseteq \text{W}_2$ or $\text{W}_2 \subseteq \text{W}_1$.

---

If $\text{W}_1 \subseteq \text{W}_2$ or $\text{W}_2 \subseteq \text{W}_1$, we have $\text{W}_1 \cup \text{W}_2 = \text{W}_2$ or $\text{W}_1 \cup \text{W}_2 = \text{W}_1$, so surely $\text{W}_1 \cup \text{W}_2$ is a subspace of $\text{V}$.

If $\text{W}_1 \nsubseteq \text{W}_2$ and $\text{W}_2 \nsubseteq \text{W}_1$, we have $w_1$ satisfy $w_1 \in \text{W}_1 \land w_1 \notin \text{W}_2$, and we have $w_2$ satisfy $w_2 \in \text{W}_2 \land w_2 \notin \text{W}_1$.

If now $\text{W}_1 \cup \text{W}_2$ is a subspace of $\text{V}$, then $w_1+w_2 \in \text{W}_1 \cup \text{W}_2$, which is $w_1+w_2 \in \text{W}_1$ or $w_1+w_2 \in \text{W}_2$. We can assume $w_1+w_2 \in \text{W}_1$, otherwise we can swap $\text{W}_1$ and $\text{W}_2$ in text below.

Since $\text{W}_1$ is a subspace of $\text{V}$, and $w_1 \in \text{W}_1$, we have $-w_1 \in \text{W}_1$ satisfy $w_1+(-w_1)=0_\text{V}$. Further more, we have $w_1+w_2 \in \text{W}_1$, so $(w_1+w_2)+(-w_1)=w_2 \in \text{W}_1$. But we know that $w_2 \notin \text{W}_1$, so $\text{W}_1 \cup \text{W}_2$ is not a subspace of $\text{V}$.

## P22 T23

Let $\text{W}_1$ and $\text{W}_2$ be subspaces of a vector space $\text{V}$.

a. Prove that $\text{W}_1 + \text{W}_2$ is a subspace of $\text{V}$ that contains both $\text{W}_1$ and $\text{W}_2$.

b. Prove that any subspace of $\text{V}$ that contains both $\text{W}_1$ and $\text{W}_2$ must also contain $\text{W}_1 + \text{W}_2$.

---

a. We have

  1. For all $w_1, w_1' \in \text{W}_1$, $w_2, w_2' \in \text{W}_2$, $(w_1+w_2)+(w_1'+w_2')=(w_1+w_1')+(w_2+w_2')$, and $w_1+w_1' \in \text{W}_1$, $w_2+w_2' \in \text{W}_2$, so $(w_1+w_2)+(w_1'+w_2') \in \text{W}_1 + \text{W}_2$.
  2. For all $c \in F$, $w_1 \in \text{W}_1$, $w_2 \in \text{W}_2$, $c(w_1+w_2)=cw_1+cw_2$, and $cw_1 \in \text{W}_1$, $cw_2 \in \text{W}_2$, so $c(w_1+w_2) \in \text{W}_1 + \text{W}_2$.
  3. $0_\text{V} = 0_\text{V}+0_\text{V} \in \text{W}_1 + \text{W}_2$.

So $\text{W}_1 + \text{W}_2$ is a subspace. Further more, we have $0_\text{V} \in \text{W}_2$, so for all $w_1 \in \text{W}_1$ we have $w_1=w_1+0_\text{V} \in \text{W}_1 + \text{W}_2$. Likewise, we have for all $w_2 \in \text{W}_2$, $w_2 \in \text{W}_1 + \text{W}_2$.

b. Assume we have $\text{W}$ as a subspace of $\text{V}$, and $\text{W}_1 \subseteq \text{W}$, $\text{W}_2 \subseteq \text{W}$. So for all $w_1 \in \text{W}_1 \subseteq \text{W}$, $w_2 \in \text{W}_2 \subseteq \text{W}$, we have $w_1+w_2 \in \text{W}$.

## P23 T31

Let $\text{W}$ be a subspace of a vector space $\text{V}$ over a field $F$. For any $v \in \text{V}$ the set $\{v\}+\text{W} = \{v+w: w \in \text{W}\}$ is called the coset of $\text{W}$ containing $v$. It is customary to denote this coset by $v + \text{W}$ rather than $\{v\} + \text{W}$.

a. Prove that $v + \text{W}$ is a subspace of $\text{V}$ if and only if $v \in \text{W}$.

b. Prove that $v_1 + \text{W} = v_2 + \text{W}$ if and only if $v_1 − v_2 \in \text{W}$.

Addition and scalar multiplication by scalars of $F$ can be defined in the collection $S = \{v + W: v \in \text{V}\}$ of all cosets of $\text{W}$ as follows:

$(v_1 + \text{W})+(v_2 + \text{W})=(v_1 + v_2) + \text{W}$ for all $v_1, v_2 \in \text{V}$, and $a(v + \text{W}) = av + \text{W}$ for all $v \in \text{V}$ and $a \in \text{F}$.

c. Prove that the preceding operations are well defined; that is, show
that if $v_1 + \text{W} = v_1' + \text{W}$ and $v_2 + \text{W} = v_2' + \text{W}$, then $(v_1 + \text{W})+(v_2 + \text{W})=(v_1' + \text{W})+(v_2' + \text{W})$ and $a(v_1 + \text{W}) = a(v_1' + \text{W})$ for all $a \in \text{F}$.

d. Prove that the set $S$ is a vector space with the operations defined in (c). This vector space is called the quotient space of $\text{V}$ modulo $\text{W}$ and is denoted by $\text{V}/\text{W}$.

---

a. Let $-v$ be the additive inverse of $v$. If $v \in \text{W}$, we have $-v \in \text{W}$, and

  1. For all $w_1, w_2 \in \text{W}$, $(v+w_1)+(v+w_2)=v+(w_1+w_2+v)$, and we have $w_1+w_2+v \in \text{W}$, so $(v+w_1)+(v+w_2) \in v+\text{W}$.
  2. For all $c \in F$, $w \in \text{W}$, $c(v+w)=v+((c-1_F)v+cw)$, and we have $c-1_F \in F$, $(c-1_F)v+cw \in \text{W}$, so $c(v+w) \in v+\text{W}$.
  3. Since $-v \in \text{W}$, we have $0_\text{V}=v+(-v) \in v+\text{W}$.

If $v \notin \text{W}$, then $-v \notin \text{W}$ (otherwise we have $v \in \text{W}$), so $0_\text{V}=v+(-v) \notin v+\text{W}$.

b. If $v_1-v_2 \in \text{W}$, for all $w \in \text{W}$, we have $v_1+w=v_2+(w+(v_1-v_2))$. Since $w+(v_1-v_2) \in \text{W}$, we have $v_1+w \in v_2+\text{W}$, which is $v_1+\text{W} \subseteq v_2+\text{W}$. We also have $v_2-v_1=-(v_1-v_2) \in \text{W}$, so likewise we have $v_2+\text{W} \subseteq v_1+\text{W}$. So $v_1+\text{W}=v_2+\text{W}$.

If $v_1-v_2 \notin \text{W}$, for all $w \in \text{W}$, we have $v_1+w=v_2+(w+(v_1-v_2))$. Since $w+(v_1-v_2) \notin \text{W}$ (otherwise $v_1-v_2=(w+(v_1-v_2))+(-w) \in \text{W}$), we have $v_1+w \notin v_2+\text{W}$, which is $v_1+\text{W} \cap v_2+\text{W}=\varnothing$. We know that $v_1 \in v_1+\text{W}$, so $v_1 \notin v_2+\text{W}$, $v_1+\text{W} \ne v_2+\text{W}$.

c. We have $v_1-v_1' \in \text{W}$, $v_2-v_2' \in \text{W}$, so $(v_1+v_2)-(v_1'+v_2')=v_1-v_1'+v_2-v_2' \in \text{W}$, so $(v_1+v_2)+\text{W}=(v_1'+v_2')+\text{W}$, $(v_1+\text{W})+(v_2+\text{W})=(v_1'+\text{W})+(v_2'+\text{W})$.

We also have $av_1-av_1'=a(v_1-v_1') \in \text{W}$, so $av_1+\text{W}=av_1'+\text{W}$, $a(v_1+\text{W})=a(v_1'+\text{W})$.

d. Let $-v$ be additive inverse of $v$ in $\text{V}$.

  1. $S$ have an additive identity $0_\text{V}+\text{W}$.
  2. $v+\text{W} \in S$ have an additive inverse $(-v)+\text{W}$.
  3. $S$ have a scalar multiplicative identity $1_F$.
  4. $(v_1+\text{W})+(v_2+\text{W})=(v_1+v_2)+\text{W}=(v_2+v_1)+\text{W}=(v_2+\text{W})+(v_1+\text{W})$.
  5. $(v_1+\text{W})+(v_2+\text{W})+(v_3+\text{W})=(v_1+v_2+v_3)+\text{W}=(v_1+(v_2+v_3))+\text{W}=(v_1+\text{W})+((v_2+\text{W})+(v_3+\text{W}))$.
  6. $(c_1c_2)(v+\text{W})=(c_1c_2v)+\text{W}=(c_1(c_2v))+\text{W}=c_1(c_2(v+\text{W}))$.
  7. $c((v_1+\text{W})+(v_2+\text{W}))=c((v_1+v_2)+\text{W})=(c(v_1+v_2))+\text{W}=(cv_1+cv_2)+\text{W}=c(v_1+\text{W})+c(v_2+\text{W})$.
  8. $(c_1+c_2)(v+\text{W})=((c_1+c_2)v)+\text{W}=(c_1v+c_2v)+\text{W}=(c_1v)+\text{W}+(c_2v)+\text{W}=c_1(v+\text{W})+c_2(v+\text{W})$.

So $S$, or $\text{V}/\text{W}$ is a vector space.

## P40 T1

a. If $S$ is a linearly dependent set, then each vector in $S$ is a linear combination of other vectors in S.

b. Any set containing the zero vector is linearly dependent.

c. The empty set is linearly dependent.

d. Subsets of linearly dependent sets are linearly dependent.

e. Subsets of linearly independent sets are linearly independent.

f. If $a_1x_1 + a_2x_2 + \cdots + a_nx_n = 0$ and $x_1, x_2,\cdots,x_n$ are linearly independent, then all the scalars $a_i$ are zero.

a. False. b. True. c. False. d. False. e. True. f. True.

## P40 T2

Determine whether the following sets are linearly dependent or linearly independent.

$$
\begin{aligned}
&\text{a. }
\left\{
\left(
\begin{matrix}
1 & -3
\\
-2 & 4
\end{matrix}
\right),
\left(
\begin{matrix}
-2 & 6
\\
4 & -8
\end{matrix}
\right)
\right\}
\text{ in M}_{2 \times 2}(R)
\\
&\text{c. }
\{
x^3+2x^2,-x^2+3x+1,x^3-x^2+2x-1
\}
\text{ in P}_3(R)
\end{aligned}
$$

---

a. Linearly dependent. c. Linearly independent.

## P41 T6

In $\text{M}_{m \times n}(F)$, let $E^{ij}$ denote the matrix whose only nonzero entry is 1 in the $i$th row and $j$th column. Prove that $\{E^{ij} : 1 \le i \le m, 1 \le j \le n\}$ is linearly independent.

---

We assume that there exists $\{a_{ij}\}$ that is not all zero, and it satisfy $\sum a_{ij}E^{ij}=0$. We have

$$
\sum a_{ij}E^{ij}=
\left[
\begin{matrix}
a_{11} & a_{12} & \cdots & a_{1n}
\\
a_{21} & a_{22} & \cdots & a_{2n}
\\
& & \cdots &
\\
a_{m1} & a_{m2} & \cdots & a_{mn}
\end{matrix}
\right],
$$

so where $a_{xy} \ne 0$, we get a contradiction that the matrix above $\ne 0$. So the set is linearly dependent.

## P42 T11

Let $S = {u_1, u_2,\cdots,u_n}$ be a linearly independent subset of a vector space $\text{V}$ over the field $Z_2$. How many vectors are there in $\text{span}(S)$? Justify your answer.

---

Since $S$ is a linearly independent subset, so for all $\{a_i\}$ satisfy $a_i \in Z_2$, $\sum a_iu_i$ is different with each other (otherwise we have $\sum a_iu_i=\sum b_iu_i$, and $\sum (a_i-b_i)u_i=0$, $\{a_i-b_i\} \ne 0$, which contradict to $S$ is a linearly independent set). So the $|\text{span}(S)|$ is the number of $\{a_i\}$, which is $2^n$.

## P42 T19

Prove that if $\{A_1, A_2,\cdots,A_k\}$ is a linearly independent subset of $\text{M}_{n \times n}(F)$, then $\{A^t_1, A^t_2,... ,A^t_k\}$ is also linearly independent.

---

If there exists $\{a_i\}$ which is not all zero, and $\sum a_iA^t_i=0$. We have $\sum a_iA^t_i=\sum (a_iA_i)^t=(\sum a_iA_i)^t=0$, which is $\sum a_iA_i=0^t=0$, contradicting to $\{A_1, A_2,\cdots,A_k\}$ is a linearly independent subset.

## P42 T20

Let $f, g \in \mathcal{F}(R, R)$ be the functions defined by $f(t) = e^{rt}$ and $g(t) = e^{st}$, where $r \ne s$. Prove that $f$ and $g$ are linearly independent in $\mathcal{F}(R, R)$.

---

If there exists $x, y \in R$ satisfying $x \ne 0 \lor y \ne 0$, $xf+yg=0$, which is $xe^{rt}+ye^{st}=0$ for all $t \in R$. When $t=0$, we have $x+y=0$, so $y=-x$. Then we can rewrite the condition as $x \ne 0$, $x(e^{rt}-e^{st})=0$ for all $t \in R$. Which is $e^{rt}-e^{st}=0$, $e^{rt}=e^{st}$ for all $t \in R$. When $t=1$, we have $e^r=e^s$, which contradict to $r \ne s$. So $f$ and $g$ are linearly independent.

## P54 T2

Determine which of the following sets are bases for $\text{R}^3$.

a. $\{(1, 0, −1),(2, 5, 1),(0, −4, 3)\}$

b. $\{(2, −4, 1),(0, 3, −1),(6, 0, −1)\}$

---

a. Consider the augmented matrix

$$
\left[
\begin{matrix}
1 & 2 & 0 & x
\\
0 & 5 & -4 & y
\\
-1 & 1 & 3 & z
\end{matrix}
\right].
$$

After solving it, we have

$$
\left[
\begin{matrix}
1 & 0 & 0 & \frac{19}{27}x-\frac{2}{9}y-\frac{8}{27}z
\\
0 & 1 & 0 & \frac{4}{27}x+\frac{1}{9}y+\frac{4}{27}z
\\
0 & 0 & 1 & \frac{5}{27}x-\frac{1}{9}y+\frac{5}{27}z
\end{matrix}
\right].
$$

So for every element $(x,y,z) \in \text{R}^3$, there is a unique linear combination of $\{(1, 0, −1),(2, 5, 1),(0, −4, 3)\}$ to form $(x,y,z)$. So $\{(1, 0, −1),(2, 5, 1),(0, −4, 3)\}$ is a base for $\text{R}^3$.

b. Consider the augmented matrix

$$
\left[
\begin{matrix}
2 & 0 & 6 & x
\\
-4 & 3 & 0 & y
\\
1 & -1 & -1 & z
\end{matrix}
\right].
$$

After solving it, we have

$$
\left[
\begin{matrix}
1 & 0 & 3 & -y-3z
\\
0 & 1 & 4 & -y-4z
\\
0 & 0 & 0 & x+2y+6z
\end{matrix}
\right].
$$

So for every element $(x,y,z) \in \text{R}^3$ satisfy $x+2y+6z \ne 0$, there is no linear combination of $\{(2, −4, 1),(0, 3, −1),(6, 0, −1)\}$ to form $(x,y,z)$. So $\{(2, −4, 1),(0, 3, −1),(6, 0, −1)\}$ is not a base for $\text{R}^3$.

## P54 T5

Is $\{(1, 4, −6),(1, 5, 8),(2, 1, 1),(0, 1, 0)\}$ a linearly independent subset of $\text{R}^3$? Justify your answer.

---

Consider the augmented matrix

$$
\left[
\begin{matrix}
1 & 1 & 2 & 0 & 0
\\
4 & 5 & 1 & 1 & 0
\\
-6 & 8 & 1 & 0 & 0
\end{matrix}
\right].
$$

After solving it, we have

$$
\left[
\begin{matrix}
1 & 0 & 0 & -\frac{15}{111} & 0
\\
0 & 1 & 0 & -\frac{13}{111} & 0
\\
0 & 0 & 1 & \frac{14}{111} & 0
\end{matrix}
\right].
$$

So the system is consistent, and there exists $x, y, z, w$ which not all zero, and $x(1, 4, −6)+y(1, 5, 8)+z(2, 1, 1)+w(0, 1, 0)=(0,0,0)$. So the set is not linearly independent.

## Extra

Consider a system of linear questions

$$
\left\{
\begin{aligned}
&(a_1+b)x_1+a_2x_2+\cdots+a_nx_n=0
\\
&a_1x_1+(a_2+b)x_2+\cdots+a_nx_n=0
\\
&\cdots
\\
&a_1x_1+a_2x_2+\cdots+(a_n+b)x_n=0
\end{aligned}
\right.,
$$

where $\sum a_i \ne 0$.

Determine the relationship between $a_1,a_2,⋯,a_n$ and $b$ such that

a. This linear system has only a zero solution.

b. This system has nonzero solutions. In this case, determine a solution set.

---

Consider the augmented matrix

$$
\left[
\begin{matrix}
a_1+b & a_2 & \cdots & a_n & 0
\\
a_1 & a_2+b & \cdots & a_n & 0
\\
\cdots
\\
a_1 & a_2 & \cdots & a_n+b & 0
\end{matrix}
\right].
$$

Add -1 times of row 1 to row $2, 3, \cdots, n$, we have

$$
\left[
\begin{matrix}
a_1+b & a_2 & \cdots & a_n & 0
\\
-b & b & \cdots & 0 & 0
\\
\cdots
\\
-b & 0 & \cdots & b & 0
\end{matrix}
\right].
$$

Let us assume $b \ne 0$, otherwise we will consider below. Multiple row $2, 3, \cdots, n$ by $\frac{1}{b}$, we have

$$
\left[
\begin{matrix}
a_1+b & a_2 & \cdots & a_n & 0
\\
-1 & 1 & \cdots & 0 & 0
\\
\cdots
\\
-1 & 0 & \cdots & 1 & 0
\end{matrix}
\right].
$$

Add $-a_2$ times of row 2, $-a_3$ times of row 3, $\cdots$, $-a_n$ times of row $n$ to row 1, we have

$$
\left[
\begin{matrix}
b+\sum a_i & 0 & \cdots & 0 & 0
\\
-1 & 1 & \cdots & 0 & 0
\\
\cdots
\\
-1 & 0 & \cdots & 1 & 0
\end{matrix}
\right].
$$

Let us assume $b+\sum a_i \ne 0$, otherwise we will consider below. Multiple row 1 by $\frac{1}{b+\sum a_i}$, we have

$$
\left[
\begin{matrix}
1 & 0 & \cdots & 0 & 0
\\
-1 & 1 & \cdots & 0 & 0
\\
\cdots
\\
-1 & 0 & \cdots & 1 & 0
\end{matrix}
\right].
$$

Add row 1 to row $2, 3, \cdots, n$, we have

$$
\left[
\begin{matrix}
1 & 0 & \cdots & 0 & 0
\\
0 & 1 & \cdots & 0 & 0
\\
\cdots
\\
0 & 0 & \cdots & 1 & 0
\end{matrix}
\right].
$$

Which only have a zero solution.

So when $b \ne 0$ and $b+\sum a_i \ne 0$, the system only have a zero solution.

When $b=0$, there is exactly only one constraint $\sum a_ix_i=0$. Let $k$ be the smallest position that $a_k \ne 0$, since $\sum a_i \ne 0$, the position is exist. We have $x_i \space (i \ne k)$ is free, and $x_k = \frac{-a_{k+1}x_{k+1}-a_{k+2}x_{k+2}-\cdots-a_nx_n}{a_k}$. So when $n>1$, the system have nonzero solutions; when $n=1$, the system only have a zero solution.

When $b \ne 0$ and $b+\sum a_i = 0$, we have $x_n$ is free, and $x_i=x_n \space (i \ne n)$. So when $n>1$, the system have nonzero solutions; when $n=1$, the system only have a zero solution.

In summary, when $n=1$, the system only have a zero solution; otherwise when $b=0$, the system have nonzero solutions which $x_i \space (i \ne k)$ is free, and $x_k = \frac{-a_{k+1}x_{k+1}-a_{k+2}x_{k+2}-\cdots-a_nx_n}{a_k}$; otherwise when $b+\sum a_i=0$, the system have nonzero solutions which $x_n$ is free, and $x_i=x_n \space (i \ne n)$.
