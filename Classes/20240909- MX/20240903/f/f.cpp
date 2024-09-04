#include <fstream>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const LL kMaxN = 2e5 + 3, kInf = 2e18, kMod = 998244353, kInv3 = 332748118;
struct A {
  LL x, y;
} a[kMaxN];
struct Q {
  int x;
  LL k;
} q[kMaxN];
int n, m, h, t, l[kMaxN];
LL ans;

LLL Cross(int o, int x, int y) {
  return (LLL)(a[x].x - a[o].x) * (LLL)(a[y].y - a[o].y) -
         (LLL)(a[y].x - a[o].x) * (LLL)(a[x].y - a[o].y);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  t = 1, a[++n] = {m, 0};
  for (int i = 0; i <= n; i++) {
    for (; h > 1 && Cross(l[h - 1], l[h], i) >= 0; h--) {
    }
    l[++h] = i;
  }
  for (int i = 2; i <= h; i++) {
    int x = l[i];
    for (;; t--) {
      LL dx = a[x].x - a[q[t].x].x, dy = a[x].y - a[q[t].x].y;
      LL kl, kr;
      if (dy >= dx * (dx - 1) / 2) {
        kr = (dy - dx * (dx - 1) / 2) / dx;
      } else {
        kr = (dy - dx * (dx + 1) / 2 + 1) / dx;
      }
      kl = kr + dx;
      if ((LLL)dx * (LLL)kr + dx * (dx - 1) / 2 == dy) {
        kl--;
      }
      if (t == 1 || q[t].k > kl) {
        q[++t] = {x, kr};
        break;
      }
    }
  }
  for (int i = 2; i <= t; i++) {
    LL dx = (a[q[i].x].x - a[q[i - 1].x].x) % kMod;
    LL dy = (a[q[i].x].y - a[q[i - 1].x].y) % kMod;
    LL k = q[i].k % kMod;
    ans = (ans + a[q[i].x].y % kMod * dx) % kMod;
    ans = (ans - k * (dx - 1) % kMod * (dx - 1)) % kMod;
    ans = (ans + (dx - 2) * (dx - 1) / 2 % kMod * (k * 3 - dx) % kMod * kInv3) % kMod;
    LL d = (k * dx + dx * (dx - 1) / 2 - dy) % kMod;
    ans = (ans - d * (d + 1) / 2) % kMod;
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
