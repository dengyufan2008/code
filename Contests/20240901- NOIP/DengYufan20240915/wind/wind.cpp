#include <fstream>
#define LL long long

using namespace std;

ifstream cin("wind.in");
ofstream cout("wind.out");

const LL kMaxN = 1e6 + 1, kInf = 1e18;
int n, l, r, h, t, a[kMaxN];
LL k, f[kMaxN];
pair<LL, int> q[kMaxN];

LL Calc(int x) {
  h = 1, t = 1, q[1] = {0, 0};
  for (int i = 1; i <= n; i++) {
    for (; h <= t && q[h].second < i - x; h++) {
    }
    f[i] = q[h].first + a[i];
    for (; t >= h && q[t].first >= f[i]; t--) {
    }
    q[++t] = {f[i], i};
  }
  for (; h <= t && q[h].second <= n - x; h++) {
  }
  return q[h].first;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Calc(mid) > k) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (l <= n) {
    LL ansl = Calc(l), ansr = Calc(r);
    cout << (ansr - k < k - ansl ? ansr : ansl) << '\n';
  } else {
    cout << Calc(r) << '\n';
  }
  return 0;
}
