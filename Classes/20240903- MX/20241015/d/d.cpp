#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 51, kMod = 1e9 + 7;
int t, a[10];
LL ans, c[kMaxN][kMaxN], w[kMaxN];
string s;

void Calc(int n) {
  static LL f[kMaxN], g[kMaxN];
  for (int x = 1; x < 10; x++) {
    for (int o = 0; o <= n; o++) {
      for (int i = 0; i <= n; i++) {
        f[i] = 0;
      }
      f[o] = 1;
      for (int y = 0; y < 10; y++) {
        if (y != x) {
          for (int i = 0; i <= n; i++) {
            g[i] = f[i], f[i] = 0;
          }
          for (int i = 0; i <= o + a[x] - a[y] - (y > x); i++) {
            for (int j = o; j <= n - i; j++) {
              f[j + i] = (f[j + i] + g[j] * c[j + i][j]) % kMod;
            }
          }
        }
      }
      ans = (ans + f[n] * x) % kMod;
    }
  }
}

void Calc(string s) {
  int n = s.size();
  for (int i = 0; i < n; i++) {
    for (int x = !i; x < s[i] - '0'; x++) {
      a[x]++, Calc(n - i - 1), a[x]--;
    }
    a[s[i] - '0']++;
  }
  int mx = 0;
  for (int i = 1; i < 10; i++) {
    a[mx] <= a[i] && (mx = i);
  }
  ans = (ans + mx) % kMod;
  for (int i = 0; i < 10; i++) {
    a[i] = 0;
  }
}

void Init() {
  for (int i = 0; i < kMaxN; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % kMod;
    }
  }
  for (int i = 1; i < kMaxN; i++) {
    Calc(string(i, '9'));
    w[i] = (w[i - 1] + ans) % kMod;
    ans = 0;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  cin >> t;
  while (t--) {
    cin >> s;
    ans = w[s.size() - 1], Calc(s);
    cout << ans << '\n';
  }
  return 0;
}
