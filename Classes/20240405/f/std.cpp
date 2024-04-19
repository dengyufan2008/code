// xtqqwq
#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template <typename T>
bool chkmax(T &x, T y) { return x < y ? x = y, 1 : 0; }
template <typename T>
bool chkmin(T &x, T y) { return x > y ? x = y, 1 : 0; }

int readint() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

struct node {
  int opt, l, r, c;
} b[200005];

int n, m;
int mina[600000], maxa[600000], mx1[600000], mx2[600000], nxt[200005], lst[200005], act[200005];
ll tag1[600000], tag2[600000][2], tag3[600000], ans[200005];
vector<int> vec[200005], chn[600000];
vector<pii> tl[30], tr[30];

void modify2(int id, int l, int r, int c1, int c2, ll c3) {
  if (l == r) {
    if (act[l]) {
      if (c1 == 1 && b[l].opt == 2) chkmin(c2, b[l].c);
      if (c1 == 2 && b[l].opt == 1) chkmax(c2, b[l].c);
    }
    ans[l] += c2 * c3;
    return;
  }
  int mid = (l + r) / 2;
  if ((c1 == 1 && mina[id << 1] >= c2) || (c1 == 2 && maxa[id << 1] <= c2)) {
    tag3[id << 1] += c2 * c3;
    modify2(id << 1 | 1, mid + 1, r, c1, c2, c3);
  } else {
    tag2[id][c1 - 1] += c3;
    modify2(id << 1, l, mid, c1, c2, c3);
  }
}

void modify(int id, int l, int r, int c1, int c2, int c3) {
  if (l == r) {
    if (act[l]) {
      if (lst[l] > c1)
        c1 = lst[l], c2 = b[l].c;
      else if (b[c1].opt == 1 && b[l].opt == 2)
        chkmin(c2, b[l].c);
      else if (b[c1].opt == 2 && b[l].opt == 1)
        chkmax(c2, b[l].c);
    }
    ans[l] += 1ll * c1 * c2 * c3;
    return;
  }
  int mid = (l + r) / 2;
  if (mx1[id << 1] > c1) {
    tag1[id] += c3;
    modify(id << 1, l, mid, c1, c2, c3);
  } else {
    if (c1) modify2(id << 1, l, mid, b[c1].opt, c2, 1ll * c1 * c3);
    if (!c1)
      modify(id << 1 | 1, mid + 1, r, c1, c2, c3);
    else if (b[c1].opt == 1)
      modify(id << 1 | 1, mid + 1, r, c1, min(c2, mina[id << 1]), c3);
    else
      modify(id << 1 | 1, mid + 1, r, c1, max(c2, maxa[id << 1]), c3);
  }
}

void update(int id) {
  maxa[id] = max(maxa[id << 1], maxa[id << 1 | 1]);
  mina[id] = min(mina[id << 1], mina[id << 1 | 1]);
  if (mx1[id << 1] > mx1[id << 1 | 1]) {
    mx1[id] = mx1[id << 1];
    if (b[mx1[id]].opt == 1)
      mx2[id] = min(mx2[id << 1], mina[id << 1 | 1]);
    else
      mx2[id] = max(mx2[id << 1], maxa[id << 1 | 1]);
  } else
    mx1[id] = mx1[id << 1 | 1], mx2[id] = mx2[id << 1 | 1];
}

void build(int id, int l, int r) {
  maxa[id] = 0, mina[id] = 1 << 30;
  if (l == r) return;
  int mid = (l + r) / 2;
  build(id << 1, l, mid);
  build(id << 1 | 1, mid + 1, r);
}

void pushdown(int id, int l, int r) {
  int mid = (l + r) / 2;
  if (tag1[id]) {
    modify(id << 1 | 1, mid + 1, r, mx1[id << 1], mx2[id << 1], tag1[id]);
    tag1[id] = 0;
  }
  if (tag2[id][0]) {
    modify2(id << 1 | 1, mid + 1, r, 1, mina[id << 1], tag2[id][0]);
    tag2[id][0] = 0;
  }
  if (tag2[id][1]) {
    modify2(id << 1 | 1, mid + 1, r, 2, maxa[id << 1], tag2[id][1]);
    tag2[id][1] = 0;
  }
  if (tag3[id]) {
    tag3[id << 1] += tag3[id];
    tag3[id << 1 | 1] += tag3[id];
    tag3[id] = 0;
  }
}

void change(int id, int l, int r, int x, int c) {
  if (l == r) return (void)(mx1[id] = c, mx2[id] = b[l].c);
  pushdown(id, l, r);
  int mid = (l + r) / 2;
  if (x <= mid)
    change(id << 1, l, mid, x, c);
  else
    change(id << 1 | 1, mid + 1, r, x, c);
  update(id);
}

void flip(int id, int l, int r, int x, int c) {
  if (l == r) {
    act[l] = c;
    if (b[x].opt == 1)
      maxa[id] = c ? b[x].c : 0;
    else
      mina[id] = c ? b[x].c : 1 << 30;
    return;
  }
  pushdown(id, l, r);
  int mid = (l + r) / 2;
  if (x <= mid)
    flip(id << 1, l, mid, x, c);
  else
    flip(id << 1 | 1, mid + 1, r, x, c);
  update(id);
}

