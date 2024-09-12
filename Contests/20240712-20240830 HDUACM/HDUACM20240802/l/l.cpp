#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 1e6 + 1;
struct V {
  int f, l, e[26];
  int c, r, p[26];                 // endpos 大小, 最大的 endpos, 前缀加字符跳到的儿子
  int b, v;                        // 属于的连通块, 最左侧一格/最上方一格对应的另一个 sam 结点
  LL g;                            // 到最左侧一格/最上方一格时的最小代价
} v1[kMaxN << 1], v2[kMaxN << 1];  // 正串/反串
int u, n, m1, m2, r1, r2, k;
string s, t;
vector<int> d1[kMaxN], d2[kMaxN];  // 连通块的行号, 列号

void Init() {
  cin >> s, t = s, n = s.size();
  s = '~' + s, reverse(t.begin(), t.end()), t = '~' + t;
  Init!!!!!!;
}

void CalcSam(V v[kMaxN << 1], int &m, int &r, string &s) {
  r = m = 1;
  for (int i = 1; i <= n; i++) {
    int x = s[i] - 'a', p = r;
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
  vector<int> l[kMaxN];
  for (int i = 1, p = 1; i <= n; i++) {
    p = v[p].e[s[i] - 'a'], v[p].c = 1, v[p].r = i;
  }
  for (int i = 1; i <= m; i++) {
    l[v[i].l].push_back(i);
  }
  for (int i = n; i >= 1; i--) {
    for (int j : l[i]) {
      v[v[j].f].c += v[j].c;
      v[v[j].f].r = max(v[v[j].f].r, v[j].r);
      v[v[j].f].p[s[v[j].r - v[v[j].f].l] - 'a'] = j;
    }
  }
}

void FindBlock() {
  queue<pair<int, int>> q;
  for (q.push({1, 1}); !q.empty(); q.pop()) {
    int x = q.front().first, y = q.front().second;
    v1[x].v = y, v2[y].v = x;
    if (v1[x].l == v2[y].l) {
      v1[x].b = v2[y].b = ++k;
    }
    for (int i = 0; i < 26; i++) {
      if (v1[x].e[i] && v1[x].l + 1 == v1[v1[x].e[i]].l) {
        q.push({v1[x].e[i], v2[y].p[i]});
      }
    }
  }
  for (int i = m1; i >= 1; i--) {
    if (!v1[i].b) {
      for (int j = 0; j < 26; j++) {
        if (v1[i].e[j]) {
          v1[i].b = v1[v1[i].e[j]].b;
          break;
        }
      }
    }
    d1[v1[i].b].push_back(i);
  }
  for (int i = m2; i >= 1; i--) {
    if (!v2[i].b) {
      for (int j = 0; j < 26; j++) {
        if (v2[i].e[j]) {
          v2[i].b = v2[v2[i].e[j]].b;
          break;
        }
      }
    }
    d2[v2[i].b].push_back(i);
  }
}

void Update(LL &x, LL y) { x = min(x, y); }

void Dp() {
  for (int i = 1; i <= k; i++) {
    reverse(d1[i].begin(), d1[i].end());
    reverse(d2[i].begin(), d2[i].end());
    for (int u = 0; u < d1[i].size(); u++) {
      int j = d1[i][u], f = v1[j].f;
      Update(v1[j].g, v1[f].g + 1LL * v1[j].l * v1[j].c);
      Update(v2[v2[v1[f].v].e[s[v1[j].r] - 'a']].g, v1[f].g + 1LL * (d1[i].size() - u) * v1[j].c);
    }
    for (int u = 0; u < d2[i].size(); u++) {
      int j = d2[i][u], f = v2[j].f;
      Update(v2[j].g, v2[f].g + 1LL * v2[j].l * v2[j].c);
      Update(v1[v1[v2[f].v].e[t[v2[j].r] - 'a']].g, v2[f].g + 1LL * (d2[i].size() - u) * v2[j].c);
    }
    for (int u = 1; u < d1[i].size(); u++) {
      int j1 = d1[i][u - 1], j2 = d1[i][u];
      Update(v1[j2].g, v1[j1].g + v1[j1].c);
    }
    for (int u = 1; u < d2[i].size(); u++) {
      int j1 = d2[i][u - 1], j2 = d2[i][u];
      Update(v2[j2].g, v2[j1].g + v2[j1].c);
    }
  }
  cout << min(v1[r1].g, v2[r2].g) << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    Init();
    CalcSam(v1, m1, r1, s), CalcSam(v2, m2, r2, t);
    FindBlock(), Dp();
  }
  return 0;
}
