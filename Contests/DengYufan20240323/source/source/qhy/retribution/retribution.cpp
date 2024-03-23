#include <bits/stdc++.h>

using namespace std;

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

int main() {
  cin >> n >> c;
  s[m] = 0, s[++m] = -1;
  for (i = 0; i < n; ++i) {
    cin >> a[i];
    s[++m] = a[i], cnt[s[m]]++, s[++m] = '#';
  }
  for (int i = 1; i <= c; i++) {
    ans2 = max(ans2, cnt[i]);
  }
  cout << manacher() << endl;
  return 0;
}