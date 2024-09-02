#pragma GCC optimize("O2")
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 31, kMaxM = 42, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int t, n, m, k, l, r, nt[kMaxN], e[kMaxN][2];
LL ans, f[2][kMaxN][kMaxN][kMaxN][kMaxM];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> s, l = -m >> 1, r = m >> 1, k = s.size(), s = '~' + s;
    for (int i = 2, j; i <= k; i++) {
      for (j = nt[i - 1]; j && s[j + 1] != s[i]; j = nt[j]) {
      }
      nt[i] = s[j + 1] == s[i] ? j + 1 : 0;
    }
    e[0][0] = e[0][1] = 0;
    for (int i = 0; i < k; i++) {
      bool o = s[i + 1] == 'R';
      e[i][o] = i + 1, e[i][!o] = e[nt[i]][!o];
    }
    for (int i = 0; i < k; i++) {
      fill(&f[0][0][0][0][0], &f[1][0][0][0][0], 0), f[0][i][0][0][-l] = 1;
      for (int j = 0; j < m; j++) {
        fill(&f[j & 1 ^ 1][0][0][0][0], &f[j & 1 ^ 1][kMaxN][0][0][0], 0);
        for (int x = 0; x < min(k, i + j + 1); x++) {
          for (int pre = 0; pre < min(n, j + 1); pre++) {
            for (int suf = 0; suf < min(n, j + 1); suf++) {
              for (int sum = max(l, -j); sum <= min(r, j); sum++) {
                LL _f = f[j & 1][x][pre][suf][sum - l], *__f;
                if (_f) {
                  _f = _f * kInv2 % kMod;
                  __f = &f[j & 1 ^ 1][e[x][0]][pre][max(suf - 1, 0)][max(sum - 1 - l, 0)];
                  *__f += _f, *__f >= kMod && (*__f -= kMod);
                  __f = &f[j & 1 ^ 1][e[x][1]][max(pre, sum + 1)][suf + 1][sum + 1 - l];
                  *__f += _f, *__f >= kMod && (*__f -= kMod);
                }
              }
            }
          }
        }
      }
      for (int pre = 0; pre < n; pre++) {
        for (int suf = 0; suf < n - pre; suf++) {
          for (int sum = 0; sum <= -l; sum++) {
            ans = (ans + f[m & 1][i][pre][suf][sum] * (n - pre)) % kMod;
          }
        }
      }
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
