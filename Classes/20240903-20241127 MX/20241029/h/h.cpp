#include <fstream>
#include <vector>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 25001, kMaxM = 4001, kInf = 1e9;
struct V {
  int w, f[kMaxM];
  vector<int> e;
} v[kMaxN];
int t, n, ans;

void T(int x) {
  if (v[x].e.empty()) {
    for (int i = 1; i < kMaxM; i++) {
      v[x].f[i] = i == v[x].w ? kInf : 0;
    }
  } else if (v[x].e.size() == 1) {
    int y = v[x].e.front(), mn = kInf;
    T(y);
    for (int i = 1; i < kMaxM; i++) {
      mn = min(mn, i == v[x].w ? kInf : v[y].f[i] + i);
    }
    if (x == 1) {
      cout << mn << '\n';
    } else {
      for (int i = 1; i < kMaxM; i++) {
        v[x].f[i] = i == v[x].w ? kInf : min(v[y].f[i], mn);
      }
    }
  } else {
    int l = v[x].e.front(), r = v[x].e.back();
    int mnl = kInf, mnr = kInf, mnlr = kInf;
    T(l), T(r);
    for (int i = 1; i < kMaxM; i++) {
      mnl = min(mnl, i == v[x].w ? kInf : v[l].f[i] + i);
      mnr = min(mnr, i == v[x].w ? kInf : v[r].f[i] + i);
      mnlr = min(mnlr, i == v[x].w ? kInf : v[l].f[i] + v[r].f[i] + i);
    }
    mnlr = min(mnlr, min(mnl + mnr, kInf));
    if (x == 1) {
      cout << mnlr << '\n';
    } else {
      for (int i = 1; i < kMaxM; i++) {
        v[x].f[i] = i == v[x].w ? kInf : min(min(v[l].f[i] + mnr, v[r].f[i] + mnl), mnlr);
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].w, v[i].e.clear();
    }
    for (int i = 2, x; i <= n; i++) {
      cin >> x, v[x].e.push_back(i);
    }
    T(1);
  }
  return 0;
}
