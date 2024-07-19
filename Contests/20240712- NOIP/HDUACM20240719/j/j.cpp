#include <fstream>
#include <map>
#include <vector>
#define LL long long

ifstream cin("j.in");
ofstream cout("j.out");

using namespace std;

const int kMaxN = 2e5 + 2, kMaxM = 601;
int u, n, m, o, a[kMaxN], r[kMaxN], p[kMaxN], q[kMaxN];
int pt[kMaxN], qt[kMaxN], ans[kMaxN];
LL hs, s[kMaxN], t[kMaxN], mx[kMaxN], w[kMaxN];
pair<int, int> f[kMaxN];
map<int, int> h;
vector<int> v[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    m = hs = 0, h.clear();
    cin >> n >> o;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], h[a[i]] = 0;
    }
    for (int i = 1; i <= o; i++) {
      cin >> f[i].first >> f[i].second;
      mx[i] = ans[i] = 0, w[i] = 1LL * (f[i].second - f[i].first + 1) * (f[i].second - f[i].first + 2) / 2;
    }
    for (auto &i : h) {
      i.second = ++m, r[m] = i.first;
    }
    for (int i = 1; i <= n; i++) {
      a[i] = h[a[i]];
    }
    for (int i = 1; i <= n; i++) {
      p[i] = a[i] > max(m - kMaxM, 0) ? i : p[i - 1];
    }
    for (int i = n; i >= 1; i--) {
      q[i] = a[i] > max(m - kMaxM, 0) ? i : q[i + 1];
    }
    for (int i = 1; i <= n; i++) {
      if (a[i] > max(m - kMaxM, 0)) {
        t[i] = t[p[i]] + 1LL * (i - p[i] - 1) * (i - p[i]) / 2;
      }
    }
    for (int i = m; i > max(m - kMaxM, 0); i--) {
      for (int j = 1; j <= n; j++) {
        pt[j] = pt[j - 1];
        a[j] >= i && (pt[j] = j);
      }
      qt[n + 1] = n + 1;
      for (int j = n; j >= 1; j--) {
        qt[j] = qt[j + 1];
        a[j] >= i && (qt[j] = j);
      }
      for (int j = 1; j <= n; j++) {
        if (a[j] >= i) {
          int k = pt[j - 1];
          s[j] = s[k] + 1LL * (j - k - 1) * (j - k) / 2;
        }
      }
      for (int j = 1, l, r; j <= o; j++) {
        static LL ww;
        l = f[j].first, r = f[j].second;
        int _l = qt[l], _r = pt[r];
        if (_l <= _r) {
          ww = s[_r] - s[_l];
          ww += 1LL * (_l - l) * (_l - l + 1) / 2;
          ww += 1LL * (r - _r) * (r - _r + 1) / 2;
          if (w[j] - ww > mx[j]) {
            mx[j] = w[j] - ww, ans[j] = i;
          }
          w[j] = ww;
        }
      }
    }
    for (int i = 1, l, r; i <= o; i++) {
      static LL ww;
      l = f[i].first, r = f[i].second;
      if (q[l] <= p[r]) {
        w[i] = t[p[r]] - t[q[l]];
        w[i] += 1LL * (r - p[r]) * (r - p[r] + 1) / 2;
        w[i] += 1LL * (q[l] - l) * (q[l] - l + 1) / 2;
      } else {
        w[i] = 1LL * (r - l + 1) * (r - l + 2) / 2;
      }
      if (w[i] > mx[i]) {
        for (int j = l; j <= r; j++) {
          v[a[j]].push_back(j);
        }
        for (int j = m; j >= 1; j--) {
          if (!v[j].empty()) {
            int c = l - 1;
            ww = 0, v[j].push_back(r + 1);
            for (int k : v[j]) {
              ww += 1LL * (k - c - 1) * (k - c) / 2, c = k;
            }
            if (w[i] - ww > mx[i]) {
              mx[i] = w[i] - ww, ans[i] = j;
            }
            w[i] = ww, v[j].clear();
          }
        }
      }
      hs ^= 1LL * i * ::r[ans[i]];
    }
    cout << hs << '\n';
  }
  return 0;
}
