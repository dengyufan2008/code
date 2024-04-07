#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMod = 998244353;
int n;
LL a, b;
string s;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

namespace Solve1 {
bool C() {
  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      return 1;
    }
  }
  return 0;
}

int main() {
  cout << (C() ? -1 : 0) << '\n';
  return 0;
}
}  // namespace Solve1
namespace Solve2 {
bool C() {
  for (int i = 1; i < n; i++) {
    if (s[i] == '0' && s[i - 1] == '1') {
      return 1;
    }
  }
  return 0;
}

int M() {
  int ans = 0;
  for (int i = 0; i < n && s[i] == '0'; i++) {
    ans++;
  }
  return ans;
}

int main() {
  cout << (C() ? -1 : M()) << '\n';
  return 0;
}
}  // namespace Solve2
namespace Solve3 {
const int kMaxN = 4;
struct A {
  LL x, y;
  bool b;  // 0:+ 1:-

  LL Gcd(LL x, LL y) { return y ? Gcd(y, x % y) : x; }

  void ReCalc() {
    x < 0 && (x = -x, b ^= 1);
    y < 0 && (y = -y, b ^= 1);
    x == 0 && (b = 0);
    LL t = Gcd(x, y);
    x /= t, y /= t;
  }

  A operator+(A a) {
    b && (x = -x), a.b && (a.x = -a.x);
    A ans(x * a.y + y * a.x, y * a.y, 0);
    ans.ReCalc();
    return ans;
  }

  A operator-(A a) {
    b && (x = -x), a.b && (a.x = -a.x);
    A ans(x * a.y - y * a.x, y * a.y, 0);
    ans.ReCalc();
    return ans;
  }

  A operator*(A a) {
    A ans(x * a.x, y * a.y, b ^ a.b);
    ans.ReCalc();
    return ans;
  }

  A operator/(A a) {
    A ans(x * a.y, y * a.x, b ^ a.b);
    ans.ReCalc();
    return ans;
  }

  bool operator<(const A a) const {
    if (b ^ a.b) {
      return !b;
    } else if (b) {
      return x * a.y > y * a.x;
    }
    return x * a.y < y * a.x;
  }

  A() : x(0), y(1), b(0) {}
  A(LL _x, LL _y, bool _b) : x(_x), y(_y), b(_b) {
    ReCalc();
  }

  LL W() {
    LL w = x * Pow(y) % kMod;
    b && (w = (kMod - w) % kMod);
    return w;
  }
} p, q, ans, d[1 << kMaxN][1 << kMaxN | 1];
int m, t;

int main() {
  m = 1 << n, p = A(a, a + b, 0), q = A(b, a + b, 0);
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      t |= 1 << i;
    }
  }
  for (int i = 0; i < 1 << m; i++) {
    fill(&d[0][0], &d[1 << kMaxN][0], A());
    for (int j = 0; j < m; j++) {
      d[j][j] = d[j][m] = A(1, 1, 1);
      if (j & 1) {
        int _j = j >> 1 | (i >> j & 1) << n - 1;
        d[j][_j] = d[j][_j] + A(1, 1, 0);
      } else {
        int _j = j >> 1 | 1 << n - 1;
        d[j][_j] = d[j][_j] + p, d[j][j >> 1] = d[j][j >> 1] + q;
      }
    }
    for (int i = 0; i < m; i++) {
      if (!d[i][i].x) {
        for (int j = i + 1; j < m; j++) {
          if (d[j][i].x) {
            swap(d[i], d[j]);
            break;
          }
        }
      }
      if (d[i][i].x) {
        for (int j = m; j >= i; j--) {
          d[i][j] = d[i][j] / d[i][i];
        }
        for (int j = i + 1; j < m; j++) {
          for (int k = m; k >= i; k--) {
            d[j][k] = d[j][k] - d[j][i] * d[i][k];
          }
        }
      }
    }
    for (int i = m - 1; i >= 0; i--) {
      if (d[i][i].x) {
        for (int j = i - 1; j >= 0; j--) {
          d[j][m] = d[j][m] - d[j][i] * d[i][m];
          d[j][i] = A();
        }
      }
    }
    if (d[t][t].x) {
      ans = max(ans, d[t][m]);
    } else {
      cout << -1 << '\n';
      return 0;
    }
  }
  cout << ans.W() << '\n';
  return 0;
}
}  // namespace Solve3

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> a >> b;
  n = s.size();
  if (!a) {
    return Solve1::main();
  } else if (!b) {
    return Solve2::main();
  } else {
    return Solve3::main();
  }
  return 0;
}
