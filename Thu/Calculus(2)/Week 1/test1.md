Prob 1. 设 $K \subseteq R^k$ 有界闭, $f:R^m \times K \rarr R$ 连续, $g(x) = \min_{y \in K} f(x, y)$. 证明 $g:R^m \rarr R$ 连续.

Proof.

$$
\begin{aligned}
|g(x_1)-g(x_2)| &= |\min_{y \in K} f(x_1, y) - \min_{y \in K} f(x_2, y)|
\\
&= \sum_{cyc} \max(\min_{y \in K} f(x_1, y) - \min_{y \in K} f(x_2, y), 0)
\\
& \le \sum_{cyc} \max(\max_{y \in K} (f(x_1, y) - f(x_2, y)), 0)
\\
& \le \sum_{cyc} \max_{y \in K} |f(x_1, y) - f(x_2, y)|
\\
&= 2\max_{y \in K} |f(x_1, y) - f(x_2, y)|.
\end{aligned}
$$

由于 $f$ 连续, 则 $g$ 连续.
