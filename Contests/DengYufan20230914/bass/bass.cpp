#include <fstream>
#define LL long long

using namespace std;

ifstream cin("bass.in");
ofstream cout("bass.out");

const LL kMaxN = 3001, kInf = 1e9;
struct V {
  LL u, v, d, e;
} v[kMaxN];
LL n, t, f[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> t;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].u >> v[i].v >> v[i].d >> v[i].e;
  }
  f[0][0] = (n + 1) * t, fill(&f[0][1], &f[kMaxN][0], kInf);
  for (LL i = 1; i <= n; i++) {
    f[i][0] = f[i - 1][0] + v[i].u + v[i].v;
    for (LL j = 1; j <= n; j++) {
      f[i][j] = f[i - 1][j] + min(v[i].u + v[i].v, v[i].d + v[i].e);
    }
    for (LL j = 1; j <= n; j++) {
      f[i][j] = min(f[i][j], f[i - 1][j - 1] + v[i].d + v[i].v - i * t * 2);
    }
    for (LL j = n - 1; j >= 0; j--) {
      f[i][j] = min(f[i][j], f[i - 1][j + 1] + v[i].u + v[i].e + i * t * 2);
    }
    for (LL j = 1; j <= n; j++) {
      f[i][j] = min(f[i][j], f[i][j - 1] + v[i].d + v[i].v - i * t * 2);
    }
    for (LL j = n - 1; j >= 0; j--) {
      f[i][j] = min(f[i][j], f[i][j + 1] + v[i].u + v[i].e + i * t * 2);
    }
  }
  cout << f[n][0];
  return 0;
}
