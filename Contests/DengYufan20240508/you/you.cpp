#include <fstream>

using namespace std;

ifstream cin("you.in");
ofstream cout("you.out");

const int kMaxN = 2e7 + 1, kU = 7055, kV = 5164;
int t, n, a[kMaxN];

int Gcd(int x, int y) {
  static int gcd[kU + 1][kV + 1] = {};
  if (!x || !y) {
    return x | y;
  } else if (gcd[x][y]) {
    return gcd[x][y];
  }
  return gcd[x][y] = Gcd(y, x % y);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i <= kU; i++) {
    for (int j = -kV; j <= kV; j++) {
      if (Gcd(i, abs(j)) == 1) {
        int ii = i * i, ij = i * j, jj = j * j;
        int y = ii + ij + jj;
        int x = y + (ij << 1);
        int z = y - (jj << 1);
        int w = max(max(x, y), z);
        x > 0 && z > 0 && w < kMaxN && a[w]++;
      }
    }
  }
  for (int i = 1; i < kMaxN; i++) {
    a[i] += a[i - 1];
  }
  cin >> t;
  while (t--) {
    cin >> n;
    cout << a[n] << '\n';
  }
  return 0;
}
