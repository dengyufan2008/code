#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5e5 + 1;
struct E {
  int p, n, d, f;
} e[kMaxN * 8];
int n, s, t, k, d[kMaxN];
bool o[kMaxN];
vector<int> l, a[kMaxN], b[kMaxN], c[kMaxN];

void Clear() {
  for (int i : l) {
    o[i] = d[i] = 0;
  }
  k = n + t + 1 + (n + t & 1), l.clear();
}

void AddEdge(int x, int y, int f = 0) {
  if (!o[x]) {
    o[x] = 1, e[x].p = e[x].n = x, l.push_back(x);
  }
  if (!o[y]) {
    o[y] = 1, e[y].p = e[y].n = y, l.push_back(y);
  }
  d[x]++, d[y]++;
  e[++k] = {x, e[x].n, y, f}, e[e[x].n].p = k, e[x].n = k;
  e[++k] = {y, e[y].n, x, f}, e[e[y].n].p = k, e[y].n = k;
}

void S(int x) {
  if (e[x].n != x) {
    int i = e[x].n;
    e[x].n = e[i].n, e[e[i].n].p = x;
    e[e[i ^ 1].p].n = e[i ^ 1].n;
    e[e[i ^ 1].n].p = e[i ^ 1].p;
    if (x <= n) {
      b[x].push_back(e[i].d - n);
    } else if (e[i].d <= n) {
      c[e[i].d].push_back(x - n);
    }
    S(e[i].d);
  }
}

void Solve(int l, int r) {
  if (l == r) {
    return;
  }
  Clear();
  for (int i = 1; i <= n; i++) {
    for (int j = l; j <= r; j++) {
      AddEdge(i, n + a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = l; j <= r; j++) {
      if (d[n + a[i][j]] & 1) {
        AddEdge(n + t + 1, n + a[i][j], i);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    S(i);
  }
  int mid = l + r >> 1;
  for (int i = 1; i <= n; i++) {
    for (int j = l; j <= mid; j++) {
      a[i][j] = b[i][j - l];
    }
    for (int j = mid + 1; j <= r; j++) {
      a[i][j] = c[i][j - mid - 1];
    }
    b[i].clear(), c[i].clear();
  }
  Solve(l, mid), Solve(mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s >> t;
  for (int i = 1; i <= n; i++) {
    a[i].resize(1);
    for (int j = 1, x; j <= s; j++) {
      cin >> x, a[i].push_back(x);
    }
  }
  Solve(1, s);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= s; j++) {
      cout << a[i][j] << " \n"[j == s];
    }
  }
  return 0;
}