int getnxt(int id, int l, int r, int ql, int qr, int knd, int c) {
  if (knd == 1 && mina[id] > c) return r + 1;
  if (knd == 2 && maxa[id] < c) return r + 1;
  if (l == r) return r;
  int mid = (l + r) / 2;
  if (qr <= mid)
    return getnxt(id << 1, l, mid, ql, qr, knd, c);
  else if (ql > mid)
    return getnxt(id << 1 | 1, mid + 1, r, ql, qr, knd, c);
  else {
    int tmp = getnxt(id << 1, l, mid, ql, mid, knd, c);
    if (tmp <= mid)
      return tmp;
    else
      return getnxt(id << 1 | 1, mid + 1, r, mid + 1, qr, knd, c);
  }
}

int getlst(int id, int l, int r, int ql, int qr, int knd, int c) {
  if (knd == 1 && mina[id] > c) return l - 1;
  if (knd == 2 && maxa[id] < c) return l - 1;
  if (l == r) return l;
  int mid = (l + r) / 2;
  if (qr <= mid)
    return getlst(id << 1, l, mid, ql, qr, knd, c);
  else if (ql > mid)
    return getlst(id << 1 | 1, mid + 1, r, ql, qr, knd, c);
  else {
    int tmp = getlst(id << 1 | 1, mid + 1, r, mid + 1, qr, knd, c);
    if (tmp > mid)
      return tmp;
    else
      return getlst(id << 1, l, mid, ql, mid, knd, c);
  }
}

void findnxt(int dp, int x) {
  nxt[x] = 0;
  int pl = getnxt(1, 1, m, x, m, b[x].opt, b[x].c);
  if (pl <= m && getlst(1, 1, m, 1, pl, b[pl].opt, b[pl].c) == x) {
    if (lst[pl]) {
      tr[dp].pb(mp(lst[pl], pl));
      nxt[lst[pl]] = 0;
    }
    tl[dp].pb(mp(pl, lst[pl]));
    tr[dp].pb(mp(x, 0));
    change(1, 1, m, pl, x);
    nxt[x] = pl;
    lst[pl] = x;
  }
}

void findlst(int dp, int x) {
  lst[x] = 0;
  int pl = getlst(1, 1, m, 1, x, b[x].opt, b[x].c);
  if (pl && getnxt(1, 1, m, pl, m, b[pl].opt, b[pl].c) == x) {
    if (nxt[pl]) {
      tl[dp].pb(mp(nxt[pl], pl));
      change(1, 1, m, nxt[pl], 0);
      lst[nxt[pl]] = 0;
    }
    tl[dp].pb(mp(x, 0));
    tr[dp].pb(mp(pl, nxt[pl]));
    change(1, 1, m, x, pl);
    nxt[pl] = x;
    lst[x] = pl;
  }
}

void add(int dp, int x) {
  flip(1, 1, m, x, 1);
  findnxt(dp, x);
  findlst(dp, x);
}

void calc(int id, int l, int r) {
  if (l == r) return (void)(ans[l] += tag3[id]);
  pushdown(id, l, r);
  int mid = (l + r) / 2;
  calc(id << 1, l, mid);
  calc(id << 1 | 1, mid + 1, r);
}

void addop(int id, int l, int r, int ql, int qr, int c) {
  if (l == ql && r == qr) return (void)(chn[id].pb(c));
  int mid = (l + r) / 2;
  if (qr <= mid)
    addop(id << 1, l, mid, ql, qr, c);
  else if (ql > mid)
    addop(id << 1 | 1, mid + 1, r, ql, qr, c);
  else
    addop(id << 1, l, mid, ql, mid, c), addop(id << 1 | 1, mid + 1, r, mid + 1, qr, c);
}

void work(int id, int l, int r, int dp) {
  for (auto r : chn[id]) add(dp, r);
  if (l == r)
    modify(1, 1, m, 0, 0, 1);
  else {
    int mid = (l + r) / 2;
    work(id << 1, l, mid, dp + 1);
    work(id << 1 | 1, mid + 1, r, dp + 1);
  }
  for (auto r : chn[id]) flip(1, 1, m, r, 0);
  reverse(tl[dp].begin(), tl[dp].end());
  reverse(tr[dp].begin(), tr[dp].end());
  for (auto r : tr[dp]) nxt[r.fi] = r.se;
  for (auto r : tl[dp]) change(1, 1, m, r.fi, r.se), lst[r.fi] = r.se;
  tl[dp].clear();
  tr[dp].clear();
}

int main() {
  freopen("f.in", "r", stdin);
  freopen("f.ans", "w", stdout);
  n = readint();
  m = readint();
  assert(1 <= n && 1 <= m);
  assert(n <= 100000 && m <= 100000);
  for (int i = 1; i <= m; i++) {
    b[i].opt = readint(), b[i].l = readint(), b[i].r = readint(), b[i].c = readint();
    assert(b[i].opt == 1 || b[i].opt == 2);
    assert(b[i].l <= b[i].r && 1 <= b[i].l && b[i].r <= n);
    assert(1 <= b[i].c && b[i].c <= 1e8);
    addop(1, 1, n, b[i].l, b[i].r, i);
  }
  build(1, 1, m);
  work(1, 1, n, 0);
  calc(1, 1, m);
  for (int i = 1; i <= m; i++) printf("%lld", ans[i]), cout << " \n"[i == m];
  return 0;
}
