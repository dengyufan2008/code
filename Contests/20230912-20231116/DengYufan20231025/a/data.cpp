#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("a.in");

const int kN = 20, kM = 20, kV = 20;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << Rand() % kM + 1 << '\n';
  for (int i = 1; i <= kN; i++) {
    cout << Rand() % kV + 1 << ' ';
  }
  return 0;
}
