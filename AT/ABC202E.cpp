#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d;
} e[400002];
struct B {
  int et, d;
} v[200001];
int n, q, u, d, p[200001];

void T(int f, int x) {  //生成每个点到根的距离
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f) {
      v[e[i].d].d = v[x].d + 1;
      T(x, e[i].d);
    }
  }
}

int M(int f, int x, int d) {
  if (!d) {
    return 1;
  }
  int ans = 0;
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f) {
      ans += M(x, e[i].d, d - 1);
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> p[i];
    e[i * 2] = {v[i].et, p[i]}, v[i].et = i * 2;
    e[i * 2 + 1] = {v[p[i]].et, i}, v[p[i]].et = i * 2 + 1;
  }
  T(0, 1);
  cin >> q;
  while (q--) {
    cin >> u >> d;
    cout << M(p[u], u, d - v[u].d) << endl;
  }
  return 0;
}
