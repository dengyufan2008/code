// 1553ms
#include <ctime>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("collect.in");
ofstream cout("collect.out");

const LL kMaxN = 1e6 + 1, kMaxM = 2e6 + 1, kInf = 1e18;
struct E {
  int x, y, z;
} e[kMaxM];
int n, m, o, f[kMaxN], s[kMaxN];
LL mn, w[kMaxN], ans[kMaxN];

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    f[i] = i, s[i] = 1;
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z, e[i] = {x, y, z};
    x = GetRoot(x), y = GetRoot(y);
    if (x == y) {
      w[x] += z;
    } else {
      s[x] < s[y] ? swap(x, y) : void();
      f[y] = x, s[x] += s[y], w[x] += w[y] + z;
    }
  }
  mn = kInf;
  for (int i = 1; i <= n; i++) {
    if (f[i] == i && mn > w[i]) {
      mn = w[i], o = i;
    }
  }
  for (int i = 1; i <= m; i++) {
    if (GetRoot(e[i].x) == o) {
      ans[e[i].x] += e[i].z;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
