#include <fstream>

using namespace std;

ifstream cin("sort.in");
ofstream cout("sort.out");

const int kMaxN = 1e6 + 1, kMaxM = 31;
int n, m, k, ans, a[kMaxN], c[kMaxM][2];  // 0:01 1:10

void Calc(int x, int o) {
  if (x == 0 || x == n || a[x] == a[x + 1]) {
    return;
  }
  int p = 31 - __builtin_clz(a[x] ^ a[x + 1]);
  ans ^= ans & 1 << p;
  k -= c[p][0] && c[p][1];
  c[p][a[x] >> p & 1] += o;
  k += c[p][0] && c[p][1];
  c[p][1] && (ans |= 1 << p);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    Calc(i, 1);
  }
  cout << (k ? -1 : ans) << '\n';
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    Calc(x - 1, -1), Calc(x, -1);
    a[x] = y;
    Calc(x - 1, 1), Calc(x, 1);
    cout << (k ? -1 : ans) << '\n';
  }
  return 0;
}
