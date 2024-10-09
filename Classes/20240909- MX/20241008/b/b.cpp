#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 101;
int n, m, c[kMaxN];

void Invalid() {
  cout << "Impossible\n";
  exit(0);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, c[x]++, m = max(m, x);
  }
  for (int i = m; i > m >> 1; i--) {
    if (c[i] < 2) {
      Invalid();
    }
  }
  if ((m & 1) && c[m + 1 >> 1] != 2) {
    Invalid();
  } else if ((m & 1 ^ 1) && c[m + 1 >> 1] != 1) {
    Invalid();
  }
  for (int i = m - 1 >> 1; i >= 1; i--) {
    if (c[i]) {
      Invalid();
    }
  }
  cout << "Possible\n";
  return 0;
}
