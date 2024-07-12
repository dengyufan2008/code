#include <fstream>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

ifstream cin("whiteqwq.in");
ofstream cout("whiteqwq.out");

const int kMaxN = 1001;
int n, m, p, _p;
LL ans, a[kMaxN];

int W(int x, int k, int b) {
  return (a[x] * k + b) % p;
}

bool C(int x, int y, int k, int b) {
  return W(x, k, b) == a[y] && W(y, k, b) == a[x];
}

void CalcP() {
  int q = p;
  _p = p;
  for (int i = 2; i * i <= q; i++) {
    if (!(q % i)) {
      _p = _p * (i - 1) / i;
      while (!(q % i)) {
        q /= i;
      }
    }
  }
  if (q > 1) {
    _p = _p * (q - 1) / q;
  }
}

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

int Pow(LL x, int y) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

PLL Solve(int x, int y) {
  if (!y) {
    return {Pow(x, _p - 1), 1};
  }
  PLL ans = Solve(y, x % y);
}

PLL Solve(int x, int y, int b) {
  int w = Gcd(x, p);
  x = a[x], y = a[y] - b;
  if (y % w) {
    return {-1, -1};
  }
  x /= w, y /= w;
  auto ans = Solve(x, p / w);
  swap(ans.first, ans.second);
  ans.first = ans.first * y % p;
  ans.second = ans.second * y % p;
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  CalcP();
  for (int i = 1, o, x; i <= m; i++) {
    cin >> o, ans = 0;
    if (o == 1) {
      cin >> x;
      for (int j = 1; j <= n; j++) {
        int y = a[j] * (1 - x + p) % p;
        for (int l = j, r = j; l >= 1 && r <= n && C(l, r, x, y); l--, r++) {
          ans++;
        }
        if (j < n) {
          int y = (a[j + 1] - a[j] * x % p + p) % p;
          for (int l = j, r = j + 1; l >= 1 && r <= n && C(l, r, x, y); l--, r++) {
            ans++;
          }
        }
      }
    } else {
      cin >> x;
      for (int j = 1; j <= n; j++) {
        auto y = Solve(j, j, x);
        for (int l = j, r = j; l >= 1 && r <= n; l--, r++) {
          ;
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
