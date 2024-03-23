#include <bits/stdc++.h>
using namespace std;
namespace QYB {
  int n, m, k, a[3005], b[3005], p[3005], ans[3005];
  char getchar() {
    static char buf[1 << 25], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 25, stdin)) == buf? EOF: *p1++;
  } int read() {
    int res = 0; char ch = getchar();
    while (ch < 48 || ch > 57) ch = getchar();
    while (ch >= 48 && ch <= 57) res = res * 10 + ch - 48, ch = getchar();
    return res;
  } bool check(int x) {
    for (int i = 1; i <= n; i++) p[i] = i <= x;
    bool res = false;
    do {
      bool ok = true;
      for (int i = 1; i <= m; i++) {
        if (!p[a[i]] && !p[b[i]]) {
          ok = false; break;
        }
      } if (ok == true) {
        for (int i = 1; i <= n; i++) ans[i] |= p[i];
        res = true;
      }
    } while (prev_permutation(p + 1, p + n + 1));
    return res;
  } int main() {
    freopen("medrcy.in", "r", stdin);
    freopen("medrcy.out", "w", stdout);
    for (int T = read(); T; T--) {
      n = read(), m = read(), k = read();
      for (int i = 1; i <= n; i++) ans[i] = 0;
      for (int i = 1; i <= m; i++) a[i] = read(), b[i] = read();
      for (int i = 1; i <= k; i++) {
        if (check(i)) {
          vector<int> v;
          for (int j = 1; j <= n; j++) {
            if (ans[j]) v.push_back(j);
          } printf("%d %d\n", i, int(v.size()));
          for (int j: v) printf("%d ", j);
          printf("\n"); goto end;
        }
      } printf("-1\n"); end: ;
    } return 0;
  }
} int main() { return QYB::main(); }