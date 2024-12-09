#include <fstream>

using namespace std;

ifstream cin("robot.in");
ofstream cout("robot.out");

const int kMaxN = 1e5 + 1, kMaxM = 450, kMod = 1e9 + 7;
int t, f[kMaxN], g[kMaxN], ff[kMaxN], gg[kMaxN];

void Init() {
  for (int i = kMaxM; i >= 1; i--) {
    for (int j = i; j < kMaxN; j++) {
      ff[j] = f[j], gg[j] = g[j];
    }
    f[i - 1] = i - 1, g[i - 1] = 1;
    for (int j = i; j < kMaxN; j++) {
      if (j - i >= i) {
        f[j] = f[j - i] + ff[j - i], f[j] >= kMod && (f[j] -= kMod);
        g[j] = g[j - i] + gg[j - i], g[j] >= kMod && (g[j] -= kMod);
      } else {
        f[j] = j, g[j] = 1;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), cin >> t;
  for (int i = 1, n, m, c; i <= t; i++) {
    cin >> n >> c, m = n / c;
    cout << (1LL * f[m] * c + 1LL * g[m] * (n % c)) % kMod << '\n';
  }
  return 0;
}
