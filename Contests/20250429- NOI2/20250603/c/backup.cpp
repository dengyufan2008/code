#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 + 1, kMaxM = 1e6 + 2;
int t, n, c[kMaxM], ans[kMaxN];
pair<int, int> a[kMaxN];

bool S(int x) {
  if (x == n + 1) {
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " \n"[i == n];
    }
    return 1;
  }
  for (int i = a[x].first; i <= a[x].second; i++) {
    if (!c[i]) {
      bool u = 0;
      c[i - 1]++, c[i]++, c[i + 1]++;
      ans[x] = i, u = S(x + 1);
      c[i - 1]--, c[i]--, c[i + 1]--;
      if (u) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
      a[i].second--;
    }
    if (!S(1)) {
      cout << -1 << '\n';
    }
  }
  return 0;
}
