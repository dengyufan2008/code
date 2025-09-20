# Week1 Homework

By Deng Yufan.

## P10 T8

Solve the augmented matrix
$$
\left[
\begin{matrix}
1 & -5 & 4 & 0 & 0
\\
0 & 1 & 0 & 1 & 0
\\
0 & 0 & 3 & 0 & 0
\\
0 & 0 & 0 & 2 & 0
\end{matrix}
\right].
$$

---

Divide row 3 by 3, we have
$$
\left[
\begin{matrix}
1 & -5 & 4 & 0 & 0
\\
0 & 1 & 0 & 1 & 0
\\
0 & 0 & 1 & 0 & 0
\\
0 & 0 & 0 & 2 & 0
\end{matrix}
\right].
$$

Divide row 4 by 2, we have
$$
\left[
\begin{matrix}
1 & -5 & 4 & 0 & 0
\\
0 & 1 & 0 & 1 & 0
\\
0 & 0 & 1 & 0 & 0
\\
0 & 0 & 0 & 1 & 0
\end{matrix}
\right].
$$

Add 5 times of row 2 to row 1, we have
$$
\left[
\begin{matrix}
1 & 0 & 4 & 5 & 0
\\
0 & 1 & 0 & 1 & 0
\\
0 & 0 & 1 & 0 & 0
\\
0 & 0 & 0 & 1 & 0
\end{matrix}
\right].
$$

Add -4 times of row 3 to row 1, we have
$$
\left[
\begin{matrix}
1 & 0 & 0 & 5 & 0
\\
0 & 1 & 0 & 1 & 0
\\
0 & 0 & 1 & 0 & 0
\\
0 & 0 & 0 & 1 & 0
\end{matrix}
\right].
$$

Add -5 times of row 4 to row 1, we have
$$
\left[
\begin{matrix}
1 & 0 & 0 & 0 & 0
\\
0 & 1 & 0 & 1 & 0
\\
0 & 0 & 1 & 0 & 0
\\
0 & 0 & 0 & 1 & 0
\end{matrix}
\right].
$$

Add -1 times of row 4 to row 2, we have
$$
\left[
\begin{matrix}
1 & 0 & 0 & 0 & 0
\\
0 & 1 & 0 & 0 & 0
\\
0 & 0 & 1 & 0 & 0
\\
0 & 0 & 0 & 1 & 0
\end{matrix}
\right].
$$

In the end, the solution for this linear equation system is $x_1=x_2=x_3=x_4=0$.

## P10 T13

Solve the system
$$
\left\{
\begin{aligned}
&& x_2 &+& 5x_3 &=& -4
\\
x_1 &+& 4x_2 &+& 3x_3 &=& -2
\\
2x_1 &+& 7x_2 &+& x_3 &=& -2
\end{aligned}
\right.
$$

---

Transform the system into augmented matrix, we have
$$
\left[
\begin{matrix}
0 & 1 & 5 & -4
\\
1 & 4 & 3 & -2
\\
2 & 7 & 1 & -2
\end{matrix}
\right].
$$

Swap row 1 and row 2, we have
$$
\left[
\begin{matrix}
1 & 4 & 3 & -2
\\
0 & 1 & 5 & -4
\\
2 & 7 & 1 & -2
\end{matrix}
\right].
$$

Add -2 times of row 1 to row 3, we have
$$
\left[
\begin{matrix}
1 & 4 & 3 & -2
\\
0 & 1 & 5 & -4
\\
0 & -1 & -5 & 2
\end{matrix}
\right].
$$

Add row 2 to row 3, we have
$$
\left[
\begin{matrix}
1 & 4 & 3 & -2
\\
0 & 1 & 5 & -4
\\
0 & 0 & 0 & -2
\end{matrix}
\right].
$$

Notice that we have column 4 is a pivot column, so the system is inconsistent. In other words, the system have no solution.

## P11 T24

a. Two matrices are row equivalent if they have the same number of rows.

b. Elementary row operations on an augmented matrix never change the solution set of the associated linear system.

c. Two equivalent linear systems can have different solution sets.

d. A consistent system of linear equations has one or more solutions.

a. False. b. True. c. False. d.True.

## P21 T1

<!--
This is practice T1, damn it!

Find the general solution of the augmented matrix
$$
\left[
\begin{matrix}
1 & -3 & -5 & 0
\\
0 & 1 & 1 & 3
\end{matrix}
\right].
$$

---

Add 3 times of row 2 to row 1, we have
$$
\left[
\begin{matrix}
1 & 0 & -2 & 9
\\
0 & 1 & 1 & 3
\end{matrix}
\right].
$$

Transform the augmented matrix into equations, we have
$$
\left\{
\begin{aligned}
&x_1 &&-&2x_3 &= 9
\\
&&x_2 &+& x_3 &= 3
\end{aligned}
\right..
$$

In which basic variables are $x_1$ and $x_2$, then we have
$$
\left\{
\begin{aligned}
&x_1 = 9 &+& &2x_3
\\
&x_2 = 3 &-& &x_3
\\
&x_3 \text{ is free}
\end{aligned}
\right..
$$
-->

Determine which matrices are in reduced echelon form and which others are only in echelon form.

a.
$
\left[
\begin{matrix}
1 & 0 & 0 & 0
\\
0 & 1 & 0 & 0
\\
0 & 0 & 1 & 1
\end{matrix}
\right]
$
b.
$
\left[
\begin{matrix}
1 & 0 & 1 & 0
\\
0 & 1 & 1 & 0
\\
0 & 0 & 0 & 1
\end{matrix}
\right]
$
c.
$
\left[
\begin{matrix}
1 & 0 & 0 & 0
\\
0 & 1 & 1 & 0
\\
0 & 0 & 0 & 0
\\
0 & 0 & 0 & 1
\end{matrix}
\right]
$
d.
$
\left[
\begin{matrix}
1 & 1 & 0 & 1 & 1
\\
0 & 2 & 0 & 2 & 2
\\
0 & 0 & 0 & 3 & 3
\\
0 & 0 & 0 & 0 & 4
\end{matrix}
\right]
$.

a. Reduced echelon form, since it follows the definition of reduced echelon form.

b. Reduced echelon form, since it follows the definition of reduced echelon form.

c. Not in echelon form, since row 3 have no leading entry but row 4 do have.

d. Echelon form, since it follows the definition of echelon form but the leading entry in row 2 does not equal to 1.

## P22 T3

