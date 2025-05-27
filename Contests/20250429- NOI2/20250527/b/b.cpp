#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1001;
int n, m, s, ans[kMaxN], f[kMaxN][kMaxN];
bool b1[kMaxN], b2[kMaxN];
pair<int, int> p1[kMaxN], p2[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> f[i][j];
    }
  }
  p1[n] = {-1, -1};
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (p1[j].first && !p1[f[i][j]].first) {
        p1[f[i][j]] = {i, j};
        break;
      }
    }
  }
  p2[1] = {-1, -1}, p1[1].first && (s = 1);
  for (int i = m + 1; i < n; i++) {
    for (int j = 1; j <= n; j++) {
      if (p2[j].first && !p2[f[i][j]].first) {
        p2[f[i][j]] = {i, j};
        if (!s && p1[f[i][j]].first) {
          s = f[i][j];
        }
        break;
      }
    }
  }
  b1[s] = 1;
  for (int i = s; i != n; i = p1[i].second) {
    ans[p1[i].second] = p1[i].first;
    b1[p1[i].second] = b2[p1[i].first] = 1;
  }
  for (int i = s; i != 1; i = p2[i].second) {
    ans[p2[i].second] = p2[i].first;
    b1[p2[i].second] = b2[p2[i].first] = 1;
  }
  for (int i = 1; i < n; i++) {
    if (!b2[i]) {
      for (int j = 1; j <= n; j++) {
        if (!b1[j] && b1[f[i][j]]) {
          b1[j] = 1, ans[j] = i;
          break;
        }
      }
    }
  }
  cout << "Yes\n";
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
