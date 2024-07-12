#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("ladamatek.in");
ofstream cout("ladamatek.out");

const int kMaxN = 5e4 + 1;
struct V {
  int f, l, s, e[26];
} v[kMaxN << 1];
int n, m, r, q, l[kMaxN << 1];
string s;

void Insert(int c) {
  int p = r;
  v[++m].l = v[p].l + 1;
  for (; p && !v[p].e[c]; p = v[p].f) {
    v[p].e[c] = m;
  }
  if (p) {
    int q = v[p].e[c];
    if (v[p].l + 1 == v[q].l) {
      v[m].f = q, r = m;
    } else {
      v[++m] = v[q], v[m].l = v[p].l + 1;
      for (; p && v[p].e[c] == q; p = v[p].f) {
        v[p].e[c] = m;
      }
      v[q].f = v[m - 1].f = m, r = m - 1;
    }
  } else {
    v[m].f = 1, r = m;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  m = r = 1;
  for (char c : s) {
    Insert(c - 'a');
  }
  for (int i = 0, p = 1; i < s.size(); i++) {
    p = v[p].e[s[i] - 'a'], v[p].s++;
  }
  for (int i = 1; i <= m; i++) {
    l[i] = i;
  }
  sort(l + 1, l + m + 1, [](int i, int j) { return v[i].l < v[j].l; });
  for (int i = m; i >= 1; i--) {
    v[v[l[i]].f].s += v[l[i]].s;
  }
  v[0].s = 0;
  cin >> q;
  for (int i = 1, a, b, c, d, p; i <= q; i++) {
    cin >> a >> b >> c >> d;
    p = 1;
    for (int j = 1, w = b % c; j <= d && p; j++) {
      p = v[p].e[w % 26];
      w = (w * a + b) % c;
    }
    cout << v[p].s << '\n';
  }
  return 0;
}
