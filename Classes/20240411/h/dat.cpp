#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("h.in");

const int kN = 1e5, kS = 3e5, kV = 'z';
int a[kS + 1];
char c[kS];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << '\n';
  for (int i = 0; i < kS; i++) {
    a[i] = i, c[i] = R('a', kV);
  }
  shuffle(a + 1, a + kS, Rand);
  sort(a + 1, a + kN), a[kN] = kS;
  for (int i = 1; i <= kN; i++) {
    for (int j = a[i - 1]; j < a[i]; j++) {
      cout << c[j];
    }
    cout << '\n';
  }
  return 0;
}
