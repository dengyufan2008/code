#include <chrono>
#include <fstream>
#include <random>
#include <unordered_set>
#define LL long long

using namespace std;

ifstream cin("CON");
ofstream cout("collect.in");

const int kN = 1e6, kM = 2e6, kV = 1e9;
unordered_set<LL> s;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

LL R(LL l, LL r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << kM << '\n';
  for (int i = 1; i <= kM; i++) {
    int x = R(1, kN), y = R(1, kN);
    x > y ? swap(x, y) : void();
    while (x == y || s.count(1LL * x * (kN + 1) + y)) {
      x = R(1, kN), y = R(1, kN);
      x > y ? swap(x, y) : void();
    }
    s.insert(1LL * x * (kN + 1) + y);
    cout << x << ' ' << y << ' ' << R(1, kV) << '\n';
  }
  return 0;
}
