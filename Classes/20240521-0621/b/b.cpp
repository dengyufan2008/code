#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 25001, kMaxM = 401, kMod = 1e9 + 7;
int n, m, t, a[kMaxN];
LL ans;

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

bool Check1() {
  if (t < m) {
    return 1;
  }
  static int s = 0, c[kMaxM] = {};
  for (int i = 1; i <= m; i++) {
    s += !c[a[i]], c[a[i]]++;
  }
  for (int i = m + 1; i <= t; i++) {
    if (s == m) {
      return 0;
    }
    c[a[i - m]]--, s -= !c[a[i - m]];
    s += !c[a[i]], c[a[i]]++;
  }
  return s != m;
}

bool Check2() {
  static bool b[kMaxM] = {};
  for (int i = 1; i <= t; i++) {
    if (b[a[i]]) {
      return 1;
    }
    b[a[i]] = 1;
  }
  return 0;
}

void Solve1() {
  static int x, y, b[kMaxM] = {};
  static LL f[kMaxN][kMaxM] = {}, g[kMaxN][kMaxM] = {};
  for (int i = 1; i <= t; i++) {
    if (b[a[i]] != 1) {
      b[a[i]] = 1;
    } else {
      x = i - 1;
      break;
    }
  }
  for (int i = t; i >= 1; i--) {
    if (b[a[i]] != 2) {
      b[a[i]] = 2;
    } else {
      y = t - i;
      break;
    }
  }
  for (int o : {0, 1}) {
    fill(&f[x][1], &f[x][x] + 1, 1);
    for (int i = x + 1; i <= n; i++) {
      for (int j = 1; j < m; j++) {
        f[i][j] = kMod - f[i - 1][j] * (m - j) % kMod;
        f[i][j] = (f[i][j] + f[i - 1][j - 1] * (m - j + 1)) % kMod;
      }
      f[i][1] = (f[i][1] + f[i - 1][1] * m) % kMod;
      for (int j = m - 1; j >= 1; j--) {
        f[i][j] = (f[i][j] + f[i][j + 1]) % kMod;
      }
    }
    swap(f, g), swap(x, y);
  }
  for (int i = x; i <= n - t + x; i++) {
    int j = n - t + x + y - i;
    ans = (ans - f[i][1] * g[j][1] % kMod + kMod) % kMod;
  }
}

void Solve2() {
  static LL w = 1, f[kMaxN][kMaxM] = {}, g[kMaxN][kMaxM] = {};
  f[1][1] = m, t == 1 && (g[1][1] = m);
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      f[i][j] = kMod - f[i - 1][j] * (m - j) % kMod;
      f[i][j] = (f[i][j] + f[i - 1][j - 1] * (m - j + 1)) % kMod;
    }
    f[i][1] = (f[i][1] + f[i - 1][1] * m) % kMod;
    for (int j = 1; j < m; j++) {
      g[i][j] = kMod - g[i - 1][j] * (m - j) % kMod;
      g[i][j] = (g[i][j] + g[i - 1][j - 1] * (m - j + 1)) % kMod;
    }
    g[i][1] = (g[i][1] + g[i - 1][1] * m) % kMod;
    for (int j = t; j < m; j++) {
      g[i][j] = (g[i][j] + f[i][j]) % kMod;
    }
    for (int j = m - 1; j >= 1; j--) {
      f[i][j] = (f[i][j] + f[i][j + 1]) % kMod;
    }
    for (int j = m - 1; j >= 1; j--) {
      g[i][j] = (g[i][j] + g[i][j + 1]) % kMod;
    }
  }
  for (int i = m - t; i < m; i++) {
    w = w * Pow(i) % kMod;
  }
  ans = (ans - w * g[n][1] % kMod + kMod) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t;
  for (int i = 1; i <= t; i++) {
    cin >> a[i];
  }
  if (n >= m) {
    ans = Pow(m, n - t) * (n - t + 1) % kMod;
    if (Check1()) {
      Check2() ? Solve1() : Solve2();
    }
  }
  cout << ans << '\n';
  return 0;
}
