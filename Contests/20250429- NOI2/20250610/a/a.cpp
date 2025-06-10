#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
int t, u, n, m, x, y, c, a[kMaxN], ans[kMaxN];
string s;
vector<pair<int, int>> l;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> u;
  while (t--) {
    cin >> n >> s, n <<= 1, s = '1' + s + '1';
    u = m = x = y = c = 0;
    fill(&a[1], &a[n] + 1, 0);
    fill(&ans[1], &ans[n] + 1, 0);
    for (int i = 1; i <= n; i++) {
      if (s[i - 1] == '1' && s[i] == '1') {
        a[i] = 3, c++;
      } else if (s[i - 1] == '1') {
        a[i] = 1;
      } else if (s[i] == '1') {
        a[i] = 2;
      }
    }
    if (c & 1) {
      cout << "No\n";
      continue;
    } else if (c & 3) {
      l.clear();
      for (int i = 1, j = 1; i <= n; i = j) {
        for (; j <= n && (a[i] == 3) == (a[j] == 3); j++) {
        }
        if (a[i] == 3) {
          l.push_back({i, j - 1});
          if (l.size() == 2) {
            break;
          }
        }
      }
      if (l.size() < 2 || l[0].first == 1 && l[1].second == n) {
        cout << "No\n";
        continue;
      } else if (l[1].second < n) {
        ans[l[1].first - 1] = ans[l[1].second + 1] = ++m;
      } else {
        ans[l[0].first - 1] = ans[l[0].second + 1] = ++m;
        u = 1;
      }
      x = l[0].second, y = l[1].second, ans[x] = ans[y] = ++m;
    }
    for (int i = u ? l[1].first : 1;;) {
      static vector<int> v;
      if (a[i] == 3 && i != x && i != y) {
        v.push_back(i);
        if (v.size() == 4) {
          ans[v[0]] = ans[v[2]] = ++m;
          ans[v[1]] = ans[v[3]] = ++m;
          v.clear();
        }
      }
      i = i == n ? 1 : i + 1;
      if (i == (u ? l[1].first : 1)) {
        break;
      }
    }
    for (int i = 1, p; i <= n; i++) {
      if (!ans[i]) {
        if (a[i] == 1) {
          p = i;
        } else if (a[i] == 2) {
          ans[p] = ans[i] = ++m;
        }
      }
    }
    for (int i = 1, p = 0; i <= n; i++) {
      if (a[i] == 0) {
        if (!p) {
          p = i;
        } else {
          ans[p] = ans[i] = ++m, p = 0;
        }
      }
    }
    cout << "Yes\n";
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " \n"[i == n];
    }
  }
  return 0;
}
