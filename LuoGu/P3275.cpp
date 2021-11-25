#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  LL d = -1, c;
  bool b;
  vector<pair<LL, LL>> e;
} v[100001];
LL n, k, ans;
queue<LL> q;

bool Update(LL x, LL d) {
  if (v[x].d < d) {
    v[x].d = d;
    if (++v[x].c == n) {
      return 0;
    }
    if (!v[x].b) {
      v[x].b = 1;
      q.push(x);
    }
  }
  return 1;
}

bool Spfa() {
  for (Update(0, 0); !q.empty(); q.pop()) {
    for (auto i : v[q.front()].e) {
      if (!Update(i.first, v[q.front()].d + i.second)) {
        return 0;
      }
    }
    v[q.front()].b = 0;
  }
  return 1;
}

int main() {
  cin >> n >> k;
  for (LL i = 1, x, y, z; i <= k; i++) {
    cin >> x >> y >> z;
    if (x == 1) {
      v[y].e.push_back({z, 0}), v[z].e.push_back({y, 0});
    } else if (x == 2) {
      v[y].e.push_back({z, 1});
    } else if (x == 3) {
      v[z].e.push_back({y, 0});
    } else if (x == 4) {
      v[z].e.push_back({y, 1});
    } else {
      v[y].e.push_back({z, 0});
    }
    if (!(x & 1) && y == z) {
      cout << -1;
      return 0;
    }
  }
  for (LL i = 1; i <= n; i++) {
    v[0].e.push_back({i, 1});
  }
  if (Spfa()) {
    for (LL i = 1; i <= n; i++) {
      ans += v[i].d;
    }
  } else {
    ans = -1;
  }
  cout << ans;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
