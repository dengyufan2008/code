#include <fstream>

using namespace std;

ifstream cin("dstr.in");
ofstream cout("dstr.out");

const int kMod = 998244353;

namespace Sub1 {

const int kMaxN = 20;
int n, ans, f[kMaxN + 1][1 << kMaxN], b[1 << kMaxN];
string str;

bool C(int s) {
  for (int i = 0; i < n; i++) {
    if ('0' + (s >> i & 1 ^ 1) == str[i]) {
      return 0;
    }
  }
  return 1;
}

int main() {
  f[1][0] = f[1][1] = 1;
  for (int i = 2, o = 0; i <= n; i++) {
    for (int s = 0; s < (1 << i); s++) {
      o++;
      for (int j = 0; j < i; j++) {
        int t = s & ~(-1 << j) | s >> j + 1 << j;
        if (b[t] != o) {
          b[t] = o, f[i][s] = (f[i][s] + f[i - 1][t]) % kMod;
        }
      }
    }
  }
  for (int s = 0; s < (1 << n); s++) {
    if (C(s)) {
      ans = (ans + f[n][s]) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}

}  // namespace Sub1
namespace Sub2 {

int n, ans = 1;
string str;

int main() {
  for (int i = 1; i <= n; i++) {
    ans = 1LL * ans * (i + 1) % kMod;
  }
  cout << ans << '\n';
  return 0;
}

}  // namespace Sub2

int n;
string str;

bool Chick() {
  for (int i = 0; i < n; i++) {
    if (str[i] != '?') {
      return 0;
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> str;
  if (n <= 20) {
    Sub1::n = n, Sub1::str = str;
    return Sub1::main();
  } else if (Chick()) {
    Sub2::n = n, Sub2::str = str;
    return Sub2::main();
  } else {
    cout << "Shit! I Can't Solve This Hard Problem!\n";
  }
}
