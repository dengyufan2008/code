#include <iostream>
#define LL long long

using namespace std;

struct V {
  int h, l, r;
  bool b;
} v[1001][1001];
int n, m, ans;
char c;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> c;
      v[i][j].b = c == 'R';
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1, p = 0; j <= m; j++) {
      if (v[i][j].b) {
        p = j;
      }
      v[i][j].l = p;
    }
    for (int j = m, p = m + 1; j >= 1; j--) {
      if (v[i][j].b) {
        p = j;
      }
      v[i][j].r = p;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!v[i][j].b) {
        if (v[i - 1][j].b || i == 1) {
          v[i][j].h = 1;
        } else {
          v[i][j].h = v[i - 1][j].h + 1;
          v[i][j].l = max(v[i][j].l, v[i - 1][j].l);
          v[i][j].r = min(v[i][j].r, v[i - 1][j].r);
        }
        ans = max(ans, v[i][j].h * (v[i][j].r - v[i][j].l - 1));
      }
    }
  }
  cout << ans * 3;
  return 0;
}
