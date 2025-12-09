# Week1 Homework (Reference Book)

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

So the solution for this linear equation system is

$$
\left\{
\begin{aligned}
&x_1=0
\\
&x_2=0
\\
&x_3=0
\\
&x_4=0
\\
&x_5=0
\end{aligned}
\right..
$$

## P10 T13

Solve the equation system

$$
\left\{
\begin{aligned}
&x_1 - 3x_3 = 8
\\
&2x_1 + 2x_2 + 9x_3 = 7
\\
&x_2 + 5x_3 = -2
\end{aligned}
\right..
$$

---

Transform the system into augmented matrix, we have

$$
\left[
\begin{matrix}
1 & 0 & -3 & 8
\\
2 & 2 & 9 & 7
\\
0 & 1 & 5 & -2
\end{matrix}
\right].
$$

Add -2 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 0 & -3 & 8
\\
0 & 2 & 15 & -9
\\
0 & 1 & 5 & -2
\end{matrix}
\right].
$$

Swap row 2 and row 3, we have

$$
\left[
\begin{matrix}
1 & 0 & -3 & 8
\\
0 & 1 & 5 & -2
\\
0 & 2 & 15 & -9
\end{matrix}
\right].
$$

Add -2 times of row 2 to row 3, we have

$$
\left[
\begin{matrix}
1 & 0 & -3 & 8
\\
0 & 1 & 5 & -2
\\
0 & 0 & 5 & -5
\end{matrix}
\right].
$$

Multiply row 3 by $\frac{1}{5}$, we have

$$
\left[
\begin{matrix}
1 & 0 & -3 & 8
\\
0 & 1 & 5 & -2
\\
0 & 0 & 1 & -1
\end{matrix}
\right].
$$

Add 3 times of row 3 to row 1, we have

$$
\left[
\begin{matrix}
1 & 0 & 0 & 5
\\
0 & 1 & 5 & -2
\\
0 & 0 & 1 & -1
\end{matrix}
\right].
$$

Add -5 times of row 3 to row 2, we have

$$
\left[
\begin{matrix}
1 & 0 & 0 & 5
\\
0 & 1 & 0 & 3
\\
0 & 0 & 1 & -1
\end{matrix}
\right].
$$

So the solution is

$$
\left\{
\begin{aligned}
&x_1=5
\\
&x_2=3
\\
&x_3=-1
\end{aligned}
\right..
$$

## P11 T24

a. Two matrices are row equivalent if they have the same number of rows.

b. Elementary row operations on an augmented matrix never change the solution set of the associated linear system.

c. Two equivalent linear systems can have different solution sets.

d. A consistent system of linear equations has one or more solutions.

a. False. b. True. c. False. d. True.

## P21 T1

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

Transform the augmented matrix

$$
\left[
\begin{matrix}
1 & 2 & 4 & 8
\\
2 & 4 & 6 & 8
\\
3 & 6 & 9 & 12
\end{matrix}
\right]
$$

to reduced echelon form and mark the pivot positions and pivot columns.

---

Add -2 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 2 & 4 & 8
\\
0 & 0 & -2 & -8
\\
3 & 6 & 9 & 12
\end{matrix}
\right].
$$

Add -3 times of row 1 to row 3, we have

$$
\left[
\begin{matrix}
1 & 2 & 4 & 8
\\
0 & 0 & -2 & -8
\\
0 & 0 & -3 & -12
\end{matrix}
\right].
$$

Multiply row 2 by $-\frac{1}{2}$, we have

$$
\left[
\begin{matrix}
1 & 2 & 4 & 8
\\
0 & 0 & 1 & 4
\\
0 & 0 & -3 & -12
\end{matrix}
\right].
$$

Add 3 times of row 2 to row 3, we have

$$
\left[
\begin{matrix}
1 & 2 & 4 & 8
\\
0 & 0 & 1 & 4
\\
0 & 0 & 0 & 0
\end{matrix}
\right].
$$

Add -4 times of row 2 to row 1, we have

$$
\left[
\begin{matrix}
1 & 2 & 0 & -8
\\
0 & 0 & 1 & 4
\\
0 & 0 & 0 & 0
\end{matrix}
\right].
$$

Mark the pivot positions by circling, we have

$$
\left[
\begin{matrix}
\textcircled 1 & 2 & 0 & -8
\\
0 & 0 & \textcircled 1 & 4
\\
0 & 0 & 0 & 0
\end{matrix}
\right],
\left[
\begin{matrix}
\textcircled 1 & 2 & 4 & 8
\\
2 & 4 & \textcircled 6 & 8
\\
3 & 6 & 9 & 12
\end{matrix}
\right].
$$

And the pivot columns are column 1 and column 3.

## P22 T7

Find the general solutions of the augmented matrix

$$
\left[
\begin{matrix}
1 & 3 & 4 & 7
\\
3 & 9 & 7 & 6
\end{matrix}
\right].
$$

---

Add -3 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 3 & 4 & 7
\\
0 & 0 & -5 & -15
\end{matrix}
\right].
$$

