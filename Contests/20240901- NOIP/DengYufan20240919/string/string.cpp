#include <fstream>
#define LL long long

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 1e6 + 1;
struct V {
  int f, l, c, e[26];
  LL w;
} v[kMaxN << 1];
int n, m, w[kMaxN];
string s;

void Manacher() {
  int m = n << 1 | 1, d[kMaxN << 1];
  string t = "";
  for (int i = 0; i < n; i++) {
    t += '~', t += s[i];
  }
  t += '~';
  for (int i = 0, j, k = 0; i < m; i++) {
    if (i < k && i + d[(j << 1) - i] < k) {
      d[i] = d[(j << 1) - i];
      continue;
    }
    for (j = i; k < m && k <= (j << 1) && t[k] == t[(j << 1) - k]; k++) {
    }
    d[i] = k - j;
  }
  for (int i = 0; i < m; i++) {
    w[i >> 1]--, w[i + d[i] >> 1]++;
  }
  for (int i = n - 1; i >= 0; i--) {
    w[i] += w[i + 1];
  }
}

void BuildSam() {
  int m, r, l[kMaxN << 1], c[kMaxN] = {};
  m = r = 1;
  for (int i = n - 1; i >= 0; i--) {
    int x = s[i] - 'a', p = r;
    v[++m].l = v[p].l + 1;
    for (; p && !v[p].e[x]; p = v[p].f) {
      v[p].e[x] = m;
    }
    if (p) {
      int q = v[p].e[x];
      if (v[p].l + 1 == v[q].l) {
        v[m].f = q, r = m;
      } else {
        v[++m] = v[q], v[m].l = v[p].l + 1;
        for (; p && v[p].e[x] == q; p = v[p].f) {
          v[p].e[x] = m;
        }
        v[m - 1].f = v[q].f = m, r = m - 1;
      }
    } else {
      v[m].f = 1, r = m;
    }
  }
  for (int i = n - 1, p = 1; i >= 0; i--) {
    p = v[p].e[s[i] - 'a'], v[p].c = 1, v[p].w += w[i];
  }
  for (int i = 1; i <= m; i++) {
    c[v[i].l]++;
  }
  for (int i = 1; i <= n; i++) {
    c[i] += c[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    l[c[v[i].l]--] = i;
  }
  for (int i = m; i >= 1; i--) {
    int j = l[i];
    v[v[j].f].c += v[j].c, v[v[j].f].w += v[j].w;
  }
  v[1].c = v[1].w = 0;
}

LL CalcAns() {
  int m = n << 1 | 1;
  static int d[kMaxN << 1];
  LL ans = 0;
  string t = "";
  for (int i = 0; i < n; i++) {
    t += '~', t += s[i];
  }
  t += '~';
  for (int i = 0, j, k = 0; i < m; i++) {
    if (i < k && i + d[(j << 1) - i] < k) {
      d[i] = d[(j << 1) - i];
      continue;
    }
    for (j = i; k < m && k <= (j << 1) && t[k] == t[(j << 1) - k]; k++) {
    }
    d[i] = k - j;
  }
  int p = 1;
  for (int i = 0; i < n; i++) {
    if (d[i + n] == n - i + 1) {
      ans += v[p].c;
    }
    if (v[p].e[s[i] - 'a']) {
      p = v[p].e[s[i] - 'a'];
    } else {
      return ans;
    }
  }
  return ans + v[p].c + v[p].w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s;
  Manacher(), BuildSam();
  for (int i = 1; i <= m; i++) {
    cin >> s, n = s.size(), cout << CalcAns() << '\n';
  }
  return 0;
}
