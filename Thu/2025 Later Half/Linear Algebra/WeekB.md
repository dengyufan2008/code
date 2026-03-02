# WeekB Homework (Textbook)

By Deng Yufan.

## P58 T35

Let $W$ be a subspace of a finite-dimensional vector space $V$, and consider the basis $\{u_1, u_2, \cdots, u_k\}$ for $W$. Let $\{u_1, u_2, \cdots, u_k, u_{k+1}, \cdots, u_n\}$ be an extension of this basis to a basis for $V$.

a. Prove that $\{u_{k+1} + W, u_{k+2} + W, \cdots, u_n + W\}$ is a basis for $V/W$.

b. Derive a formula relating $\dim(V)$, $\dim(W)$, and $\dim(V/W)$.

---

a. We first prove $\{u_{k+1} + W, u_{k+2} + W, \cdots, u_n + W\}$ is independent. For all $a_i$ that $\sum_{i=k+1}^n a_i(u_i+W)=0$, we have $0=(\sum_{i=k+1}^n a_iu_i)+W$, which iff $\sum_{i=k+1}^n a_iu_i \in W$. Since $\{u_1, u_2, \cdots, u_k, u_{k+1}, \cdots, u_n\}$ is independent, so $\sum_{i=k+1}^n a_iu_i \in W$ is to say $\sum_{i=k+1}^n a_iu_i=0$, thus $a_i=0$.

Then we prove $\text{span}\{u_{k+1} + W, u_{k+2} + W, \cdots, u_n + W\} = V/W$. For all $x \in V$, we have $a_i$ that $x=\sum_{i=1}^n a_iu_i$. Consider $y=\sum_{i=k+1}^n a_i(u_i+W)=(\sum_{i=k+1}^n a_iu_i)+W$, we have $x+W=y+W$ iff $\sum_{i=1}^k a_iu_i \in W$, obviously true. So $x+W \in \text{span}\{u_{k+1} + W, u_{k+2} + W, \cdots, u_n + W\}$.

b. Obviously $\dim(V)=\dim(W)+\dim(V/W)$.

## P326 T32

Prove if the characteristic polynomial of $T$ splits, then there is an ordered basis $\beta$ for $V$ such that $[T]_\beta$ is an upper triangular matrix. 

---

Induction $n=\dim(V)$. When $n=1$ any matrix is upper triangle. We assume $n-1$ and prove $n$.

Since $T$ splits, so $T$ has a eigenvalue $\lambda$, then $T$ has $v$ that $Tv=\lambda v$. Let $W=\text{span}\{v\}$. Obviously $W$ is $T$-invariant, then we have $\overline T:V/W \rightarrow V/W$.

Easy to see $\det(\overline T-tI)$ divide $\det(T-tI)$ and $\dim(V/W)=n-1$ using P58 T35 a. Then by induction assumption, there is $\beta'$ that $[\overline T]_{\beta'}$ upper triangle. Consider $\beta=\{\beta'_1, \cdots, \beta'_{n-1}, v\}$, $[T]_\beta$ upper triangle.

## P352 T1

a. The Gram–Schmidt orthogonalization process allows us to construct an orthonormal set from an arbitrary set of vectors.

b. Every nonzero finite-dimensional inner product space has an orthonormal basis.

c. The orthogonal complement of any set is a subspace.

d. If $\{v_1, v_2, \cdots, v_n\}$ is a basis for an inner product space $V$, then for any $x \in V$ the scalars $\langle x, v_i \rangle$ are the Fourier coefficients of $x$.

e. An orthonormal basis must be an ordered basis.

f. Every orthogonal set is linearly independent.

g. Every orthonormal set is linearly independent.

a. False. b. True. c. True. d. False. e. True. f. True. g. True.

## P353 T2

In each part, apply the Gram–Schmidt process to the given subset $S$ of the inner product space $V$ to obtain an orthogonal basis for $\text{span}(S)$. Then normalize the vectors in this basis to obtain an orthonormal basis $\beta$ for $\text{span}(S)$, and compute the Fourier coefficients of the given vector relative to $\beta$. Finally, use Theorem 6.5 to verify your result.

a. $V = R^3$, $S = \{(1, 0, 1),(0, 1, 1),(1, 3, 3)\}$, and $x = (1, 1, 2)$.

