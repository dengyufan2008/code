#include <fstream>
#define LL long long

using namespace std;

ifstream cin("bracket.in");
ofstream cout("bracket.out");

const LL kMaxN = 5e5 + 1, kInf = 1e16;
LL n, a, b, t, f[kMaxN], d[2][kMaxN], p[kMaxN], q[kMaxN], v[2][kMaxN << 2];
string s;

void Change(LL p, LL l, LL r, LL k, bool o) {
  if (l == r) {
    v[o][p] = k;
    return;
  }
  LL mid = l + r >> 1;
  mid >= t ? Change(p << 1, l, mid, k, o) : Change(p << 1 | 1, mid + 1, r, k, o);
  v[o][p] = max(v[o][p << 1], v[o][p << 1 | 1]);
}

LL Ask(LL p, LL l, LL r, LL k, bool o) {
  if (q[l] >= k && r <= t) {
    return v[o][p];
  }
  LL mid = l + r >> 1, ans = -kInf;
  if (mid > t || q[mid] >= k) {
    ans = max(ans, Ask(p << 1, l, mid, k, o));
  }
  if (mid < t) {
    ans = max(ans, Ask(p << 1 | 1, mid + 1, r, k, o));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> a >> b >> s;
  s = '~' + s;
  for (LL i = 1; i <= n; i++) {
    d[0][i] = d[0][i - 1] + (s[i] == '(' ? 1 : -1);
    d[1][i] = d[1][i - 1] + (s[i] == ')' ? -1 : 1);
  }
  for (LL i = n; i >= 1; i--) {
    for (; t && d[0][q[t]] > d[0][i]; t--) {
      p[q[t]] = i + 1;
    }
    q[++t] = i;
  }
  for (; t; t--) {
    p[q[t]] = 0;
  }
  t = 0, fill(&v[0][1], &v[0][n << 2], -kInf), fill(&v[1][1], &v[1][n << 2], -kInf);
  for (LL i = 1; i <= n; i++) {
    f[i] = max(f[i - 1], t && q[t] >= p[i] ? Ask(1, 1, n, p[i], i & 1) + i * a + b : -kInf);
    for (; t && d[1][q[t]] > d[1][i]; t--) {
      Change(1, 1, n, -kInf, q[t] & 1);
    }
    if (d[1][i - 1] <= d[1][i]) {
      q[++t] = i - 1;
      Change(1, 1, n, f[i - 1] - (i - 1) * a, i & 1 ^ 1);
    }
  }
  cout << f[n];
  return 0;
}
