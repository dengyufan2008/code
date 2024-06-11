#include <chrono>
#include <fstream>
#include <random>
#include <set>

using namespace std;

ifstream cin("CON");
ofstream cout("o.in");

const int kN = 1000, kM = 2000, kV = 10000;
set<pair<int, int>> s;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << kM << '\n';
  for (int i = 2; i <= kN; i++) {
    int j = R(1, i - 1);
    s.insert({j, i});
    cout << j << ' ' << i << ' ' << R(0, kV) << '\n';
  }
  for (int i = kN, x, y; i <= kM; i++) {
    do {
      x = R(1, kN), y = R(1, kN);
      x > y ? swap(x, y) : void();
      if (s.count({x, y})) {
        y = x;
      }
    } while (x == y);
    s.insert({x, y});
    cout << x << ' ' << y << ' ' << R(0, kV) << '\n';
  }
  return 0;
}
