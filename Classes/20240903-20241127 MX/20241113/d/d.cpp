#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 1e6 + 1, kMaxM = 20, kInf = 1e9;
struct A {
  int x, y;
} a[kMaxN];
int n, m, k, w, l, r, p[kMaxN], f[1 << kMaxM], g[1 << kMaxM];
int ans, ansl, ansr;
char c;

void Min(int &x, int y) { x = min(x, y); }
void Max(int &x, int y) { x = max(x, y); }

void Update(int x, int l, int r) {
  if (ans < x) {
    ans = x, ansl = l, ansr = r;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k, w = k, ansl = 1, ansr = n;
  for (int i = 0; i < k; i++) {
    cin >> c, c == '1' && (l |= 1 << i) && w--;
  }
  for (int i = 0; i < k; i++) {
    cin >> c, c == '1' && (r |= 1 << i) && w--;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y, a[i].x--, a[i].y--;
  }
  for (int s = 0; s < 1 << k; s++) {
    f[s] = kInf, g[s] = -kInf;
  }
  for (int i = 0; i < k; i++) {
    p[i] = i;
  }
  Min(f[l], n + 1);
  for (int i = n; i >= 1; i--) {
    swap(p[a[i].x], p[a[i].y]);
    int s = 0;
    for (int j = 0; j < k; j++) {
      (l >> j & 1) && (s |= 1 << p[j]);
    }
    Min(f[s], i);
  }
  for (int i = 0; i < k; i++) {
    p[i] = i;
  }
  Max(g[r], n + 1);
  for (int i = n; i >= 1; i--) {
    swap(p[a[i].x], p[a[i].y]);
    int s = 0;
    for (int j = 0; j < k; j++) {
      (r >> j & 1) && (s |= 1 << p[j]);
    }
    Max(g[s], i);
  }
  for (int i = 0; i < k; i++) {
    for (int s = 1 << i; s < 1 << k; s = s + 1 | 1 << i) {
      Min(f[s ^ 1 << i], f[s]), Max(g[s ^ 1 << i], g[s]);
    }
  }
  for (int s = 0; s < 1 << k; s++) {
    if (g[s] - f[s] >= m) {
      Update(w + (__builtin_popcount(s) << 1), f[s], g[s] - 1);
    }
  }
  cout << ans << '\n';
  cout << ansl << ' ' << ansr << '\n';
  return 0;
}
