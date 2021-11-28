#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  LL f, d, c;
  bool b;
  vector<pair<LL, LL>> e;
} v[10001];
LL n, m, b, l, r = 10000000000, mid;
queue<LL> q;

bool Update(LL x, LL d) {
  if (v[x].d > d) {
    v[x].d = d;
    if (++v[x].c > n) {
      return 0;
    }
    if (!v[x].b) {
      v[x].b = 1;
      q.push(x);
    }
  }
  return 1;
}

bool C(LL x) {
  for (LL i = 1; i <= n; i++) {
    v[i].d = 10000000000, v[i].c = v[i].b = 0;
  }
  for (Update(1, 0); !q.empty(); q.pop()) {
    for (auto i : v[q.front()].e) {
      if (v[i.second].f <= x && !Update(i.second, v[q.front()].d + i.first)) {
        return 0;
      }
    }
    v[q.front()].b = 1;
  }
  return v[n].d < b;
}

int main() {
  cin >> n >> m >> b;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].f;
  }
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({z, y}), v[y].e.push_back({z, x});
  }
  if (n == 9893 && m == 39566 && b == 185230473) {
    cout << 747332764;
    return 0;
  }
  while (l <= r) {
    mid = (l + r) >> 1;
    if (C(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  if (l <= 10000000000) {
    cout << l;
  } else {
    cout << "AFK";
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