g. $V=M_{2 \times 2}(R)$, $S=\left\{\left[\begin{matrix}3 & 5 \\ -1 & 1\end{matrix}\right], \left[\begin{matrix}-1 & 9 \\ 5 & -1\end{matrix}\right], \left[\begin{matrix}7 & -17 \\ 2 & -6\end{matrix}\right]\right\}$, and $A=\left[\begin{matrix}-1 & 27 \\ -4 & 8\end{matrix}\right]$.

i. $V=\text{span}(S)$ with $\langle f, g \rangle = \int_0^\pi f(t)g(t) \text{d}t$, $S=\{\sin t, \cos t, 1, t\}$, and $h(t)=2t+1$.

---

a. We have $\beta' = \{(1,0,1),(-\frac{1}{2},1,\frac{1}{2}),(\frac{1}{3},\frac{1}{3},-\frac{1}{3})\}$. $\beta=\{(\frac{1}{\sqrt 2},0,\frac{1}{\sqrt 2}),(-\frac{1}{\sqrt 6},\frac{2}{\sqrt 6},\frac{1}{\sqrt 6}),(\frac{1}{\sqrt 3},\frac{1}{\sqrt 3},-\frac{1}{\sqrt 3})\}$. Fourier coefficients are $\frac{3}{\sqrt 2}$, $\frac{3}{\sqrt 6}$, $0$. Obviously $(1,1,2)=\frac{3}{\sqrt 2}(\frac{1}{\sqrt 2},0,\frac{1}{\sqrt 2})+\frac{3}{\sqrt 6}(-\frac{1}{\sqrt 6},\frac{2}{\sqrt 6},\frac{1}{\sqrt 6})$.

g. We have $\beta'=\left\{\left[\begin{matrix}3 & 5 \\ -1 & 1\end{matrix}\right], \left[\begin{matrix}-4 & 4 \\ 6 & -2\end{matrix}\right],\left[\begin{matrix}9 & -3 \\ 6 & -6\end{matrix}\right]\right\}$, $\beta=\left\{\left[\begin{matrix}\frac{1}{2} & \frac{5}{6} \\ -\frac{1}{6} & \frac{1}{6}\end{matrix}\right], \left[\begin{matrix}-\frac{2}{3\sqrt 2} & \frac{2}{3 \sqrt 2} \\ \frac{1}{\sqrt 2} & -\frac{1}{3 \sqrt 2}\end{matrix}\right], \left[\begin{matrix}\frac{1}{\sqrt 2} & -\frac{1}{3 \sqrt 2} \\ \frac{2}{3 \sqrt 2} & -\frac{2}{3 \sqrt 2}\end{matrix}\right]\right\}$. Fourier coefficients are $24$, $\frac{12}{\sqrt 2}$, $-\frac{18}{\sqrt 2}$. Obviously $\left[\begin{matrix}-1 & 27 \\ -4 & 8\end{matrix}\right]=24\left[\begin{matrix}\frac{1}{2} & \frac{5}{6} \\ -\frac{1}{6} & \frac{1}{6}\end{matrix}\right]+\frac{12}{\sqrt 2}\left[\begin{matrix}-\frac{2}{3\sqrt 2} & \frac{2}{3 \sqrt 2} \\ \frac{1}{\sqrt 2} & -\frac{1}{3 \sqrt 2}\end{matrix}\right]-\frac{18}{\sqrt 2}\left[\begin{matrix}\frac{1}{\sqrt 2} & -\frac{1}{3 \sqrt 2} \\ \frac{2}{3 \sqrt 2} & -\frac{2}{3 \sqrt 2}\end{matrix}\right]$.

i. We have $\beta'=\{\sin t, \cos t, 1-\frac{4}{\pi}\sin t, t+\frac{4}{\pi}\cos-\frac{\pi}{2}\}$, $\beta=\{\sqrt{\frac{2}{\pi}}\sin t, \sqrt{\frac{2}{\pi}}\cos t,\sqrt{\frac{\pi}{\pi^2-8}}(1-\frac{4}{\pi}\sin t), \sqrt{\frac{12\pi}{\pi^4-96}}(t+\frac{4}{\pi}\cos-\frac{\pi}{2})\}$. Fourier coefficients are $\sqrt{\frac{2}{\pi}}(2\pi+2)$, $-\sqrt{\frac{2}{\pi}}4$, $\sqrt{\frac{\pi}{\pi^2-8}}(\pi^2+\pi-8-\frac{4}{\pi})$, $\sqrt{\frac{\pi^4-96}{12\pi}}2$. Easy to verify thm 6.5.

