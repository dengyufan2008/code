#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 2.5e5 + 1;
int t, n, m, w, a[kMaxN], b[kMaxN], l[kMaxN];
long long ans;
vector<int> v, s, _s;

void Update(int &x, int y) {
  ans -= x, x = max(x, y), ans += x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    ans = 0, s.clear(), v.clear();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
      ans += a[i], l[i] = i;
    }
    sort(l + 1, l + n + 1, [](int i, int j) {
      return b[i] > b[j];
    });
    w = b[l[(int)sqrt(n)]];
    for (int i = 1; i <= n; i++) {
      a[i] <= w ? s.push_back(i) : void();
      b[i] > w ? v.push_back(i) : void();
    }
    for (int i = 1, x; i <= m; i++) {
      cin >> x;
      for (int j : s) {
        Update(a[j], b[j + x > n ? j + x - n : j + x]);
        a[j] <= w ? _s.push_back(j) : void();
      }
      s.swap(_s), _s.clear();
      for (int j : v) {
        Update(a[j - x < 1 ? j - x + n : j - x], b[j]);
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
