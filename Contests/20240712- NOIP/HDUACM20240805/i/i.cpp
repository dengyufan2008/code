// O((n+q) \sqrt t)
#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 5e5 + 1;
struct V {
  int l, r, o;
} v[kMaxN << 1];
int t, n, m, ht, _ht, ans;
pair<int, int> h[kMaxN], _h[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1, o, l, r; i <= n; i++) {
      cin >> v[i].o >> v[i].l >> v[i].r;
    }
    for (int i = 1, o; i <= m; i++) {
      cin >> v[i + n].o, v[i + n].l = 1, v[i + n].r = 0;
    }
    sort(v + 1, v + n + m + 1, [](V i, V j) {
      return i.o < j.o || i.o == j.o && (i.l > i.r) < (j.l > j.r);
    });
    ht = ans = 1, h[1] = {0, 0};
    for (int o = 1, j = 0; o <= n + m; o++) {
      V i = v[o];
      if (i.o > j) {
        int l = 1, r = 0, w = i.o - j;
        j = i.o, _ht = ans = 0;
        for (int u = 1; u <= ht; u++) {
          pair<int, int> k = h[u];
          if (l > r || r + 1 < k.first - w) {
            l <= r ? h[++_ht] = {l, r} : h[1];
            ans += r - l + 1, l = k.first - w;
          }
          r = k.second + w;
        }
        l <= r ? h[++_ht] = {l, r} : h[1];
        ans += r - l + 1, ht = _ht, _ht = 0;
      }
      if (i.l <= i.r) {
        ans = 0;
        for (int u = 1; u <= ht; u++) {
          pair<int, int> k = h[u];
          if (k.second < i.l || k.first > i.r) {
            _h[++_ht] = k, ans += k.second - k.first + 1;
          } else if (k.first < i.l && k.second > i.r) {
            _h[++_ht] = {k.first, i.l - 1}, _h[++_ht] = {i.r + 1, k.second};
            ans += k.second - k.first - i.r + i.l;
          } else if (k.first < i.l) {
            _h[++_ht] = {k.first, i.l - 1}, ans += i.l - k.first;
          } else if (k.second > i.r) {
            _h[++_ht] = {i.r + 1, k.second}, ans += k.second - i.r;
          }
        }
        for (int u = 1; u <= _ht; u++) {
          h[u] = _h[u];
        }
        ht = _ht, _ht = 0;
      } else {
        cout << ans << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}
