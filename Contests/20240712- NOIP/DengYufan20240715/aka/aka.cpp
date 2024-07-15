#include <fstream>
#include <vector>

using namespace std;

ifstream cin("aka.in");
ofstream cout("aka.out");

const int kMaxN = 5001;
int t, n, m, k, ans, b[kMaxN], r[kMaxN];
vector<int> e[kMaxN];

bool T(int o, int x) {
  if (b[x] == o) {
    return 0;
  }
  b[x] = o;
  for (int i : e[x]) {
    if (!r[i] || T(o, r[i])) {
      return r[i] = x;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> t;
  while (t--) {
    k = ans = 0;
    for (int i = 1; i <= n; i++) {
      b[i] = r[i] = 0, e[i].clear();
    }
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y, e[x].push_back(y), e[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
      k += e[i].empty(), ans += T(i, i);
    }
    ans = ans * 2 - n, k == 1 && (ans = min(ans, n - 4));
    cout << ans << '\n';
  }
  return 0;
}
