#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct E {
  int p, d, x;
} e[100001];
struct V {
  int et, i, e, l = 1e9;
} v[100001];
int n, m, k, a[100001];

void Sort() {
  int h = 0, d[100001];
  for (int i = 1; i <= n; i++) {
    if (!v[i].i) {
      d[++h] = i;
    }
  }
  while (h) {
    int x = d[h--];
    a[++k] = x;
    for (int i = v[x].et; i; i = e[i].p) {
      if (!--v[e[i].d].i) {
        d[++h] = e[i].d;
      }
    }
  }
}

void Early() {
  for (int i = 1; i <= k; i++) {
    for (int j = v[a[i]].et; j; j = e[j].p) {
      v[e[j].d].e = max(v[e[j].d].e, v[a[i]].e + e[j].x);
    }
  }
}

void Late() {
  v[a[k]].l = v[a[k]].e;
  for (int i = k - 1; i; i--) {
    for (int j = v[a[i]].et; j; j = e[j].p) {
      v[a[i]].l = min(v[a[i]].l, v[e[j].d].l - e[j].x);
    }
  }
}

void Print(int x, int y) {
  if (e[y].p) {
    Print(x, e[y].p);
  }
  cout << x << " " << e[y].d << " " << v[x].e << " " << v[e[y].d].l - e[y].x << " " << v[e[y].d].l - e[y].x - v[x].e << endl;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; i++) {
    cin >> a >> b >> c;
    e[i] = {v[a].et, b, c}, v[a].et = i, v[b].i++;
  }
  Sort();
  Early();
  Late();
  for (int i = 1; i <= n; i++) {
    if (v[i].et) {
      Print(i, v[i].et);
    }
  }
  return 0;
}
