#include <fstream>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 3e5 + 1;
int n, s, t, a[kMaxN], g[kMaxN];
bool f[kMaxN];

bool C(int x) {
  int mn = 0;
  for (int i = 2; i <= n + 1; i += 2) {
    f[i] = mn <= g[i] + a[i] - x;
    f[i] && (mn = min(mn, g[i]));
  }
  return f[n + 1];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], (i & 1) ? s += a[i] : t += a[i];
  }
  if (n & 1) {
    for (int i = 2; i <= n + 1; i++) {
      g[i] = g[i - 2] + a[i - 1] - a[i];
    }
    int l = 0, r = s;
    while (l <= r) {
      int mid = l + r >> 1;
      if (C(mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << max(s, t + r) << ' ' << min(s - r, t) << '\n';
  } else {
    cout << max(s, t) << ' ' << min(s, t) << '\n';
  }
  return 0;
}
