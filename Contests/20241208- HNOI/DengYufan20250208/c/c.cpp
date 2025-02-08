#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2001;
int n, m, a[kMaxN][kMaxN];
bool b[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, b[x] = 1;
  }
  for (int i = 1; i < kMaxN; i++) {
    a[0][i] = i;
  }
  for (int i = 1, s = kMaxN; i < kMaxN; i++) {
    for (int j = 1, k = 1; j < kMaxN; j++) {
      if (!b[j]) {
        a[i][k++] = a[i - 1][j];
      }
    }
    for (int j = kMaxN - n; j < kMaxN; j++) {
      a[i][j] = s++;
    }
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, cout << a[y][x] << '\n';
  }
  return 0;
}
