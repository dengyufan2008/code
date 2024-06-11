#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("o.in");

const int kV = 1e4;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << 90000 << ' ' << 90299 << '\n';
  for (int i = 0; i < 300; i++) {
    for (int j = 1; j < 300; j++) {
      cout << i * 300 + j << ' ' << i * 300 + j + 1 << ' ' << R(0, kV) << '\n';
    }
    cout << i * 300 + 300 << ' ' << i * 300 + 1 << ' ' << R(0, kV) << '\n';
  }
  for (int i = 1; i < 300; i++) {
    cout << R(1, i) * 300 - R(0, 299) << ' ' << 300 * i + R(1, 300) << ' ' << R(0, kV) << '\n';
  }
  return 0;
}
