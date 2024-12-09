#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("seer.in");
ofstream cout("seer.out");

const int kMaxN = 2e5 + 1, kInf = 2e9;
struct V {
  int l, r, c;
} v[kMaxN * 19];
int n, m, k, a[kMaxN], b[kMaxN], l[kMaxN], s[kMaxN];

void Add(int &p, int l, int r, int x) {
  static int t = 0;
  v[++t] = v[p], p = t;
  if (l == r) {
    v[p].c++;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(v[p].l, l, mid, x);
  } else {
    Add(v[p].r, mid + 1, r, x);
  }
  v[p].c = v[v[p].l].c + v[v[p].r].c;
}

int Pre(int p, int q, int l, int r) {
  if (v[p].c == v[q].c) {
    return 0;
  } else if (l == r) {
    return a[l];
  }
  int mid = l + r >> 1;
  if (v[v[p].r].c != v[v[q].r].c) {
    return Pre(v[p].r, v[q].r, mid + 1, r);
  } else {
    return Pre(v[p].l, v[q].l, l, mid);
  }
}

int Pre(int p, int q, int l, int r, int x) {
  if (r <= x) {
    return Pre(p, q, l, r);
  }
  int mid = l + r >> 1, ans = 0;
  if (mid < x) {
    ans = Pre(v[p].r, v[q].r, mid + 1, r, x);
  }
  if (!ans) {
    ans = Pre(v[p].l, v[q].l, l, mid, x);
  }
  return ans;
}

int Ask(int l, int r, int x) {
  int p = lower_bound(a + 1, a + k + 1, x) - a - 1;
  return p ? Pre(s[l - 1], s[r], 1, k, p) : 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return a[i] < a[j];
  });
  for (int i = 1; i <= n; i++) {
    b[l[i]] = b[l[i - 1]] + (a[l[i]] > a[l[i - 1]]);
  }
  sort(a + 1, a + n + 1), k = unique(a + 1, a + n + 1) - a - 1;
  for (int i = 1; i <= n; i++) {
    Add(s[i] = s[i - 1], 1, k, b[i]);
  }
  for (int i = 1, l1, r1, l2, r2; i <= m; i++) {
    cin >> l1 >> r1 >> l2 >> r2;
    int x = Ask(l1, r1, kInf), y = Ask(l2, r2, x);
    while (x && y && y < x >> 1) {
      x = Ask(l1, r1, y + 1 << 1);
      if (x <= y) {
        y = Ask(l2, r2, x);
      } else {
        break;
      }
    }
    cout << (x && y ? x + y : 0) << '\n';
  }
  return 0;
}
