#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("zh.in");
ofstream cout("zh.out");

const LL kMaxN = 1e6 + 1;
struct V {
  LL l, *s, *p;
  vector<LL> e;
} v[kMaxN];
LL n, ans, *t, h[kMaxN * 5];

void S(LL f, LL x) {
  for (LL &i : v[x].e) {
    if (i != f) {
      S(x, i);
      v[x].l = max(v[x].l, v[i].l + 1);
      if (v[x].e[0] == f || v[v[x].e[0]].l < v[i].l) {
        swap(v[x].e[0], i);
      }
    }
  }
}

void T(LL f, LL x, bool b) {
  if (b) {
    v[x].s = t, v[x].p = t + v[x].l * 2 + 3, t += v[x].l * 3 + 4;
  }
  if (v[x].e.size() > 1) {
    v[v[x].e[0]].s = v[x].s + 1, v[v[x].e[0]].p = v[x].p - 1;
    T(x, v[x].e[0], 0);
  }
  for (int i : v[x].e) {
    if (i != f && i != v[x].e[0]) {
      T(x, i, 1);
      for (int j = 0; j <= v[i].l; j++) {
        ans += v[x].p[j + 1] * v[i].s[j];
        if (j) {
          ans += v[x].s[j - 1] * v[i].p[j];
        }
      }
      for (int j = 0; j <= v[i].l; j++) {
        v[x].p[j + 1] += v[x].s[j + 1] * v[i].s[j];
        if (j) {
          v[x].p[j - 1] += v[i].p[j];
        }
      }
      for (int j = 0; j <= v[i].l; j++) {
        v[x].s[j + 1] += v[i].s[j];
      }
    }
  }
  v[x].s[0]++, ans += v[x].p[0];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  t = h, S(0, 1), T(0, 1, 1);
  cout << ans;
  return 0;
}
