#include <fstream>
#include <unordered_set>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e6 + 1;
int t, n, m, c[kMaxN];
bool a[kMaxN];
unordered_set<int> f[kMaxN];
string s;

void Print(int x, int y) {
  if (x < m) {
    int w = y + c[x] - a[x];
    if (w & 1 ^ 1 && f[x + 1].count(w >> 1)) {
      Print(x + 1, w >> 1), cout << 0;
    } else {
      Print(x + 1, y - c[x] + n - a[x] >> 1), cout << 1;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
      a[i] = s[m - i - 1] == '1', c[i] = 0;
    }
    for (int i = 0; i < n; i++) {
      cin >> s;
      for (int j = 0; j < m; j++) {
        c[j] += s[m - j - 1] == '1';
      }
    }
    f[m].clear(), f[m].insert(0);
    for (int i = m - 1; i >= 0; i--) {
      f[i].clear();
      for (int j : f[i + 1]) {
        int w = j << 1 | a[i];
        if (0 <= w - c[i] && w - c[i] < n) {
          f[i].insert(w - c[i]);
        }
        if (0 <= w + c[i] - n && w + c[i] - n < n) {
          f[i].insert(w + c[i] - n);
        }
      }
    }
    if (f[0].count(0)) {
      Print(0, 0), cout << '\n';
    } else {
      cout << -1 << '\n';
    }
  }
  return 0;
}