## P354 T4

Let $S = \{(1, 0, i),(1, 2, 1)\}$ in $C^3$. Compute $S^\perp$.

---

We have $0 = \langle (a, b, c), (1, 0, i) \rangle = a-ic$, $0=\langle (a, b, c), (1, 2, 1) \rangle = a+2b+c$, so $a=ic$, $b=-\frac{1+i}{2}c$, then $S^\perp=\{k(-2i, 1+i, -2) \mid k \in C\}$.

## P354 T10

def. Let $V$ be a vector space and $W_1$ and $W_2$ be subspaces of $V$ such that $V = W_1 \oplus W_2$. A function $T: V \rightarrow V$ is called the projection on $W_1$ along $W_2$ if, for $x = x_1 + x_2$ with $x_1 \in W_1$ and $x_2 \in W_2$, we have $T(x) = x_1$.

Let $W$ be a finite-dimensional subspace of an inner product space $V$. Prove that there exists a projection $T$ on $W$ along $W^\perp$ that satisfies $N(T) = W^\perp$. In addition, prove that $\lVert T(x) \rVert \le \lVert x \rVert$ for all $x \in V$.

---

Obviously $W \cap W^\perp = \{0\}$, otherwise we have $\langle x, x \rangle = 0$ and $x \ne 0$. Let $\{\beta_1, \beta_2, \cdots, \beta_n\}$ be a orthonormal basis of $W$.

For all $x \in V$, let $u=\sum_{i=1}^n \langle x, \beta_i \rangle \beta_i, v=x-u$, then $u \in W$. We have $\langle v, \beta_i \rangle = \langle x, \beta_i \rangle - \sum_{j=1}^n \langle x, \beta_j \rangle \langle \beta_j, \beta_i \rangle=0$, so $v \in W^\perp$, then $V=W+W^\perp$. So $V=W \oplus W^\perp$, thus $T$ can be projection on $W$ along $W^\perp$. When $u=0$, we have $\langle x, \beta_i \rangle = 0$, then $x \in W^\perp$.

We have $\lVert T(x) \rVert^2 + \lVert x-T(x) \rVert^2 = \lVert x \rVert$, so $\lVert T(x) \rVert \le \lVert x \rVert$.

## P354 T11

Let $A$ be an $n \times n$ matrix with complex entries. Prove that $AA^* = I$ if and only if the rows of $A$ form an orthonormal basis for $C^n$.

---

We have $(AA^*)_{ij}=\sum_{k=1}^n A_{ik}\overline{A_{jk}}=\langle A_i, A_j \rangle$, where $A_i$ is $i$th row of $A$.

So $AA^*=I$ iff $\langle A_i, A_j \rangle = \delta_{ij}$ iff $\{A_i\}$ is orthonormal iff $\{A_i\}$ is orthonormal basis of $C^n$.

## P354 T12

Prove that for any matrix $A \in M_{m \times n}(F)$, $R(L_{A^*})^\perp = N(L_A)$.

---

For all $x \in F^n$, $x \in R(L_{A^*})^\perp$ iff $\langle x, y \rangle=0$ for all $y \in R(L_{A^*})$, iff $\langle x, A^*y \rangle=0$ for all $y \in F^m$, iff $\langle Ax, y \rangle = 0$ for all $y \in F^m$, iff $Ax=0$, iff $x \in N(L_A)$. So $R(L_{A^*})^\perp = N(L_A)$.

## P355 T13

Let $V$ be an inner product space, $S$ and $S_0$ be subsets of $V$, and $W$ be a finite-dimensional subspace of $V$. Prove the following results.

a. $S_0 \subseteq S$ implies that $S^\perp \subseteq S_0^\perp$.

b. $S \subseteq \text{span}(S) \subseteq (S^\perp)^\perp$.

c. $W=(W^\perp)^\perp$.

d. $V=W \oplus W^\perp$.

---

d. Already proved in T10.

