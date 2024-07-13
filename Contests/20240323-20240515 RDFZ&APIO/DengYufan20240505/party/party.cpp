#include <algorithm>
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
int n, w, q[kMaxN], l[kMaxN];
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

void CalcAns(int x) {
  static LL s;
  s = 0, T(x);
  for (int i = 1; i <= n; i++) {
    s += v[q[i]].d, ans = max(ans, sqt[i] * w - s);
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
  for (int i = 1; i <= n; i++) {
    l[i] = i, sqt[i] = sqrt(i);
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return v[i].e.size() > v[j].e.size();
  });
  for (int i = 1; i <= 100; i++) {
    CalcAns(l[i]);
  }
  cout << fixed << setprecision(2) << ans << '\n';
  return 0;
}
