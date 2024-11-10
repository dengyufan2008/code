#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 2e5 + 1;
struct V {
  LL w, s;
  int c, ans;
  int l, r;
} v[kMaxN * 40];
int t, n, m, k, s[kMaxN * 4];
LL a[kMaxN];

void Pushup(int x) {
  v[x].s = v[x].w, v[x].c = 1, v[x].ans = -1;
  if (v[x].l) {
    v[x].s += v[v[x].l].s, v[x].c += v[v[x].l].c;
    v[x].ans = max(v[x].ans, v[v[x].l].ans);
  }
  if (v[x].r) {
    v[x].s += v[v[x].r].s, v[x].c += v[v[x].r].c;
    v[x].ans = max(v[x].ans, v[v[x].r].ans);
  }
}

int Merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  }
  int p = ++k;
  if (max(v[x].w, v[y].w) * 2 < v[x].s + v[y].s) {
    v[p] = {max(v[x].w, v[y].w), v[x].s + v[y].s,
            v[x].c + v[y].c, v[x].c + v[y].c};
  } else if (v[x].w >= v[y].w) {
    v[p] = v[x], v[p].r = Merge(v[p].r, y), Pushup(p);
  } else {
    v[p] = v[y], v[p].l = Merge(x, v[p].l), Pushup(p);
  }
  return p;
}

void Init(int p, int l, int r) {
  if (l == r) {
    s[p] = ++k, v[s[p]] = {a[l], a[l], 1, -1};
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  s[p] = Merge(s[p << 1], s[p << 1 | 1]);
}

void Update(int p, int l, int r, int x) {
  if (l == r) {
    v[s[p]] = {a[l], a[l], 1, -1};
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Update(p << 1, l, mid, x);
  } else {
    Update(p << 1 | 1, mid + 1, r, x);
  }
  s[p] = Merge(s[p << 1], s[p << 1 | 1]);
}

int Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return s[p];
  }
  int mid = l + r >> 1;
  if (mid >= _l && mid < _r) {
    int x = Ask(p << 1, l, mid, _l, _r);
    int y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
    int ans = Merge(x, y);
    return ans;
  } else if (mid >= _l) {
    return Ask(p << 1, l, mid, _l, _r);
  } else {
    return Ask(p << 1 | 1, mid + 1, r, _l, _r);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    k = 0, Init(1, 1, n);
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x;
      if (x == 1) {
        cin >> x >> y;
        cout << v[Ask(1, 1, n, x, y)].ans << '\n';
      } else {
        cin >> x >> a[x];
        Update(1, 1, n, x);
      }
    }
  }
  return 0;
}
