#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("c.in");

const int kN = 5, kQ = 2.5e5;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << Rand() % kN + 1 << ' ' << kQ << '\n';
  for (int i = 1; i <= kQ; i++) {
    for (int j = 0; j < 4; j++) {
      cout << Rand() % kN + 1 << ' ';
    }
    cout << '\n';
  }
  return 0;
}
