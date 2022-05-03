#include <cmath>
#include <complex>
#include <iostream>
#define CD complex<double>

using namespace std;

const double kPi = acos(-1.0);
int n, k, r[1000001], ans[1000001];
CD a[1000001], b[1000001];
string s1, s2;

void FFT(CD a[], int n, int b) {
  for (int i = 0; i < n; i++) {
    if (i < r[i]) {
      swap(a[i], a[r[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    CD wn(cos(kPi / i), sin(kPi / i) * b);
    for (int j = 0; j < n; j += (i << 1)) {
      CD w(1, 0);
      for (int k = j; k < j + i; k++, w *= wn) {
        CD x = a[k], y = w * a[k + i];
        a[k] = x + y, a[k + i] = x - y;
      }
    }
  }
  if (b == -1) {
    for (int i = 0; i < n; i++) {
      a[i] /= n;
    }
  }
}

int main() {
  cin >> s1 >> s2;
  for (int i = 0; i < s1.size(); i++) {
    a[i] = double(s1[s1.size() - i - 1] - '0');
  }
  for (int i = 0; i < s2.size(); i++) {
    b[i] = double(s2[s2.size() - i - 1] - '0');
  }
  k = max(int(ceil(log2(s1.size() + s2.size() - 1))), 1);
  n = 1 << k;
  for (int i = 0; i < n; i++) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) << (k - 1));
  }
  FFT(a, n, 1), FFT(b, n, 1);
  for (int i = 0; i < n; i++) {
    a[i] *= b[i];
  }
  FFT(a, n, -1);
  for (int i = 0; i < n; i++) {
    ans[i] += (int)(a[i].real() + 0.5);
    ans[i + 1] += ans[i] / 10;
    ans[i] %= 10;
  }
  for (; n > -1 && !ans[n]; n--) {
  }
  if (n == -1) {
    cout << 0;
  } else {
    for (int i = n; i >= 0; i--) {
      cout << ans[i];
    }
  }
  return 0;
}
