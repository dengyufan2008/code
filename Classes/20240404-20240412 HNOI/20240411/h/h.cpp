#include <algorithm>
#include <fstream>
#include <unordered_map>
#define PII pair<int, int>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 3e5 + 1, kMaxL = 19, kBase = 15553;
int n, m, o[kMaxN], w[kMaxN], d[kMaxN];
int a[kMaxN], r[kMaxN], l[kMaxL][kMaxN], lg[kMaxN];
LL v, ans;
PII p[kMaxN];
pair<PII, int> t[kMaxN << 1];
string s, _s;
unordered_map<unsigned LL, int> q;

void Sort() {
  static int b[kMaxN], c[kMaxN];
  for (int i = 1; i <= m; i++) {
    a[i] = i;
  }
  sort(a + 1, a + m + 1, [](int i, int j) {
    return s[i] < s[j];
  });
  for (int i = 1; i <= m; i++) {
    r[a[i]] = r[a[i - 1]] + (s[a[i]] != s[a[i - 1]]);
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
      if (r[a[i]] != r[a[i - 1]]) {
        b[a[i]]++;
      } else if ((a[i] + h <= m) ^ (a[i - 1] + h <= m)) {
        b[a[i]]++;
      } else if (a[i] + h <= m && r[a[i] + h] != r[a[i - 1] + h]) {
        b[a[i]]++;
      }
    }
    copy(&b[1], &b[m] + 1, &r[1]);
  }
}

void CalcL() {
  for (int i = 2; i <= m; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  for (int i = 1; i <= m; i++) {
    if (r[i] < m) {
      l[0][r[i]] = max(l[0][r[i - 1]] - 1, 0);
      for (int &j = l[0][r[i]]; s[i + j] == s[a[r[i] + 1] + j]; j++) {
      }
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

int Lcp0(int x, int y) {
  if (x == y) {
    return s.size() - x;
  } else {
    x = r[x], y = r[y];
    x > y ? swap(x, y) : void();
    int u = lg[y - x];
    return min(l[u][x], l[u][y - (1 << u)]);
  }
}

bool Cmp0(PII x, PII y) {  // [l, r)
  int lx = x.second - x.first, ly = y.second - y.first;
  int lcp = Lcp0(x.first, y.first);
  if (lcp >= min(lx, ly)) {
    return lx < ly;
  }
  return s[x.first + lcp] < s[y.first + lcp];
}

int Lcp1(PII x, PII y) {
  static int lcp;
  int lx = x.second - x.first, ly = y.second - y.first;
  if (lx > ly) {
    swap(x, y), swap(lx, ly);
  }
  if ((lcp = Lcp0(x.first, y.first)) < lx) {
    return lcp;
  } else if ((lcp = Lcp0(y.first, y.first + lx)) < ly - lx) {
    return lx + lcp;
  } else if ((lcp = Lcp0(y.first + ly - lx, x.first)) < lx) {
    return ly + lcp;
  }
  return -1;
}

bool Cmp1(PII x, PII y) {
  int lcp = Lcp1(x, y), w = 0;
  int lx = x.second - x.first, ly = y.second - y.first;
  if (lx > ly) {
    w = 1, swap(x, y), swap(lx, ly);
  }
  if (lcp < lx) {
    return (s[x.first + lcp] < s[y.first + lcp]) ^ w;
  } else if (lcp < ly) {
    return (s[y.first + lcp - lx] < s[y.first + lcp]) ^ w;
  } else if (lcp < lx + ly) {
    return (s[y.first + lcp - lx] < s[x.first + lcp - ly]) ^ w;
  } else if (lx != ly) {
    return (lx < ly) ^ w;
  } else if (x.first != y.first) {
    return x.first < y.first;
  }
  return 0;
}

int Z(PII x) {
  for (int i = x.first; i < x.second; i++) {
    if (s[i] != 'z') {
      return i - x.first;
    }
  }
  return -1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  s = "~", cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> _s, o[i] = i, p[i].first = s.size(), s += _s, p[i].second = s.size();
  }
  m = s.size() - 1, Sort(), CalcL(), m = 0;
  for (int u : {-1, 1}) {
    for (int _i = 1; _i <= n; _i++) {
      int i = u == -1 ? _i : n - _i + 1;
      unsigned LL h;
      h = s[p[i].first];
      for (int j = p[i].first + 1; j < p[i].second; j++) {
        if (q.count(h)) {
          t[++m] = {{j, p[i].second}, q[h]};
        }
        h = h * kBase + s[j];
      }
      !q.count(h) && (q[h] = 0), q[h] += u;
    }
    q.clear();
  }
  sort(t + 1, t + m + 1, [](pair<PII, int> i, pair<PII, int> j) {
    return Cmp1(i.first, j.first);
  });
  for (int i = 1; i <= m; i++) {
    v += t[i].second;
    int lcp = i < m ? Lcp1(t[i].first, t[i + 1].first) : Z(t[i].first);
    if (lcp >= 0) {
      ans = min(ans, 1LL + lcp - v);
    }
  }
  sort(o + 1, o + n + 1, [](int i, int j) {
    return Cmp0(p[i], p[j]);
  });
  for (int i = 1; i <= n; i++) {
    w[o[i]] = w[o[i - 1]] + Cmp0(p[o[i - 1]], p[o[i]]);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = w[i] + 1; j <= n; j += j & -j) {
      ans += d[j];
    }
    for (int j = w[i]; j >= 1; j -= j & -j) {
      d[j]++;
    }
  }
  cout << ans << '\n';
  return 0;
}
