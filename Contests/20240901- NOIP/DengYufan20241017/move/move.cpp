#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("move.in");
ofstream cout("move.out");

const int kMaxN = 1e6 + 1, kInf = 1e9;
struct A {
  int l, r;
  bool operator<(const A &a) const {
    return r < a.r;
  }
} a[2][kMaxN];
int t, n, k, m[2], f[2][kMaxN];

void Update(int &x, int y) { x = min(x, y); }

int FindR(int x, bool o) {
  return lower_bound(a[o] + 1, a[o] + m[o] + 1, A{x, x}) - a[o];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> k, m[0] = m[1] = 0;
    for (int i = 1, x, y, z; i <= n; i++) {
      cin >> x >> y >> z, z--;
      a[z][++m[z]] = {x, y};
    }
    sort(a[0] + 1, a[0] + m[0] + 1);
    sort(a[1] + 1, a[1] + m[1] + 1);
    f[0][0] = 1, f[1][0] = k;
    for (int i = 1; i <= n; i++) {
      f[0][i] = f[1][i] = kInf;
    }
    for (int i = 0; i < n; i++) {
      for (int o : {0, 1}) {
        int p = f[o][i], x = FindR(p, o);
        if (x <= m[o]) {
          Update(f[o][i + 1], a[o][x].r + 1);
          p = max(p, a[o][x].l);
          if (p <= a[o][x].r - k * 2) {
            int c = FindR(a[o][x].r - k + 1, o ^ 1) - FindR(p + k, o ^ 1);
            Update(f[o ^ 1][i], p + k);
            Update(f[o ^ 1][i + 1 + c], a[o][x].r - k + 1);
          } else {
            Update(f[o ^ 1][i + 1], p + k);
          }
        }
      }
    }
    for (int i = n; i >= 0; i--) {
      if (f[0][i] < kInf || f[1][i] < kInf) {
        cout << i << '\n';
        break;
      }
    }
  }
  return 0;
}
