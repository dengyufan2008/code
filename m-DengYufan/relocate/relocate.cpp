#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kM = 1e8;
struct V {
  int d[6] = {kM, kM, kM, kM, kM, kM};
  vector<pair<int, int>> e;
} v[10001];
int n, m, k, ans = kM, a[6];
bool b[6];
priority_queue<pair<int, int>> q;  // dis, num

void S(int x, int p, int d, int s) {
  if (x == k) {
    for (int i = 1; i <= n; i++) {
      if (!b[i]) {
        ans = min(ans, d + v[i].d[s] + v[i].d[p]);
      }
    }
    return;
  }
  for (int i = 1; i <= k; i++) {
    if (!b[i]) {
      b[i] = 1;
      S(x + 1, i, d + v[a[i]].d[p], s);
      b[i] = 0;
    }
  }
}

int main() {
  freopen("relocate.in", "r", stdin);
  freopen("relocate.out", "w", stdout);
  cin >> n >> m >> k;
  for (int i = 1; i <= k ;i++) {
    cin >> a[i];
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  for (int i = 1; i <= k; i++) {
    q.push({0, a[i]});
    v[a[i]].d[i] = 0;
    for (int j = 1; j <= n; j++) {
      auto c = q.top();
      q.pop();
      for (auto k : v[c.second].e) {
        if (v[k.first].d[i] > v[c.second].d[i] + k.second) {
          v[k.first].d[i] = v[c.second].d[i] + k.second;
          q.push({-v[k.first].d[i], k.first});
        }
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    b[i] = 1;
    S(1, i, 0, i);
    b[i] = 0;
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
