#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("z.in");
ofstream cout("z.out");

const int kMaxN = 1e5 + 1;
int n, m, a[kMaxN], b[kMaxN], d[kMaxN], _d[kMaxN];
int prime[kMaxN], mu[kMaxN];
bool o[kMaxN];
vector<int> p[kMaxN], v[kMaxN];

int Lower(int o, int x) {
  int l = 0, r = v[o].size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (v[o][mid] >= x) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

int Upper(int o, int x) {
  int l = 0, r = v[o].size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (v[o][mid] > x) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

int Chick(int m, int x, bool o) {  // O(d(x)logn)
  int ans = 0;
  for (int i : p[x]) {
    if (mu[i]) {
      ans += mu[i] * (o ? v[i].size() - Lower(i, m) : Upper(i, m));
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  o[1] = 1, mu[1] = 1;
  for (int i = 2, k = 0; i <= n; i++) {
    if (!o[i]) {
      prime[++k] = i, mu[i] = -1;
    }
    for (int j = 1; j <= k && i * prime[j] <= n; j++) {
      o[i * prime[j]] = 1, mu[i * prime[j]] = -mu[i];
      if (!(i % prime[j])) {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      p[j].push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    int ans = 0;
    m = n / i;
    for (int j = 1; j <= m; j++) {
      d[j] = j;
    }
    sort(d + 1, d + m + 1, [i](int x, int y) {
      return b[i * x] < b[i * y];
    });
    for (int j = 1; j <= m; j++) {
      _d[d[j]] = j;
    }
    for (int j = 1; j <= m; j++) {
      v[j].clear();
      for (int k = j; k <= m; k += j) {
        v[j].push_back(_d[k]);
      }
      sort(v[j].begin(), v[j].end());
    }
    for (int j = 1; j <= m; j++) {  // O(mlog^3m)
      int l = 1, r = m;
      while (l <= r) {
        int mid = l + r >> 1;
        if (Chick(mid, j, 0)) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      ans = max(ans, a[i * j] - b[i * d[l]]);
      r = m;
      while (l <= r) {
        int mid = l + r >> 1;
        if (Chick(mid, j, 1)) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = max(ans, b[i * d[r]] - a[i * j]);
    }
    cout << ans << " \n"[i == n];
  }
  return 0;
}
