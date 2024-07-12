#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

ifstream cin("isaac.in");
ofstream cout("isaac.out");

const int kMaxN = 101, kMaxM = 1001;
const double kInf = 1e9, kEps = 1e-10;
struct V {
  int l, r;
  double f[kMaxM];
  vector<pair<int, double>> e;
} v[kMaxN];
int n, m;
double l, r, mid;

void T(int x, double w) {
  for (auto i : v[x].e) {
    T(i.first, w);
  }
  for (int i = 0; i <= m; i++) {
    v[x].f[i] = 0;
    for (int j = v[x].l; j <= v[x].r; j++) {
      if (i >= j) {
        double s = 0;
        for (auto k : v[x].e) {
          s += v[k.first].f[i - j] * k.second;
        }
        v[x].f[i] += min(s, w) + j;
      } else {
        v[x].f[i] += w + j;
      }
    }
    v[x].f[i] /= v[x].r - v[x].l + 1;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].l >> v[i].r;
  }
  for (int i = 2, x; i <= n; i++) {
    cin >> x >> l;
    v[x].e.push_back({i, l});
  }
  l = 0, r = kInf * 2.0;
  while (l < r - kEps) {
    mid = (l + r) / 2.0, T(1, mid);
    if (v[1].f[m] > mid) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (l > kInf - kEps) {
    cout << -1 << '\n';
  } else {
    cout << fixed << setprecision(9) << l << '\n';
  }
  return 0;
}
