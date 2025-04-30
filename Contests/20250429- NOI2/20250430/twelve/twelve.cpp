#include <fstream>
#define LL long long

using namespace std;

ifstream cin("twelve.in");
ofstream cout("twelve.out");

const int kMaxN = 1e6 + 2;
struct V {
  int f, l, e[26];
  int p = kMaxN, q;
} v[kMaxN << 1];
int t, n, m;
string s;

void BuildSam() {
  int r = m = 1;
  for (int i = 1; i <= n; i++) {
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
}

void CalcPQ() {
  static int a[kMaxN];
  a[0] = 1;
  for (int i = 1; i <= n; i++) {
    a[i] = v[a[i - 1]].e[s[i] - 'a'];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = a[i]; j && v[j].p > i; j = v[j].f) {
      v[j].p = i;
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = a[i]; j && v[j].q < i; j = v[j].f) {
      v[j].q = i;
    }
  }
}

void CalcAns() {
  static LL ans[kMaxN];
  fill(&ans[1], &ans[n + 1] + 1, 0);
  for (int i = 2; i <= m; i++) {
    if (v[i].q - v[i].p > v[v[i].f].l) {
      int l = v[v[i].f].l + 1, r = min(v[i].q - v[i].p, v[i].l);
      ans[v[i].p] += r - l + 1, ans[v[i].p + 1] -= r - l + 1;
      ans[v[i].q - r + 1]--, ans[v[i].q - l + 2]++;
    }
  }
  for (int o = 0; o < 2; o++) {
    for (int i = 1; i <= n; i++) {
      ans[i] += ans[i - 1];
    }
  }
  LL output = 0;
  for (int i = 1; i < n; i++) {
    output ^= ans[i];
  }
  cout << output << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    fill(&v[1], &v[m] + 1, v[0]);
    cin >> n >> s, s = '~' + s;
    BuildSam(), CalcPQ(), CalcAns();
  }
  return 0;
}
