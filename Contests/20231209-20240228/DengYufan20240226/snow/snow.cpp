#include <bitset>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("snow.in");
ofstream cout("snow.out");

const int kMaxN = 3001, kMod = 998244353;
int n, a[kMaxN], c[kMaxN];
LL f[kMaxN * 2][2], fact[kMaxN], _fact[kMaxN];
bitset<kMaxN * 2> t, s[kMaxN * 2];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i *= 2) {
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

LL Plus() {
  LL ans = 1;
  for (int i = 1; i <= n; i++) {
    c[a[i]]++;
  }
  for (int i = 1; i <= n; i++) {
    LL s = 0, w = 1;
    for (int j = 0; j * 2 <= c[i]; j++) {
      s = (s + C(c[i], j * 2) * w) % kMod;
      w = w * (j * 2 + 1) % kMod;
    }
    ans = ans * s % kMod;
  }
  return ans;
}

LL Reduce() {
  for (int i = 1; i <= n; i++) {
    s[n + a[i]][i] = 1;
    for (int j = 1; j < i; j++) {
      s[i][j] = a[i] < a[j];
    }
  }
  for (int i = 1; i < n * 2; i++) {
    for (int j = i + 1; j <= n * 2; j++) {
      if (s[i][j]) {
        s[j][i].flip(), s[i][j] = 0;
      }
    }
    int p = i + 1;
    for (int j = i + 2; j <= n * 2; j++) {
      if (s[j][i]) {
        p = j;
        break;
      }
    }
    swap(s[i + 1], s[p]);
    for (int j = i + 1; j <= n * 2; j++) {
      bool x = s[j][i + 1], y = s[j][p];
      s[j][i + 1] = y, s[j][p] = x;
    }
    t.reset();
    for (int j = i + 2; j <= n * 2; j++) {
      if (s[j][i]) {
        s[j] ^= s[i + 1], t.set(j);
      }
    }
    for (int j = i + 1; j <= n * 2; j++) {
      if (s[j][i + 1]) {
        s[j] ^= t;
      }
    }
  }
  f[0][0] = 1;
  for (int i = 1; i <= n * 2; i++) {
    f[i][0] = f[i][1] = f[i - 1][1];
    f[i][0] = (f[i][0] + f[i - 1][0]) % kMod;
    s[i][i - 1] && (f[i][1] = kMod - f[i][1]);
    f[i][1] = (f[i][1] + f[i - 1][0]) % kMod;
    s[i][i] && (f[i][1] = kMod - f[i][1]);
  }
  return (f[n * 2][0] + f[n * 2][1]) % kMod * Pow(2, kMod - n - 1) % kMod;
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
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cout << (Plus() + Reduce()) * Pow(2) % kMod << '\n';
  return 0;
}
