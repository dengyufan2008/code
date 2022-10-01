#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e1 + 1;
struct H {
  int a[kMaxN];

  void Add(int x, int y) {
    for (int i = x; i < kMaxN; i += i & -i) {
      a[i] += y;
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += a[i];
    }
    return ans;
  }

  int Ask(int x, int y) {
    return Ask(y) - Ask(x - 1);
  }
} d[3];
struct V {
  int s, t, _t;
  vector<int> e;
} v[kMaxN];
int t, n, s, ans;

void S(int f, int x, bool b) {
  v[x].s = 1, v[x].t = v[x]._t = 0;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i, b);
      v[x].s += v[i].s;
      if (v[v[x].t].s < v[i].s) {
        v[x]._t = v[x].t, v[x].t = i;
      } else if (v[v[x]._t].s < v[i].s) {
        v[x]._t = i;
      }
    }
  }
  if (b && max(v[v[x].t].s, n - v[x].s) <= n / 2) {
    s = x;
  } else if (!b) {
    d[1].Add(v[x].s, 1);
  }
}

void T(int f, int x) {
  if (x == v[s].t) {
    ans += (d[2].Ask(n - 2 * v[v[s].t].s) - d[2].Ask(n - 2 * v[v[s]._t].s)) * s;
  }
  ans += d[2].Ask(n - 2 * v[x].s, n - 2 * v[v[x].t].s) * x, d[2].Add(v[x].s, 1);
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
  ans += (d[1].Ask(n - 2 * v[x].s, n - 2 * v[v[x].t].s) - d[2].Ask(n - 2 * v[x].s, n - 2 * v[v[x].t].s)) * x;
  if (x == v[s].t) {
    ans += (d[2].Ask(n - 2 * v[v[s]._t].s) - d[2].Ask(n - 2 * v[v[s].t].s)) * s;
  }
}

int main() {
  cin >> t;
  while (t--) {
    d[1] = d[2] = d[0], fill(&v[1], &v[kMaxN], v[0]);
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    S(0, 1, 1), S(0, s, 0), ans = d[1].Ask(n - 2 * v[v[s].t].s) * s;
    for (int i : v[s].e) {
      T(s, i);
    }
    cout << ans << '\n';
  }
  return 0;
}
/*
n-2sx <= i <= n-2tx
非子树
1
5
1 2
2 3
2 4
3 5

*/
