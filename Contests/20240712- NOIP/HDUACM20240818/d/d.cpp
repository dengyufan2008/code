#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 3002;
struct A {
  bool b;
  int u, d, l, r;
} a[kMaxN][kMaxN];
int t, n, m, ans;
char ch;

bool C1(int x, int y) {
  for (int i = x; i <= n; i += x) {
    for (int j = m; j >= 1; j--) {
      ;
    }
  }
}

bool C(int x, int y) { return x >= y ? C1(x, y) : C2(x, y); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> ch, a[i][j].b = ch == '1';
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        a[i][j].u = a[i - 1][j].u, a[i][j].l = a[i][j - 1].l;
        if (a[i][j].b) {
          a[i][j].u = i, a[i][j].l = j;
        }
      }
    }
    for (int i = n; i >= 1; i--) {
      for (int j = m; j >= 1; j--) {
        a[i][j].d = a[i + 1][j].d, a[i][j].r = a[i][j + 1].r;
        if (a[i][j].b) {
          a[i][j].d = i, a[i][j].r = j;
        }
      }
    }
    for (int i = 1, j = m; i <= n; i++) {
      for (; j >= 1 && !C(i, j); j--) {
      }
      ans += j;
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
