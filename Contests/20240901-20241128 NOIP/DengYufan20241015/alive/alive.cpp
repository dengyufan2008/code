#include <fstream>

using namespace std;

ifstream cin("alive.in");
ofstream cout("alive.out");

const int kMaxN = 8e6 + 1;
int n, m, c[kMaxN];
long long ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      c[i * i + j * j]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (m - i * i + j * j > 0) {
        ans += c[m - i * i + j * j];
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
