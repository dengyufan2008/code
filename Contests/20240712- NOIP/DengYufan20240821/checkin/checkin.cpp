#include <fstream>
#define LL long long

using namespace std;

ifstream cin("checkin.in");
ofstream cout("checkin.out");

const int kMaxM = 101, kMod = 998244353;
LL m, b, c, d, ans, fact[kMaxM], _fact[kMaxM];
LL f[kMaxM][kMaxM][kMaxM], t[kMaxM];
string s;

struct A {
  int t, a[kMaxM];
  void operator+=(int x) {
    a[0] += x;
    for (int i = 0;; i++) {
      if (a[i] >= b) {
        a[i + 1] += a[i] / b;
        a[i] %= b;
        i + 1 == t && (t++);
      } else {
        break;
      }
    }
  }
  void operator-=(int x) {
    a[0] -= x;
    for (int i = 0; i < t; i++) {
      if (a[i] < 0) {
        a[i + 1] += (a[i] - b + 1) / b;
        a[i] %= b, a[i] < 0 && (a[i] += b);
      } else {
        break;
      }
    }
    if (a[t] < 0) {
      for (int i = 0; i <= t; i++) {
        a[i] = 0;
      }
      t = 0;
    } else {
      for (; t && !a[t - 1]; t--) {
      }
    }
  }
} n;

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

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void ToBaseB() {
  int t = s.size(), a[1001] = {};
  for (int i = 0; i < t; i++) {
    a[i] = s[t - i - 1] - '0';
  }
  while (t) {
    int w = 0;
    for (int i = t - 1; i >= 0; i--) {
      w = w * 10 + a[i];
      a[i] = w / b, w %= b;
    }
    n.a[n.t++] = w;
    for (; t && !a[t - 1]; t--) {
    }
  }
}

void CalcF() {
  LL g = f[0][0][0] = 1;
  for (int i = 1; i <= m; i++) {
    g = g * b % kMod;
    for (int j = 0; j < i; j++) {
      for (int k = 0; k <= m; k++) {
        LL w = 1;
        f[i][j][k] = (f[i][j][k] + f[i - 1][j][k]) % kMod;
        for (int l = 0; l <= k; l++) {
          LL t = f[i - 1][j][k - l] * w % kMod * C(k, l);
          f[i][j + 1][k] = (f[i][j + 1][k] + t) % kMod;
          w = w * g % kMod;
        }
      }
    }
  }
}

void CalcSum(int o, int x, int y) {
  if (y <= x) {
    LL w = 0;
    for (int i = o; i >= 0; i--) {
      w = (w * b + n.a[i]) % kMod;
    }
    t[0] = 1;
    for (int i = 1; i <= m; i++) {
      for (int j = i; j >= 1; j--) {
        t[j] = (t[j] * w - t[j - 1] + kMod) % kMod;
      }
      t[0] = t[0] * w % kMod;
      w = (w - 1 + kMod) % kMod;
    }
    for (int i = 0; i <= m; i++) {
      d = (d + t[i] * f[x][y][i]) % kMod, t[i] = 0;
    }
  }
}

void CalcAns() {
  n += m - 1;
  for (int i = 0; i <= m && n.t; i++) {
    int j = n.t - 1, k = 0;
    if (j > m) {
      CalcSum(j, m, i);
    } else {
      for (; j >= 1 && k <= i; j--) {
        if (n.a[j] > 1) {
          CalcSum(j, j, i - k);
          break;
        } else if (n.a[j] == 1) {
          CalcSum(j, j - 1, i - k);
          k++;
        }
      }
      if (!j && k == i) {
        LL w = 1;
        for (int l = 0; l < m; l++) {
          w = w * (n.a[0] - l) % kMod;
        }
        d = (d + w) % kMod;
      }
    }
    if (i & 1) {
      ans = (ans - d + kMod) % kMod;
    } else {
      ans = (ans + d) % kMod;
    }
    d = 0, c >= 0 ? n += c : n -= -c;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> m >> b >> c >> s, c--;
  ToBaseB(), CalcF(), CalcAns();
  for (int i = 1; i <= m; i++) {
    ans = ans * Pow(i) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
