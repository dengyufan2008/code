#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("polaris.in");
ofstream cout("polaris.out");

const int kMaxN = 1001, kMaxV = 2e6 + 1;
int n, a[kMaxN], f[kMaxV], g[kMaxV];
string ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  f[1] = g[1] = 1, f[2] = g[2] = 3;
  for (int i = 3; i < kMaxV; i++) {
    if (i % 2 == 0) {
      f[i] = min(f[i / 2], g[i / 2]) + 2;
    } else {
      f[i] = min(f[i / 2 + 1], g[i / 2 + 1]) + 6;
    }
    if (i % 3 == 0) {
      g[i] = min(f[i / 3 + 3], g[i / 3 + 3]) + 12;
    } else if (i % 3 == 1) {
      g[i] = min(f[i / 3 + 1], g[i / 3 + 1]) + 6;
    } else {
      g[i] = min(f[i / 3 + 1], g[i / 3 + 1]) + 4;
    }
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n, j = 0; i >= 1; i--) {
    a[i] += j;
    while (a[i] > 1) {
      if (f[a[i]] <= g[a[i]]) {
        if (a[i] % 2 == 0) {
          ans += "+c", j += 1, a[i] = a[i] / 2;
        } else {
          ans += "+++11c", j += 3, a[i] = a[i] / 2 + 1;
        }
      } else {
        if (a[i] % 3 == 0) {
          ans += "+++++11+11cc", j += 6, a[i] = a[i] / 3 + 3;
        } else if (a[i] % 3 == 1) {
          ans += "+++1cc", j += 3, a[i] = a[i] / 3 + 1;
        } else {
          ans += "++cc", j += 2, a[i] = a[i] / 3 + 1;
        }
      }
    }
    ans += "1";
  }
  reverse(ans.begin(), ans.end());
  cout << ans << '\n';
  return 0;
}
