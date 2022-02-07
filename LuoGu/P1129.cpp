#include <iostream>
#define LL long long

using namespace std;

int t, n, m, e, ans, b[201], v[201];
bool l[201][201];

bool T(int x, int y) {
  if (b[x] != y) {
    b[x] = y;
    for (int i = 1; i <= n; i++) {
      if (l[x][i] && (!v[i] || T(v[i], y))) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> t;
  while (t--) {
    ans = 0;
    fill(&b[0], &b[200] + 1, 0), fill(&v[0], &v[200] + 1, 0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> l[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      ans += T(i, i);
    }
    cout << (ans == n ? "Yes\n" : "No\n");
  }
  return 0;
}
