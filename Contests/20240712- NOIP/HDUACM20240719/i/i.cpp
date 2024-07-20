#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 501, kMod = 998244353;
int o, n, m;
LL f[kMaxN][kMaxN][10][2];
string l, r, s;

LL CalcF(string o) {
  int t[10] = {};
  LL w = 0, ans = 0;
  n = o.size() - 1, m = s.size() - 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= min(i, m); j++) {
      for (int k = 0; k < 10; k++) {
        f[i][j][k][0] = (f[i - 1][j][k][0] * 10 + f[i - 1][j][k][1] * (o[i] - '0')) % kMod;
        f[i][j][k][1] = f[i - 1][j][k][1];
      }
      if (j) {
        if (s[j] == '<') {
          t[0] = f[i - 1][j - 1][0][0];
          for (int k = 1; k < 10; k++) {
            t[k] = (t[k - 1] + f[i - 1][j - 1][k][0]) % kMod;
          }
          for (int k = 1; k < 10; k++) {
            f[i][j][k][0] = (f[i][j][k][0] + t[k - 1]) % kMod;
          }
          t[0] = f[i - 1][j - 1][0][1];
          for (int k = 1; k < 10; k++) {
            t[k] = (t[k - 1] + f[i - 1][j - 1][k][1]) % kMod;
          }
          for (int k = 1; k < o[i] - '0'; k++) {
            f[i][j][k][0] = (f[i][j][k][0] + t[k - 1]) % kMod;
          }
          for (int k = 0; k < o[i] - '0'; k++) {
            f[i][j][o[i] - '0'][1] = (f[i][j][o[i] - '0'][1] + f[i - 1][j - 1][k][1]) % kMod;
          }
        } else {
          t[0] = f[i - 1][j - 1][0][0];
          for (int k = 1; k < 10; k++) {
            t[k] = (t[k - 1] + f[i - 1][j - 1][k][0]) % kMod;
          }
          for (int k = 0; k < 9; k++) {
            f[i][j][k][0] = (f[i][j][k][0] + t[9] - t[k] + kMod) % kMod;
          }
          t[0] = f[i - 1][j - 1][0][1];
          for (int k = 1; k < 10; k++) {
            t[k] = (t[k - 1] + f[i - 1][j - 1][k][1]) % kMod;
          }
          for (int k = 0; k < o[i] - '0'; k++) {
            f[i][j][k][0] = (f[i][j][k][0] + t[9] - t[k] + kMod) % kMod;
          }
          for (int k = o[i] - '0' + 1; k < 10; k++) {
            f[i][j][o[i] - '0'][1] = (f[i][j][o[i] - '0'][1] + f[i - 1][j - 1][k][1]) % kMod;
          }
        }
      }
    }
    f[i][0][0][0] = (f[i][0][0][0] - 1 + kMod) % kMod;
    for (int k = 0; k < 10; k++) {
      f[i][0][k][0] = (f[i][0][k][0] + w) % kMod;
    }
    for (int k = 0; k < o[i] - '0'; k++) {
      f[i][0][k][0] = (f[i][0][k][0] + 1) % kMod;
    }
    f[i][0][o[i] - '0'][1] = (f[i][0][o[i] - '0'][1] + 1) % kMod;
    w = (w * 10 + (o[i] - '0')) % kMod;
  }
  for (int k = 0; k < 10; k++) {
    ans = (ans + f[n][m][k][0] + f[n][m][k][1]) % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> l >> r >> s, l.back()--;
    l = '~' + l, r = '~' + r, s = '~' + s;
    for (int i = l.size() - 1; l[i] == '/'; i--) {
      l[i] = '9', l[i - 1]--;
    }
    cout << (CalcF(r) - CalcF(l) + kMod) % kMod << '\n';
  }
  return 0;
}
