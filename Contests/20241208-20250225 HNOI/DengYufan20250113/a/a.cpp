#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 4001;
int t, n, m, ans, a[kMaxN];
int c[kMaxN][26], d[kMaxN][kMaxN], mx[kMaxN];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxN; i++) {
    d[i][0] = 26;
  }
  cin >> t;
  while (t--) {
    cin >> m >> s, n = s.size();
    for (int i = 1; i <= n; i++) {
      a[i] = s[i - 1] - 'a';
    }
    for (int x = 1; x < n; x++) {  // Match(i, i+x)
      for (int i = 1, _i = x > 1, j = 0, _j = 0, k = 0; i <= n;) {
        for (; j <= n && j - i + 1 - k <= m;) {
          j++, _j = _j == x - 1 ? 0 : _j + 1;
          if (j <= n) {
            int &_c = c[_j][a[j]];
            d[_j][_c]--, _c++, d[_j][_c]++;
            mx[_j] < _c && (mx[_j]++, k++);
          }
        }
        i + x <= n && (ans = max(ans, j - i - x));
        int &_c = c[_i][a[i]];
        d[_i][_c]--, _c--, d[_i][_c]++;
        !d[_i][mx[_i]] && (mx[_i]--, k--);
        i++, _i = _i == x - 1 ? 0 : _i + 1;
      }
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
