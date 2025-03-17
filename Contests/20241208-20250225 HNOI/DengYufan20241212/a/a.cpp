#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5001, kMod = 1e9 + 7;
int n, m, t[kMaxN][kMaxN];
LL ans, f[kMaxN][kMaxN], s1[kMaxN], s2[kMaxN];
vector<int> a[kMaxN][4];

int GetRoot(int o, int x) {
  return t[o][x] == x ? x : t[o][x] = GetRoot(o, t[o][x]);
}

void Calc(int i, int &l1, int &r1, int &l2, int &r2) {
  if (!a[i][2].empty()) {
    l1 = a[i][2].front();
  } else if (!a[i][3].empty()) {
    l1 = a[i][3].front();
  } else {
    l1 = 0;
  }
  if (!a[i][1].empty()) {
    r1 = a[i][1].back() - 1;
  } else {
    r1 = i - 1;
  }
  if (!a[i][3].empty()) {
    l2 = a[i][3].front();
  } else {
    l2 = 0;
  }
  if (!a[i][2].empty()) {
    r2 = a[i][2].back() - 1;
  } else if (!a[i][1].empty()) {
    r2 = a[i][1].back() - 1;
  } else {
    r2 = i - 1;
  }
}

void Clear(int i, int l1, int r1, int l2, int r2) {
  for (int j = 0; j < l1; j++) {
    for (int k = GetRoot(j, 0); k < j + !j; k = GetRoot(j, k)) {
      s1[j] = (s1[j] - f[j][k] + kMod) % kMod;
      s2[k] = (s2[k] - f[j][k] + kMod) % kMod;
      f[j][k] = 0;
      t[j][k] = GetRoot(j, k + 1);
    }
  }
  for (int j = l1; j <= r1; j++) {
    for (int k = GetRoot(j, 0); k < l2; k = GetRoot(j, k)) {
      s1[j] = (s1[j] - f[j][k] + kMod) % kMod;
      s2[k] = (s2[k] - f[j][k] + kMod) % kMod;
      f[j][k] = 0;
      t[j][k] = GetRoot(j, k + 1);
    }
    for (int k = GetRoot(j, r2 + 1); k < j + !j; k = GetRoot(j, k)) {
      s1[j] = (s1[j] - f[j][k] + kMod) % kMod;
      s2[k] = (s2[k] - f[j][k] + kMod) % kMod;
      f[j][k] = 0;
      t[j][k] = GetRoot(j, k + 1);
    }
  }
  for (int j = r1 + 1; j < i; j++) {
    for (int k = GetRoot(j, 0); k < j + !j; k = GetRoot(j, k)) {
      s1[j] = (s1[j] - f[j][k] + kMod) % kMod;
      s2[k] = (s2[k] - f[j][k] + kMod) % kMod;
      f[j][k] = 0;
      t[j][k] = GetRoot(j, k + 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, l, r, x; i <= m; i++) {
    cin >> l >> r >> x, a[r][x].push_back(l);
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      t[i][j] = j;
    }
  }
  f[0][0] = s1[0] = s2[0] = 3;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= 3; j++) {
      sort(a[i][j].begin(), a[i][j].end(), greater<int>());
    }
    int l1, r1, l2, r2;
    static LL _s1[kMaxN], _s2[kMaxN];
    Calc(i, l1, r1, l2, r2);
    for (int k = 0; k < i - 1; k++) {
      _s1[k] = s1[k], _s2[k] = s2[k];
    }
    for (int k = 0; k < i - 1; k++) {
      f[i - 1][k] = (s1[k] + s2[k]) % kMod;
      _s1[i - 1] = (_s1[i - 1] + f[i - 1][k]) % kMod;
      _s2[k] = (_s2[k] + f[i - 1][k]) % kMod;
    }
    for (int k = 0; k < i; k++) {
      s1[k] = _s1[k], s2[k] = _s2[k];
    }
    Clear(i, l1, r1, l2, r2);
  }
  for (int i = 0; i < n; i++) {
    ans = (ans + s1[i]) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
