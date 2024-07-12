#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 5e4 + 1, kMaxM = 1e5 + 1;
int n, m;
string s, t;
bitset<kMaxN> p, w[128], f[kMaxM];
vector<pair<int, bool>> ans;

void M(int l, int r) {
  int c = 0;
  for (int i, j = r; j >= l; j = i) {
    for (i = j; i >= l && t[i] != 'A'; i--) {
    }
    for (int k = i + 1; k <= j; k++) {
      ans.push_back({i, t[k] == 'G'});
    }
    for (i--; i >= l && t[i] == 'A'; i--) {
      ans.push_back({i, 0});
    }
    c++;
  }
  for (int i = 1; i < c; i++) {
    ans.push_back({l, 0});
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s >> t;
  s = '~' + s, t = '~' + t, f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    w[s[i]][i] = 1;
  }
  for (int i = 1; i <= m; i++) {
    f[i] |= f[i - 1] << 1 & w[t[i]];
    if (t[i] == 'T') {
      p.reset();
    } else if (t[i] == 'A') {
      p |= f[i - 1];
    } else {
      f[i] |= p << 1;
    }
  }
  if (f[m][n]) {
    cout << "Yes\n";
    for (int i = n - 1, j = m, k = m; i >= 0; i--, k = j) {
      if (s[i + 1] != t[j--] || !f[j][i]) {
        for (; j >= 1 && (t[j + 1] != 'A' || !f[j][i]); j--) {
        }
        M(j + 1, k);
      }
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
      cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
  } else {
    cout << "No\n";
  }
  return 0;
}
