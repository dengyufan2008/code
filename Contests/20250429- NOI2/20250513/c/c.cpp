#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

int n, m, ans;

template <typename T>
void Do(T &s, int o, int x, int y) {
  int l = y - x + 1;
  T u = s >> x << (s.size() - l) >> (s.size() - y - 1);
  if (o == 1) {
    T t = ~(u << 1) & u;
    t.reset(x);
    s ^= t ^ t >> 1;
  } else if (o == 2) {
    T t = ~(u >> 1) & u;
    t.reset(y);
    s ^= t ^ (t << 1);
  } else {
    ans = u.count();
  }
}

namespace Sub1 {
const int kMaxN = 1e5;
bitset<kMaxN> s;

int main() {
  for (int i = 0; i < n; i++) {
    static char c;
    cin >> c;
    if (c == '1') {
      s.set(i);
    }
  }
  for (int i = 0, o, x, y; i < m; i++) {
    cin >> o >> x >> y, x--, y--;
    Do(s, o, x, y);
    if (o == 3) {
      cout << ans << '\n';
    }
  }
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
const int kB = 2e4, kC = 200;
bitset<kB> s[kC];

int main() {
  for (int i = 0; i < n; i++) {
    static char c;
    cin >> c;
    if (c == '1') {
      s[i / kB].set(i % kB);
    }
  }
  for (int i = 0, o, x, y; i < m; i++) {
    cin >> o >> x >> y, x--, y--;
    int p = x / kB, q = y / kB;
    x %= kB, y %= kB;
    if (p == q) {
      Do(s[p], o, x, y);
      if (o == 3) {
        cout << ans << '\n';
      }
    } else {
      int res = 0;
      bool l = s[p].test(kB - 1), r = s[q].test(0);
      Do(s[p], o, x, kB - 1);
      res += ans;
      Do(s[q], o, 0, y);
      res += ans;
      if (o == 1) {
        if (!l && r) {
          s[p].set(kB - 1), s[q].reset(0);
        }
      } else if (o == 2) {
        if (l && !r) {
          s[p].reset(kB - 1), s[q].set(0);
        }
      } else {
        cout << res << '\n';
      }
    }
  }
  return 0;
}
}  // namespace Sub2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  if (n <= 100000 && m <= 100000) {
    return Sub1::main();
  } else {
    return Sub2::main();
  }
  return 0;
}
