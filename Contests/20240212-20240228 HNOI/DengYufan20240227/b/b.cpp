#include <iostream>

using namespace std;

const int kMaxN = 5e5 + 2;
struct V {
  int w, l, r;
} v[kMaxN * 48];
int o, n, m, k, t, a[kMaxN], b[kMaxN], s[kMaxN], f[kMaxN];

void Add(int &p, int l, int r, int x) {
  v[++k] = v[p], p = k;
  if (l == r) {
    v[p].w++;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(v[p].l, l, mid, x);
  } else {
    Add(v[p].r, mid + 1, r, x);
  }
  v[p].w = v[v[p].l].w + v[v[p].r].w;
}

int FindPre(int p, int q, int l, int r, int x) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1, ans = 0;
  if (mid < x - 1 && v[v[p].r].w < v[v[q].r].w) {
    ans = FindPre(v[p].r, v[q].r, mid + 1, r, x);
  }
  if (v[v[p].l].w < v[v[q].l].w && !ans) {
    ans = FindPre(v[p].l, v[q].l, l, mid, x);
  }
  return ans;
}

int FindSuf(int p, int q, int l, int r, int x) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1, ans = 0;
  if (mid >= x + 1 && v[v[p].l].w < v[v[q].l].w) {
    ans = FindSuf(v[p].l, v[q].l, l, mid, x);
  }
  if (v[v[p].r].w < v[v[q].r].w && !ans) {
    ans = FindSuf(v[p].r, v[q].r, mid + 1, r, x);
  }
  return ans;
}

void Solve1() {
  for (int i = 1; i <= n; i++) {
    b[a[i]] = i, Add(s[i] = s[i - 1], 1, n, a[i]);
  }
  for (int i = 1, l, r, x; i <= m; i++) {
    cin >> l >> r >> x;
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      int pre = a[y] == 1 ? 0 : FindPre(s[l - 1], s[y], 1, n, a[y]);
      int suf = a[y] == n ? 0 : FindSuf(s[l - 1], s[y], 1, n, a[y]);
      cout << (pre && (!suf || b[pre] > b[suf]) ? pre : suf) << " \n"[j == x];
    }
  }
}

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

void Solve2() {
  for (int i = 1; i <= n + 1; i++) {
    f[i] = i;
  }
  for (int i = 1, l, r, x; i <= m; i++) {
    cin >> l >> r >> x;
    for (int j = GetRoot(l); j <= r; j = GetRoot(j + 1)) {
      b[a[j]] = ++t, Add(s[t] = s[t - 1], 1, n, a[j]);
      f[GetRoot(j)] = GetRoot(j + 1);
    }
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      int pre = a[y] == 1 ? 0 : FindPre(0, s[b[a[y]]], 1, n, a[y]);
      int suf = a[y] == n ? 0 : FindSuf(0, s[b[a[y]]], 1, n, a[y]);
      cout << (pre && (!suf || b[pre] > b[suf]) ? pre : suf) << " \n"[j == x];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cin >> m;
  o ? Solve2() : Solve1();
  return 0;
}
