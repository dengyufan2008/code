#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 4003, kInf = 1e18;
int n, p, r, g, a[kMaxN], b[kMaxN], w[kMaxN], nt[kMaxN], s[kMaxN], t[kMaxN << 1];
LL s1, s2, ans;

void Match(int &p, int x) {
  for (; p && w[p + 1] != x; p = nt[p]) {
  }
  p += p < n - 1 && w[p + 1] == x;
}

int Exgcd(int x, int y, LL &a, LL &b) {
  if (!y) {
    a = 1, b = 0;
    return x;
  }
  int g = Exgcd(y, x % y, b, a);
  b -= x / y * a;
  return g;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n + 1; i++) {
    cin >> b[i], r = (r + 1LL * b[i] * n) % p;
  }
  b[n + 2] = b[1], g = Exgcd(r, p, s1, s2);
  s1 = (s1 % (p / g) + p / g) % (p / g);
  for (int i = 1; i < n; i++) {
    w[i] = (a[i] - a[i + 1] + p + 1LL * b[i] * (n - i + 1) + 1LL * b[i + 1] * i) % p;
  }
  for (int i = 2, j; i < n; i++) {
    for (j = nt[i - 1]; j && w[j + 1] != w[i]; j = nt[j]) {
    }
    nt[i] = w[j + 1] == w[i] ? j + 1 : 0;
  }
  ans = kInf;
  for (int i = 0; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i + j <= n) {
        t[j] = (1LL * b[j] * (n - j + 1 - i) + 1LL * b[j + 1] * (j + i)) % p;
      } else {
        t[j] = (1LL * b[j + 1] * (n - j + 1 - i + n) + 1LL * b[j + 2] * (j + i - n)) % p;
      }
      t[j + n] = t[j], s[j] = (s[j - 1] + t[j]) % p;
    }
    int u = 0;
    for (int j = 1; j <= n - 2; j++) {
      Match(u, t[j]);
    }
    for (int j = n - 1; j <= n * 2 - 2; j++) {
      Match(u, t[j]);
      if (u == n - 1) {
        u = nt[u];
        int x = (p * 2 - a[1] - s[j - n + 1]) % p;
        if (x % g == 0) {
          int o = (s1 * x / g) % (p / g);
          ans = min(ans, 1LL * o * n * (n + 1) + (j - n + 1) * (n + 1) + i);
        }
      }
    }
    s[0] = (s[0] + b[1]) % p;
  }
  cout << (ans == kInf ? -1 : ans) << '\n';
  return 0;
}
