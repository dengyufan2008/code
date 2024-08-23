#include <fstream>
#include <vector>

using namespace std;

ifstream cin("game.in");
ofstream cout("game.out");

const int kMaxN = 301, kV = kMaxN * (kMaxN - 1) / 2, kMod = 998244353;
struct V {
  int a, d;
  vector<int> e;
} v[kMaxN];
int n, m, k, ans, f[kMaxN][kMaxN * kMaxN];
char ch;

void Update(int &x, int y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> ch, v[i].a = ch == 'W' ? 1 : -1;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, x > y ? swap(x, y) : void(), v[x].e.push_back(y);
  }
  for (int i = n - 1; i >= 1; i--) {
    if (v[i].a == 1) {
      for (int j : v[i].e) {
        v[i].d = max(v[i].d, v[j].d + 1);
      }
    } else {
      for (int j : v[i].e) {
        v[i].d = min(v[i].d, v[j].d - 1);
      }
    }
  }
  k = n * (n - 1) / 2, f[0][kV] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = -k; j <= k; j++) {
      Update(f[i][j + kV], f[i - 1][j + kV]);
      Update(f[i][j + v[i].d + kV], f[i - 1][j + kV]);
    }
  }
  for (int i = 1; i <= k; i++) {
    Update(ans, f[n][i + kV]);
  }
  cout << ans << '\n';
  return 0;
}