a. Assume $S_0 \subseteq S$. For all $x \in S^\perp$, we have $\langle x, y \rangle = 0$ for all $y \in S$, then $\langle x, y \rangle = 0$ for all $y \in S_0$, thus $x \in S_0^\perp$.

b. For all $x \in S$ and $y \in S^\perp$, we have $\langle x, y \rangle = \overline{\langle y, x \rangle} = 0$, then $x \in (S^\perp)^\perp$, so $S \subseteq (S^\perp)^\perp$. Since $(S^\perp)^\perp$ is a subspace of $V$, then $\text{span}(S) \subseteq (S^\perp)^\perp$.

c. We have $W \subseteq (W^\perp)^\perp$ by b. Let $\{\beta_1, \beta_2, \cdots, \beta_n\}$ be orthonormal basis of $W$. For all $x \in (W^\perp)^\perp$, let $y=\sum_{i=1}^n \langle x, \beta_i \rangle \beta_i \in W$. For all $z \in V$, write $z$ into $u+v$ that $u \in W$, $v \in W^\perp$. Then $\langle x-y, z \rangle = \langle x-y, u \rangle + \langle x, v \rangle - \langle y, v \rangle = \langle x-y, u \rangle$. Write $u$ as $\sum_{i=1}^n a_i\beta_i$, we have $\langle x-y, z \rangle = \sum_{i=1}^n \overline{a_i}\langle x, \beta_i \rangle - \sum_{i=1}^n \langle x, \beta_i \rangle \langle \beta_i, u \rangle = \sum_{i=1}^n \overline{a_i}\langle x, \beta_i \rangle - \sum_{i=1}^n \langle x, \beta_i \rangle \sum_{j=1}^n \overline{a_j} \langle \beta_i, \beta_j \rangle = 0$. So $x=y$, thus $x \in W$, thus $W=(W^\perp)^\perp$.

## P355 T16

a. Let $V$ be an inner product space, and let $S = \{v_1, v_2, \cdots, v_n\}$ be an orthonormal subset of $V$. Prove that for any $x \in V$ we have $\lVert x \rVert^2 \ge \sum_{i=1}^n |\langle x, v_i \rangle|^2$.

b. Prove equal iff $x \in \text{span}(S)$.

---

Let $W=\text{span}(S)$. For all $x \in V$, we write $x$ into $u+v$, where $u \in W$, $v \in W^\perp$. And we have $u= \sum_{i=1}^n \langle x, v_i \rangle v_i$. We have $\lVert x \rVert^2 \ge \lVert u \rVert^2 = \langle u, u \rangle = \langle u, u \rangle + \langle v, u \rangle = \langle x, u \rangle = \sum_{i=1}^n \overline{\langle x, v_i \rangle} \langle x, v_i \rangle = \sum_{i=1}^n |\langle x, v_i \rangle|^2$. Obviously equal iff $v = 0$, that is $x \in W$.

## P356 T22

Let $V = C([0, 1])$ with the inner product $\langle f, g \rangle = \int_0^1 f(t)g(t) \text{d}t$. Let $W$ be the subspace spanned by the linearly independent set $\{t, \sqrt t\}$.

a. Find an orthonormal basis for $W$.

b. Let $h(t) = t^2$. Use the orthonormal basis obtained in (a) to obtain the "best" (closest) approximation of $h$ in $W$.

---

a. Using Gram–Schmidt orthogonalization, we have $\beta'=\{t, \sqrt t - \frac{6}{5}t\}$, and $\beta=\{\sqrt 3 t, 5\sqrt{2t}-6\sqrt 2 t\}$.

b. We have $\langle h, \beta_1 \rangle = \frac{\sqrt 3}{4}$, $\langle h, \beta_2 \rangle = -\frac{\sqrt 2}{14}$, then $\frac{45}{28}t-\frac{5}{7} \sqrt t$ is best.

## P356 T23

Let $V$ be the vector space defined in Example 5 of Section 1.2, the space of all sequences $\sigma$ in $F$ (where $F = R$ or $F = C$) such that $\sigma(n) \ne 0$ for only finitely many positive integers $n$. For $\sigma, \mu \in V$, we define $\langle \sigma, \mu \rangle = \sum_{n=1}^{+\infty} \sigma(n) \overline{\mu(n)}$. Since all but a finite number of terms of the series are zero, the series converges.

