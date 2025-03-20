#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 18, kMaxM = 1e5, kMaxL = 17;
int t, n, m, c[kMaxM], mn[kMaxL][kMaxM], lg[kMaxM + 1];
int nt[kMaxN][kMaxM], d[kMaxN];
bool a[kMaxN][kMaxM], b[kMaxN];
vector<pair<int, int>> u;

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

void CalcConst() {
  u.push_back({0, 1});
  for (int i = 1; i <= kMaxN; i++) {
    for (int j = 1; j < i; j++) {
      if (Gcd(i, j) == 1) {
        u.push_back({j, i});
      }
    }
  }
  sort(u.begin(), u.end(), [](pair<int, int> i, pair<int, int> j) {
    return i.first * j.second < j.first * i.second;
  });
  for (int i = 2; i <= kMaxM; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
}

void CalcST() {
  for (int i = 0; i < m; i++) {
    c[i] = 0;
    for (int j = 0; j < n; j++) {
      c[i] += a[j][i];
    }
    mn[0][i] = i;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 0; j < m; j++) {
      mn[i][j] = mn[i - 1][j];
      if (j + (1 << i - 1) < m && c[mn[i][j]] >= c[mn[i - 1][j + (1 << i - 1)]]) {
        mn[i][j] = mn[i - 1][j + (1 << i - 1)];
      }
    }
  }
}

bool Invalid() {
  for (int i = 0; i < m; i++) {
    if (!c[i]) {
      return 1;
    }
  }
  return 0;
}

int Min(int l, int r) {
  int o = lg[r - l + 1], x = mn[o][l], y = mn[o][r - (1 << o) + 1];
  return c[x] < c[y] ? x : y;
}

int CalcT(int l, int p, int o, int t) {
  for (int i = o; i >= 0 && d[i] + l > d[o]; i--) {
    int x = d[o], y = d[i] + l - 1;
    if (i > 0) {
      x = max(x, d[i - 1] + l);
    }
    if (x > y) {
      continue;
    }
    int z = Min(x / p, y / p);
    if (c[z] == o - i + 2) {
      return min(z * p + p - 1, y) + 1;
    }
  }
  return max(t, d[o]);
}

int Next(int l, int p, int x, int t) {
  if (nt[x][t / p] == t / p &&
      ((l - 1) % p < p - t % p || t / p + 1 < m && nt[x][t / p + 1] == t / p + 1)) {
    return t;
  } else if (t / p == m - 1) {
    return m * p;
  } else {
    return nt[x][t / p + 1] * p;
  }
}

bool S(int l, int p, int o, int t) {
  if (o == n) {
    return 1;
  } else if (t >= m * p) {
    return 0;
  }
  pair<int, int> mn1 = {-1, m * p}, mn2 = {-1, m * p};
  for (int i = 0; i < n; i++) {
    if (!b[i]) {
      int w = Next(l, p, i, t);
      if (mn1.second > w) {
        mn2 = mn1, mn1 = {i, w};
      } else if (mn2.second > w) {
        mn2 = {i, w};
      }
    }
  }
  for (pair<int, int> i : {mn1, mn2}) {
    if (i.second + l > m * p) {
      return 0;
    }
    b[i.first] = 1, d[o] = i.second;
    if (S(l, p, o + 1, CalcT(l, p, o, t))) {
      b[i.first] = 0;
      return 1;
    }
    b[i.first] = 0;
  }
  return 0;
}

bool Check(int l, int p) {
  if (l > p * m) {
    return 0;
  }
  int g = (l + p - 1) / p;
  for (int i = 0; i < n; i++) {
    int cc = 0, ca = 0;
    for (int j = m - 1; j >= m - g; j--) {
      cc += c[j] >= 2, ca += a[i][j];
      nt[i][j] = m;
    }
    (cc == g && ca == g) && (nt[i][m - g] = m - g);
    for (int j = m - g - 1; j >= 0; j--) {
      cc -= c[j + g] >= 2, ca -= a[i][j + g];
      cc += c[j] >= 2, ca += a[i][j];
      nt[i][j] = (cc == g && ca == g) ? j : nt[i][j + 1];
    }
  }
  return S(l, p, 0, 0);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  CalcConst(), cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        static char c;
        cin >> c, a[i][j] = c == '.';
      }
    }
    CalcST();
    if (Invalid()) {
      cout << -1 << '\n';
      continue;
    }
    int l = 0, r = kMaxM;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Check(mid, 1)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    int x = r;
    l = 0, r = u.size() - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Check(x * u[mid].second + u[mid].first, u[mid].second)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << x * u[r].second + u[r].first << '/' << u[r].second << '\n';
  }
  return 0;
}
