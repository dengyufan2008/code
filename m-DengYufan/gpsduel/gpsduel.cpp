#include <time.h>
#include <windows.h>

#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL d[2] = {1145141919810, 1145141919810}, p[2];
  bool b[2];
  vector<pair<LL, LL>> e[2], _e[2];
} v[10001];
LL n, m, ans = 1145141919810;
bool b[10001];

void M(LL c) {
  v[n].d[c] = 0;
  for (LL i = 1; i < n; i++) {
    LL mn = 0;
    for (LL j = 1; j <= n; j++) {
      if (!v[j].b[c] && v[j].d[c] < v[mn].d[c]) {
        mn = j;
      }
    }
    v[mn].b[c] = 1;
    for (pair<LL, LL> j : v[mn]._e[c]) {
      if (v[j.first].d[c] > v[mn].d[c] + j.second) {
        v[j.first].d[c] = v[mn].d[c] + j.second;
        v[j.first].p[c] = mn;
      }
    }
  }
}

void S(LL x, LL s) {
  if (b[x]) {
    return;
  } else if (x == n) {
    ans = min(ans, s);
    return;
  }
  b[x] = 1;
  for (pair<LL, LL> j : v[x].e[0]) {
    S(j.first, s + (v[x].p[0] != j.first) + (v[x].p[1] != j.first));
  }
  b[x] = 0;
}

int main() {
  freopen("gpsduel.in", "r", stdin);
  freopen("gpsduel.out", "w", stdout);
  cin >> n >> m;
  for (LL i = 1, a, b, p, q; i <= m; i++) {
    cin >> a >> b >> p >> q;
    v[a].e[0].push_back(make_pair(b, p));
    v[a].e[1].push_back(make_pair(b, q));
    v[b]._e[0].push_back(make_pair(a, p));
    v[b]._e[1].push_back(make_pair(a, q));
  }
  M(0), M(1);
  S(1, 0);
  cout << ans << endl;
  return 0;
}
