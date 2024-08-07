#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("usd.in");
ofstream cout("usd.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
struct V {
  int f;
  bool o;
} v[kMaxN], t[kMaxN * 4];
int n, ans, a[kMaxN * 2];
pair<int, int> o[kMaxN];

int GetRoot(int x, bool &o) {
  if (v[x].f == x) {
    return x;
  }
  bool _o = o;
  o ^= v[x].o;
  v[x].f = GetRoot(v[x].f, o);
  v[x].o = o ^ _o;
  return v[x].f;
}

void Merge(int x, int y, bool o) {
  x = GetRoot(x, o), y = GetRoot(y, o);
  if (x == y) {
    o && (ans = 0);
  } else {
    v[x].f = y, v[x].o = o;
  }
}

void Tag(int p, int x) {
  if (t[p].o) {
    if (!x || !t[p].f) {
      t[p].f |= x;
    } else {
      Merge(x, t[p].f, 0);
    }
  }
}

void Pushdown(int p) {
  if (t[p].f) {
    Tag(p << 1, t[p].f);
    Tag(p << 1 | 1, t[p].f);
    t[p].f = 0;
  }
}

bool Change(int p, int l, int r, int x) {
  if (l == r) {
    if (t[p].f && t[p].o) {
      Merge(l, t[p].f, 1), t[p].f = 0;
    }
    return t[p].o ^= 1;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  bool ans;
  if (mid >= x) {
    ans = Change(p << 1, l, mid, x);
  } else {
    ans = Change(p << 1 | 1, mid + 1, r, x);
  }
  t[p].o = t[p << 1].o || t[p << 1 | 1].o;
  return ans;
}

void Tag(int p, int l, int r, int _l, int _r, int x) {
  if (l >= _l && r <= _r) {
    return Tag(p, x);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Tag(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Tag(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
}

void Pushall(int p, int l, int r) {
  if (l == r) {
    if (t[p].f && t[p].o) {
      Merge(l, t[p].f, 1), t[p].f = 0;
    }
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  Pushall(p << 1, l, mid);
  Pushall(p << 1 | 1, mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> o[i].first >> o[i].second;
  }
  sort(o + 1, o + n + 1);
  for (int i = 1; i <= n; i++) {
    a[o[i].first] = a[o[i].second] = v[i].f = i;
  }
  ans = 1;
  for (int i = 1; i <= n * 2; i++) {
    if (!Change(1, 1, n, a[i])) {
      int l = a[i] + 1, r = n;
      while (l <= r) {
        int mid = l + r >> 1;
        if (o[mid].first < i) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      if (a[i] < r) {
        Tag(1, 1, n, a[i] + 1, r, a[i]);
      }
    }
  }
  Pushall(1, 1, n);
  for (int i = 1; i <= n; i++) {
    if (v[i].f == i) {
      ans = ans * 2 % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
