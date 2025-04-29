#include <chrono>
#include <fstream>
#include <random>
#include <set>
#define LL long long

using namespace std;

ifstream cin("CON");
ofstream cout("a.in");

const int kN = 4, kC = 3, kD = 3;
set<pair<int, int>> s;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

LL R(LL l, LL r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kC << ' ' << kD << ' ' << kN << '\n';
  for (int i = 1; i <= kN; i++) {
    int x = R(1, kC - 1), y = R(1, kD - 1);
    while (s.count({x, y})) {
      x = R(1, kC - 1), y = R(1, kD - 1);
    }
    s.insert({x, y});
    cout << x << ' ' << y << '\n';
  }
  return 0;
}
