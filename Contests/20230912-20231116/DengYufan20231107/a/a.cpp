#include <algorithm>
#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxM = 5e5 + 1;
int n, f[kMaxM], s[kMaxM];

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxM; i++) {
    f[i] = i;
  }
  cin >> n;
  for (int i = 1, x, ans = 0; i <= n; i++) {
    cin >> x;
    if (!s[x]) {
      s[x] = 1, ans++;
      if (x > 1 && s[x - 1]) {
        ans -= s[GetRoot(x - 1)] + 1 >> 1;
        ans -= s[x] + 1 >> 1;
        s[x] += s[GetRoot(x - 1)];
        f[GetRoot(x - 1)] = x;
        ans += s[x] + 1 >> 1;
      }
      if (x < kMaxM - 1 && s[x + 1]) {
        ans -= s[GetRoot(x + 1)] + 1 >> 1;
        ans -= s[x] + 1 >> 1;
        s[x] += s[GetRoot(x + 1)];
        f[GetRoot(x + 1)] = x;
        ans += s[x] + 1 >> 1;
      }
    }
    cout << ans << ' ';
  }
  return 0;
}
