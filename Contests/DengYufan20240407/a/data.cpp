#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("a.in");

const int kN = 2e5;
int a[kN + 1];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << 1 << '\n';
  for (int i = 1; i <= kN; i++) {
    a[i] = i;
  }
  shuffle(a + 1, a + kN + 1, Rand);
  for (int i = 1; i <= kN; i++) {
    cout << a[i] << " \n"[i == kN];
  }
  return 0;
}
