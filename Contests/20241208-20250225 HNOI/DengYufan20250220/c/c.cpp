#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e6 + 1, kMod = 998244353;
int n, m, a[kMaxN], t[kMaxN];
LL ans, w[kMaxN];
LL s[kMaxN];  // s_i = \sum_{1 \le j \le i, j+i \in Even} {n \choose j}
LL fact[kMaxN], _fact[kMaxN];

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
  if (y < 0 || y > x) {
    return 0;
  }
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

LL Calc(int t) {
  LL w = min(n >> 1, t) * C(n, t) % kMod;
  if (min(n - t, t) >= 2) {
    w = (w - s[min(n - t, t) - 2] + kMod) % kMod;
  }
  return w * fact[t] % kMod * fact[n - t] % kMod;
}

void Init() {
  s[0] = 1, s[1] = n;
  for (int i = 2; i < kMaxN; i++) {
    s[i] = (s[i - 2] + C(n, i)) % kMod;
  }
  for (int i = kMaxN - 2; i >= 1; i--) {
    t[i] += t[i + 1];
  }
  for (int i = 1; i < kMaxN; i++) {
    w[i] = Calc(t[i]);
    ans = (ans + w[i]) % kMod;
  }
}

void Change(int x, int y) {
  if (y < 0) {
    for (int i = a[x] + y + 1; i <= a[x]; i++) {
      ans = (ans - w[i] + kMod) % kMod;
      w[i] = Calc(--t[i]);
      ans = (ans + w[i]) % kMod;
    }
  } else if (y > 0) {
    for (int i = a[x] + 1; i <= a[x] + y; i++) {
      ans = (ans - w[i] + kMod) % kMod;
      w[i] = Calc(++t[i]);
      ans = (ans + w[i]) % kMod;
    }
  }
  a[x] += y;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], t[a[i]]++;
  }
  Init();
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, Change(x, y);
    cout << ans << '\n';
  }
  return 0;
}
