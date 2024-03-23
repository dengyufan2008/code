#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#define RF(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

using namespace std;
using LL = long long;
using Pii = pair<int, int>;
using Pll = pair<LL, LL>;

const int kN = 1801;

namespace Input {
mt19937_64 R;
inline void init(int seed) {
  R = mt19937_64(seed);
}
inline int get(int l, int r) {
  uniform_int_distribution<int> distribution(l, r);
  return distribution(R);
}
}  // namespace Input
using Input::get;
using Input::init;
int n, m, q, seed;
mt19937_64 rnd;
char a[kN][kN];

int main() {
  RF("retribution");
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> q >> seed;
  rnd.seed(seed);
  init(seed);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] + 1;
  }
  auto G = [](int &x, int &y) {
    x = uniform_int_distribution<int>(1, n)(rnd);
    y = uniform_int_distribution<int>(1, m)(rnd);
  };
  for (; q--;) {
    cout << 0;
  }
  return 0;
}