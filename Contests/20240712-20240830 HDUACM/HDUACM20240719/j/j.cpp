#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 2e5 + 1, kMaxL = 18, kMaxB = 601;
int o, n, m, t, ans, a[kMaxN], p[kMaxL][kMaxN], lg[kMaxN];
LL w, h;
pair<LL, int> d[kMaxN];
struct V {
  int l, r, p;
  LL Calc() {
    return 1LL * (p - l + 1) * (r - p + 1);
  }
  bool operator<(const V &v) const {
    return a[p] < a[v.p] || a[p] == a[v.p] && p > v.p;
  }
} v;
priority_queue<V> q;

int Max(int l, int r) {
  int t = lg[r - l + 1];
  int x = p[t][l], y = p[t][r - (1 << t) + 1];
  return a[x] < a[y] ? y : x;
}

void Update(int x, LL y) {
  if (d[x].second < t) {
    d[x] = {0, t};
  }
  d[x].first += y;
  if (d[x].first > w) {
    ans = x, w = d[x].first;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  p[0][1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1, p[0][i] = i;
  }
  cin >> o;
  while (o--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        p[i][j] = p[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          if (a[p[i][j]] < a[p[i - 1][j + (1 << i - 1)]]) {
            p[i][j] = p[i - 1][j + (1 << i - 1)];
          }
        }
      }
    }
    for (int i = 1, l, r; i <= m; i++) {
      cin >> l >> r;
      ans = w = 0, t++, priority_queue<V>().swap(q);
      q.push({l, r, Max(l, r)});
      for (LL s = 1LL * (r - l + 1) * (r - l + 2) / 2, c; s > w;) {
        for (int t = a[q.top().p]; a[q.top().p] == t && (ans != t || s > w);) {
          v = q.top(), q.pop(), c = v.Calc(), s -= c, Update(a[v.p], c);
          if (v.p > v.l) {
            q.push({v.l, v.p - 1, Max(v.l, v.p - 1)});
          }
          if (v.p < v.r) {
            q.push({v.p + 1, v.r, Max(v.p + 1, v.r)});
          }
        }
      }
      h ^= 1LL * i * ans;
    }
    cout << h << '\n', h = 0;
  }
  return 0;
}
