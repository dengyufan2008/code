Lemma 1. 若 $P(x, y)$, $Q(x, y)$ 都是 $k$ 次齐次函数, 即 $P(\lambda x, \lambda y) = \lambda^k P(x, y) \space (\lambda > 0)$, 则 $P(x,y)\text{d}x+Q(x,y)\text{d}y=0$ 在极坐标下可以分离变量.

Proof. 令 $x=r\cos \theta$, $y=r\sin \theta$, 则

$$r^kP(\cos \theta, \sin \theta) (\cos \theta \text{d}r - r \sin \theta \text{d}\theta) + r^kQ(\cos \theta, \sin \theta) (\sin \theta \text{d}r + r \cos \theta \text{d}\theta) = 0.$$

即

$$(P(\cos \theta, \sin \theta) \cos \theta + Q(\cos \theta, \sin \theta) \sin \theta) \text{d}r = (P(\cos \theta, \sin \theta) \sin \theta - Q(\cos \theta, \sin \theta) \cos \theta) r\text{d}\theta.$$

即

$$\frac{1}{r} \text{d}r = \frac{P(\cos \theta, \sin \theta) \sin \theta - Q(\cos \theta, \sin \theta) \cos \theta}{P(\cos \theta, \sin \theta) \cos \theta + Q(\cos \theta, \sin \theta) \sin \theta} \text{d}\theta.$$
