#include <algorithm>
#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1, kMaxL = 20;
int n, m, p, b, a[kMaxN];
pair<int, int> q[kMaxN];
bitset<kMaxN> w, s[kMaxL][kMaxL];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p, b = (n + kMaxL - 1) / kMaxL;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i += b) {
    w.reset();
    for (int j = i; j < n; j++) {
      w.set(a[j]);
      if (j % b == b - 1) {
        s[i / b][j / b] = w;
      }
    }
  }
  for (int i = 1, k, _k, ans = 0; i <= m; i++) {
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> q[j].first >> q[j].second;
      if (i > 1 && p) {
        q[j].first = (q[j].first ^ ans) % n;
        q[j].second = (q[j].second ^ ans) % n;
        q[j].first > q[j].second ? swap(q[j].first, q[j].second) : void();
      } else {
        q[j].first--, q[j].second--;
      }
    }
    sort(q, q + k), _k = -1;
    for (int j = 0; j < k; j++) {
      if (_k < 0 || q[_k].second + 1 < q[j].first) {
        q[++_k] = q[j];
      } else {
        q[_k].second = max(q[_k].second, q[j].second);
      }
    }
    k = _k, w.reset();
    if (k < 20) {
      for (int j = 0; j <= k; j++) {
        int l = q[j].first, r = q[j].second;
        int lo = l / b, ro = r / b;
        if (lo == ro) {
          for (int t = l; t <= r; t++) {
            w.set(a[t]);
          }
        } else {
          for (int t = lo * b + b - 1; t >= l; t--) {
            w.set(a[t]);
          }
          for (int t = ro * b; t <= r; t++) {
            w.set(a[t]);
          }
          if (lo + 1 <= ro - 1) {
            w |= s[lo + 1][ro - 1];
          }
        }
      }
      cout << (ans = w.count()) << '\n';
    } else {
      ans = 0;
      for (int j = 0; j <= k; j++) {
        for (int t = q[j].first; t <= q[j].second; t++) {
          ans += !w[a[t]], w[a[t]] = 1;
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
