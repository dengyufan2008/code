#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e6 + 1, kMaxM = kMaxN << 1;
const LL kBase = 1110721, kW[2] = {114514, 1919810}, kMod = 1000000000000000003;
struct V {
  int f, l, p, e[2];
} v[kMaxM];
int n, m, o[kMaxM], p[kMaxN];
LL ans, h[kMaxN], pw[kMaxN];
vector<int> _w, w[kMaxN];
string s;

void BuildSam() {
  int r = m = 1;
  for (int i = 1; i <= n; i++) {
    int x = s[i] == '1', p = r;
    v[++m].l = v[p].l + 1;
    for (; p && !v[p].e[x]; p = v[p].f) {
      v[p].e[x] = m;
    }
    if (p) {
      int q = v[p].e[x];
      if (v[p].l + 1 == v[q].l) {
        v[m].f = q, r = m;
      } else {
        v[++m] = v[q], v[m].l = v[p].l + 1;
        for (; p && v[p].e[x] == q; p = v[p].f) {
          v[p].e[x] = m;
        }
        v[m - 1].f = v[q].f = m, r = m - 1;
      }
    } else {
      v[m].f = 1, r = m;
    }
  }
}

void Sort() {
  static int c[kMaxN];
  for (int i = 1; i <= m; i++) {
    c[v[i].l]++;
  }
  for (int i = 1; i <= n; i++) {
    c[i] += c[i - 1];
  }
  for (int i = m; i >= 1; i--) {
    o[c[v[i].l]--] = i;
  }
}

void Init() {
  for (int i = 1; i <= m; i++) {
    v[i].p = n + 1;
  }
  p[0] = 1;
  for (int i = 1; i <= n; i++) {
    p[i] = v[p[i - 1]].e[s[i] == '1'];
    v[p[i]].p = i;
  }
  for (int i = m; i >= 1; i--) {
    int x = o[i];
    v[v[x].f].p = min(v[v[x].f].p, v[x].p);
  }
  pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw[i] = (LLL)pw[i - 1] * kBase % kMod;
    h[i] = ((LLL)h[i - 1] * kBase + kW[s[i] == '1']) % kMod;
  }
}

LL Hash(int l, int r) {
  LL ans = (h[r] - (LLL)h[l - 1] * pw[r - l + 1]) % kMod;
  return ans < 0 ? ans + kMod : ans;
}

void CalcRange() {
  static int c[kMaxM], g[kMaxM];
  static vector<int> e[kMaxN];
  for (int i = 1; i <= m; i++) {
    c[v[i].f]++;
  }
  g[1] = 1;
  for (int i = 2; i <= m; i++) {
    int x = o[i];
    if (c[x] < 2 && v[x].l != v[x].p) {
      g[x] = g[v[x].f];
    } else {
      int y = g[v[x].f];
      e[v[x].l - v[y].l].push_back(v[x].p - v[x].l + 1);
      g[x] = x;
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j : e[i]) {
      bool o = 0;
      for (int k = 0; k < _w.size(); k++) {
        if (Hash(_w[k], _w[k] + i - 1) == Hash(j, j + i - 1)) {
          o = 1, w[_w[k]].push_back(i);
          break;
        }
      }
      if (!o) {
        _w.push_back(j), w[j].push_back(i);
      }
    }
  }
}

void CalcAns() {
  static LL f[kMaxN];
  for (int o : _w) {
    fill(&v[1], &v[m] + 1, v[0]);
    int r = m = 1;
    for (int i = 1; i <= w[o][0]; i++) {
      int x = s[o + i - 1] == '1', p = r;
      v[++m].l = v[p].l + 1;
      for (; p && !v[p].e[x]; p = v[p].f) {
        v[p].e[x] = m;
      }
      if (p) {
        int q = v[p].e[x];
        if (v[p].l + 1 == v[q].l) {
          v[m].f = q, r = m;
        } else {
          v[++m] = v[q], v[m].l = v[p].l + 1;
          for (; p && v[p].e[x] == q; p = v[p].f) {
            v[p].e[x] = m;
          }
          v[m - 1].f = v[q].f = m, r = m - 1;
        }
      } else {
        v[m].f = 1, r = m;
      }
      f[i] = f[i - 1] + v[r].l - v[v[r].f].l;
    }
    for (int i : w[o]) {
      ans += f[i];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s, n = s.size();
  reverse(s.begin(), s.end()), s = '~' + s;
  BuildSam(), Sort(), Init(), CalcRange(), CalcAns();
  cout << ans << '\n';
  return 0;
}
