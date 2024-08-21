#include <fstream>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 2e5 + 1;
int t, n, m, k, s, a[kMaxN], b[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], s = min(s + a[i], m) - 1;
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
    }
    cout << (s < k ? "YES\n" : "NO\n"), s = 0;
  }
  return 0;
}
