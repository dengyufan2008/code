#include <fstream>

using namespace std;

ifstream cin("radio.in");
ofstream cout("radio.out");

const int kMaxN = 1e6 + 1;
int n, m, k, ans, f[kMaxN], mn[kMaxN], mx[kMaxN];
string s;

void Calc(char c, int mid) {
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] + (s[i] != c);
    mn[i] = mn[i - 1], mx[i] = mx[i - 1];
    if (i >= k) {
      if (f[i] > f[i - k] + mid) {
        f[i] = f[i - k] + mid;
        mn[i] = mn[i - k] + 1;
        mx[i] = mx[i - k] + 1;
      } else if (f[i] == f[i - k] + mid) {
        mn[i] = min(mn[i], mn[i - k] + 1);
        mx[i] = max(mx[i], mx[i - k] + 1);
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k >> s;
  ans = n, s = '~' + s;
  for (char c : {'R', 'B', 'Y'}) {
    int l = 0, r = k, o = -1, w;
    while (l <= r) {
      int mid = l + r >> 1;
      Calc(c, mid);
      if (mn[n] > m) {
        l = mid + 1;
      } else if (mx[n] < m) {
        r = mid - 1;
      } else {
        ans = min(ans, f[n] - m * mid);
        break;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
