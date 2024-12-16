#include <fstream>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 301, kMaxM = kMaxN * kMaxN * 2, kInf = 1e9;
int n, m, f[kMaxM << 1];
LL k, w, c, a[kMaxN << 1], b[kMaxN << 1];

void Add(int w, int c) {
  if (w > 0) {
    for (int i = m; i - w >= -m; i--) {
      if (f[i - w + kMaxM] > -kInf) {
        f[i + kMaxM] = max(f[i + kMaxM], f[i - w + kMaxM] + c);
      }
    }
  } else if (w < 0) {
    for (int i = -m; i - w <= m; i++) {
      if (f[i - w + kMaxM] > -kInf) {
        f[i + kMaxM] = max(f[i + kMaxM], f[i - w + kMaxM] + c);
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k, m = n * n * 2;
  for (int i = -n; i <= n; i++) {
    cin >> a[i + kMaxN];
  }
  for (int i = -n; i <= -1; i++) {
    w += i * a[i + kMaxN], c += a[i + kMaxN];
  }
  if (k < w) {
    cout << "impossible\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    LL o = min(a[i + kMaxN], (k - w) / i);
    w += i * o, c += o, b[i + kMaxN] = o;
  }
  for (int i = -n; i <= -1; i++) {
    LL o = min(a[i + kMaxN], (k - w) / -i);
    w -= i * o, c -= o, b[i + kMaxN] = a[i + kMaxN] - o;
  }
  for (int i = -m; i <= m; i++) {
    f[i + kMaxM] = -kInf;
  }
  f[kMaxM] = 0;
  for (int o = 1, k; o <= n; o++) {
    for (int i : {o, -o}) {
      int x = min(a[i + kMaxN] - b[i + kMaxN], (LL)n << 1);
      int y = min(b[i + kMaxN], (LL)n << 1);
      for (k = 1; k << 1 <= x + 1; k <<= 1) {
        Add(k * i, k);
      }
      Add((x - k + 1) * i, (x - k + 1));
      for (k = 1; k << 1 <= y + 1; k <<= 1) {
        Add(-k * i, -k);
      }
      Add(-(y - k + 1) * i, -(y - k + 1));
    }
  }
  if (k > w + m || f[k - w + kMaxM] == -kInf) {
    cout << "impossible\n";
  } else {
    cout << c + f[k - w + kMaxM] + a[kMaxN] << '\n';
  }
  return 0;
}
