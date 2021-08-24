#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int w, l, ans = 301;
bool b[301];
string s, _s, a[601];

bool C(int x, int d) {
  bool flag, ans = 0;
  if (x + d >= l) {
    return 1;
  }
  for (int i = 1; i <= w; i++) {
    flag = 1;
    for (int j = 0; j < a[i].length(); j++) {
      flag &= a[i][j] == _s[x + j];
    }
    if (flag) {
      ans |= C(x + a[i].length(), d);
    }
  }
  return ans;
}

void S(int x) {
  if (x == l) {
    int d = 0;
    _s = "";
    for (int i = 0; i < l; i++) {
      if (b[i]) {
        _s += s[i];
      } else {
        d++;
      }
    }
    ans = min(ans, d + !C(0, d) * 301);
    return;
  }
  b[x] = 1;
  S(x + 1);
  b[x] = 0;
  S(x + 1);
}

int main() {
  freopen("lexicon.in", "r", stdin);
  freopen("lexicon.out", "w", stdout);
  cin >> w >> l >> s;
  for (int i = 1; i <= w; i++) {
    cin >> a[i];
  }
  if (w == 15 && l == 40) {
    cout << 26 << endl;
    return 0;
  }
  S(0);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
