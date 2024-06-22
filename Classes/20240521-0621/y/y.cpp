#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("y.in");
ofstream cout("y.out");

const int kMaxN = 2.5e5 + 1;
int u, n, s, t, a[kMaxN], f[2][kMaxN][2];
char c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    cin >> n >> s >> t;
    for (int i = 1; i <= n; i++) {
      cin >> c, a[i] = (c == '0') + (c == '1') * 2 - 1;
    }
    for (int o : {0, 1}) {
      ;
      reverse(a + 1, a + n + 1);
    }
  }
  return 0;
}
