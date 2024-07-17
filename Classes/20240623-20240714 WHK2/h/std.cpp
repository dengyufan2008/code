#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.ans");

const int kMaxN = 9, kMod = 1e9 + 7;
int n, m, ans, a[1 << kMaxN];

int PopCount(int s) {
  int ans = 0;
  for (; s; s >>= 1) {
    ans += s & 1;
  }
  return ans;
}

int Pow(int x, int y = kMod - 2) {
  int ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = 1LL * ans * x % kMod;
    }
    x = 1LL * x * x % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n, [](int i, int j) {
    return abs(i) > abs(j);
  });
  for (int i = n - 1; i >= 0; i--) {
    a[1 << i] = a[i], a[i] = 0;
  }
  for (int s = 1; s < 1 << n; s++) {
    if (s != (s & -s)) {
      a[s] = a[s ^ (s & -s)] * a[s & -s];
    }
  }
  for (int s = 1; s < 1 << n; s++) {
    if (PopCount(s) >= m) {
      int mx = -kMod;
      for (int t = s; t; t = t - 1 & s) {
        if (PopCount(t) == m) {
          mx = max(mx, a[t]);
        }
      }
      ans = (ans + mx + (mx < 0 ? kMod : 0)) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
