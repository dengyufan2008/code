#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1, kInf = 1e9;
struct H {
  int f, l, s, e[26];
} h[kMaxN << 1];
struct V {
  int l, r, mn, mx, ans;
} v[kMaxN << 6];
int n, m, r, k, ansp, ansq, l[kMaxN << 1];
string s;

void Update(int p, int q) {
  if (1LL * ansp * q < 1LL * ansq * p) {
    ansp = p, ansq = q;
  }
}

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

void Pushup(int p) {
  v[p].mn = kInf, v[p].mx = -kInf, v[p].ans = kInf;
  if (v[p].l) {
    v[p].mn = min(v[p].mn, v[v[p].l].mn);
    v[p].mx = max(v[p].mx, v[v[p].l].mx);
    v[p].ans = min(v[p].ans, v[v[p].l].ans);
  }
  if (v[p].r) {
    v[p].mn = min(v[p].mn, v[v[p].r].mn);
    v[p].mx = max(v[p].mx, v[v[p].r].mx);
    v[p].ans = min(v[p].ans, v[v[p].r].ans);
  }
  if (v[p].l && v[p].r) {
    v[p].ans = min(v[p].ans, v[v[p].r].mn - v[v[p].l].mx);
  }
}

void Add(int &p, int l, int r, int x) {
  !p && (v[p = ++k].ans = kInf);
  if (l == r) {
    v[p].mn = v[p].mx = x;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(v[p].l, l, mid, x);
  } else {
    Add(v[p].r, mid + 1, r, x);
  }
  Pushup(p);
}

void Merge(int &p, int q, int l, int r) {
  if (!p || !q) {
    p += q;
    return;
  }
  int mid = l + r >> 1;
  Merge(v[p].l, v[q].l, l, mid);
  Merge(v[p].r, v[q].r, l, mid);
  Pushup(p);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  n = s.size(), m = r = ansq = 1;
  for (char c : s) {
    int o = c - 'a', p = r;
    h[++m].l = h[p].l + 1;
    for (; p && !h[p].e[o]; p = h[p].f) {
      h[p].e[o] = m;
    }
    if (p) {
      int q = h[p].e[o];
      if (h[p].l + 1 == h[q].l) {
        h[m].f = q, r = m;
      } else {
        h[++m] = h[q], h[m].l = h[p].l + 1;
        for (; p && h[p].e[o] == q; p = h[p].f) {
          h[p].e[o] = m;
        }
        h[m - 1].f = h[q].f = m, r = m - 1;
      }
    } else {
      h[m].f = 1, r = m;
    }
  }
  for (int i = 0, p = 1; i < n; i++) {
    p = h[p].e[s[i] - 'a'], Add(h[p].s, 0, n - 1, i);
  }
  for (int i = 1; i <= m; i++) {
    l[i] = i;
  }
  sort(l + 1, l + m + 1, [](int i, int j) {
    return h[i].l > h[j].l;
  });
  for (int i = 1; i <= m; i++) {
    int p = l[i];
    Update(v[h[p].s].ans + h[p].l, v[h[p].s].ans);
    Merge(h[h[p].f].s, h[p].s, 0, n - 1);
  }
  int gcd = Gcd(ansp, ansq);
  ansp /= gcd, ansq /= gcd;
  cout << ansp << '/' << ansq << '\n';
  return 0;
}
