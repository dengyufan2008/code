#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("apples.in");
ofstream cout("apples.out");

const int kMaxN = 151, kMaxM = 4230144, kInf = 1e9;
int n, m, a[kMaxN], b[kMaxN], c[kMaxN];
int w[kMaxN][kMaxN], o[kMaxN], d[kMaxM], f[kMaxM], ans[kMaxN];
vector<int> u;
vector<vector<int>> l[kMaxN];

void CalcD(int x, int s, int w) {
  if (x == 0) {
    d[s] = w;
    return;
  }
  for (int i = 0; i <= c[x]; i++) {
    CalcD(x - 1, s * (c[x] + 1) + i, w + x * i);
  }
}

void Init() {
  static int p[kMaxN];
  static bool b[kMaxN];
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      static vector<int> v;
      v.clear(), b[i] = 1, v.push_back(i);
      for (int j = p[i]; j != i; j = p[j]) {
        b[j] = 1, v.push_back(j);
      }
      c[v.size()]++, l[v.size()].push_back(v);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (c[i]) {
      u.push_back(i);
    }
  }
  m = o[0] = 1;
  for (int i = 1; i <= n; i++) {
    m = o[i] = o[i - 1] * (c[i] + 1);
  }
  for (int i = 1; i < m; i++) {
    f[i] = kInf;
  }
  CalcD(n, 0, 0);
  for (int i = 1; i < n; i++) {
    w[2][i] = a[i + 1] - a[i];
  }
  for (int i = 3; i <= n; i++) {
    for (int j = 1; j + i - 1 <= n; j++) {
      for (int k = j + 1; k < j + i - 1; k++) {
        w[i][j] = max(w[i][j], a[k + 1] - a[k - 1]);
      }
    }
  }
}

void Dp(int x, int s) {
  if (x == 0) {
    for (int i : u) {
      if (b[i] < c[i]) {
        f[s + o[i - 1]] = min(f[s + o[i - 1]], max(f[s], w[i][d[s] + 1]));
      }
    }
    return;
  }
  for (int &i = b[x] = 0; i <= c[x]; i++) {
    Dp(x - 1, s * (c[x] + 1) + i);
  }
}

void CalcAns(int m) {
  static vector<int> v;
  for (int i : u) {
    if (m / o[i - 1] % (c[i] + 1) > 0) {
      if (max(f[m - o[i - 1]], w[i][d[m] - i + 1]) == f[m]) {
        v.swap(l[i].back()), l[i].pop_back();
        for (int j = d[m] - i + 1; j <= d[m]; j += 2) {
          ans[v.back()] = a[j], v.pop_back();
        }
        for (int j = d[m] - (i & 1); j > d[m] - i; j -= 2) {
          ans[v.back()] = a[j], v.pop_back();
        }
        return CalcAns(m - o[i - 1]);
      }
    }
  }
}

void Print() {
  CalcAns(m - 1);
  cout << f[m - 1] << '\n';
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Dp(n, 0), Print();
  return 0;
}
