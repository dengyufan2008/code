#include <fstream>
#include <queue>
#include <set>

using namespace std;

ifstream cin("star.in");
ofstream cout("star.out");

const int kMaxN = 5e5 + 1;
int n, m, a[kMaxN], d[kMaxN << 2];
set<int> s[kMaxN];
priority_queue<int> q1[kMaxN], q2[kMaxN];

void Change(int p, int l, int r, int x, int y) {
  if (l == r) {
    d[p] = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, y);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, y);
  }
  d[p] = max(d[p << 1], d[p << 1 | 1]);
}

int Ask(int p, int l, int r, int x) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1;
  if (d[p << 1] > x) {
    return Ask(p << 1, l, mid, x);
  } else {
    return Ask(p << 1 | 1, mid + 1, r, x);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], s[a[i]].insert(i);
  }
  for (int i = 0, p; i <= n; i++) {
    p = 0, s[i].insert(n + 1);
    for (auto j : s[i]) {
      q1[i].push(j - p), p = j;
    }
    s[i].insert(0), Change(1, 0, n, i, q1[i].top());
  }
  for (int i = 1, o, x, l, r; i <= m; i++) {
    static auto p = s[0].begin();
    cin >> o >> x;
    if (o == 2) {
      cout << Ask(1, 0, n, x) << '\n';
    } else if (a[x] != a[x + 1]) {
      s[a[x]].erase(x);
      p = s[a[x]].upper_bound(x), r = *p, l = *--p;
      q2[a[x]].push(x - l), q2[a[x]].push(r - x);
      q1[a[x]].push(x - l + 1), q1[a[x]].push(r - x - 1);
      s[a[x]].insert(x + 1), s[a[x + 1]].erase(x + 1);
      p = s[a[x + 1]].upper_bound(x), r = *p, l = *--p;
      q1[a[x + 1]].push(x - l), q1[a[x + 1]].push(r - x);
      q2[a[x + 1]].push(x - l + 1), q2[a[x + 1]].push(r - x - 1);
      s[a[x + 1]].insert(x);
      while (!q2[a[x]].empty() && q1[a[x]].top() == q2[a[x]].top()) {
        q1[a[x]].pop(), q2[a[x]].pop();
      }
      Change(1, 0, n, a[x], q1[a[x]].top());
      while (!q2[a[x + 1]].empty() && q1[a[x + 1]].top() == q2[a[x + 1]].top()) {
        q1[a[x + 1]].pop(), q2[a[x + 1]].pop();
      }
      Change(1, 0, n, a[x + 1], q1[a[x + 1]].top());
      swap(a[x], a[x + 1]);
    }
  }
  return 0;
}
