#include <fstream>
#define LL long long

using namespace std;

ifstream cin("route.in");
ofstream cout("route.out");

const LL kMaxN = 101, kMod = 1e9 + 7;
int t, n, c[kMaxN];
LL ans, fact[kMaxN], a[kMaxN][kMaxN];
char ch;

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

void Det() {
  ans = 1;
  for (int i = 1; i <= n; i++) {
    if (!a[i][i]) {
      for (int j = i + 1; j <= n; j++) {
        if (a[j][i]) {
          swap(a[i], a[j]);
          break;
        }
      }
    }
    if (!a[i][i]) {
      continue;
    }
    ans = ans * a[i][i] % kMod;
    LL inv = Pow(a[i][i]);
    for (int j = n; j >= i; j--) {
      a[i][j] = a[i][j] * inv % kMod;
    }
    for (int j = i + 1; j <= n; j++) {
      if (a[j][i]) {
        for (int k = n; k >= i; k--) {
          a[j][k] = (a[j][k] - a[j][i] * a[i][k] + kMod * kMod) % kMod;
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  cin >> t;
  while (t--) {
    cin >> n >> c[0];
    for (int i = 1; i <= n; i++) {
      cin >> ch, c[i] = ch == 'R';
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> ch, a[i][j] = ch == '1', c[i] += a[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        a[i][j] = i == j ? c[i] : (kMod - a[i][j]) % kMod;
      }
    }
    Det();
    for (int i = 1; i <= n; i++) {
      if (c[i]) {
        ans = ans * fact[c[i] - 1] % kMod;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
