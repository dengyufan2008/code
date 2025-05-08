#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1001, kMod = 998244353;
int n, m, o;
pair<int, int> a[kMaxN];

bool Init() {
  static int u[kMaxN], d[kMaxN], l[kMaxN], r[kMaxN];
  cin >> n >> m >> o;
  for (int i = 1; i <= m; i++) {
    cin >> u[i];
  }
  for (int i = 2; i < n; i++) {
    cin >> l[i] >> r[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> d[i];
  }
  l[1] = u[1], r[1] = u[m], l[n] = d[1], r[n] = d[m];
  for (int i = 1; i < n; i++) {
    if (max(abs(l[i] - l[i + 1]), abs(r[i] - r[i + 1])) > 1) {
      cout << -1 << '\n';
      return 0;
    }
  }
  for (int i = 1; i < m; i++) {
    if (max(abs(u[i] - u[i + 1]), abs(d[i] - d[i + 1])) > 1) {
      cout << -1 << '\n';
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (abs(l[i] - r[i]) >= m) {
      for (int j = 1; j <= n; j++) {
        a[j] = {l[j], r[j]};
      }
      return 1;
    }
  }
  for (int i = 1; i <= m; i++) {
    if (abs(u[i] - d[i]) >= n) {
      swap(n, m);
      for (int j = 1; j <= n; j++) {
        a[j] = {u[j], d[j]};
      }
      return 1;
    }
  }
  if (o) {
    cout << 0 << ' ' << 1 << '\n';
  } else {
    cout << 0 << '\n';
  }
  return 0;
}

bool Calc() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += abs(a[i].first - a[i].second) >= m;
  }
  cout << ans << " \n"[!o];
  return o;
}

void Dp() {
  static LL f[kMaxN], s[kMaxN];
  f[0] = 1, fill(&f[1], &f[kMaxN], 0);
  for (int i = 2; i <= n; i++) {
    bool o1 = abs(a[i - 1].first - a[i - 1].second) < m;
    bool o2 = abs(a[i].first - a[i].second) < m;
    if (o1 && o2) {
      continue;
    } else if (o1) {
      for (int j = 2; j < m; j++) {
        f[j] = f[0];
      }
      f[0] = 0;
      continue;
    } else if (o2) {
      for (int j = 2; j < m; j++) {
        f[0] += f[j], f[j] = 0;
      }
      f[0] %= kMod;
      continue;
    }
    bool o3 = a[i - 1].first > a[i - 1].second;
    if (o3) {
      swap(a[i - 1].first, a[i - 1].second);
      swap(a[i].first, a[i].second);
      reverse(f + 2, f + m);
    }
    for (int j = 2; j < m; j++) {
      s[j] = s[j - 1] + f[j];
    }
    for (int j = 2; j < m; j++) {
      int l = max(j - 1, 2), r = min(j + 1, m - 1);
      (a[i - 1].second - a[i].first <= m) && (l = 2);
      (a[i].second - a[i - 1].first <= m) && (r = m - 1);
      f[j] = (s[r] - s[l - 1]) % kMod;
    }
    if (o3) {
      swap(a[i - 1].first, a[i - 1].second);
      swap(a[i].first, a[i].second);
      reverse(f + 2, f + m);
    }
  }
  cout << f[0] << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init() && Calc() && (Dp(), 0);
  return 0;
}
