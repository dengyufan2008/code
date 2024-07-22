#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("i.in");

const int kT = 5, kN = 5, kM = 5;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kT << '\n';
  for (int i = 1; i <= kT; i++) {
    cout << '\n';
    cout << kN << ' ' << kM << '\n';
    for (int j = 1; j <= kM; j++) {
      int x = R(0, kN), y = R(0, kN);
      while (x == y) {
        x = R(0, kN), y = R(0, kN);
      }
      x > y ? swap(x, y) : void();
      cout << x << ' ' << y << '\n';
    }
  }
  return 0;
}
