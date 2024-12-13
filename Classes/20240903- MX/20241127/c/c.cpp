#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
struct E {
  int a, b, c;
  LL s;
} e[kMaxN];
int t, n, m, k, h;
LL d[kMaxL][kMaxN];

bool Solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b, e[i].c = e[i].a + e[i].b;
  }
  if (k <= e[1].a) {
    return 1;
  } else if (n == 1 || k > e[1].a + e[1].b) {
    return 0;
  }
  k -= e[1].b;
  sort(e + 2, e + n + 1, [](E i, E j) { return i.c < j.c; });
  e[n].s = e[n].b;
  for (int i = n - 1; i >= 2; i--) {
    e[i].s = e[i + 1].s + e[i].b;
  }
  for (m = n; m >= 2 && e[m].a + e[m].s >= k; m--) {
  }
  for (h = 0; 1 << h <= n - m; h++) {
  }
  m++;
  for (int i = m; i <= n; i++) {
    d[0][i] = e[i].a + e[i].s;
  }
  for (int i = 1; i < h; i++) {
    for (int j = m; j <= n; j++) {
      d[i][j] = d[i - 1][j];
      if (j - (1 << i - 1) >= m) {
        d[i][j] = min(d[i][j], d[i - 1][j - (1 << i - 1)]);
      }
    }
  }
  h--;
  for (int i = m; i <= n; i++) {
    int p = i - 1;
    for (int j = h; j >= 0 && p >= m; j--) {
      if (p - (1 << j) + 1 >= m && d[j][p] >= k + e[i].b) {
        p -= 1 << j;
      }
    }
    if (e[p + 1].s + e[i].a >= k + e[i].b) {
      return 1;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cout << (Solve() ? "YES\n" : "NO\n");
  }
  return 0;
}
