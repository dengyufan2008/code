#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("triangle.in");
ofstream cout("triangle.out");

const int kMaxN = 5001;
struct A {
  int x, y, l;
} a[kMaxN];
struct E {
  int x, y, l, r;
};
int n, m;
vector<E> e, v;

void Move(int p, int t, bool o) {
  int q = p;
  for (; p && o && e[p - 1].r < e[p - 1].l; p--) {
  }
  for (; e[q].r < e[q].l; q++) {
  }
  t++;
  int g = e[p].x + e[p].l - t;
  if (g) {
    v.push_back({t, e[p].y, e[q].y + e[q].l - e[p].y, g});
  }
  for (int i = p; i <= q;) {
    e[i].l -= g, e[i].r = min(e[i].r, e[i].l);
    if (e[i].l) {
      i++;
    } else {
      q--, e.erase(e.begin() + i);
    }
  }
}

bool MoveNext(int t) {
  if (e.empty()) {
    return 0;
  }
  int p = -1, s = 0;
  for (int i = 0; i < e.size(); i++) {
    if (e[i].r < e[i].l) {
      if (p == -1 || s < e[i].x + e[i].r - 2) {
        p = i, s = e[i].x + e[i].r - 2;
      }
    } else {
      if (p == -1 || s < e[i].x - 1) {
        p = i, s = e[i].x - 1;
      }
    }
  }
  return s >= t ? Move(p, s, 1), 1 : 0;
}

void Init() {
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.x + i.l > j.x + j.l;
  });
  for (int i = 1, j; i <= n; i++) {
    int t = a[i].x + a[i].l - 1;
    while (MoveNext(t)) {
    }
    for (j = 0; j < e.size(); j++) {
      if (e[j].y >= a[i].y && (e[j].y > a[i].y || e[j].x > a[i].x)) {
        break;
      }
    }
    if (j && e[j - 1].x - e[j - 1].y <= a[i].x - a[i].y) {
      continue;
    }
    if (j < e.size()) {
      Move(j, t, 1);
    }
    for (; j < e.size() && a[i].x - a[i].y <= e[j].x - e[j].y;) {
      bool o = e[j].r == e[j].l;
      e.erase(e.begin() + j);
      if (o && j < e.size()) {
        Move(j, t, 0);
      }
    }
    if (j < e.size() && e[j].y - a[i].y < a[i].l) {
      e.insert(e.begin() + j, {a[i].x, a[i].y, a[i].l, e[j].y - a[i].y});
    } else {
      e.insert(e.begin() + j, {a[i].x, a[i].y, a[i].l, a[i].l});
    }
    if (j) {
      j--;
      if (e[j].r == e[j].l) {
        Move(j, t, 1);
      }
      if (e[j].x <= t && e[j].r > a[i].y - e[j].y) {
        e[j].r = a[i].y - e[j].y;
      }
    }
  }
  while (MoveNext(0)) {
  }
}

LL Merge(A p, A q) {
  p.y > q.y ? swap(p, q) : void();
  if (p.y - p.x <= q.y - q.x) {
    if (q.y - p.y < p.l && q.y - q.x - p.y + p.x < q.l) {
      int l = min(p.l, q.l - p.x + q.x) + p.y - q.y;
      return 1LL * l * (l + 1) / 2;
    }
  } else {
    if (q.x - p.x < p.l) {
      int l = min(p.x - q.x + p.l, q.l);
      return 1LL * l * (l + 1) / 2;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y >> a[i].l;
  }
  Init(), cin >> m;
  for (int i = 1, x, y, l; i <= m; i++) {
    cin >> x >> y >> l;
    LL ans = 1LL * l * (l + 1) / 2;
    for (E j : v) {
      ans -= Merge({j.x + j.r - j.l, j.y, j.l}, {x, y, l});
      ans += Merge({j.x + j.r - j.l, j.y, j.l - j.r}, {x, y, l});
    }
    cout << ans << '\n';
  }
  return 0;
}
