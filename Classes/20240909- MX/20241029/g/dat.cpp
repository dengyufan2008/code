#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#define LL long long

using namespace std;

ifstream cin("CON");
ofstream cout("g.in");

const int kT = 1, kN = 3e5, kM = 3e5;
// const int kT = 1, kN = 4, kM = 4;
int a[kN + 1];
vector<int> q[kN + 1];
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

LL R(LL l, LL r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i <= kN; i++) {
    a[i] = i;
  }
  cout << kT << '\n';
  for (int i = 1; i <= kT; i++) {
    cout << '\n';
    cout << kN << '\n';
    shuffle(a + 1, a + kN + 1, Rand);
    for (int j = 1; j <= kN; j++) {
      cout << a[j] << " \n"[j == kN];
      q[j].clear();
    }
    for (int j = 1; j <= kM; j++) {
      int k = R(1, kN);
      q[k].push_back(R(1, k));
    }
    for (int j = 1; j <= kN; j++) {
      cout << q[j].size() << ' ';
      for (int k : q[j]) {
        cout << k << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