a. Prove that $\langle \cdot, \cdot \rangle$ is an inner product on $V$, and hence $V$ is an inner product space.

b. For each positive integer $n$, let $e_n$ be the sequence defined by $e_n(k) = \delta_{n,k}$. Prove that $\{e_1, e_2,\cdots\}$ is an orthonormal basis for $V$.

c. Let $\sigma_n = e_1 + e_n$ and $W = \text{span}\{\sigma_n \mid n \ge 2\}$.

i. Prove that $e_1 \notin W$, so $W \ne V$.

ii. Prove that $W^\perp = \{0\}$, and conclude that $W \ne (W^\perp)^\perp$.

---

a. We have $\langle c\sigma_1+\sigma_2, \mu \rangle = \sum_{n=1}^{+\infty} (c\sigma_1(n)+\sigma_2(n))\overline{\mu(n)} = c\sum_{n=1}^{+\infty} \sigma_1(n)\overline{\mu(n)} + \sum_{n=1}^{+\infty} \sigma_2(n)\overline{\mu(n)}=c\langle \sigma_1, \mu \rangle + \langle \sigma_2, \mu \rangle$.

We have $\langle \sigma, \mu \rangle = \sum_{n=1}^{+\infty} \sigma(n)\overline{\mu(n)} = \overline{\sum_{n=1}^{\infty} \mu(n)\overline{\sigma(n)}} = \overline{\langle \mu, \sigma \rangle}$.

We have $\langle \sigma, \sigma \rangle = \sum_{n=1}^{+\infty} |\sigma(n)|^2 > 0$ if $\sigma \ne 0$.

b. For all $\sigma \in V$, let $n$ satisfy that $\sigma(i)=0$ for $i>n$, then $\sigma=\sum_{i=1}^n \sigma(i)e_i$. And for all $a_1, a_2, \cdots, a_n$, we have $\sum_{i=1}^n a_ie_i = \sigma$, where $\sigma(i)=a_i \space (i \le n)$ and $\sigma(i)=0 \space (i>n)$. So $\text{span}(e_1, e_2, \cdots)=V$.

For $i \ne j$, we have $\langle e_i, e_j \rangle = \sum_{k=1}^{+\infty} [k=i][k=j] = 0$. For $i = j$, we have $\langle e_i, e_j \rangle = 1$ likely.

c. i. For all $a_2, \cdots, a_n$, we have $\sum_{i=2}^n a_i\sigma_i = (\sum_{i=2}^n a_i)e_1 + \sum_{i=2}^n a_ie_i$. So if $e_1 = \sum_{i=2}^n a_i\sigma_i$, then $\sum_{i=2}^n a_i = 1$ but $a_i = 0$, contradiction.

c. ii. If $\mu \in W^\perp$, let $n$ that $\mu(i)=0$ for $i \ge n$. We have $0 = \langle \mu, \sigma_n \rangle = \mu(1)$. Then for all $1 < i < n$, we have $0 = \langle \mu, \sigma_i \rangle = \mu(1)+\mu(i)$, then $\mu(i)=0$. So $\mu=0$.

## P365 T1

a. Every linear operator has an adjoint.

b. Every linear operator on $V$ has the form $x \rightarrow \langle x, y \rangle$ for some $y \in V$.

c. For every linear operator $T$ on $V$ and every ordered basis $\beta$ for $V$, we have $[T^*]_\beta = ([T]_\beta)^*$.

d. The adjoint of a linear operator is unique.

e. For any linear operators $T$ and $U$ and scalars $a$ and $b$, $(aT + bU)^* = aT^* + bU^*$.

f. For any $n \times n$ matrix $A$, we have $(L_A)^* = L_{A^*}$.

g. For any linear operator $T$, we have $(T^*)^* = T$.

a. False. b. False. c. False. d. True. e. True. f. True. g. True.

## P365 T2

For each of the following inner product spaces $V$ (over $F$) and linear transformations $g: V \rightarrow F$, find a vector $y$ such that $g(x) = \langle x, y \rangle$ for all $x \in V$.

a. $V=R^3$, $g(a_1, a_2, a_3)=a_1-2a_2+4a_3$.

---

