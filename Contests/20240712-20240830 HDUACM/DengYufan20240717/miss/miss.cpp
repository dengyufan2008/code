#include <fstream>
#define LL long long

using namespace std;

ifstream cin("miss.in");
ofstream cout("miss.out");

const LL kMaxN = 5e5 + 1, kInf = 1e12;
int n, m, p;
LL a[kMaxN], f[kMaxN], g[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i] += a[i - 1], g[i] = -kInf;
  }
  f[0] = -kInf;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      g[j] = max(g[j - 1], g[j] * p - a[j]);
      f[j] = (g[j - 1] + a[j]) / p;
      g[j - 1] = f[j - 1];
    }
  }
  cout << a[n] - p * f[n] << '\n';
  return 0;
}
