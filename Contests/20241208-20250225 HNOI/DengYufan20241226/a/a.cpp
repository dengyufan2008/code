#include <algorithm>
#include <fstream>
#include <queue>
#define PII pair<int, int>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
int n, m, ans, a[kMaxN], v[kMaxN], w[kMaxN];
bool b[kMaxN];
vector<int> d[kMaxN];
priority_queue<pair<int, int>> q;

class Seg {
  int c[kMaxN << 2];

  void Change(int p, int l, int r, int x, int y) {
    if (l == r) {
      c[p] += y;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    c[p] = c[p << 1] + c[p << 1 | 1];
  }

  int LowerBound(int p, int l, int r) {
    if (!c[p]) {
      return n + 2;
    } else if (l == r) {
      return l;
    }
    int mid = l + r >> 1, ans = LowerBound(p << 1, l, mid);
    if (ans == n + 2) {
      ans = LowerBound(p << 1 | 1, mid + 1, r);
    }
    return ans;
  }

  int LowerBound(int p, int l, int r, int x) {
    if (l >= x) {
      return LowerBound(p, l, r);
    }
    int mid = l + r >> 1, ans = n + 2;
    if (mid >= x) {
      ans = LowerBound(p << 1, l, mid, x);
    }
    if (ans == n + 2) {
      ans = LowerBound(p << 1 | 1, mid + 1, r, x);
    }
    return ans;
  }

 public:
  void Change(int x, int y) { Change(1, 1, n + 1, x, y); }
  int LowerBound(int x) { return LowerBound(1, 1, n + 1, x); }
} seg;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] >= 1) {
      d[a[i]].push_back(i);
    } else {
      seg.Change(i, 1);
    }
  }
  seg.Change(n + 1, n);
  for (int i = 1; i <= n; i++) {
    static vector<int> e;
    reverse(d[i].begin(), d[i].end());
    for (int j : d[i]) {
      int x = seg.LowerBound(j);
      if (x <= n + 1) {
        e.push_back(x), seg.Change(x, -1), v[j] = x;
      }
    }
    for (int j : e) {
      seg.Change(j, 1);
    }
    e.clear();
  }
  for (int i = 1; i <= n; i++) {
    if (v[i]) {
      ans++, b[i] = 1, w[i]++, w[v[i]]--;
    }
  }
  for (int i = 1, j = 0; i <= n; i++) {
    v[i] ? q.push({v[i], i}) : void();
    for (j += w[i]; j > m; j--) {
      w[q.top().first]++, ans--, b[q.top().second] = 0, q.pop();
    }
  }
  cout << ans << '\n';
  for (int i = 1; i <= n; i++) {
    if (b[i]) {
      cout << i << ' ';
    }
  }
  cout << '\n';
  return 0;
}
