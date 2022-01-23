#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct H {
  int n, a[100001];

  void Add(int x, int y) {
    for (; x <= n; x += x & -x) {
      a[x] += y;
    }
  }

  int Find(int x) {
    int ans = 0;
    for (; x; x -= x & -x) {
      ans += a[x];
    }
    return ans;
  }
} h[2];
int n, ans, a[2][100001], d[2][100001], l[100001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[0][i];
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return a[0][i] > a[0][j]; });
  for (int i = 1; i <= n; i++) {
    a[1][l[i]] = a[1][l[i - 1]] + (a[0][l[i]] != a[0][l[i - 1]]);
  }
  h[0].n = h[1].n = n;
  for (int i = 1; i <= n; i++) {
    h[0].Add(a[1][i], 1);
    d[0][i] = h[0].Find(a[1][i] - 1);
  }
  for (int i = n; i >= 1; i--) {
    h[1].Add(a[1][i], 1);
    d[1][i] = h[1].Find(a[1][i] - 1);
  }
  for (int i = 1; i <= n; i++) {
    if (min(d[0][i], d[1][i]) * 2 < max(d[0][i], d[1][i])) {
      ans++;
    }
  }
  cout << ans;
  return 0;
}
