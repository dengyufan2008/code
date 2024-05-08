Calc number of solution
$$x^2 - xy - y^2 + yz + z^2 - zx = 0$$
With
$$x, y, z \in [1, n], \gcd(x, y, z) = 1$$

---

$$x(x - y) + z(z - x) = y(y - z)$$

Let
$$a = x - y, b = y - z, c = z - x$$

We get
$$ax + cz = by$$
$$c = -a - b, y = x - a, z = x - a - b$$

Thus
$$ax - (a + b)(x - a - b) = b(x - a)$$
$$a^2 + 3ab + b^2 = 2bx$$

If $b = 0$, $x = y = z = 1$.
$$x = \frac{a^2 + 3ab + b^2}{2b}$$

Because (Considering every possibility can get)
$$x, y, z \in Odd$$
$$a, b, c \in Even$$

Thus
$$\frac{a^2}{b} \in Even$$

Let
$$g = \gcd(a, b), a = ug, b = vg$$
$$\frac{u^2g}{v} \in \Z$$

Let
$$g = kv, a = kuv, b = kv^2$$
$$k = \frac{g}{v} = \frac{g^2}{b} \in Even$$

Thus
$$x = \frac{k}{2}(u^2 + 3uv + v^2)$$
$$y = \frac{k}{2}(u^2 + uv + v^2)$$
$$z = \frac{k}{2}(u^2 + uv - v^2)$$

Because $\gcd(x, y, z) = 1$.
$$\frac{k}{2} = \plusmn 1$$

Because $y > 0, u^2 + uv + v^2 = (u - \frac{1}{2}v)^2 + \frac{3}{4}v^2 \ge 0$.
$$\frac{k}{2} = 1$$

Thus
$$x = u^2 + 3uv + v^2$$
$$y = u^2 + uv + v^2$$
$$z = u^2 + uv - v^2$$

We have
$$y = (u - \frac{1}{2}v)^2 + \frac{3}{4}v^2$$
$$\frac{3}{4}v^2 \le y, (u - \frac{1}{2}v)^2 \le y$$
$$|v| \le 2\sqrt\frac{y}{3} \le 2\sqrt\frac{n}{3}, |u - \frac{1}{2}v| \le \sqrt y \le \sqrt n$$
$$-\frac{2 \sqrt 3}{3}\sqrt n \le v \le \frac{2 \sqrt 3}{3}\sqrt n$$
$$\frac{1}{2}v -\sqrt n \le u \le \frac{1}{2}v + \sqrt n$$
$$-\frac{3 + \sqrt 3}{3}\sqrt n \le u \le \frac{3 + \sqrt 3}{3}\sqrt n$$

In summary
$$x = u^2 + 3uv + v^2$$
$$y = u^2 + uv + v^2$$
$$z = u^2 + uv - v^2$$
$$1 \le u \le \frac{3 + \sqrt 3}{3}\sqrt n$$
$$-\frac{2 \sqrt 3}{3}\sqrt n \le v \le \frac{2 \sqrt 3}{3}\sqrt n$$
$$\gcd(u, v) = 1$$

Especially when $u = 1, v = 0$
$$x = y = z = 1$$

$O(n)$.
