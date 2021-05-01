#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d;
} e[200001];

struct B {
  int et, ans, d;
} v[200001];

int t, n, m, q[200001] = {1};

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    fill(e + 1, e + m + 1, e[0]), fill(v + 1, v + n + 1, v[0]);
    for (int i = 1, a, b; i <= m; i++) {
      cin >> a >> b;
      e[i] = {v[a].et, b}, v[a].et = i;
    }
    v[1].d = v[1].ans = 1;
    for (int h = 0, t = 0; h <= t; h++) {  //求每个点到1的距离
      for (int i = v[q[h]].et; i; i = e[i].p) {
        if (!v[e[i].d].d) {
          v[e[i].d].d = v[q[h]].d + 1;
          q[++t] = e[i].d;
        }
      }
    }
    for (int i = n; i >= 1; i--) {  //求答案
      v[q[i]].ans = v[q[i]].d;
      for (int j = v[q[i]].et; j; j = e[j].p) {
        v[q[i]].ans = min(v[q[i]].ans, (v[e[j].d].d <= v[q[i]].d ? v[e[j].d].d : v[e[j].d].ans));
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << v[i].ans - 1 << " ";
    }
    cout << endl;
  }
  return 0;
}
