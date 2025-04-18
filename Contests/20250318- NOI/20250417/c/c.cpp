// https://qoj.ac/problem/3040
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e6 + 2;
int n, w, p[kMaxN];
LL ans;
pair<int, int> d[kMaxN];

class Uni {
  int f[kMaxN];

 public:
  void Init(int m) {
    for (int i = 1; i <= m; i++) {
      f[i] = i;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  void Merge(int x) {
    f[GetRoot(x)] = GetRoot(x + 1);
  }
} uni;

void Input() {
  static int k, a[kMaxN], b[kMaxN];
  static string s, t;
  cin >> k >> w >> s >> t, w += 3;
  n = 0, s = '~' + s;
  for (int i = 1; i <= k; i++) {
    if (s[i] == '2') {
      n++, a[n] = i - n;
    }
  }
  n = 0, t = '~' + t;
  for (int i = 1; i <= k; i++) {
    if (t[i] == '2') {
      n++, b[n] = i - n;
    }
  }
  ans = 0;
  for (int i = 1; i <= n; i++) {
    d[i].first = i + min(a[i], b[i]);
    d[i].second = i + max(a[i], b[i]);
    int l = d[i].second - d[i].first;
    ans += 1LL * (l >> 1) * (w + 1);
    (l & 1) && (ans += w);
  }
}

void CalcP(bool o) {
  static int cl[kMaxN], cr[kMaxN];
  static vector<int> h, q[kMaxN << 1], v[kMaxN << 1];
  int l = n, r = -n;
  h.clear();
  for (int i = n; i >= 1; i--) {
    if (d[i].second - d[i].first & 1) {
      if ((d[i].first & 1) == o) {
        h.push_back(i);
      }
      if ((d[i].second & 1) == o && !h.empty()) {
        p[i] = h.back(), h.pop_back();
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cl[i] = cl[i - 1] + ((d[i].first & 1) == o);
    cr[i] = cr[i - 1] + ((d[i].second & 1) == o);
  }
  uni.Init(cl[n] + 1);
  for (int i = 1, j = 1; i <= n; i++) {
    if (cr[i] > cr[i - 1] && p[i]) {
      int k = cr[i - 1] - cl[i - 1];
      q[k + kMaxN].push_back(i);
      l = min(l, k), r = max(r, k);
    }
    if (cl[i] > cl[i - 1]) {
      for (; j <= n && (cr[j] == cr[j - 1] || d[i].first > d[j].second); j++) {
      }
      if (j <= n) {
        if (cr[j] - cl[i] <= l) {
          uni.Merge(cl[i]);
        } else if (cr[j] - cl[i] <= r) {
          v[cr[j] - cl[i] + kMaxN].push_back(cl[i]);
        }
      }
    }
  }
  for (int i = l + kMaxN; i <= r + kMaxN; i++) {
    for (int j : v[i]) {
      uni.Merge(j);
    }
    for (int j : q[i]) {
      if (uni.GetRoot(cl[j - 1] + 1) <= cl[p[j]]) {
        p[j] = 0;
      }
    }
    q[i].clear(), v[i].clear();
  }
}

void Dp() {
  static LL f[kMaxN], s[2][kMaxN];
  for (int i = 1; i <= n; i++) {
    s[0][i] = s[0][i - 1], s[1][i] = s[1][i - 1];
    if (d[i].second - d[i].first & 1) {
      s[d[i].second & 1][i] += w + i;
      s[d[i].second & 1 ^ 1][i] -= 1 + i;
    }
  }
  fill(&f[1], &f[n + 1] + 1, 0);
  for (int i = 1; i <= n; i++) {
    f[i + 1] = max(f[i + 1], f[i]);
    if (p[i]) {
      bool o = d[i].second & 1;
      f[p[i] + 1] = max(f[p[i] + 1], f[i] + s[o][p[i]] - s[o][i - 1]);
      p[i] = 0;
    }
  }
  cout << ans - f[n + 1] << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    Input(), CalcP(0), CalcP(1), Dp();
  }
  return 0;
}
