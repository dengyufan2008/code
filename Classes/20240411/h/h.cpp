#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>
#define ULL unsigned long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");
// const int kMaxN = 3e5 + 2, kMaxL = 19, kBase = 15553;
const int kMaxN = 65 + 2, kMaxL = 7, kBase = 15553;
int n, o[kMaxN];
string s[kMaxN];
unordered_map<ULL, int> q;
vector<pair<string, int>> v;

namespace SA {
int m, p[kMaxN], a[kMaxN], r[kMaxN];
int l[kMaxL][kMaxN], lg[kMaxN];
string t = "~";

void Sort() {
  static int b[kMaxN], c[kMaxN];
  for (int i = 1; i <= m; i++) {
    a[i] = i;
  }
  sort(a + 1, a + m + 1, [](int i, int j) {
    return t[i] < t[j];
  });
  for (int i = 1; i <= m; i++) {
    r[a[i]] = r[a[i - 1]] + (t[a[i]] != t[a[i - 1]]);
  }
  for (int h = 1; h < m; h <<= 1) {
    fill(&b[1], &b[m] + 1, 0);
    fill(&c[1], &c[m] + 1, 0);
    for (int i = 1; i <= h; i++) {
      b[i] = m - h + i;
    }
    for (int i = 1, j = h; i <= m; i++) {
      if (a[i] > h) {
        b[++j] = a[i] - h;
      }
    }
    for (int i = 1; i <= m; i++) {
      c[r[i]]++;
    }
    for (int i = 1; i <= m; i++) {
      c[i] += c[i - 1];
    }
    for (int i = m; i >= 1; i--) {
      a[c[r[b[i]]]--] = b[i];
    }
    for (int i = 1; i <= m; i++) {
      b[a[i]] = b[a[i - 1]];
      if (r[a[i]] != r[a[i - 1]] || r[a[i] + h] != r[a[i - 1] + h]) {
        b[a[i]]++;
      }
    }
    copy(&b[1], &b[m] + 1, &r[1]);
  }
}

void CalcL() {
  for (int i = 1; i <= m; i++) {
    if (r[i] < m) {
      l[0][r[i]] = max(l[0][r[i - 1]] - 1, 0);
      for (int &j = l[0][r[i]]; t[i + j] == t[a[r[i] + 1] + j]; j++) {
      }
    } else {
      l[0][r[i]] = 0;
    }
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j < m; j++) {
      l[i][j] = l[i - 1][j];
      if (j + (1 << i - 1) < m) {
        l[i][j] = min(l[i][j], l[i - 1][j + (1 << i - 1)]);
      }
    }
  }
}

int Lcp0(int x, int xl, int y, int yl) {
  x = r[p[x] + xl], y = r[p[y] + yl];
  x > y ? swap(x, y) : void();
  int u = lg[y - x];
  return min(l[u][x], l[u][y - (1 << u)]);
}

bool Cmp0(int x, int xl, int xr, int y, int yl, int yr) {  // [l, r)
  int lcp = Lcp0(x, xl, y, yl);
  if (lcp >= min(xr - xl, yr - yl)) {
    return xr - xl < yr - yl;
  }
  return t[p[x] + xl + lcp] < t[p[y] + yl + lcp];
}

int Lcp1(int x, int y) {
  static int lcp;
  int lx = p[x + 1] - p[x];
  int ly = p[y + 1] - p[y];
  if (lx > ly) {
    swap(x, y), swap(lx, ly);
  }
  if ((lcp = Lcp0(x, 0, y, 0)) < lx) {
    return lcp;
  } else if ((lcp = Lcp0(y, 0, y, lx)) < ly - lx) {
    return lx + lcp;
  } else if ((lcp = Lcp0(y, ly - lx, x, 0)) < lx) {
    return ly + lcp;
  }
  return kMaxN;
}

bool Cmp1(int x, int y) {
  int lcp = Lcp1(x, y), w = 0;
  int lx = p[x + 1] - p[x];
  int ly = p[y + 1] - p[y];
  if (lx > ly) {
    w = 1, swap(x, y), swap(lx, ly);
  }
  if (lcp < lx) {
    return (t[p[x] + lcp] < t[p[y] + lcp]) ^ w;
  } else if (lcp < ly) {
    return (t[p[y] + lcp - lx] < t[p[y] + lcp]) ^ w;
  } else if (lcp < lx + ly) {
    return (t[p[y] + lcp - lx] < t[p[x] + lcp - ly]) ^ w;
  }
  return 0;
}
}  // namespace SA
using namespace SA;

int W(int x) {
  static int d[kMaxN] = {};
  int ans = 0;
  for (int i = x + 1; i <= n; i += i & -i) {
    ans += d[i];
  }
  for (int i = x; i >= 1; i -= i & -i) {
    d[i]++;
  }
  return ans;
}

int Calc1() {
  int w = 0;
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i], m += s[i].size();
    p[i] = t.size(), t += s[i], o[i] = i;
  }
  p[n + 1] = m + 1, Sort(), CalcL();
  sort(o + 1, o + n + 1, [](int i, int j) {
    return Cmp0(i, 0, s[i].size(), j, 0, s[j].size());
  });
  a[o[1]] = 1;
  for (int i = 2; i <= n; i++) {
    int x = o[i - 1], y = o[i];
    a[y] = a[x] + Cmp0(x, 0, s[x].size(), y, 0, s[y].size());
  }
  for (int i = 1; i <= n; i++) {
    w += W(a[i]);
  }
  return w;
}

int Z(string s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != 'z') {
      return i;
    }
  }
  return s.size();
}

int Calc2() {
  int w = 0;
  t.resize(1), m = 0;
  for (int i = n; i >= 1; i--) {
    static ULL h;
    h = s[i][0];
    for (int j = 1; j < s[i].size(); j++) {
      if (q.count(h)) {
        v.push_back({s[i].substr(j), q[h]});
      }
      h = h * kBase + s[i][j];
    }
    !q.count(h) && (q[h] = 0), q[h]++;
  }
  for (int i = 0; i < v.size(); i++) {
    p[i] = t.size(), t += v[i].first, m += v[i].first.size(), o[i] = i;
  }
  p[v.size()] = m + 1, Sort(), CalcL();
  sort(o, o + v.size(), Cmp1);
  for (int i = 0, j = 0; i < v.size(); i++) {
    j += v[o[i]].second;
    int lcp = i < v.size() ? Lcp1(o[i], o[i + 1]) : Z(v.back().first);
    w = min(w, lcp + 1 - j);
  }
  return w;
  // for (int i = 0; o[i] != 5; i++) {
  //   cout << v[o[i]].second << ' ';
  // }
  // cout << v[5].second << '\n';
  // int _w = -217;
  // for (int i = 1; i <= n; i++) {
  //   int __w = 0;
  //   for (int j = i + 1; j <= n; j++) {
  //     __w += s[i] + 'r' > s[j] + 'r';
  //   }
  //   _w += __w;
  //   cout << __w << " \n"[i == n];
  // }
  // return _w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << Calc1() + Calc2() << '\n';
  return 0;
}
