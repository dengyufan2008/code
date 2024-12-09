#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("emu.in");
ofstream cout("emu.out");

const int kMaxN = 1e5 + 1, kMaxM = 6, kMaxL = 32768;
int n, m, a[kMaxN][kMaxM], f[kMaxL], g[kMaxL];
long long ans;
vector<int> l;

void S(int x, int w) {
  static bool b[kMaxM] = {};
  w ? l.push_back(w) : void();
  if (x > m) {
    return;
  }
  for (int i = 1; i <= m; i++) {
    if (!b[i]) {
      b[i] = 1, S(x + 1, (w << 3) + i), b[i] = 0;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  S(1, 0), ans = 1, f[0] = n;
  for (int i : l) {
    f[i] = n + 1;
  }
  for (int i = n - 1; i >= 1; i--) {
    int t = 0;
    for (int j : l) {
      g[j] = f[j >> 3];
      for (int k = 0; k < m * 3 && 1 << k <= j; k += 3) {
        int s = (j >> 3) & ~(-1 << k);
        if (f[s] <= n && a[f[s]][j & 7] == a[i][j & 7]) {
          g[j] = f[s + ((j & 7) << k) + (j >> (k + 3) << (k + 3))];
          break;
        }
      }
      t = max(t, g[j]);
    }
    ans += t - i, f[0] = i;
    for (int j : l) {
      f[j] = g[j];
    }
  }
  cout << ans << '\n';
  return 0;
}
