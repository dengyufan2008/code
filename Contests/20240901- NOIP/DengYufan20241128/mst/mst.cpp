#include <fstream>

using namespace std;

ifstream cin("mst.in");
ofstream cout("mst.out");

const int kMaxN = 2e5 + 1;
int t, n, a[kMaxN];
bool o;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    if (n == 1) {
      cout << 0 << '\n';
      continue;
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y, a[x]++, a[y]++;
    }
    o = 0;
    for (int i = 1; i <= n; i++) {
      o |= a[i] == n - 1, a[i] = 0;
    }
    cout << (o ? -1 : n * 2 - 1) << '\n';
  }
  return 0;
}
