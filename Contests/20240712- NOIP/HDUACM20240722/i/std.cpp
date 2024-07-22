#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.ans");

const int kMaxN = 1e5 + 1, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int t, n, m, p, a[kMaxN * 2];
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n * 2; i++) {
      a[i] = 0;
    }
    cin >> n >> m;
    for (int i = 1, l, r; i <= m; i++) {
      cin >> l >> r, l++;
      for (int j = l; j <= r; j++) {
        a[j]++;
      }
      p = ans = 0;
      for (int j = 1; j <= n * 2; j++) {
        if (p == a[j]) {
          ans = (ans + p) % kMod;
        } else if (p < a[j]) {
          ans = (ans + p + kInv2) % kMod, p++;
        } else {
          ans = (ans + p - kInv2 + kMod) % kMod, p--;
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