Mutiply row 2 by $-\frac{1}{5}$, we have

$$
\left[
\begin{matrix}
1 & 3 & 4 & 7
\\
0 & 0 & 1 & 3
\end{matrix}
\right].
$$

Add -4 times of row 2 to row 1, we have

$$
\left[
\begin{matrix}
1 & 3 & 0 & -5
\\
0 & 0 & 1 & 3
\end{matrix}
\right].
$$

Transform the augmented matrix into equations, we have

$$
\left\{
\begin{aligned}
&x_1 + 3x_2 = -5
\\
&x_3 = 3
\end{aligned}
\right..
$$

In which basic variables are $x_1$ and $x_3$, then we have

$$
\left\{
\begin{aligned}
&x_1 = -5 - 3x_2
\\
&x_2 \text{ is free}
\\
&x_3 = 3
\end{aligned}
\right..
$$

## P22 T11

Find the general solutions of the augmented matrix

$$
\left[
\begin{matrix}
3 & -2 & 4 & 0
\\
9 & -6 & 12 & 0
\\
6 & -4 & 8 & 0
\end{matrix}
\right].
$$

---

Add -3 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
3 & -2 & 4 & 0
\\
0 & 0 & 0 & 0
\\
6 & -4 & 8 & 0
\end{matrix}
\right].
$$

Add -2 times of row 1 to row 3, we have

$$
\left[
\begin{matrix}
3 & -2 & 4 & 0
\\
0 & 0 & 0 & 0
\\
0 & 0 & 0 & 0
\end{matrix}
\right].
$$

Multiply row 1 by $\frac{1}{3}$, we have

$$
\left[
\begin{matrix}
1 & -\frac{2}{3} & \frac{4}{3} & 0
\\
0 & 0 & 0 & 0
\\
0 & 0 & 0 & 0
\end{matrix}
\right].
$$

Transform the augmented matrix into equations, we have

$$
\left\{
\begin{aligned}
&x_1 - \frac{2}{3}x_2 + \frac{4}{3}x_3 = 0
\end{aligned}
\right..
$$

In which basic variable is $x_1$, then we have

$$
\left\{
\begin{aligned}
&x_1 = \frac{2}{3}x_2 - \frac{4}{3}x_3
\\
&x_2 \text{ is free}
\\
&x_3 \text{ is free}
\end{aligned}
\right..
$$

## P22 T15

Determine if the system is consistent and if the solution is unique.

We have

$$
\left[
\begin{matrix}
\blacksquare & * & * & *
\\
0 & \blacksquare & * & *
\\
0 & 0 & 0 & 0
\end{matrix}
\right]
$$

is consistent, but the solution of it is not unique. Since it has no conflicts, and the column 3 is not a pivot column.

We also have

$$
\left[
\begin{matrix}
0 & \blacksquare & * & * & *
\\
0 & 0 & \blacksquare & * & *
\\
0 & 0 & 0 & \blacksquare & 0
\end{matrix}
\right]
$$

is consistent, but the solution of it is not unique. Since it has no conflicts, and the column 1 is not a pivot column.

## P22 T21

a. In some cases, a matrix may be row reduced to more than one matrix in reduced echelon form, using different sequences of row operations.

c. A basic variable in a linear system is a variable that corresponds to a pivot column in the coefficient matrix.

e. If one row in an echelon form of an augmented matrix is $[0 \space 0 \space 0 \space 5 \space 0]$, then the associated linear system is inconsistent.

a. False. c. True. e. False.

## P22 T22

a. The reduced echelon of a matrix is unique.

b. If every column of an augmented matrix contains a pivot, then the corresponding system is consistent.

c. The pivot positions in a matrix depend on whether row interchanges are used in the row reduction process.

d. A general solution of a system is an explicit description of all solutions of the system.

e. Whenever a system has free variables, the solution set contains many solutions.

a. True. b. True. c. False. d. True. e. False.

## P32 T1

Compute $\vec u+\vec v$ and $\vec u-2\vec v$, when $
\vec u=
\left[
\begin{matrix}
-1
\\
2
\end{matrix}
\right]
, \vec v=
\left[
\begin{matrix}
-3
\\
-1
\end{matrix}
\right]
$.

---

We have

$$
\vec u+\vec v=\left[
\begin{matrix}
-1
\\
2
\end{matrix}
\right]+\left[
\begin{matrix}
-3
\\
-1
\end{matrix}
\right]=\left[
\begin{matrix}
-1 + -3
\\
2 + -1
\end{matrix}
\right]=\left[
\begin{matrix}
-4
\\
1
\end{matrix}
\right]
$$

and

$$
\vec u-2\vec v=\left[
\begin{matrix}
-1
\\
2
\end{matrix}
\right]-2\left[
\begin{matrix}
-3
\\
-1
\end{matrix}
\right]=\left[
\begin{matrix}
-1 - 2(-3)
\\
2 - 2(-1)
\end{matrix}
\right]=\left[
\begin{matrix}
5
\\
4
\end{matrix}
\right].
$$

## P32 T6

Write a system of equations that is equivalent to the given vector equation

$$
x_1\left[
\begin{matrix}
3
\\
-2
\end{matrix}
\right]+x_2\left[
\begin{matrix}
7
\\
3
\end{matrix}
\right]+x_3\left[
\begin{matrix}
-2
\\
1
\end{matrix}
\right]=\left[
\begin{matrix}
0
\\
0
\end{matrix}
\right].
$$

---

We have

$$
\left[
\begin{matrix}
3x_1 + 7x_2 - 2x_3
\\
-2x_1 + 3x_2 + x_3
\end{matrix}
\right]=\left[
\begin{matrix}
0
\\
0
\end{matrix}
\right].
$$

Which is equivalent to

$$
\left\{
\begin{aligned}
&3x_1 + 7x_2 - 2x_3 = 0
\\
&-2x_1 + 3x_2 + x_3 = 0
\end{aligned}
\right..
$$

## P32 T9

Write a vector equation that is equivalent to the given system of equation

$$
\left\{
\begin{aligned}
&x_2 + 5x_3 = 0
\\
&4x_1 + 6x_2 - x_3 = 0
\\
&-x_1 + 3x_2 - 8x_3 = 0
\end{aligned}
\right..
$$

---

We have

$$
\left[
\begin{matrix}
x_2 + 5x_3
\\
4x_1 + 6x_2 - x_3
\\
-x_1 + 3x_2 - 8x_3
\end{matrix}
\right]=\left[
\begin{matrix}
0
\\
0
\\
0
\end{matrix}
\right].
$$

Which is

$$
x_1
\left[
\begin{matrix}
0
\\
4
\\
-1
\end{matrix}
\right]+x_2\left[
\begin{matrix}
1
\\
6
\\
3
\end{matrix}
\right]+x_3\left[
\begin{matrix}
5
\\
-1
\\
-8
\end{matrix}
\right]=\left[
\begin{matrix}
0
\\
0
\\
0
\end{matrix}
\right].
$$

## P32 T13

Determine if $
\vec b = 
\left[
\begin{matrix}
3
\\
-7
\\
-3
\end{matrix}
\right]
$ is a linear combination of the vectors formed from the columns of the matrix $
A = \left[
\begin{matrix}
1 & -4 & 2
\\
0 & 3 & 5
\\
-2 & 8 & -4
\end{matrix}
\right]
$.

---

Consider the augmented matrix

$$
\left[
\begin{matrix}
1 & -4 & 2 & 3
\\
0 & 3 & 5 & -7
\\
-2 & 8 & -4 & -3
\end{matrix}
\right].
$$

Add 2 times of row 1 to row 3, we have

$$
\left[
\begin{matrix}
1 & -4 & 2 & 3
\\
0 & 3 & 5 & -7
\\
0 & 0 & 0 & 3
\end{matrix}
\right].
$$

Which is inconsistent, so the equation

$$
x_1
\left[
\begin{matrix}
1
\\
0
\\
-2
\end{matrix}
\right]+x_2\left[
\begin{matrix}
-4
\\
3
\\
8
\end{matrix}
\right]+x_3\left[
\begin{matrix}
2
\\
5
\\
-4
\end{matrix}
\right]=\left[
\begin{matrix}
3
\\
-7
\\
-3
\end{matrix}
\right]
$$

has no solution. So that $\vec b$ is not a linear combination of the vectors formed from the columns of the matrix $A$.

## P32 T15

Let $
\vec{a_1} =
\left[
\begin{matrix}
1
\\
3
\\
-1
\end{matrix}
\right]
$, $
\vec{a_2} =
\left[
\begin{matrix}
-5
\\
-8
\\
2
\end{matrix}
\right]
$, and $
\vec b =
\left[
\begin{matrix}
3
\\
-5
\\
h
\end{matrix}
\right]
$. For what value of $h$ is $\vec b$ in the plane spanned by $\vec{a_1}$ and $\vec{a_2}$?

---

Consider augmented matrix

$$
\left[
\begin{matrix}
1 & -5 & 3
\\
3 & -8 & -5
\\
-1 & 2 & h
\end{matrix}
\right].
$$

Add -3 times of row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & -5 & 3
\\
0 & 7 & -14
\\
-1 & 2 & h
\end{matrix}
\right].
$$

Add row 1 to row 3, we have

$$
\left[
\begin{matrix}
1 & -5 & 3
\\
0 & 7 & -14
\\
0 & -3 & h+3
\end{matrix}
\right].
$$

Mutiply row 2 by $\frac{1}{7}$, we have

$$
\left[
\begin{matrix}
1 & -5 & 3
\\
0 & 1 & -2
\\
0 & -3 & h+3
\end{matrix}
\right].
$$

Add 3 times of row 2 to row 3, we have

$$
\left[
\begin{matrix}
1 & -5 & 3
\\
0 & 1 & -2
\\
0 & 0 & h-3
\end{matrix}
\right].
$$

So when $h-3=0$, that is $h=3$, the augmented matrix is consistent, then $\vec b$ is in the plane spanned by $\vec{a_1}$ and $\vec{a_2}$.

## P32 T21

Let $
\vec u =
\left[
\begin{matrix}
2
\\
-1
\end{matrix}
\right]
$ and $
\vec v =
\left[
\begin{matrix}
2
\\
1
\end{matrix}
\right]
$, Proof $
\left[
\begin{matrix}
h
\\
k
\end{matrix}
\right]
$ is in $\text{Span} \set{u, v}$ for all $h$ and $k$.

---

Consider augmented matrix

$$
\left[
\begin{matrix}
2 & 2 & h
\\
-1 & 1 & k
\end{matrix}
\right].
$$

Multiply row 1 by $\frac{1}{2}$, we have

$$
\left[
\begin{matrix}
1 & 1 & \frac{h}{2}
\\
-1 & 1 & k
\end{matrix}
\right].
$$

Add row 1 to row 2, we have

$$
\left[
\begin{matrix}
1 & 1 & \frac{h}{2}
\\
0 & 2 & \frac{h}{2} + k
\end{matrix}
\right].
$$

Obviously the augmented matrix is consistent, so $
\left[
\begin{matrix}
h
\\
k
\end{matrix}
\right]
$ is in $\text{Span} \set{u, v}$ for all $h$ and $k$.

## P34 T34

Use the vector $\vec u = (u_1, \cdots, u_n)$ to verify the following algebraic properties of $\R^n$.

a. $\vec u + (-\vec u) = (-\vec u) + \vec u = \vec 0$

b. $c(d\vec u) = (cd)\vec u$ for all scalars $c$ and $d$

---

Let's consider a. first. We have

$$
\begin{aligned}
\vec u + (-\vec u) &= (u_1, \cdots, u_n) + (-u_1, \cdots, -u_n)
\\
&= (0, \cdots, 0)
\\
&= \vec 0
\end{aligned}
$$

and

$$
\begin{aligned}
(-\vec u) + \vec u &= (-u_1, \cdots, -u_n) + (u_1, \cdots, u_n)
\\
&= (0, \cdots, 0)
\\
&= \vec 0.
\end{aligned}
$$

Then we consider b. We have

$$
\begin{aligned}
c(d\vec u) &= c(du_1, \cdots, du_n)
\\
&= (cdu_1, \cdots, cdu_n)
\\
&= cd(u_1, \cdots, u_n)
\\
&= (cd)\vec u.
\end{aligned}
$$

## P40 T1

Calculate the product

$$
\left[
\begin{matrix}
-4 & 2
\\
1 & 6
\\
0 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
3
\\
-2
\\
7
\end{matrix}
\right].
$$

---

The result is undefined, because we only defined the product of matrix $A$ and vector $\vec b$, which the number of columns of $A$ should be equal to the dementions of $\vec b$.

## P40 T4

Calculate the product

$$
\left[
\begin{matrix}
1 & 3 & -4
\\
3 & 2 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
1
\\
2
\\
1
\end{matrix}
\right].
$$

---

We have

$$
\begin{aligned}
\left[
\begin{matrix}
1 & 3 & -4
\\
3 & 2 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
1
\\
2
\\
1
\end{matrix}
\right]&=\left[
\begin{matrix}
1
\\
3
\end{matrix}
\right]+2\left[
\begin{matrix}
3
\\
2
\end{matrix}
\right]+\left[
\begin{matrix}
-4
\\
1
\end{matrix}
\right]
\\
&=\left[
\begin{matrix}
3
\\
8
\end{matrix}
\right].
\end{aligned}
$$

## P40 T7

Write the vector equation

$$
x_1
\left[
\begin{matrix}
4
\\
-1
\\
7
\\
-4
\end{matrix}
\right]+x_2
\left[
\begin{matrix}
-5
\\
3
\\
-5
\\
1
\end{matrix}
\right]+x_3
\left[
\begin{matrix}
7
\\
-8
\\
0
\\
2
\end{matrix}
\right]=\left[
\begin{matrix}
6
\\
-8
\\
0
\\
-7
\end{matrix}
\right]
$$

as a matrix equation.

---

Obviously we have

$$
\left[
\begin{matrix}
4 & -5 & 7
\\
-1 & 3 & -8
\\
7 & -5 & 0
\\
-4 & 1 & 2
\end{matrix}
\right] \vec x =
\left[
\begin{matrix}
6
\\
-8
\\
0
\\
-7
\end{matrix}
\right].
$$

## P40 T9

Write the system

$$
\left\{
\begin{aligned}
&5x_1 + x_2 - 3x_3 = 8
\\
&2x_2 + 4x_3 = 0
\end{aligned}
\right.
$$

first as a vector equation and then as a matrix equation.

---

We have

$$
\left[
\begin{matrix}
5x_1 + x_2 - 3x_3
\\
2x_2 + 4x_3
\end{matrix}
\right] = \left[
\begin{matrix}
8
\\
0
\end{matrix}
\right].
$$

Which is

$$
x_1
\left[
\begin{matrix}
5
\\
0
\end{matrix}
\right]
+x_2
\left[
\begin{matrix}
1
\\
2
\end{matrix}
\right]+x_3\left[
\begin{matrix}
-3
\\
4
\end{matrix}
\right]=\left[
\begin{matrix}
8
\\
0
\end{matrix}
\right].
$$

Which is also

$$
\left[
\begin{matrix}
5 & 1 & -3
\\
0 & 2 & 4
\end{matrix}
\right]
\vec x =
\left[
\begin{matrix}
8
\\
0
\end{matrix}
\right].
$$

## P41 T22

Let $
\vec{v_1} =
\left[
\begin{matrix}
0
\\
0
\\
-3
\end{matrix}
\right]
$, $
\vec{v_2} =
\left[
\begin{matrix}
0
\\
-3
\\
9
\end{matrix}
\right]
$, $
\vec{v_3} =
\left[
\begin{matrix}
4
\\
-2
\\
6
\end{matrix}
\right]
$. Does $\set{v_1, v_2, v_3}$ span $\R^3$? Why or why not?

---

For all $a$, $b$ and $c$, consider the augmented matrix

$$
\left[
\begin{matrix}
0 & 0 & 4 & a
\\
0 & -3 & -2 & b
\\
-3 & 9 & 6 & c
\end{matrix}
\right].
$$

Swap row 1 and row 3, we have

$$
\left[
\begin{matrix}
-3 & 9 & 6 & c
\\
0 & -3 & -2 & b
\\
0 & 0 & 4 & a
\end{matrix}
\right].
$$

Obviously the augmented matrix is now simplified to echelon augmented matrix, and there are no conflicts, so the system is consistent. Which is to say, $\set{v_1, v_2, v_3}$ span $\R^3$.

## P41 T23

a. The equation $A \vec x = \vec b$ is referred to as a vector equation.

b. A vector $\vec b$ is a linear combination of the columns of a matrix $A$ if and only if the equation $A \vec x = \vec b$ has at least one solution.

c. The equation $A \vec x = \vec b$ is consistent if the augmented matrix $[ A \space \vec b]$ has a pivot position in every row.

e. If the columns of an $m \times n$ matrix $A$ span $\R^m$, then the equation $A \vec x = \vec b$ is consistent for each $\vec b$ in $\R^m$.

f. If $A$ is an $m \times n$ matrix and if the equation $A \vec x = \vec b$ is inconsistent for some $\vec b$ in $\R^m$, then $A$ cannot have a pivot in every row.

a. False. b. True. c. False. e. True. f. True.
