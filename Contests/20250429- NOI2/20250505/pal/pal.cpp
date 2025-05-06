#include <fstream>

using namespace std;

ifstream cin("pal.in");
ofstream cout("pal.out");

const int kMaxN = 1e6 + 1;
int t, n, m, a[kMaxN];

void Input() {
  static string s;
  cin >> s, n = 0, m = s.size();
  for (int i = 0; i < m; i++) {
    if (s[i] == '1') {
      a[++n] = i + 1;
    }
  }
}

int Calc(int l, int r) {
  int mx = 0;
  for (int i = l, j = l; i <= r; i = j = j + 1) {
    for (; j < r && a[j] + 2 == a[j + 1]; j++) {
    }
    mx = max(mx, j - i + 1);
  }
  if (mx * 2 <= r - l + 1) {
    return (r - l + 1 & 1) << 1 | 1;
  } else {
    return (mx << 1) - (r - l + 1) << 1 | 1;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Input();
    if (m == 1) {
      cout << 1 << '\n';
    } else {
      int ans = Calc(1, n);
      if (a[1] == 1) {
        ans = min(ans, Calc(2, n) + 1);
      }
      if (a[n] == m) {
        ans = min(ans, Calc(1, n - 1) + 1);
      }
      if (a[1] == 1 && a[n] == m) {
        ans = min(ans, Calc(2, n - 1) + 2);
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
