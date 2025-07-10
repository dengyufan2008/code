#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
struct V {
  bool b1, b2;
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m;
vector<int> l;

void FindConnect(int x) {
  v[x].b1 = 1, l.push_back(x);
  for (auto i : v[x].e) {
    if (!v[i.first].b1) {
      FindConnect(i.first);
    }
  }
}

void FindOdd(int x) {
  v[x].b2 = 1;
  for (auto i : v[x].e) {
    if (!v[i.first].b2 && (i.second & 1)) {
      FindOdd(i.first);
    }
  }
}

LL CalcConnect() {
  int c = 0;
  LL ans = 2;
  for (int i : l) {
    if (!v[i].b2) {
      c++, ans = ans * kInv2 % kMod;
      FindOdd(i);
    }
  }
  for (int i : l) {
    for (auto j : v[i].e) {
      if (i <= j.first) {
        ans = ans * j.second % kMod;
      }
    }
  }
  LL w = (1 + 1LL * c * (c - 1) / 2) % kMod;
  return ans * w % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
    if (x != y) {
      v[y].e.push_back({x, z});
    }
  }
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!v[i].b1) {
      l.clear(), FindConnect(i);
      ans = (ans + CalcConnect() - 1) % kMod;
    }
  }
  ans = (ans + 1) % kMod;
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
