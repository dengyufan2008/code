#include <chrono>
#include <fstream>
#include <random>
#include <set>

using namespace std;

ifstream cin("CON");
ofstream cout("a.in");

const int kT = 100, kN = 5, kV = 5;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

struct V {
  int x, y, z;
  V() {
    x = R(0, kV), y = R(0, kV), z = R(0, kV);
  }
  bool operator<(const V &v) const {
    return x < v.x || x == v.x && y < v.y || x == v.x && y == v.y && z < v.z;
  }
};
set<V> s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kT << '\n';
  for (int i = 1; i <= kT; i++) {
    s.clear(), cout << '\n' << kN << '\n';
    for (int j = 1; j <= kN; j++) {
      V v = V();
      while (s.count(v)) {
        v = V();
      }
      s.insert(v), cout << v.x << ' ' << v.y << ' ' << v.z << '\n';
    }
  }
  return 0;
}
