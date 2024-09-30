#include <fstream>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 1e5 + 1, kInf = 1e9;
struct V {
  int f, l, p, e[10];
} v[kMaxN << 1];
int n, k, b, h, t, w[10], f[kMaxN];
string s;
pair<int, int> q[kMaxN];

void Insert(int i, int x) {
  static int m = 1, r = 1;
  int p = r;
  v[++m].l = v[p].l + 1, v[m].p = i;
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

void Push(int w, int i) {
  for (; t >= h && q[t].first >= w; t--) {
  }
  q[++t] = {w, i};
}

int Pop(int i) {
  for (; h <= t && q[h].second < i; h++) {
  }
  return h <= t ? q[h].first : kInf;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  for (int i = 0; i < 10; i++) {
    cin >> w[i];
  }
  cin >> k >> b;
  n = s.size(), h = 1, v[1].p = -1;
  for (int i = 0, y = 1; i < n; i++) {
    int x = s[i] - '0';
    Insert(i, x), f[i] = f[i - 1 + !i] + w[x], y = v[y].e[x];
    for (; y && v[y].p + v[v[y].f].l >= i; y = v[y].f) {
    }
    if (y) {
      f[i] = min(f[i], Pop(max(v[y].p, i - v[y].l)) + k * i);
    }
    Push(f[i] - k * i + b, i);
  }
  cout << f[n - 1] << '\n';
  return 0;
}
