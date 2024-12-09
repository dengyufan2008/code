#include <fstream>
#define LL long long

using namespace std;

ifstream cin("maze.in");
ofstream cout("maze.out");

const int kMaxN = 1001, kMod = 1e9 + 7;
int n, m;
LL f[kMaxN][kMaxN][2], g[kMaxN][kMaxN][2];
string s, l, r;

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void Minus(string &t, int n) {
  int w = 1;
  for (int i = 2; i <= n; i++) {
    w = (w * 2 + (t[i] & 1)) % kMod;
  }
  for (bool o : {0, 1}) {
    int k = 0;
    for (int i = 2; i <= n; i++) {
      if (o ^ (s[i - 1] == 'R') != (t[i] == '1')) {
        o ^= 1, k++;
      }
    }
    if (k <= m) {
      Update(f[n][k][o], kMod - w);
      Update(g[n][k][o], kMod - 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s >> l >> r;
  s = '~' + s, l = '~' + l, r = '~' + r;
  for (int i = n; i >= 2; i--) {
    if (l[i] == '1') {
      l[i] ^= 1, Minus(l, i), l[i] ^= 1;
    }
    if (r[i] == '0') {
      r[i] ^= 1, Minus(r, i), r[i] ^= 1;
    }
  }
  f[1][0][0] = f[1][0][1] = g[1][0][0] = g[1][0][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= m; j++) {
      Update(g[i + 1][j][0], g[i][j][0]);
      Update(g[i + 1][j][1], g[i][j][1]);
      if (j < m) {
        Update(g[i + 1][j + 1][0], g[i][j][1]);
        Update(g[i + 1][j + 1][1], g[i][j][0]);
      }
      if (s[i] == 'L') {
        Update(f[i + 1][j][0], f[i][j][0] * 2);
        Update(f[i + 1][j][1], f[i][j][1] * 2 + g[i][j][1]);
        if (j < m) {
          Update(f[i + 1][j + 1][0], f[i][j][1] * 2);
          Update(f[i + 1][j + 1][1], f[i][j][0] * 2 + g[i][j][0]);
        }
      } else {
        Update(f[i + 1][j][0], f[i][j][0] * 2 + g[i][j][0]);
        Update(f[i + 1][j][1], f[i][j][1] * 2);
        if (j < m) {
          Update(f[i + 1][j + 1][0], f[i][j][1] * 2 + g[i][j][1]);
          Update(f[i + 1][j + 1][1], f[i][j][0] * 2);
        }
      }
    }
  }
  cout << (f[n][m][0] + f[n][m][1]) % kMod << '\n';
  return 0;
}
