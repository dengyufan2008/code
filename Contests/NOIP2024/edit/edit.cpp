#include <fstream>

using namespace std;

ifstream cin("edit.in");
ofstream cout("edit.out");

int o, n, ans, c0, c1, d0, d1;
string s1, s2, t1, t2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n >> s1 >> s2 >> t1 >> t2;
    s1 = '~' + s1, s2 = '~' + s2;
    t1 = '~' + t1, t2 = '~' + t2;
    c0 = c1 = d0 = d1 = ans = 0;
    for (int i = 1, j = 1; i <= n;) {
      for (; i <= n && t1[i] == '1'; i++) {
        s1[i] == '1' ? c1++ : c0++;
      }
      for (; j <= n && t2[j] == '1'; j++) {
        s2[j] == '1' ? d1++ : d0++;
      }
      if (i > j) {
        swap(i, j), swap(s1, s2), swap(t1, t2);
        swap(c0, d0), swap(c1, d1);
      }
      int e0 = min(c0, d0), e1 = min(c1, d1);
      c0 -= e0, d0 -= e0, c1 -= e1, d1 -= e1, ans += e0 + e1;
      if (c0) {
        d1 -= c0, c0 = 0;
      } else if (c1) {
        d0 -= c1, c1 = 0;
      }
      if (i < j) {
        if (s1[i] == '0') {
          if (d0) {
            ans++, d0--;
          } else {
            d1--;
          }
        } else {
          if (d1) {
            ans++, d1--;
          } else {
            d0--;
          }
        }
        i++;
      } else if (i <= n) {
        ans += s1[i] == s2[j], i++, j++;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
