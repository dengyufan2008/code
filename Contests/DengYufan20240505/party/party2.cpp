#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("party.in");
ofstream cout("party.ans");

const LL kMaxN = 2e5 + 1, kInf = 1e18;
struct V {
  vector<int> e;
} v[kMaxN];
int n, w;
double ans;
vector<int> l;

void T(int f, int x, int d = 0) {
  l.push_back(d);
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i, d + 1);
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
  for (int i = n; i >= 1; i--) {
    LL mnw = kInf;
    vector<int> mn;
    for (int j = 1; j <= n; j++) {
      LL w = 0;
      l.clear(), T(0, j), sort(l.begin(), l.end());
      for (int k = 0; k < i; k++) {
        w += l[k];
      }
      if (mnw > w) {
        mnw = w, mn.clear();
      }
      if (mnw == w) {
        mn.push_back(j);
      }
    }
    ans = max(ans, sqrt(i) * w - mnw);
    cout << mnw << ' ' << fixed << setprecision(2) << sqrt(i) * w - mnw << '\n';
    for (int i : mn) {
      cout << i << ' ';
    }
    cout << "\n\n";
  }
  cout << fixed << setprecision(2) << ans << '\n';
  return 0;
}
