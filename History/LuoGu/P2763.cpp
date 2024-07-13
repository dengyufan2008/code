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
int k, n, m, c = 1, ans;

void AddEdge(int x, int y, int z) {
  e[++c] = {y, z, v[x].et}, v[x].et = c;
  e[++c] = {x, 0, v[y].et}, v[y].et = c;
}

bool Bfs() {
  queue<int> q;
  for (int i = 1; i <= k + n + 2; i++) {
    v[i].d = i == k + n + 1, v[i].nt = v[i].et;
  }
  for (q.push(k + n + 1); !q.empty(); q.pop()) {
    for (int i = v[q.front()].et; i; i = e[i].p) {
      if (!v[e[i].x].d && e[i].v) {
        v[e[i].x].d = v[q.front()].d + 1, q.push(e[i].x);
      }
    }
  }
  return v[k + n + 2].d;
}

int Dfs(int x, int in) {
  if (x == k + n + 2) {
    return in;
  }
  int out = 0;
  for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
    if (e[i].v && v[e[i].x].d == v[x].d + 1) {
      int t = Dfs(e[i].x, min(in, e[i].v));
      e[i].v -= t, e[i ^ 1].v += t;
      in -= t, out += t;
    }
  }
  return out;
}

int main() {
  cin >> k >> n;
  for (int i = 1, x; i <= k; i++) {
    cin >> x;
    m += x;
    AddEdge(i, k + n + 2, x);
  }
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x;
    AddEdge(k + n + 1, k + i, 1);
    for (int j = 1; j <= x; j++) {
      cin >> y;
      AddEdge(k + i, y, 1);
    }
  }
  for (; Bfs(); ans += Dfs(k + n + 1, kInf)) {
  }
  if (ans == m) {
    for (int i = 1; i <= k; i++) {
      cout << i << ':';
      for (int j = v[i].et; j; j = e[j].p) {
        if (e[j].v) {
          cout << ' ' << e[j].x - k;
        }
      }
      cout << '\n';
    }
  } else {
    cout << "No Solution!";
  }
  return 0;
}
