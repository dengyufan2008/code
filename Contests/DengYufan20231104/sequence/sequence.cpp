#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("sequence.in");
ofstream cout("sequence.out");

const int kMaxN = 3e5 + 1;
int t, n, m, k, a[kMaxN], b[kMaxN];
LL ans1, ans2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    ans1 = 0, fill(&b[1], &b[n] + 1, 0);
    for (int i = 1, j, c = 0, w = n; (j = i + m - 1) <= n; i++) {
      for (int _j = j; c < k; _j--, c++) {
        b[_j] = a[w--];
      }
      ans1 += a[w + 1], c -= b[i] > 0;
    }
    k = m - k + 1;
    ans2 = 0, fill(&b[1], &b[n] + 1, 0);
    for (int i = 1, j, c = 0, w = 1; (j = i + m - 1) <= n; i++) {
      for (int _j = j; c < k; _j--, c++) {
        b[_j] = a[w++];
      }
      ans2 += a[w - 1], c -= b[i] > 0;
    }
    cout << ans1 << ' ' << ans2 << '\n';
  }
  return 0;
}
