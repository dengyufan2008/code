#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 10001, kMaxL = 61;
int t, n;
LL a[kMaxN], l[kMaxN], r[kMaxN];
bool ans[kMaxN];

void Update(int x, int y) {
  LL s = a[x - 1] ^ a[y];
  s = s & -s, !s && (s = ~(-1LL << kMaxL));
  l[x] |= s, r[y] |= s;
  if (x == y) {
    ans[x] = 1;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      for (int j = 0; j < kMaxL; j++) {
        if (a[i] >> j & 1) {
          a[0] |= 1LL << kMaxL - j - 1;
        }
      }
      a[i] = a[0], a[0] = 0, a[i] ^= a[i - 1];
    }
    Update(1, n);
    for (int i = n - 1; i >= 1; i--) {
      for (int j = 1, k; (k = j + i - 1) <= n; j++) {
        if ((l[j] | r[k]) & (a[j - 1] ^ a[k] + 1)) {
          Update(j, k);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i], l[i] = r[i] = ans[i] = 0;
    }
    cout << '\n';
  }
  return 0;
}
