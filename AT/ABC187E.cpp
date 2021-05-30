#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct E {
  int p, d;
} e[402];
struct V {
  int et, d;
} v[201];
int n, q, x, y, z;

void T(int f, int x) {
  v[x].d += z;
  for (int i = v[x].et; i; i = e[i].p) {
    if (f != e[i].d) {
      T(x, e[i].d);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, a, b; i <= n; i++) {
    cin >> a >> b;
    e[i * 2] = {v[a].et, b}, v[a].et = i * 2;
    e[i * 2 + 1] = {v[b].et, a}, v[b].et = i * 2 + 1;
  }
  cin >> q;
  while (q--) {
    cin >> x >> y >> z;
    x == 1 ? T(e[y * 2].d, e[y * 2 + 1].d) : T(e[y * 2 + 1].d, e[y * 2].d);
  }
  for (int i = 1; i <= n; i++) {
    cout << v[i].d << endl;
  }
  return 0;
}
