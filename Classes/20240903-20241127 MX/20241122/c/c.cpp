#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxN = 26, kInf = 1e13;
int a[kMaxN];
LL ans;
string s;

void S(int x) {
  if (x * 2 >= s.size()) {
    for (int i = x; i < s.size(); i++) {
      int w = 0;
      for (int j = 0; j <= i; j++) {
        w += a[j] * a[i - j];
      }
      if (w % 10 != s[i] - '0') {
        return;
      }
    }
    LL t = 0;
    for (int i = x - 1; i >= 0; i--) {
      t = t * 10 + a[i];
    }
    ans = min(ans, t);
    return;
  }
  int w = 0;
  for (int i = 1; i < x; i++) {
    w += a[i] * a[x - i];
  }
  w = (w - (s[x] - '0') + 10) % 10;
  for (int i = 0; i < 10; i++) {
    if ((2 * a[0] * i + w) % 10 == 0) {
      a[x] = i, S(x + 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  if (s.size() & 1 ^ 1) {
    cout << -1 << '\n';
  } else {
    ans = kInf;
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
      swap(s[i], s[j]);
    }
    for (int i = 0; i < 10; i++) {
      if (i * i % 10 == s[0] - '0') {
        a[0] = i, S(1);
      }
    }
    cout << (ans == kInf ? -1 : ans) << '\n';
  }
  return 0;
}
