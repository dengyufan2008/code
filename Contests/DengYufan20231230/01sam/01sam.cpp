#include <fstream>
#define LL long long

using namespace std;

ifstream cin("01sam.in");
ofstream cout("01sam.out");

const int kMaxN = 36;
struct V {
  int f, l, e[2];
} v[kMaxN << 1];
int n, m, r;
LL ans;
string s, t;

inline void Insert(int o) {
  int p = r;
  v[++m] = v[0], v[m].l = v[p].l + 1;
  for (; p && !v[p].e[o]; p = v[p].f) {
    v[p].e[o] = m;
  }
  if (p) {
    int q = v[p].e[o];
    if (v[p].l + 1 == v[q].l) {
      v[m].f = q, r = m;
    } else {
      v[++m] = v[q], v[m].l = v[p].l + 1;
      for (; p && v[p].e[o] == q; p = v[p].f) {
        v[p].e[o] = m;
      }
      v[m - 1].f = v[q].f = m, r = m - 1;
    }
  } else {
    v[m].f = 1, r = m;
  }
}

inline void S(int x) {
  if (x == n) {
    m = r = 1, v[1] = v[0];
    for (int i = 0; i < n; i++) {
      Insert(t[i] - '0');
    }
    ans += m;
    return;
  }
  if (s[x] != '1') {
    t.push_back('0'), S(x + 1), t.pop_back();
  }
  if (s[x] != '0') {
    t.push_back('1'), S(x + 1), t.pop_back();
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s;
  S(0);
  cout << ans << '\n';
  return 0;
}
