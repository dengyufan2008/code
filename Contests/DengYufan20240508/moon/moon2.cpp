#include <fstream>
#include <vector>

using namespace std;

ifstream cin("moon.in");
ofstream cout("moon.out");

const int kMaxN = 501;
int n, m, x, a[kMaxN], b[kMaxN], r[kMaxN];
bool e[kMaxN][kMaxN];
vector<int> ans[2];

bool T(int x, int o) {
  if (b[x] == o) {
    return 0;
  }
  b[x] = o;
  for (int i = 1; i <= n; i++) {
    if (e[x][i] && (!r[i] || T(r[i], o))) {
      r[i] = x;
      return 1;
    }
  }
  return 0;
}

void W(int x, bool o) {
  if (b[x] == m + 1) {
    return;
  }
  b[x] = m + 1, ans[o].push_back(x);
  for (int i = 1; i <= n; i++) {
    if (e[x][i]) {
      W(r[i], o ^ 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= a[i]; j++) {
      cin >> x, e[i][x] = 1;
    }
  }
  for (int i = 1; i <= m; i++) {
    if (!T(i, i)) {
      x = i;
    }
  }
  W(x, 0);
  cout << ans[0].size() << ' ' << ans[1].size() << '\n';
  for (int i : ans[0]) {
    cout << i << ' ';
  }
  cout << '\n';
  for (int i : ans[1]) {
    cout << i << ' ';
  }
  cout << '\n';
  return 0;
}
