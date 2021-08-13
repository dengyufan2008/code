#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int l, r;
  bool operator<(const E &e) const {
    return r < e.r || r == e.r && l < e.l;
  }
} e[151];
int n, ans, f[151][151][151];

int main() {
  freopen("recording.in", "r", stdin);
  freopen("recording.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].l >> e[i].r;
  }
  sort(e + 1, e + n + 1);
  for (int i = 0; i < n; i++) {       // 前i个
    for (int j = 0; j <= i; j++) {    // 第一个拍的
      for (int k = 0; k <= i; k++) {  //第二个拍的
        f[i + 1][j][k] = max(f[i + 1][j][k], f[i][j][k]);
        if (e[k].r <= e[i + 1].l) {
          f[i + 1][j][i + 1] = max(f[i + 1][j][i + 1], f[i][j][k] + 1);
        }
        if (e[j].r <= e[i + 1].l) {
          f[i + 1][i + 1][k] = max(f[i + 1][i + 1][k], f[i][j][k] + 1);
        }
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      ans = max(ans, f[n][i][j]);
    }
  }
  cout << ans << endl;
  return 0;
}
