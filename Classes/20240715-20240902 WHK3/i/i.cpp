#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 401, kMod = 1e9 + 7;
int n;
LL f[kMaxN], g[kMaxN][4];

void Update(LL &x, LL y) { x = (x + y) % kMod; }

LL C(LL x, int y) {
  const static int _fact[4] = {0, 1, 500000004, 166666668};
  LL ans = _fact[y];
  for (int i = 0; i < y; i++) {
    ans = ans * (x - i) % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, g[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = n - i; j >= 0; j--) {
      for (int k = 2; k >= 0; k--) {
        if (g[j][k]) {
          for (int l = 1; j + l * i <= n && k + l <= 3; l++) {
            Update(g[j + l * i][k + l], g[j][k] * C(f[i] + l - 1, l));
          }
        }
      }
    }
    f[i + 1] = (g[i][0] + g[i][1] + g[i][2] + g[i][3]) % kMod;
  }
  cout << f[n] << '\n';
  return 0;
}
