#include <iostream>
#include <queue>

using namespace std;

const int kMaxN = 501;
struct V {
  int p, v, f, c;  // 0:白点 1:黑点
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, ans;
vector<int> l[2];
queue<int> q;

int F(int x) {
  return v[x].f == x ? x : v[x].f = F(v[x].f);
}

int Lca(int s, int x, int y) {
  int a[2] = {x, y};
  for (int p = 0; p < 2; p++) {
    l[p].clear();
    for (int i = a[p]; i != s; i = v[v[i].v].p) {
      l[p].push_back(i);
    }
    l[p].push_back(s);
  }
  for (x = l[0].size() - 1, y = l[1].size() - 1; x >= 0 && y >= 0 && F(l[0][x]) == F(l[1][y]); x--, y--) {
    for (; x > 0 && F(l[0][x - 1]) == F(l[0][x]); x--) {
    }
    for (; y > 0 && F(l[1][y - 1]) == F(l[1][y]); y--) {
    }
  }
  l[0].resize(x + 2), l[1].resize(y + 2);
  return l[0][x + 1];
}

bool S(int x) {
  for (int i = 1; i <= n; i++) {
    v[i].p = v[i].c = v[i].b = 0, v[i].f = i;
  }
  while (!q.empty()) {
    q.pop();
  }
  for (v[x].c = 1, q.push(x); !q.empty(); q.pop()) {
    int c = q.front();
    for (int i : v[c].e) {
      if (v[i].c && F(c) != F(i)) {  // 黑点
        int r = Lca(x, c, i);
        F(i) != F(r) && (v[i].p = c), F(c) != F(r) && (v[c].p = i);
        for (int p = 0; p < 2; p++) {
          for (int j = 0; j + 1 < l[p].size(); j++) {
            if (F(v[v[l[p][j]].v].p) != F(r)) {
              v[v[v[l[p][j]].v].p].p = v[l[p][j]].v;
            }
            v[v[l[p][j]].v].c = 1;
            if (!v[v[l[p][j]].v].b) {
              q.push(v[l[p][j]].v);
            }
            if (F(l[p][j]) != F(r)) {
              v[l[p][j]].f = F(r);
            }
            if (F(v[l[p][j]].v) != F(r)) {
              v[v[l[p][j]].v].f = F(r);
            }
          }
        }
      } else if (!v[i].c && !v[i].v) {  // 未匹配的白点
        v[i].p = c;
        for (int j = i; j;) {
          v[j].v = v[j].p, swap(j, v[v[j].p].v);
        }
        return 1;
      } else if (!v[i].c && !v[v[i].v].b) {  // 已匹配的白点
        v[i].p = c, v[v[i].v].c = v[v[i].v].b = 1, q.push(v[i].v);
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    ans += !v[i].v && S(i);
  }
  cout << ans << '\n';
  for (int i = 1; i <= n; i++) {
    cout << v[i].v << ' ';
  }
  return 0;
}
// https://uoj.ac/problem/79
