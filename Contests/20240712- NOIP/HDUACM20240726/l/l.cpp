#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 1e5 + 1;
int t, n, l, d, a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> l >> d;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 2, a + n + 1);
    if (a[1] < l) {
      if (max(a[1], a[n]) - min(a[1], a[2]) <= d || a[3] >= l) {
        cout << "No\n";
      } else {
        cout << "Yes\n";
      }
    } else {
      if (a[1] - a[2] <= d || a[4] >= l) {
        cout << "No\n";
      } else {
        cout << "Yes\n";
      }
    }
  }
  return 0;
}
