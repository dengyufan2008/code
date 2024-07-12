#include <fstream>
#include <queue>

using namespace std;

ifstream cin("exam.in");
ofstream cout("exam.out");

const int kMaxN = 2e5 + 1, kMaxM = 27, kInf = 1e9;
int m, k, s, ans, e[kMaxM][kMaxM], o[kMaxM][kMaxM], w[kMaxM][kMaxM], ban[kMaxM][kMaxM], lg[1 << kMaxM];

void Init() {
  int n, a[kMaxN];
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    if (x != a[i]) {
      e[x - 1][a[i] - 1] = o[x - 1][a[i] - 1] = o[a[i] - 1][x - 1] = 1;
    }
  }
  cin >> k;
  for (int i = 1, x, y, z; i <= k; i++) {
    cin >> x >> y >> z;
    ban[x][y] = 1;
  }
  for (int i = 0; i < m; i++) {
    lg[1 << i] = i;
  }
}

void S(int x) {
  if (s >> x & 1) {
    return;
  }
  s |= 1 << x;
  for (int i = 0; i < m; i++) {
    if (o[x][i]) {
      S(i);
    }
  }
}

int PopCount(int s) {
  int c = 0;
  for (; s; s >>= 1) {
    c += s & 1;
  }
  return c;
}

bool FindRing(int s) {
  queue<int> q;
  int d[kMaxM] = {};
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (s >> i & s >> j & 1) {
        d[j] += e[i][j];
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if ((s >> i & 1) && !d[i]) {
      q.push(i);
    }
  }
  for (; !q.empty(); q.pop()) {
    int x = q.front();
    for (int i = 0; i < m; i++) {
      if ((s >> i & 1) && e[x][i]) {
        if (!--d[i]) {
          q.push(i);
        }
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (d[i]) {
      return 1;
    }
  }
  return 0;
}

void Chick() {
  bool f[kMaxM][kMaxM];
  int c = 0;
  for (int i = 0; i < m; i++) {
    f[i][i] = 1;
    for (int j = 0; j < m; j++) {
      f[i][j] = w[i][j];
      if (w[i][j]) {
        c += ban[i][j] + 1;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        f[j][k] |= f[j][i] & f[i][k];
      }
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (e[i][j] && !f[i][j]) {
        return;
      }
    }
  }
  ans = min(ans, c);
}

void T(int p, int q, int t) {
  if (!t) {
    Chick();
    return;
  }
  for (int i = q + 1; i < m; i++) {
    w[p][i] = 1;
    T(p, i, t - 1);
    w[p][i] = 0;
  }
  for (int i = p + 1; i < m; i++) {
    for (int j = 0; j < m; j++) {
      w[i][j] = 1;
      T(i, j, t - 1);
      w[i][j] = 0;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  if (m <= 6) {
    ans = kInf;
    for (int i = 0; i <= ans; i++) {
      T(0, -1, i);
    }
    cout << ans;
  } else {
    ans = 0;
    for (int i = 0, b = 0; i < m; i++) {
      if (b >> i & 1 ^ 1) {
        b |= 1 << i, s = 0, S(i), ans += FindRing(s) ? PopCount(s) : PopCount(s) - 1;
      }
    }
    cout << ans;
  }
  return 0;
}