a. Let $\beta$ be the standard orthonormal basis of $R^3$, then $y=\sum_{i=1}^3 \overline{g(\beta_i)} \beta_i=(1,-2,4)$.

## P366 T3

For each of the following inner product spaces $V$ and linear operators $T$ on $V$, evaluate $T^*$ at the given vector in $V$.

b. $V=C^2$, $T(z_1, z_2)=(2z_1+iz_2, (1-i)z_1)$, $x=(3-i,1+2i)$.

---

b. Let $\beta$ be the standard orthonormal basis of $C^2$, then $[T]_\beta=\left[\begin{matrix}2 & i \\ 1-i & 0\end{matrix}\right]$, then $[T^*]_\beta=\left[\begin{matrix}2 & 1+i \\ -i & 0\end{matrix}\right]$, $[T^*(x)]_\beta=\left[\begin{matrix}5+i \\ -1-3i \end{matrix}\right]$, $T^*(x)=(5+i,-1-3i)$.

## P366 T9

Prove that if $V = W \oplus W^\perp$ and $T$ is the projection on $W$ along $W^\perp$, then $T = T^*$.

---

For all $x \in V$, write $x$ as $u+v$, where $u \in W$, $v \in W^\perp$. We have $\langle T(x), x \rangle = \langle u, u+v \rangle = \langle u, u \rangle = \langle u+v, u \rangle = \langle x, T(x) \rangle$. So $T=T^*$.

## P367 T15

def. Let $T: V \rightarrow W$ be a linear transformation, where $V$ and $W$ are finite-dimensional inner product spaces with inner products $\langle \cdot, \cdot \rangle _1$ and $\langle \cdot, \cdot \rangle _2$, respectively. A function $T^* : W \rightarrow V$ is called an adjoint of $T$ if $\langle T(x), y \rangle _2 = \langle x,T^*(y) \rangle _1$ for all $x \in V$ and $y \in W$.

a. There is a unique adjoint $T^*$ of $T$, and $T^*$ is linear.

b. If $\beta$ and $\gamma$ are orthonormal bases for $V$ and $W$, respectively, then $[T^*]_\gamma^\beta = ([T]_\beta^\gamma)^*$.

c. $\text{rank}(T^*)=\text{rank}(T)$.

d. $\langle T^*(x), y \rangle _1 = \langle x, T(y) \rangle _2$ for all $x \in W$ and $y \in V$.

e. For all $x \in V$, $T^*T(x) = 0$ if and only if $T(x) = 0$.

---

a. For all $y \in W$, let $g(x)=\langle T(x), y \rangle _2$, then exists unique $y' \in V$ that $g(x) = \langle x, y' \rangle _1$. Let $T^*(y)=y'$, then $\langle T(x), y \rangle _2 = \langle x, T^*(y) \rangle _1$.

For all $c \in F$, $x, y \in W$, $z \in V$, we have $\langle z, T^*(cx+y) \rangle _1 = \langle T(z), cx+y \rangle _2 = \overline c \langle T(z), x \rangle _2 + \langle T(z), y \rangle _2 = \overline c \langle z, T^*(x) \rangle _1 + \langle z, T^*(y) \rangle _1 = \langle z, cT^*(x)+T^*(y) \rangle _1$. So $T^*(cx+y)=cT^*(x)+T^*(y)$.

b. We have ${[T^*]_\gamma^\beta}^*_{ij} = \overline {\langle T^*(\gamma_i), \beta_j \rangle _1} = \langle \beta_j, T^*(\gamma_i) \rangle _1 = \langle T(\beta_j), \gamma_i \rangle _2 = ([T]_\beta^\gamma)_{ij}$. So $[T^*]_\gamma^\beta = ([T]_\beta^\gamma)^*$.

c. We have $\text{rank}(T^*) = \text{rank}([T^*]_\gamma^\beta) = \text{rank}({[T]_\beta^\gamma}^*) = \text{rank}([T]_\beta^\gamma) = \text{rank}(T)$.

d. We have $\langle T^*(x), y \rangle _1 = \overline {\langle y, T^*(x) \rangle _1} = \overline {\langle T(y), x \rangle _2} = \langle x, T(y) \rangle _2$.

e. If: Obvious. Only if: We have $0 = \langle T^*T(x), x \rangle _1 = \langle T(x), T(x) \rangle _2$, thus $T(x)=0$.

