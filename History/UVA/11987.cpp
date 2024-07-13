#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL f, s, d;
} v[200001];
LL n, m;

LL GetRoot(LL x) {
  return v[x].f == x ? x : v[x].f = GetRoot(v[x].f);
}

void Merge(LL x, LL y) {
  LL _x = GetRoot(x), _y = GetRoot(y);
  if (_x != _y) {
    v[_x].f = _y;
    v[_y].s += v[_x].s;
    v[_y].d += v[_x].d;
  }
}

void Move(LL x, LL y) {
  LL _x = GetRoot(x), _y = GetRoot(y);
  if (_x != _y) {
    v[x].f = _y;
    v[_x].s--, v[_y].s++;
    v[_x].d -= x, v[_y].d += x;
  }
}

int main() {
  while (cin >> n >> m) {
    for (LL i = 1; i <= n; i++) {
      v[i] = {i + n, 1, i}, v[i + n] = {i + n, 1, i};
    }
    for (LL i = 1, o, x, y; i <= m; i++) {
      cin >> o >> x;
      if (o == 1) {
        cin >> y;
        Merge(x, y);
      } else if (o == 2) {
        cin >> y;
        Move(x, y);
      } else {
        cout << v[GetRoot(x)].s << ' ' << v[GetRoot(x)].d << '\n';
      }
    }
  }
  return 0;
}
