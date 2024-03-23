#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("c.in");

const int kN = 7e4, kQ = 7e4;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << '\n';
  for (int i = 1; i < kN; i++) {
    cout << Rand() % i + 1 << ' ';
  }
  cout << '\n';
  cout << kQ << '\n';
  for (int i = 1; i <= kQ; i++) {
    // cout << Rand() % kN + 1 << ' ' << Rand() % kN + 1 << '\n';
    cout << 2 << ' ' << 527 << '\n';
  }
  return 0;
}
