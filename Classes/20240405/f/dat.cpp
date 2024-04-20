#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("f.in");

const int kN = 6, kM = 6, kV = 15;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << kM << '\n';
  for (int i = 1; i <= kM; i++) {
    cout << Rand() % 2 + 1 << ' ';
    int x = Rand() % kN + 1, y = Rand() % kN + 1;
    cout << min(x, y) << ' ' << max(x, y) << ' ';
    cout << Rand() % kV + 1 << '\n';
  }
  return 0;
}
