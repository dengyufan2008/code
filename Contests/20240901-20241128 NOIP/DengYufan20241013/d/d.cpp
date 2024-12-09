#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const LL kMaxN = 1e5 + 1, kInf = 1e18;
struct V {
  int w, mn, mx = -1;
  LL ans;
  vector<pair<int, int>> e;
} v[kMaxN];
int n;

void Init(int f, int x) {
  v[x].mn = 1e9;
  static vector<pair<int, int>> e;
  for (auto i : v[x].e) {
    if (i.first != f) {
      e.push_back(i);
    } else {
      v[x].mn = i.second;
    }
  }
  v[x].e.swap(e), e.clear();
  for (auto i : v[x].e) {
    Init(x, i.first);
    v[x].mn = min(v[x].mn, i.second);
  }
}

void CalcMax(int x);

LL Calc(int x, int t) {
  v[x].mx == -1 ? CalcMax(x) : void();
  if (t >= v[x].mx) {
    return v[x].ans;
  }
  LL ans = 1LL * v[x].w * t;
  for (auto i : v[x].e) {
    ans += Calc(i.first, i.second - t);
  }
  return ans;
}

void CalcMax(int x) {
  if (~v[x].mx) {
    return;
  } else if (v[x].e.empty()) {
    v[x].mx = v[x].mn, v[x].ans = 1LL * v[x].w * v[x].mx;
    return;
  }
  int mx = v[x].mn >> 1;
  LL ans = 1LL * v[x].w * mx;
  for (auto i : v[x].e) {
    ans += Calc(i.first, i.second - mx);
  }
  for (int i = 28; i >= 0; i--) {
    if (mx >= 1 << i) {
      int _mx = mx - (1 << i);
      LL _ans = 1LL * v[x].w * _mx;
      for (auto j : v[x].e) {
        _ans += Calc(j.first, j.second - _mx);
      }
      if (ans < _ans) {
        ans = _ans, mx -= 1 << i;
        continue;
      }
    }
    if (mx + (1 << i) <= v[x].mn) {
      int _mx = mx + (1 << i);
      LL _ans = 1LL * v[x].w * _mx;
      for (auto j : v[x].e) {
        _ans += Calc(j.first, j.second - _mx);
      }
      if (ans < _ans) {
        ans = _ans, mx += 1 << i;
        continue;
      }
    }
  }
  v[x].mx = mx, v[x].ans = ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  Init(0, 1), CalcMax(1);
  cout << v[1].ans << '\n';
  return 0;
}
