#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 3e5 + 1, kInf = 2e9;
int t, n, a[kMaxN];
LL ans;
vector<int> v[kMaxN];
vector<LL> f[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], v[i].resize(1);
    }
    for (int i = 1; i <= n; i++) {
      int l = a[i], p = kInf;
      bool o = 0;
      for (int j = i + 1; j <= n; j++) {
        int r = a[j] - l;
        if (!r || o && r < p) {
          break;
        }
        if (j == n || a[j + 1] - a[j] >= r) {
          v[j].push_back(r);
        } else {
          break;
        }
        o |= r > p, l = a[j] + r, p = r;
      }
    }
    for (int i = n; i >= 1; i--) {
      int l = a[i], p = kInf;
      bool o = 0;
      for (int j = i - 1; j >= 1; j--) {
        int r = l - a[j];
        if (!r || o && r < p) {
          break;
        }
        if (j == 1 || a[j] - a[j - 1] >= r) {
          v[j].push_back(r);
        } else {
          break;
        }
        o |= r > p, l = a[j] - r, p = r;
      }
    }
    for (int i = 1; i <= n; i++) {
      f[i].clear(), f[i].resize((int)v[i].size());
      sort(v[i].begin(), v[i].end());
    }
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < v[i].size(); j++) {
        f[i][j] += 1LL * v[i][j] * v[i][j];
      }
      LL w = 0;
      for (int j = 0, k = v[i + 1].size() - 1; k >= 0; k--) {
        for (; j < v[i].size() && v[i][j] + v[i + 1][k] <= a[i + 1] - a[i]; j++) {
          w = max(w, f[i][j]);
        }
        f[i + 1][k] = w;
      }
    }
    for (int i = 0; i < v[n].size(); i++) {
      f[n][i] += 1LL * v[n][i] * v[n][i];
      ans = max(ans, f[n][i]);
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
