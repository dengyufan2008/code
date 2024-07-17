#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("h.in");

const int kN = 4, kV = 10;
int a[kN];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << R(1, kN) << '\n';
  for (int i = 0; i < kN; i++) {
    a[i] = R(-kV, kV);
  }
  sort(a, a + kN, [](int i, int j) {
    return abs(i) > abs(j) || abs(i) == abs(j) && i > 0;
  });
  for (int i = 0; i < kN; i++) {
    cout << a[i] << " \n"[i == kN - 1];
  }
  return 0;
}
