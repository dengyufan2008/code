#include <fstream>
#define LL long long

using namespace std;

ifstream cin("cablecar.in");
ofstream cout("cablecar.out");

const LL kMaxN = 2e6 + 2, kInf = 1e18;
int n, m, k, a[kMaxN], l[kMaxN], r[kMaxN];
LL f[kMaxN], g[kMaxN], h[kMaxN];
string s;

void Init() {
  static int h, t;
  static pair<LL, int> q[kMaxN];
  for (int i = 1; i <= n; i++) {
    l[i] = s[i - 1] == '0' ? l[i - 1] : i - 1;
  }
  for (int i = n; i >= 1; i--) {
    r[i] = s[i + 1] == '0' ? r[i + 1] : i + 1;
  }
  h = 1, t = 1, q[1] = {0, 0};
  for (int i = 1; i <= n; i++) {
    for (; h <= t && q[h].second < max(l[i], i - k); h++) {
    }
    f[i] = q[h].first + a[i];
    for (; t >= h && q[t].first >= f[i]; t--) {
    }
    q[++t] = {f[i], i};
  }
  h = 1, t = 1, q[1] = {0, n + 1};
  for (int i = n; i >= 1; i--) {
    for (; h <= t && q[h].second > min(r[i], i + k); h++) {
    }
    g[i] = q[h].first + a[i];
    for (; t >= h && q[t].first >= g[i]; t--) {
    }
    q[++t] = {g[i], i};
  }
}

LL Ask(int x, int y) {
  LL ans = y + f[x] + g[x] - a[x] * 2;
  if (s[x] == '0') {
    h[x + 1] = g[x + 1];
    for (int i = x + 2; i <= min(min(x + k - 1, r[x]), n + 1); i++) {
      h[i] = min(h[i - 1], g[i]);
    }
    for (int i = max(max(x - k + 1, l[x]), 0); i < x; i++) {
      ans = min(ans, f[i] + h[min(min(i + k, r[x]), n + 1)]);
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cin >> s, s = '~' + s + '~', Init(), cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << Ask(x, y) << '\n';
  }
  return 0;
}
