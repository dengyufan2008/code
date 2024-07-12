#include <fstream>
#include <vector>

using namespace std;

ifstream cin("travel.in");
ofstream cout("travel.out");

const int kMaxN = 2e5 + 1, kInf = 1e9;
struct V {
  int f;
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  v[0].f = kInf, fill(&v[2], &v[kMaxN], v[0]);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[min(x, y)].e.push_back(max(x, y));
  }
  for (int i = 1, mx = 0, s = 0; i <= n; i++) {
    for (int j : v[i].e) {
      !v[j].b && (v[j].b = 1) && (s++);
      mx = max(mx, j);
    }
    if (i > 2) {
      v[i].f = min(v[i].f, v[i - 1].f + 1);
    }
    s -= v[i].b, mx = max(mx, i + 1);
    if (mx <= n) {
      v[mx].f = min(v[mx].f, v[i].f + mx - i - s);
    }
  }
  cout << v[n].f;
  return 0;
}
