#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 2001, kMaxM = kMaxN * 2, kMod = 1e9 + 7;
int n, s[kMaxN];
bool a[4][kMaxN];
LL f[2][kMaxM][2];  // 0:竖 1:横
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
  cin >> n;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= n; j++) {
      static char c;
      cin >> c, a[i][j] = c == 'x';
    }
  }
  if (a[1][1] || a[1][n] || a[3][1] || a[3][n]) {
    cout << 0 << '\n';
    return 0;
  }
  for (int i = 1; i <= 3; i += 2) {
    for (int j = 1; j < n; j++) {
      if (a[i][j] && a[i][j + 1]) {
        cout << 0 << '\n';
        return 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[1][i] + a[2][i] + a[3][i];
  }
  f[1][a[2][1]][0] = 1;
  for (int i = 2; i <= n; i++) {
    int c = s[i] - s[i - 1];
    for (int j = 0; j <= s[i]; j++) {
      f[i & 1][j][0] = f[i & 1][j][1] = 0;
    }
    if (a[2][i]) {
      if (a[2][i - 1]) {
        LL s1 = 0, s2 = 0;
        for (int j = 0; j <= s[i - 1]; j++) {
          s1 = (s1 + f[i & 1 ^ 1][j][0]) % kMod;
          s2 = (s2 + f[i & 1 ^ 1][j][1]) % kMod;
        }
        for (int j = c; j <= s[i]; j++) {
          s2 = (s2 - f[i & 1 ^ 1][j - c][1] + kMod) % kMod;
          f[i & 1][j][0] = (s1 + s2) * fact[j - 1] % kMod * _fact[j - c] % kMod;
        }
        if (c == 2) {
          LL s3 = 0;
          for (int j = 1; j <= s[i]; j++) {
            f[i & 1][j][1] = s3 * (s[i] - j) % kMod;
            s3 = (s3 + f[i & 1 ^ 1][j][0]) % kMod;
          }
        } else if (c == 3) {
          LL s3 = 0;
          for (int j = 2; j <= s[i]; j++) {
            f[i & 1][j][1] = s3 * 2 * (j - 1) % kMod * (s[i] - j) % kMod;
            s3 = (s3 + f[i & 1 ^ 1][j - 1][0]) % kMod;
            f[i & 1][j][1] = (f[i & 1][j][1] + s3 * (s[i] - j) % kMod * (s[i] - j - 1)) % kMod;
          }
        }
      } else {
        for (int j = c; j <= s[i]; j++) {
          f[i & 1][j][0] = f[i & 1 ^ 1][0][0] * fact[j - 1] % kMod * _fact[j - c] % kMod;
        }
        if (c == 2) {
          for (int j = 1; j <= s[i]; j++) {
            f[i & 1][j][1] = f[i & 1 ^ 1][0][0] * (s[i] - j) % kMod;
          }
        } else if (c == 3) {
          for (int j = 1; j <= s[i]; j++) {
            f[i & 1][j][1] = f[i & 1 ^ 1][0][0] * (s[i] - j) % kMod * (s[i] + j - 3) % kMod;
          }
        }
      }
    } else {
      LL w = fact[s[i]] * _fact[s[i - 1]] % kMod;
      if (a[2][i - 1]) {
        for (int j = 1; j <= s[i - 1]; j++) {
          f[i & 1][0][0] = (f[i & 1][0][0] + (f[i & 1 ^ 1][j][0] + f[i & 1 ^ 1][j][1]) * w) % kMod;
        }
      } else {
        f[i & 1][0][0] = f[i & 1 ^ 1][0][0] * w % kMod;
      }
    }
  }
  if (a[2][n]) {
    LL ans = 0;
    for (int i = 1; i <= s[n]; i++) {
      ans = (ans + f[n & 1][i][0]) % kMod;
    }
    cout << ans << '\n';
  } else {
    cout << f[n & 1][0][0] << '\n';
  }
  return 0;
}
