#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("decompose.in");
ofstream cout("decompose.out");

const int kMaxN = 1001;
int n, k, m, d[kMaxN * kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int o = 0; o < n; o++) {
    d[++m] = n, d[++m] = o % (n - 1) + 1;
    for (int i = 2, j = n - 1; i < j; i++, j--) {
      d[++m] = (i + o - 1) % (n - 1) + 1, d[++m] = (j + o - 1) % (n - 1) + 1;
    }
    d[++m] = ((n + 1) / 2 + o - 1) % (n - 1) + 1;
  }
  d[++m] = n;
  for (int i = 1, p = 0, x; i <= k; i++) {
    cin >> x;
    for (int j = 1; j <= x + 1; j++) {
      cout << d[++p] << ' ';
    }
    p--;
    cout << '\n';
  }
  return 0;
}
// spj decompose.in decompose.out decompose.out
