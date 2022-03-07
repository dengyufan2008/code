#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kInf = 1e9;
struct E {
  int x, v, p;
} e[42042];
struct V {
  int et, nt, d;
} v[1023];
int n, b, c, l, r, a[1002][21];

void AddE(int x, int y, int z) {
  e[++c] = {y, z, v[x].et}, v[x].et = c;
  e[++c] = {x, 0, v[y].et}, v[y].et = c;
}

bool Bfs() {
  queue<int> q;
  for (int i = 1; i <= n + b + 2; i++) {
    v[i].d = i == n + b + 1, v[i].nt = v[i].et;
  }
  for (q.push(n + b + 1); !q.empty(); q.pop()) {
    for (int i = v[q.front()].et; i; i = e[i].p) {
      if (!v[e[i].x].d && e[i].v) {
        v[e[i].x].d = v[q.front()].d + 1, q.push(e[i].x);
      }
    }
  }
  return v[n + b + 2].d;
}

int Dfs(int x, int in) {
  if (x == n + b + 2) {
    return in;
  }
  int out = 0;
  for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
    if (e[i].v && v[x].d + 1 == v[e[i].x].d) {
      int t = Dfs(e[i].x, min(in, e[i].v));
      e[i].v -= t, e[i ^ 1].v += t;
      in -= t, out += t;
    }
  }
  return out;
}

bool C(int x) {
  for (int i = 1, j, t = 0; (j = i + x - 1) <= b; i++, t = 0) {
    c = 1;
    for (int k = 1; k <= n + b + 2; k++) {
      v[k].et = 0;
    }
    for (int k = 1; k <= n; k++) {
      AddE(n + b + 1, k, 1);
    }
    for (int k = 1; k <= b; k++) {
      AddE(n + k, n + b + 2, a[n + 1][k]);
    }
    for (int k = 1; k <= n; k++) {
      for (int l = i; l <= j; l++) {
        AddE(k, n + a[k][l], 1);
      }
    }
    for (; Bfs(); t += Dfs(n + b + 1, kInf)) {
    }
    if (t == n) {
      return 1;
    }
  }
  return 0;
}

int main() {
  cin >> n >> b;
  for (int i = 1; i <= n + 1; i++) {
    for (int j = 1; j <= b; j++) {
      cin >> a[i][j];
    }
  }
  l = 1, r = b - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (C(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << l;
  return 0;
}
