// #include <ctime>
#include <fstream>

using namespace std;

ifstream cin("fly.in");
ofstream cout("fly.out");
// ofstream cerr("CON");

const int kMaxN = 502, kMaxM = 202, kInf = 1e9;
struct Q {
  int x, y, k, o;
} q[kMaxM];
int n, m, p, a[kMaxN], ans[kMaxM], f[2][kMaxN][kMaxM], g[2][kMaxN][kMaxM], _f[kMaxM], _g[kMaxM];

void Divide(int l, int r, int _l, int _r) {
  if (l > r || _l > _r) {
    return;
  }
  int mid = l + r + 1 >> 1, mid1 = _l, mid2, mn = mid, mx = mid;
  for (int i = _l; i <= _r; i++) {
    if (q[i].y < mid) {
      swap(q[mid1++], q[i]);
    }
  }
  mid2 = mid1;
  for (int i = _l; i <= _r; i++) {
    if (q[i].x > mid) {
      swap(q[mid2++], q[i]);
    }
  }
  for (int i = mid2; i <= _r; i++) {
    mn = min(mn, q[i].x), mx = max(mx, q[i].y);
  }
  for (int i = mn; i <= mx; i++) {
    for (int j = 0; j < p; j++) {
      f[0][i][j] = f[1][i][j] = kInf;
    }
  }
  f[0][mid][0] = f[1][mid][0] = 0;
  for (int i = mid - 1; i >= mn; i--) {
    for (int j = 0; j < p; j++) {
      for (int k = 1; k < p * 2; k += 2) {
        f[0][i][j] = min(f[0][i][j], f[0][i + 1][(j - k * a[i] % p + p) % p] + k);
      }
    }
  }
  for (int i = mid + 1; i <= mx; i++) {
    for (int j = 0; j < p; j++) {
      for (int k = 1; k < p * 2; k += 2) {
        f[1][i][j] = min(f[1][i][j], f[1][i - 1][(j - k * a[i - 1] % p + p) % p] + k);
      }
    }
  }
  for (int i = mid2; i <= _r; i++) {
    for (int j = 0; j < p; j++) {
      _f[j] = _g[j] = kInf;
      for (int k = 0; k < p; k++) {
        _f[j] = min(_f[j], f[0][q[i].x][k] + f[1][q[i].y][(j - k + p) % p]);
        _g[j] = min(_g[j], g[0][q[i].x][k] + g[1][q[i].y][(j - k + p) % p]);
      }
    }
    ans[q[i].o] = -1;
    for (int j = 0; j < p; j++) {
      for (int k = 0; k < p; k++) {
        if (_f[j] + _g[k] <= q[i].k) {
          ans[q[i].o] = max(ans[q[i].o], (j + k) % p);
        }
      }
    }
  }
  Divide(l, mid - 1, _l, mid1 - 1), Divide(mid + 1, r, mid1, mid2 - 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  for (int i = 1; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].x >> q[i].y >> q[i].k;
    q[i].o = i;
    if (q[i].x > q[i].y) {
      swap(q[i].x, q[i].y);
    }
  }
  for (int i = 1; i <= n; i++) {
    g[0][i][0] = g[1][i][0] = 0;
    for (int j = 1; j < p; j++) {
      g[0][i][j] = g[1][i][j] = kInf;
    }
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < p; j++) {
      for (int k = 2; k < p * 2; k += 2) {
        g[0][i][j] = min(g[0][i][j], g[0][i - 1][(j - k * a[i - 1] % p + p) % p] + k);
      }
    }
  }
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 0; j < p; j++) {
      for (int k = 2; k < p * 2; k += 2) {
        g[1][i][j] = min(g[1][i][j], g[1][i + 1][(j - k * a[i] % p + p) % p] + k);
      }
    }
  }
  Divide(1, n, 1, m);
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  // cerr << clock();
  return 0;
}
