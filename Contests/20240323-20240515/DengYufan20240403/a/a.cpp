#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3e5 + 1, kInf = 1e9;
struct V {
  int l, r, mn, x, y, ans;
} v[kMaxN << 2];
int n, m, a[kMaxN];

V Merge(V x, V y) {
  V ans = {x.l, y.r, min(x.mn, y.mn)};
  if (x.mn < y.mn) {
    ans.x = x.x, ans.y = x.y + y.r - y.l + 1, ans.ans = x.ans;
  } else if (x.mn > y.mn) {
    ans.x = y.x + x.r - x.l + 1, ans.y = y.y, ans.ans = y.ans;
  } else {
    int l = x.y + y.x;
    ans.x = x.x, ans.y = y.y, ans.ans = x.ans + y.ans;
    ans.ans += l & 1 ? l + 1 : l / 2;
  }
  return ans;
}

void Init(int p, int l, int r) {
  v[p].l = l, v[p].r = r;
  if (l == r) {
    v[p].mn = a[l];
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

void Change(int p, int l, int r, int x, int y) {
  if (l == r) {
    v[p].mn = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, y);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, y);
  }
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

V Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p];
  }
  int mid = l + r >> 1;
  if (mid >= _l && mid < _r) {
    V x = Ask(p << 1, l, mid, _l, _r);
    V y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
    return Merge(x, y);
  } else if (mid >= _l) {
    return Ask(p << 1, l, mid, _l, _r);
  } else {
    return Ask(p << 1 | 1, mid + 1, r, _l, _r);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Init(1, 1, n);
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      Change(1, 1, n, x, y);
    } else {
      V t = Ask(1, 1, n, x, y);
      int ans = t.ans;
      if (t.mn && (y - x + 1 & 1)) {
        ans = y - x + 1;
      } else {
        int l = t.x + t.y;
        ans += l & 1 ? l + 1 : l / 2;
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
