#include <chrono>
#include <fstream>
#include <random>
#include <unordered_map>
#define LL long long
#define ULL unsigned LL

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 5e4 + 1, kMaxM = 101, kBase = 715876003;
struct V {
  int r, f, s;
  vector<int> e;
} v[kMaxM][kMaxN];
int o, n, m, t, k;
LL ans;
ULL w[kMaxN], pw[kMaxN], d[kMaxN];
unordered_map<ULL, int> s;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

void Change(int o, int x, int y) {
  ans -= --s[d[x]];
  d[x] -= pw[o] * w[v[o][x].r];
  v[o][x].r = y;
  d[x] += pw[o] * w[v[o][x].r];
  ans += s[d[x]]++;
  for (int i : v[o][x].e) {
    Change(o, i, y);
  }
}

void Merge(int o, int x, int y) {
  x = v[o][x].r, y = v[o][y].r;
  if (x != y) {
    v[o][x].s > v[o][y].s ? swap(x, y) : void();
    v[o][x].f = y, v[o][y].s += v[o][x].s;
    v[o][y].e.push_back(x);
    Change(o, x, y);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * kBase;
  }
  for (int i = 1; i < kMaxN; i++) {
    w[i] = Rand();
  }
  cin >> o;
  while (o--) {
    ans = 0, s.clear();
    for (int i = 1; i <= n; i++) {
      d[i] = 0;
    }
    cin >> n >> m >> t >> k;
    for (int i = 0; i <= t; i++) {
      for (int j = 1; j <= n; j++) {
        v[i][j].r = v[i][j].f = j, v[i][j].s = 1, v[i][j].e.clear();
        d[j] += pw[i] * w[j];
      }
    }
    for (int i = 1; i <= n; i++) {
      s[d[i]]++;
    }
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      for (int j = 0; j <= t; j++) {
        Merge(j, x, y);
      }
    }
    for (int i = 1, x, y, z; i <= k; i++) {
      cin >> x >> y >> z, z--;
      Merge(z, x, y);
      cout << ans << '\n';
    }
  }
  return 0;
}
