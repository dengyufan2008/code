#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const LL kMaxN = 1 << 17, kMaxM = 1LL << 34;
struct A {
  int x, y;
};
struct V {
  int s;
  LL w;
  A e[2];
  vector<A> f;
} v[kMaxN];
int n;
LL l, r, m;

void S(int x) {
  if (!x) {
    return;
  }
  v[x].s = 1;
  for (int o : {0, 1}) {
    v[v[x].e[o].x].w = v[x].w + v[x].e[o].y;
    S(v[x].e[o].x);
    v[x].s += v[v[x].e[o].x].s;
  }
  if (v[v[x].e[0].x].s < v[v[x].e[1].x].s) {
    swap(v[x].e[0], v[x].e[1]);
  }
}

void T(int x) {
  v[x].f.clear();
  if (v[x].s == 1) {
    v[x].f.push_back({x, x});
    return;
  }
  int l = v[x].e[0].x, r = v[x].e[1].x;
  T(l), T(r);
  for (int i = v[r].f.size() - 1, j = 0, mn = 0; i >= 0; i--) {
    for (; j < v[l].f.size(); j++) {
      if (v[v[l].f[j].x].w + v[v[r].f[i].x].w - v[x].w * 2 > m) {
        break;
      }
      if (!mn || v[mn].w > v[v[l].f[j].y].w) {
        mn = v[l].f[j].y;
      }
    }
    if (mn) {
      v[x].f.push_back({mn, v[r].f[i].y}), v[x].f.push_back({v[r].f[i].y, mn});
    }
  }
  v[l].f.clear(), v[r].f.clear();
  sort(v[x].f.begin(), v[x].f.end(), [](A i, A j) {
    return v[i.x].w < v[j.x].w;
  });
}

bool C() { return T(1), !v[1].f.empty(); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2, x, y; i <= n; i++) {
    cin >> x >> y;
    if (v[x].e[0].x) {
      v[x].e[1] = {i, y};
    } else {
      v[x].e[0] = {i, y};
    }
  }
  S(1), l = 0, r = kMaxM;
  while (l <= r) {
    m = l + r >> 1;
    if (C()) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
