#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("delete.in");
ofstream cout("delete.out");

const int kMaxN = 2001, kMod = 1e9 + 7;
int n, a[kMaxN], b[kMaxN], l[kMaxN];
LL ans, f[kMaxN][kMaxN], d[kMaxN][kMaxN], fact[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> b[i], l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return b[i] < b[j];
  });
  for (int i = 1; i <= n; i++) {
    a[l[i]] = a[l[i - 1]] + (b[l[i]] > b[l[i - 1]]);
  }
  f[0][0] = 1;
  for (int i = 1; i <= n; i += i & -i) {
    d[i][0] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = a[i]; j >= 1; j -= j & -j) {
      for (int k = 0; k < i; k++) {
        f[i][k + 1] = (f[i][k + 1] + d[j][k]) % kMod;
      }
    }
    for (int j = a[i]; j <= n; j += j & -j) {
      for (int k = 1; k <= i; k++) {
        d[j][k] = (d[j][k] + f[i][k]) % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      f[i][j] = (f[i][j] + f[i - 1][j]) % kMod;
    }
  }
  for (int i = 0; i < n; i++) {
    ans = (ans + f[n][i] * fact[n - i - 1] % kMod * (n - i)) % kMod;
    ans = (ans - f[n][i + 1] * fact[n - i - 1] % kMod * (i + 1)) % kMod;
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
