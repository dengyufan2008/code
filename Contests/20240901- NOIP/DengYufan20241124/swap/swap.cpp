#include <fstream>
#define LL long long

using namespace std;

ifstream cin("swap.in");
ofstream cout("swap.out");

const int kMaxN = 1e5 + 1;
int n, m, a[kMaxN], p[kMaxN], q[kMaxN], o[kMaxN];
pair<int, int> d[kMaxN];
LL k, t;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], p[i] = i;
  }
  cin >> d[m].first >> d[m].second;
  for (int i = 1; i < m; i++) {
    cin >> d[i].first >> d[i].second;
  }
  for (int i = 1; i <= m; i++) {
    d[i].first = (d[i].first + i) % n + 1;
    d[i].second = (d[i].second + i) % n + 1;
    swap(p[d[i].first], p[d[i].second]);
  }
  for (int i = 1; i <= n; i++) {
    q[i] = p[(i + m - 1) % n + 1];
  }
  for (int i = 1; i <= n; i++) {
    p[i] = i;
  }
  k = t / m, t %= m;
  for (LL i = 1; i <= k; i <<= 1) {
    if (i & k) {
      for (int j = 1; j <= n; j++) {
        o[j] = p[q[j]];
      }
      for (int j = 1; j <= n; j++) {
        p[j] = o[j];
      }
    }
    for (int j = 1; j <= n; j++) {
      o[j] = q[q[j]];
    }
    for (int j = 1; j <= n; j++) {
      q[j] = o[j];
    }
  }
  for (int i = 1; i <= t; i++) {
    swap(p[d[i].first], p[d[i].second]);
  }
  for (int i = 1; i <= n; i++) {
    q[(i + k * m - 1) % n + 1] = p[i];
  }
  for (int i = 1; i <= n; i++) {
    cout << a[q[i]] << " \n"[i == n];
  }
  return 0;
}
