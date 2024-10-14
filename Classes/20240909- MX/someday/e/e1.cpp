#include <fstream>

using namespace std;

ifstream cin("e1.in");
ofstream cout("e1.out");

const int kMaxN = 1001, kMod = 1e9 + 7;
int t, n, ans, a[kMaxN], d[kMaxN], w[kMaxN], f[kMaxN][kMaxN];

bool In(int x, int l, int r) {
  if (l <= r) {
    return x >= l && x <= r;
  } else {
    return x >= l || x <= r;
  }
}

bool Valid(int x, int l, int r, bool o) {
  if ((x <= (n + 1 >> 1)) ^ o) {
    return (d[x] == 1 || !In(a[d[x] - 1], l, r)) &&
           (d[x] == n || !In(a[d[x] + 1], l, r));
  } else {
    return (d[x] == 1 || In(a[d[x] - 1], l, r)) &&
           (d[x] == n || In(a[d[x] + 1], l, r));
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n, ans = 0;
    for (int i = 1; i <= n; i++) {
      w[i] = 0, a[i] = i & 1 ? n - i + 2 >> 1 : n + i + 1 >> 1, d[a[i]] = i;
    }
    for (int i = 1, x; i <= n; i++) {
      cin >> x, ~x && (w[x] = a[i]);
    }
    for (bool o : {0, 1}) {
      for (int i = 1 + o; i <= n; i += 2) {
        if (!w[1] || w[1] == a[i]) {
          f[a[i]][a[i]] = 1;
        }
      }
      for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n; i++) {
          int j = (i + l - 3) % n + 1;
          int _i = (i - 2 + n) % n + 1;
          int _j = j % n + 1;
          if (f[i][j]) {
            if (l < n) {
              if ((!w[l] || w[l] == _i) && Valid(_i, i, j, o)) {
                f[_i][j] = (f[_i][j] + f[i][j]) % kMod;
              }
              if ((!w[l] || w[l] == _j) && Valid(_j, i, j, o)) {
                f[i][_j] = (f[i][_j] + f[i][j]) % kMod;
              }
            } else if (((_i > (n + 1 >> 1)) ^ o) && (!w[l] || w[l] == _i) && Valid(_i, i, j, o)) {
              ans = (ans + f[i][j]) % kMod;
            }
            f[i][j] = 0;
          }
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
