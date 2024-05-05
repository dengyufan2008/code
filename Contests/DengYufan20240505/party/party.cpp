#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("party.in");
ofstream cout("party.out");

const int kMaxN = 2e5 + 1;
struct V {
  int d;
  vector<int> e;
} v[kMaxN];
int n, w, q[kMaxN];
double ans, sqt[kMaxN];

void T(int x) {
  for (int i = 1; i <= n; i++) {
    v[i].d = -1;
  }
  v[x].d = 0, q[1] = x;
  for (int h = 1, t = 1; h <= t; h++) {
    for (int i : v[q[h]].e) {
      if (!~v[i].d) {
        v[i].d = v[q[h]].d + 1, q[++t] = i;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> w;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (w == 1) {
    cout << "1.00\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    sqt[i] = sqrt(i);
  }
  for (int i = 1; i <= n; i++) {
    LL s = 0;
    T(i);
    for (int j = 1; j <= n; j++) {
      s += v[q[j]].d, ans = max(ans, sqt[j] * w - s);
    }
  }
  cout << fixed << setprecision(2) << ans << '\n';
  return 0;
}
