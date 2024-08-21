#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 20, kMod = 1e9 + 7;
struct V {
  int e, c;
} v[kMaxN];
int t, n, m, k, q, l[kMaxN];
LL inv[kMaxN + 2], f[1 << kMaxN][kMaxN + 1];
string o;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxN + 2; i++) {
    inv[i] = Pow(i);
  }
  cin >> t;
  while (t--) {
    k = 0;
    for (int i = 0; i < n; i++) {
      v[i].e = v[i].c = 0;
    }
    cin >> n >> m >> q;
    for (int i = 0, x, y; i < m; i++) {
      cin >> x >> y, v[x - 1].e |= 1 << y - 1, v[y - 1].c++;
    }
    for (int i = 0; i < n; i++) {
      !v[i].c && (l[k++] = i);
    }
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < n; j++) {
        if ((v[l[i]].e >> j & 1) && !--v[j].c) {
          l[k++] = j;
        }
      }
    }
    for (int s = 0; s < 1 << n; s++) {
      for (int i = 0; i <= n; i++) {
        f[s][i] = 0;
      }
    }
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
      for (int s = 0; s < 1 << n; s++) {
        if (s >> l[i] & 1 ^ 1) {
          int e = 0;
          for (int j = 0; j < n; j++) {
            (s >> j & 1) && (e |= v[j].e);
          }
          if (e >> l[i] & 1 ^ 1) {
            Update(f[s | 1 << l[i]][1], f[s][0]);
            for (int j = 1; j < n; j++) {
              Update(f[s | 1 << l[i]][j], f[s][j] * j);
              Update(f[s | 1 << l[i]][j + 1], f[s][j] * 2);
            }
          }
        }
      }
    }
    for (int i = 1, x, s; i <= q; i++) {
      s = 0, cin >> x >> o;
      for (int j = 0; j < n; j++) {
        s |= (o[j] == '1') << j;
      }
      LL w = 1, ans = 0;
      for (int j = 0; j <= n; j++) {
        Update(ans, f[s][j] * w);
        w = w * (x - j) % kMod * inv[j + 1] % kMod;
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
