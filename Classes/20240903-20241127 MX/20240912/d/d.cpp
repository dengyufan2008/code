// 懒得写线段树
#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 2e5 + 1;
int n, m, a[kMaxN], u[128];

int Calc() {
  int l[3] = {n + 1, n + 1, n + 1}, r[3] = {}, ans = 0;
  for (int i = 1; i <= n; i++) {
    l[a[i]] = min(l[a[i]], i);
    r[a[i]] = max(r[a[i]], i);
  }
  int x = 1, y = n;
  for (; x <= n && a[x] == a[1]; x++) {
  }
  for (; y >= 1 && a[y] == a[n]; y--) {
  }
  for (int i = 1; i <= n; i++) {
    if ((i >= l[(a[i] + 1) % 3] || i < x) && (i <= r[(a[i] + 1) % 3] || i > y)) {
      ans++;
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  u['R'] = 0, u['S'] = 1, u['P'] = 2;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c, a[i] = u[c];
  }
  cout << Calc() << '\n';
  for (int i = 1, x; i <= m; i++) {
    static char c;
    cin >> x >> c, a[x] = u[c];
    cout << Calc() << '\n';
  }
  return 0;
}
