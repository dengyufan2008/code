#include <fstream>
#define LL long long

using namespace std;

ifstream cin("stone.in");
ofstream cout("stone.out");

const int kMaxN = 1e6 + 1, kMaxL = 13, kMod = 998244353;
int n, d[4][kMaxN], p[4][kMaxL][2], pw[kMaxL];
LL ans, f[kMaxN][kMaxL][2], g[kMaxL];
string s;

void Add(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxL; i++) {
    pw[i] = pw[i - 1] * 3;
  }
  cin >> n >> s;
  d[s[0] - 'A'][0] = 1;
  for (int i = 1; i < n; i++) {
    d[0][i] = d[0][i - 1], d[1][i] = d[1][i - 1];
    d[2][i] = d[2][i - 1], d[3][i] = d[3][i - 1];
    d[s[i] - 'A'][i]++;
  }
  for (int c = 0; c < 4; c++) {
    for (int o = 0; o < kMaxL; o++) {
      int &j = p[c][o][0];
      for (; j < n && d[c][j] < pw[o]; j++) {
      }
      if (j < n) {
        f[j][o][0] = 1;
      }
    }
  }
  for (int i = 0; i + 1 < n; i++) {
    LL w = 0;
    for (int p = 0; p < kMaxL; p++) {
      Add(w, f[i][p][0] + f[i][p][1]), g[p] = w;
    }
    for (int c = 0; c < 4; c++) {
      for (int o = 0; o < kMaxL; o++) {
        int &j = p[c][o][0];
        for (; j < n && d[c][j] < pw[o] + d[c][i]; j++) {
        }
        if (j == n) {
          continue;
        }
        if (s[i] != s[i + 1] || s[j] != s[i + 1]) {
          Add(f[j][o][0], w);
          if (s[i] == s[j]) {
            Add(f[j][o][0], kMod * 2 - f[i][o][0] - f[i][o][1]);
            Add(f[j][o][1], f[i][o][0]);
          }
        } else {
          Add(f[j][o][0], w - g[o]), Add(f[j][o][1], f[i][o][0]);
          if (o) {
            int &k = p[c][o][1];
            for (; k < n && d[c][k] < pw[o] + d[c][i] + 1; k++) {
            }
            if (k < n) {
              Add(f[k][o][0], g[o - 1]);
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < kMaxL; c++) {
      Add(ans, f[i][c][0] + f[i][c][1]);
    }
  }
  cout << ans << '\n';
  return 0;
}
