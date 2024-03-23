#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("c.in");

const int kT = 1, kN = 2000, kM = 2000, kQ = 250000;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kT << "\n\n";
  for (int i = 1; i <= kT; i++) {
    cout << kN << ' ' << kM << ' ' << kQ << '\n';
    for (int j = 1; j <= kQ; j++) {
      int x1 = Rand() % kN + 1, y1 = Rand() % kM + 1, x2 = Rand() % kN + 1, y2 = Rand() % kM + 1;
      cout << min(x1, x2) << ' ' << min(y1, y2) << ' ' << max(x1, x2) << ' ' << max(y1, y2) << '\n';
    }
    cout << '\n';
  }
  return 0;
}
