#include <fstream>
#define LL long long

using namespace std;

ifstream cin("soulist.in");
ofstream cout("soulist.out");

const int kMaxN = 5e5 + 1, kMaxM = 1001, kMod = 998244353;
struct Q {
  int o, x, y, z;
} q[kMaxM];
int n, m, k, a[kMaxN], c[kMaxN];
LL p[kMaxM * 4][kMaxM * 4], w[kMaxM * 4];

void Input() {
  int r[kMaxN] = {}, l[kMaxN] = {}, s[kMaxN] = {};
  bool b[kMaxN] = {};
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], r[a[i]] = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].o >> q[i].x, b[q[i].x] = 1;
    if (q[i].o <= 2) {
      cin >> q[i].z;
    } else if (q[i].o == 3) {
      cin >> q[i].y >> q[i].z, b[q[i].y] = 1;
    } else {
      cin >> q[i].y, b[q[i].y] = 1;
    }
  }
  c[1] = 1;
  for (int i = 1; i <= n; i++) {
    w[c[i]] = (w[c[i]] + a[i]) % kMod, l[c[i]]++;
    c[i + 1] = c[i] + (i < n && (b[i] || b[i + 1]));
  }
  k = c[n];
  for (int i = 1; i <= n; i++) {
    if (b[r[i]]) {
      for (int j = 1; j <= k; j++) {
        p[j][c[r[i]]] = s[j];
      }
    }
    s[c[r[i]]]++;
    if (b[r[i]]) {
      for (int j = 1; j <= k; j++) {
        p[c[r[i]]][j] = l[j] - s[j];
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    q[i].x = c[q[i].x], q[i].y = c[q[i].y];
  }
}

void Output() {
  for (int i = 1; i <= m; i++) {
    int o = q[i].o, x = q[i].x, y = q[i].y, z = q[i].z;
    if (o == 1) {
      for (int j = 1; j <= k; j++) {
        LL t = p[j][x] * z % kMod;
        w[j] = (w[j] + t) % kMod;
        w[x] = (w[x] - t + kMod) % kMod;
        p[x][j] = (p[x][j] + t) % kMod;
        p[j][x] = (p[j][x] - t + kMod) % kMod;
      }
    } else if (o == 2) {
      for (int j = 1; j <= k; j++) {
        LL t = p[x][j] * z % kMod;
        w[j] = (w[j] - t + kMod) % kMod;
        w[x] = (w[x] + t) % kMod;
        p[x][j] = (p[x][j] - t + kMod) % kMod;
        p[j][x] = (p[j][x] + t) % kMod;
      }
    } else if (o == 3) {
      LL t1 = p[x][y] * z % kMod, t2 = p[y][x] * z % kMod;
      p[x][y] = (p[x][y] - t1 + t2 + kMod) % kMod;
      p[y][x] = (p[y][x] + t1 - t2 + kMod) % kMod;
      w[x] = (w[x] + t1 - t2 + kMod) % kMod;
      w[y] = (w[y] - t1 + t2 + kMod) % kMod;
      for (int j = 1; j <= k; j++) {
        if (j != x && j != y) {
          t1 = p[x][j] * z % kMod, t2 = p[y][j] * z % kMod;
          p[x][j] = (p[x][j] - t1 + t2 + kMod) % kMod;
          p[y][j] = (p[y][j] + t1 - t2 + kMod) % kMod;
          t1 = p[j][x] * z % kMod, t2 = p[j][y] * z % kMod;
          p[j][x] = (p[j][x] - t1 + t2 + kMod) % kMod;
          p[j][y] = (p[j][y] + t1 - t2 + kMod) % kMod;
          w[x] = (w[x] - t1 + t2 + kMod) % kMod;
          w[y] = (w[y] + t1 - t2 + kMod) % kMod;
        }
      }
    } else {
      LL ans = 0;
      for (int j = x; j <= y; j++) {
        ans = (ans + w[j]) % kMod;
      }
      cout << ans << '\n';
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Output();
  return 0;
}
