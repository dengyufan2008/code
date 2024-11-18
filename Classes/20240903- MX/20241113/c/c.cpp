#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 8000, kMod = 998244353;
int n, ans, c[kMaxN], pw[kMaxN];
bool b[kMaxN];
bitset<kMaxN> m, t, p[kMaxN];
string s;

bool Insert() {
  for (int i = kMaxN - 1; i >= 0; i--) {
    if (t.test(i)) {
      if (b[i]) {
        t ^= p[i];
      } else {
        p[i] = t, b[i] = 1;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  cin >> n >> s, m._M_copy_from_string(s, 0, s.size());
  for (int i = 1; i <= n; i++) {
    cin >> s, t._M_copy_from_string(s, 0, s.size());
    for (int j = kMaxN >> 1; j && Insert(); j--, t <<= 1) {
    }
  }
  t.reset(), c[0] = b[0];
  for (int i = 1; i < kMaxN; i++) {
    c[i] = c[i - 1] + b[i];
  }
  for (int i = (kMaxN >> 1) - 1; i >= 0; i--) {
    if (m.test(i) ^ t.test(i)) {
      if (b[i]) {
        t ^= p[i];
      } else {
        ans--;
      }
    }
    if (m.test(i) && (b[i] || !t.test(i))) {
      ans = (ans + pw[i ? c[i - 1] : 0]) % kMod;
    }
    if (m.test(i) ^ t.test(i)) {
      break;
    }
  }
  ++ans %= kMod, cout << ans << '\n';
  return 0;
}
