#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("tracy.in");
ofstream cout("tracy.out");

const int kMaxN = 4e5 + 1;
int n, m, k, ans, a[kMaxN], b[kMaxN], l[kMaxN], d[kMaxN];
vector<int> v[kMaxN];
priority_queue<int> q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, ans = n;
  for (int i = 1; i <= n * 2; i++) {
    cin >> a[i], l[i] = i;
  }
  sort(l + 1, l + n * 2 + 1, [](int i, int j) {
    return a[i] < a[j];
  });
  for (int i = 1; i <= n * 2; i++) {
    b[l[i]] = b[l[i - 1]] + (a[l[i]] > a[l[i - 1]]);
  }
  k = b[l[n * 2]];
  for (int i = 1; i <= n; i++) {
    int l = b[i * 2 - 1], r = b[i * 2];
    v[l].push_back(r), d[l]++, d[r]--;
  }
  for (int i = 1, s = 0; i <= k; i++) {
    s += d[i];
    for (int j : v[i]) {
      q.push(j);
    }
    for (; s > m; s--) {
      d[q.top()]++, q.pop(), ans--;
    }
  }
  cout << ans << '\n';
  return 0;
}
