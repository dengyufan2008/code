#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#define LL long long

using namespace std;

ifstream cin("CON");
ofstream cout("b.in");

const int kN = 5;
int a[kN + 1], d[kN + 1];
bool b[kN + 1];
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

LL R(LL l, LL r) { return Rand() % (r - l + 1) + l; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int m = R(1, kN);
  for (int i = 1; i <= kN; i++) {
    a[i] = i;
  }
  for (int i = 1; i < m; i++) {
    b[i] = 1;
  }
  b[kN] = 1;
  shuffle(a + 1, a + kN + 1, Rand);
  shuffle(b + 1, b + kN, Rand);
  cout << kN << ' ' << m << '\n';
  for (int i = 1, j = 1, k = 0; i <= kN; i = j) {
    for (; !b[j]; j++) {
    }
    j++, k++;
    for (int l = i; l < j; l++) {
      d[a[l]] = k;
    }
  }
  for (int i = 1; i <= kN; i++) {
    cout << d[i] << " \n"[i == kN];
  }
  shuffle(a + 1, a + kN + 1, Rand);
  for (int i = 1; i < kN; i++) {
    cout << a[R(1, i)] << ' ' << a[i + 1] << '\n';
  }
  return 0;
}
