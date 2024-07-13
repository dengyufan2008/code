#include <iostream>
#include <queue>

using namespace std;

const int kInf = 1e9;
struct E {
  int x, v, p;
} e[140002];
struct V {
  int et, n, d;
} v[60001];
int n, n1, n2, n3, m1, m2, s, t, ans, g[60001];

void ReCalc(int x) {
  !--g[v[x].d] && (v[0].d = 1);
  v[x].d = n, v[x].n = v[x].et;
  for (int i = v[x].et; i; i = e[i].p) {
    v[x].d = min(v[x].d, e[i].v ? v[e[i].x].d + 1 : kInf);
  }
  g[v[x].d]++;
}

void Bfs() {
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    v[i].d = -(i != t), v[i].n = v[i].et;
  }
  for (q.push(t); !q.empty(); q.pop()) {
    int x = q.front();
    g[v[x].d]++;
    for (int i = v[x].et; i; i = e[i].p) {
      if (e[i ^ 1].v && v[e[i].x].d == -1) {
        v[e[i].x].d = v[x].d + 1, q.push({e[i].x});
      }
    }
  }
}

int Dfs(int x, int in) {
  if (x == t) {
    return in;
  }
  int out = 0;
  for (int &i = v[x].n; i && in; in && (i = e[i].p)) {
    if (e[i].v && v[e[i].x].d == v[x].d - 1) {
      int t = Dfs(e[i].x, min(in, e[i].v));
      e[i].v -= t, e[i ^ 1].v += t;
      in -= t, out += t;
    }
  }
  if (in) {
    ReCalc(x);
  }
  return out;
}

int main() {
  cin >> n1 >> n2 >> n3 >> m1;
  for (int i = 1, x, y; i <= m1; i++) {
    cin >> x >> y;
    e[i << 1] = {n2 + x, 1, v[y].et}, v[y].et = i << 1;
    e[i << 1 | 1] = {y, 0, v[n2 + x].et}, v[n2 + x].et = i << 1 | 1;
  }
  cin >> m2;
  for (int i = 1, x, y; i <= m2; i++) {
    cin >> x >> y;
    e[m1 + i << 1] = {n2 + n1 + n1 + y, 1, v[n2 + n1 + x].et}, v[n2 + n1 + x].et = m1 + i << 1;
    e[m1 + i << 1 | 1] = {n2 + n1 + x, 0, v[n2 + n1 + n1 + y].et}, v[n2 + n1 + n1 + y].et = m1 + i << 1 | 1;
  }
  n = n2 + n1 + n1 + n3 + 2, s = n - 1, t = n;
  for (int i = 1; i <= n2; i++) {
    e[m1 + m2 + i << 1] = {i, 1, v[s].et}, v[s].et = m1 + m2 + i << 1;
    e[m1 + m2 + i << 1 | 1] = {s, 0, v[i].et}, v[i].et = m1 + m2 + i << 1 | 1;
  }
  for (int i = 1; i <= n1; i++) {
    e[m1 + m2 + n2 + i << 1] = {n2 + n1 + i, 1, v[n2 + i].et}, v[n2 + i].et = m1 + m2 + n2 + i << 1;
    e[m1 + m2 + n2 + i << 1 | 1] = {n2 + i, 0, v[n2 + n1 + i].et}, v[n2 + n1 + i].et = m1 + m2 + n2 + i << 1 | 1;
  }
  for (int i = 1; i <= n3; i++) {
    e[m1 + m2 + n2 + n1 + i << 1] = {t, 1, v[n2 + n1 + n1 + i].et}, v[n2 + n1 + n1 + i].et = m1 + m2 + n2 + n1 + i << 1;
    e[m1 + m2 + n2 + n1 + i << 1 | 1] = {n2 + n1 + n1 + i, 0, v[t].et}, v[t].et = m1 + m2 + n2 + n1 + i << 1 | 1;
  }
  for (Bfs(); !v[0].d; ans += Dfs(s, kInf)) {
  }
  cout << ans;
  return 0;
}
