#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#define LL long long
#define CP complex<long double>

using namespace std;

const int kMaxN = 1e5 + 1;
const long double kPi = acos(-1);
int n, m, t[kMaxN << 2];
LL a[kMaxN], b[kMaxN], ans[kMaxN][2];
CP f[kMaxN << 2], g[kMaxN << 2];

void FFT(CP *f, int b) {
  for (int i = 1; i <= m; i++) {
    if (i < t[i]) {
      swap(f[i], f[t[i]]);
    }
  }
  for (int i = 1; i < m; i <<= 1) {
    CP g = {cos(kPi / (long double)i), b * sin(kPi / (long double)i)};
    for (int j = 0; j < m; j += i + i) {
      CP w = {1, 0};
      for (int k = j; k < j + i; k++) {
        CP f0 = f[k], f1 = f[k + i];
        f[k] = f0 + f1 * w;
        f[k + i] = f0 - f1 * w;
        w *= g;
      }
    }
  }
  if (b == -1) {
    for (int i = 0; i < m; i++) {
      f[i] /= m;
    }
  }
}

void Calc(bool o) {
  int h = 1, l = 1, r = n;
  LL w = 0;
  for (; h <= n && (a[l] <= 0 && a[r] >= 0 || b[l] <= 0 && b[r] >= 0 || a[l] * b[l] >= 0); h++) {
    if (a[l] * b[l] >= a[r] * b[r]) {
      w += a[l] * b[l], l++;
    } else {
      w += a[r] * b[r], r--;
    }
    ans[h][o] = w;
  }
  h--;
  int len = r - l + 1;
  if (a[l] < 0) {
    for (int i = 0; i < len; i++) {
      f[i] = {a[i + l], 0};
      g[i] = {b[r - i], 0};
    }
  } else {
    for (int i = 0; i < len; i++) {
      f[i] = {b[i + l], 0};
      g[i] = {a[r - i], 0};
    }
  }
  for (m = 1; m < len; m <<= 1) {
  }
  m <<= 1;
  for (int i = 1; i < m; i++) {
    t[i] = (t[i >> 1] >> 1) | (i & 1 ? m >> 1 : 0);
  }
  for (int i = len; i < m; i++) {
    f[i] = g[i] = {0, 0};
  }
  FFT(f, 1), FFT(g, 1);
  for (int i = 0; i < m; i++) {
    f[i] *= g[i];
  }
  FFT(f, -1);
  for (int i = 1; h + i <= n; i++) {
    ans[h + i][o] = w + round(f[2 * len - i - 1].real());
  }
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
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  Calc(1);
  for (int i = 1; i <= n; i++) {
    a[i] = -a[i];
  }
  reverse(a + 1, a + n + 1);
  Calc(0);
  for (int i = 1; i <= n; i++) {
    cout << -ans[i][0] << ' ' << ans[i][1] << '\n';
  }
  return 0;
}
