#include <fstream>
#include <vector>

using namespace std;

ifstream cin("easy.in");
ofstream cout("easy.out");

const int kMaxN = 1e6 + 1;
struct E {
  int p, d, o;
} e[kMaxN << 1];
struct V {
  int eh, et, d, l, r;
  bool b;
} v[kMaxN];
int n, m, k, ans[kMaxN];
vector<int> l;

void S(int f, int x) {
  if (v[x].d) {
    return;
  }
  v[x].d = v[x].l = ++k;
  l.push_back(x);
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f) {
      S(x, e[i].d);
      v[x].l = min(v[x].l, v[e[i].d].l);
    }
  }
  if (v[x].d == v[x].l) {
    while (l.back() != x) {
      v[l.back()].r = x, l.pop_back();
    }
    v[x].r = x, l.pop_back();
  }
}

void T(int f, int x) {
  if (v[x].b) {
    return;
  }
  v[x].b = 1;
  for (int i = v[x].et; i; i = e[i].p) {
    if (!ans[e[i].o] && v[e[i].d].r == v[x].r) {
      ans[e[i].o] = (i & 1) + 1;
      T(x, e[i].d);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    e[i * 2] = {v[x].et, y, i}, !v[x].eh && (v[x].eh = i * 2), v[x].et = i * 2;
    e[i * 2 + 1] = {v[y].et, x, i}, !v[y].eh && (v[y].eh = i * 2 + 1), v[y].et = i * 2 + 1;
  }
  S(0, 1);
  for (int i = 1; i <= n; i++) {
    T(0, v[i].r);
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i];
  }
  return 0;
}
