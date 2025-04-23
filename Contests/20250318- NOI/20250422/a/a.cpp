#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 2;
int n;
LL a, b, p, q, h[kMaxN];

LL Gcd(LL x, LL y) { return y ? Gcd(y, x % y) : x; }

void Exgcd(LL x, LL y, LL &a, LL &b) {
  if (!y) {
    a = 1, b = 0;
  } else {
    Exgcd(y, x % y, a, b);
    swap(a, b), b -= x / y * a;
  }
}

void Input() {
  cin >> n >> a >> b;
  a > b ? swap(a, b) : void();
  LL g = Gcd(a, b);
  a /= g, b /= g;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
    if (h[i] % g) {
      cout << -1 << '\n';
      exit(0);
    }
    h[i] /= g;
  }
  Exgcd(a, b, p, q);
  g = p < 0 ? (p - b + 1) / b : p / b;
  p -= g * b, q += g * a;
  n++;
  for (int i = n; i >= 1; i--) {
    h[i] -= h[i - 1];
  }
}

void Solve() {
  struct E {
    LL k, l;
  };
  LL x = 0, ans = 0;
  vector<E> l, r;
  for (int i = 1; i <= n; i++) {
    LL s = p * h[i], t = q * h[i];
    LL g = s < 0 ? (s - b + 1) / b : s / b;
    s -= g * b, t += g * a;
    if (t > 0) {
      if (s * 2 - a - b >= 0) {
        x += s - b, ans += b - s + t + a;
        r.push_back({s * 2 - a - b, 1});
      } else {
        x += s, ans += s + t;
        l.push_back({a + b - s * 2, 1});
      }

      g = t / a, s += g * b, t -= g * a;
      if (g > 0) {
        r.push_back({b - a, g});
      }

      r.push_back({a + b - t * 2, 1});
    } else if (t <= -a) {
      if (s * 2 + a - b >= 0) {
        x += s - b, ans += b - s - t - a;
        r.push_back({s * 2 + a - b, 1});
      } else {
        x += s, ans += s - t;
        l.push_back({b - a - s * 2, 1});
      }

      g = t / a, s += g * b, t -= g * a;
      if (-g > 1) {
        l.push_back({b - a, -g - 1});
      }

      l.push_back({t * 2 + a + b, 1});
    } else {
      if (s * 2 - t * 2 - a - b >= 0) {
        x += s - b, ans += b - s + t + a;
        r.push_back({s * 2 - t * 2 - a - b, 1});
      } else {
        x += s, ans += s - t;
        l.push_back({t * 2 - s * 2 + a + b, 1});
      }
    }
  }
  x /= b;
  if (x >= 0) {
    sort(l.begin(), l.end(), [](E i, E j) {
      return i.k < j.k;
    });
    for (E i : l) {
      if (i.l < x) {
        ans += i.l * i.k, x -= i.l;
      } else {
        ans += x * i.k;
        break;
      }
    }
  } else {
    x = -x;
    sort(r.begin(), r.end(), [](E i, E j) {
      return i.k < j.k;
    });
    for (E i : r) {
      if (i.l < x) {
        ans += i.l * i.k, x -= i.l;
      } else {
        ans += x * i.k;
        break;
      }
    }
  }
  cout << ans / 2 << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Solve();
  return 0;
}
