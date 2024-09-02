#include <fstream>
#define LL long long

using namespace std;

ifstream cin("wobinigao.in");
ofstream cout("wobinigao.out");

const LL kMaxN = 1e5 + 1, kInf = 4e18, kDiv = 1e5;
LL n, w, v[2], mx[2], ans, a[kMaxN];
int m;
string s[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, n <<= 1;
  if (n <= kDiv) {
    string s = "~", t;
    for (int i = 1, x; i <= m; i++) {
      cin >> t >> x;
      for (int j = 1; j <= x; j++) {
        s += t;
      }
    }
    for (int i = n; i >= 1; i--) {
      w += s[i] == 'M' ? 1 : -1;
      if (i & 1) {
        ans = max(ans, w - (s[i] == 'M'));
      }
    }
  } else {
    for (int i = 1; i <= m; i++) {
      cin >> s[i] >> a[i];
    }
    for (int i = m, o = 1; i >= 1; i--) {
      v[0] = v[1] = 0, mx[0] = mx[1] = -kInf;
      for (int j = s[i].size() - 1; j >= 0; j--) {
        v[j & 1] += s[i][j] == 'M' ? 1 : -1;
        mx[j & 1] = max(mx[j & 1], v[0] + v[1] - (s[i][j] == 'M'));
      }
      if (a[i] == 1) {
        ans = max(ans, w + mx[o]);
        w += v[0] + v[1];
        o ^= s[i].size() & 1;
      } else if (v[0] + v[1] >= 0) {
        w += (v[0] + v[1]) * (a[i] - 2);
        o ^= s[i].size() & a[i] & 1;
        ans = max(ans, w + mx[o]);
        w += v[0] + v[1];
        o ^= s[i].size() & 1;
        ans = max(ans, w + mx[o]);
        w += v[0] + v[1];
        o ^= s[i].size() & 1;
      } else {
        ans = max(ans, w + mx[o]);
        w += v[0] + v[1];
        o ^= s[i].size() & 1;
        ans = max(ans, w + mx[o]);
        w += (v[0] + v[1]) * (a[i] - 1);
        o ^= s[i].size() & (a[i] ^ 1) & 1;
      }
    }
  }
  cout << (w <= 0 ? ans : -1) << '\n';
  return 0;
}
