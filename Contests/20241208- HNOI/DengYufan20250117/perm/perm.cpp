#include <fstream>
#define LL long long

using namespace std;

ifstream cin("perm.in");
ofstream cout("perm.out");

const int kMaxN = 31, kMaxM = kMaxN * kMaxN, kMod = 998244353;
int n, m, k;
LL f[kMaxN][kMaxM], ans[kMaxM][kMaxN];
LL fact[kMaxM], _fact[kMaxM];

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

void Update(LL &x, LL y) { x = (x + y) % kMod; }

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
  cin >> n >> m, k = n * m;
  for (int p = 1; p <= m; p++) {
    for (int i = 0; i <= m; i++) {
      for (int s = 0; s <= k; s++) {
        f[i][s] = 0;
      }
    }
    f[0][0] = 1;
    for (int v = n; v >= 0; v--) {
      for (int i = m - 1; i >= 0; i--) {
        for (int s = 0; s <= k - v; s++) {
          if (!f[i][s]) {
            continue;
          }
          LL w = 1;
          for (int j = 1; j + i <= m && j * v + s <= k; j++) {
            if (v || i + j != p) {
              w = w * _fact[v - (i + j == p)] % kMod * _fact[n - v] % kMod;
              Update(f[i + j][s + j * v], f[i][s] * w % kMod * _fact[j]);
            } else {
              break;
            }
          }
        }
      }
    }
    for (int s = 1; s <= k; s++) {
      LL w = fact[s - 1] * fact[k - s] % kMod;
      ans[s][p] = f[m][s] * w % kMod * fact[m] % kMod;
    }
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= m; j++) {
      cout << ans[i][j] << " \n"[j == m];
    }
  }
  return 0;
}
