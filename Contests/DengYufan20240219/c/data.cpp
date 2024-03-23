#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("c.in");

const int kN = 3, kT = 2;
int b[kN + 1];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << '\n';
  for (int i = 1; i <= kN; i++) {
    cout << Rand() % i << " \n"[i == kN];
  }
  for (int i = 1; i <= kT; i++) {
    b[i] = 1;
  }
  shuffle(b + 1, b + kN, Rand);
  for (int i = 1; i <= kN; i++) {
    cout << b[i] + 1 << " \n"[i == kN];
  }
  return 0;
}