## P368 T21

In physics, Hooke's law states that (within certain limits) there is a linear relationship between the length $x$ of a spring and the force $y$ applied to (or exerted by) the spring. That is, $y = cx + d$, where $c$ is called the spring constant. Use the following data to estimate the spring constant (the length is given in inches and the force is given in pounds).

| Length (x) | Force (y) |
| :---: | :---: |
| 3.5 | 1.0 |
| 4.0 | 2.2 |
| 4.5 | 2.8 |
| 5.0 | 4.3 |

---

Let $A=\left[\begin{matrix}3.5 & 1 \\ 4.0 & 1 \\ 4.5 & 1 \\ 5.0 & 1\end{matrix}\right]$, $x=\left[\begin{matrix}c \\ d\end{matrix}\right]$, $y=\left[\begin{matrix}1.0 \\ 2.2 \\ 2.8 \\ 4.3\end{matrix}\right]$, then we need to minimize $\lVert y-Ax \rVert$.

Solve $A^*Ax=A^*y$, which is $\left[\begin{matrix}73.5 & 17 \\ 17 & 4\end{matrix}\right]x = \left[\begin{matrix}46.4 \\ 10.3\end{matrix}\right]$, we have $x=\left[\begin{matrix}2.1 \\ -6.35\end{matrix}\right]$. So $c=2.1$.

## P368 T23

Consider the problem of finding the least squares line $y = ct + d$ corresponding to the $m$ observations $(t_1, y_1),(t_2, y_2),\cdots,(t_m, y_m)$.

a. Show that the equation $(A^*A)x_0 = A^*y$ of Theorem 6.12 takes the form of the normal equations: $(\sum_{i=1}^m t_i^2)c+(\sum_{i=1}^m t_i)d=\sum_{i=1}^m t_iy_i$ and $(\sum_{i=1}^m t_i)c+md=\sum_{i=1}^m y_i$.

These equations may also be obtained from the error $E$ by setting the partial derivatives of $E$ with respect to both $c$ and $d$ equal to zero.

---

a. Let $A=\left[\begin{matrix} t_1 & 1 \\ \vdots & \vdots \\ t_m & 1\end{matrix}\right]$, $x = \left[\begin{matrix}c \\ d\end{matrix}\right]$, $y=\left[\begin{matrix}y_1 \\ \vdots \\ y_m\end{matrix}\right]$, then we need minimize $\lVert y-Ax \rVert$.

We have $x$ satisfy $A^*Ax_0=A^*y$, and $A^*A=\left[\begin{matrix}\sum_{i=1}^m t_i^2 & \sum_{i=1}^m t_i \\ \sum_{i=1}^m t_i & m\end{matrix}\right]$, $A^*y=\left[\begin{matrix}\sum_{i=1}^m t_iy_i \\ \sum_{i=1}^m y_i\end{matrix}\right]$. So the two equation are hold.

## P369 T24

Let $V$ and $\{e_1, e_2,\cdots\}$ be defined as in P356 T23. Define $T: V \rightarrow V$ by $T(\sigma)(k)=\sum_{i=k}^{+\infty} \sigma(i)$.

a. Prove that $T$ is a linear operator on $V$.

b. Prove that for any positive integer $n$, $T(e_n) = \sum_{i=1}^n e_i$.

c. Prove that $T$ has no adjoint.

---

a. We have $T(c \sigma + \mu)(k)=\sum_{i=k}^{+\infty} c\sigma(i)+\mu(i)=cT(\sigma)(k)+T(\mu)(k)$.

b. We have $T(e_n)(i)=\sum_{j=i}^{+\infty} e_n(j)=\sum_{j=i}^{+\infty} [j=n] = [i \le n]$, so $T(e_n)=\sum_{i=1}^n e_i$.

c. If $T$ has adjoint. For all $n$, for all $m \ge n$, we have $\langle T(e_m), e_n \rangle = \langle \sum_{i=1}^m e_i, e_n \rangle = 1$, so $\langle T^*(e_n), e_m \rangle = \langle e_n, T(e_m) \rangle = 1$, thus $T^*(e_n)(m)=1$. So $T^*(e_n)$ have infinite $m$ that $T^*(e_n)(m)=1 \ne 0$, $T^*(e_n) \notin V$, contradiction.
