#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("i.in");

const int kN = 5;
int a[kN + 1];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << '\n';
  for (int i = 1; i <= 13; i++) {
    int x;
    for (x = R(1, kN); a[x] == 4; x = R(1, kN)) {
    }
    a[x]++;
  }
  for (int i = 1; i <= kN; i++) {
    for (int j = 1; j <= a[i]; j++) {
      cout << i << ' ' << j << '\n';
    }
  }
  return 0;
}
