#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, m, q, k, _k, p[100001];

int main() {
  freopen("shuffle.in", "r", stdin);
  freopen("shuffle.out", "w", stdout);
  cin >> n >> m >> q;
  for (int i = 1; i <= 100000; i++) {
    p[i] = i;
  }
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    p[x] = i;
  }
  while (q--) {
    cin >> k;
    _k = max(m - k + 1, 1);
    for (int i = 1; i <= min(m, n - k + 1); i++) {
      _k = p[_k] + 1;
    }
    cout << _k - 1 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
