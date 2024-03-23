#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1.8e3 + 5;
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
int n, m, seed;
char s[N][N];
int main() {
  freopen("retribution.in", "r", stdin);
  freopen("retribution.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> seed;
  init(seed);
  for (int i = 1; i <= n; i++) {
    cin >> (s[i] + 1);
  }
  return 0;
}