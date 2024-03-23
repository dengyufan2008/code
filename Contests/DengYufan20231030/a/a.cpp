#include <bitset>
#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 5e5 + 1;
int t, n, l1, l2;
bitset<50> w[26], f[kMaxN][50];
string s, a, b;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  f[0][0] = 1;
  cin >> t;
  while (t--) {
    cin >> s >> a >> b;
    n = s.size(), l1 = a.size(), l2 = b.size(), s = '~' + s;
    for (int i = 0; i < 26; i++) {
      w[i].reset();
    }
    for (int i = 0; i < l2; i++) {
      w[b[i] - 'a'][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < l1; j++) {
        f[i][j].reset();
        f[i][j] |= (f[i - 1][j] & w[s[i] - 'a']).set(l2 - 1, 0) << 1;
        if ((f[i - 1][j] & w[s[i] - 'a'])[l2 - 1]) {
          f[i][j][0] = 1;
        }
      }
      for (int j = 0; j + 1 < l1; j++) {
        if (s[i] == a[j]) {
          f[i][j + 1] |= f[i - 1][j];
        }
      }
      if (s[i] == a.back()) {
        f[i][0] |= f[i - 1][l1 - 1];
      }
    }
    cout << (f[n][0][0] ? "Yes\n" : "No\n");
  }
  return 0;
}
