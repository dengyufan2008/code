#include <algorithm>
#include <complex>
#include <fstream>
#include <iomanip>
#define CD complex<double>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1 << 18, kB = 4400;
const double kPi = acos(-1.0);
int n, m, k, r[kMaxN];
double ans, a[kMaxN], f[kMaxN], g[kB + 1];
CD p[kMaxN], q[kMaxN];

void FFT(CD *f, bool b) {
  for (int i = 0; i < m; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < m; i <<= 1) {
    CD g(cos(kPi / (double)i), sin(kPi / (double)i) * (b ? -1.0 : 1.0));
    for (int j = 0; j < m; j += i + i) {
      CD w(1, 0);
      for (int k = j; k < j + i; k++) {
        CD f0 = f[k], f1 = f[k + i] * w;
        f[k] = f0 + f1, f[k + i] = f0 - f1;
        w *= g;
      }
    }
  }
  if (b) {
    for (int i = 0; i < m; i++) {
      f[i] /= m;
    }
  }
}

void Mul() {
  for (int i = 0; i <= n; i++) {
    p[i] = {f[i], 0};
  }
  for (int i = n + 1; i < m; i++) {
    p[i] = {0, 0};
  }
  for (int i = 0; i <= kB; i++) {
    q[i] = {g[i], 0};
  }
  for (int i = kB + 1; i < m; i++) {
    q[i] = {0, 0};
  }
  FFT(p, 0), FFT(q, 0);
  for (int i = 0; i < m; i++) {
    p[i] *= q[i];
  }
  FFT(p, 1);
  for (int i = 0; i <= n; i++) {
    f[i] = p[i].real();
  }
}

void Calc(int l, int r) {
  g[0] = 1;
  for (int i = 1; i <= kB; i++) {
    g[i] = 0;
  }
  for (int i = l; i <= r; i++) {
    for (int j = i - l + 1; j >= 1; j--) {
      g[j] = g[j] * (1 - a[i]) + g[j - 1] * a[i];
    }
    g[0] *= 1 - a[i];
    int x = i + k - 1 >> 1;
    double s = 0;
    for (int j = 0; j <= i - l + 1 && j <= x; j++) {
      s += g[j] * f[x - j];
    }
    ans = max(ans, 1 - s);
  }
  Mul();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (m = 1; m <= n + kB; m <<= 1) {
  }
  for (int i = 1; i < m; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? m >> 1 : 0);
  }
  sort(a + 1, a + n + 1, greater<double>());
  for (int i = 0; i <= n; i++) {
    f[i] = 1;
  }
  for (int i = 1; i <= n; i += kB) {
    Calc(i, min(i + kB - 1, n));
  }
  cout << fixed << setprecision(12) << ans << '\n';
  return 0;
}
