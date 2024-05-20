#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("halation.in");
ofstream cout("halation.out");

const int kMaxM = 1e5 + 1;
int n, m, k, t, q[kMaxM], l[kMaxM], d[kMaxM];
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> q[i], l[i] = i;
  }
  for (int &i = k = 1, s = 0; i <= n && s < n; i++) {
    t = min(n - s, i + 1 >> 1);
    s += t, ans += 1LL * t * i;
  }
  k--, cout << ans << '\n';
  sort(l + 1, l + m + 1, [](int i, int j) {
    return q[i] < q[j];
  });
  for (int i = 0, j = 1, p = 0, s = 0; i < k; i++) {
    int w = k - i;
    if (w & 1 ^ 1) {
      w--;
    } else if (w > t * 2 - 1) {
      w -= 2;
    }
    if (w > (p >>= 1)) {
      for (; j <= m && q[l[j]] <= s + w - p; j++) {
        int o = q[l[j]] + p - s;
        for (; o & 1 ^ 1; o >>= 1) {
          d[l[j]]++;
        }
        d[l[j]] += i + o;
      }
      s += w - p, p = w;
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << d[i] << '\n';
  }
  return 0;
}
