#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 1e5 + 1, kInf = 1e9;
struct L {
  int x, l, r, k;
} l[kMaxN * 2];
struct E {
  int mn, mncnt;
  LL ans;
};
struct V {
  int l, r, mn, mncnt, mntag, xtag;
  LL ans;
} v[kMaxN * 48];
int x, y, n, m, k, s[kMaxN];
LL lastans;
vector<int> p(1);

void Copy(int &p, int l, int r) { v[++k] = v[p], !p && (v[k].mncnt = r - l + 1), p = k; }

void Addmn(int p, int mn) { v[p].mn += mn, v[p].mntag += mn; }

void Addx(int p, int x, int mn) {
  if (v[p].mn == mn) {
    v[p].xtag += x, v[p].ans += 1LL * v[p].mncnt * x;
  }
}

void Pushdown(int p, int l, int r) {
  int mid = l + r >> 1;
  if (v[p].mntag || v[p].xtag) {
    Copy(v[p].l, l, mid), Copy(v[p].r, mid + 1, r);
  }
  if (v[p].mntag) {
    Addmn(v[p].l, v[p].mntag), Addmn(v[p].r, v[p].mntag);
    v[p].mntag = 0;
  }
  if (v[p].xtag) {
    Addx(v[p].l, v[p].xtag, v[p].mn), Addx(v[p].r, v[p].xtag, v[p].mn);
    v[p].xtag = 0;
  }
}

void Pushup(int p, int l, int r) {
  int mid = l + r >> 1;
  v[p].mn = min(v[v[p].l].mn, v[v[p].r].mn), v[p].mncnt = 0;
  if (v[p].mn == v[v[p].l].mn) {
    v[p].mncnt += v[p].l ? v[v[p].l].mncnt : mid - l + 1;
  }
  if (v[p].mn == v[v[p].r].mn) {
    v[p].mncnt += v[p].r ? v[v[p].r].mncnt : r - mid;
  }
}

void Change(int &p, int l, int r, int _l, int _r, int k) {
  Copy(p, l, r);
  if (l >= _l && r <= _r) {
    Addmn(p, k);
    return;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Change(v[p].l, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Change(v[p].r, mid + 1, r, _l, _r, k);
  }
  Pushup(p, l, r);
}

E Merge(E x, E y) {
  E ans = {min(x.mn, y.mn), 0, x.ans + y.ans};
  if (ans.mn == x.mn) {
    ans.mncnt += x.mncnt;
  }
  if (ans.mn == y.mn) {
    ans.mncnt += y.mncnt;
  }
  return ans;
}

E Ask(int p, int l, int r, int _l, int _r) {
  if (!p) {
    return {0, min(r, _r) - max(l, _l) + 1, 0};
  } else if (l >= _l && r <= _r) {
    return {v[p].mn, v[p].mncnt, v[p].ans};
  }
  int mid = l + r >> 1;
  E ans = {kInf, 0, 0};
  if (mid >= _l) {
    ans = Merge(ans, Ask(v[p].l, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = Merge(ans, Ask(v[p].r, mid + 1, r, _l, _r));
  }
  ans.mn += v[p].mntag;
  if (ans.mn == v[p].mn) {
    ans.ans += 1LL * ans.mncnt * v[p].xtag;
  }
  return ans;
}

int Find(int x) {
  int l = 0, r = p.size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (p[mid] < x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> x >> y >> n >> m;
  for (int i = 1, x1, y1, x2, y2; i <= n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    x1 > x2 ? swap(x1, x2) : (void)0;
    y1 > y2 ? swap(y1, y2) : (void)0;
    l[i * 2 - 1] = {x1, y1 + 1, y2, 1};
    l[i * 2] = {x2, y1 + 1, y2, -1};
  }
  n <<= 1, l[++n] = {x - 1, 1, y, 0}, s[0] = k = 1;
  sort(l + 1, l + n + 1, [](L i, L j) { return i.x < j.x; });
  for (int i = 1, j; i <= n; i = j) {
    p.push_back(l[i].x), s[p.size() - 1] = s[p.size() - 2];
    Addx(s[p.size() - 1], l[i].x - l[i - 1].x, 0);
    for (j = i; j <= n && l[i].x == l[j].x; j++) {
      Change(s[p.size() - 1], 1, y, l[j].l, l[j].r, l[j].k);
    }
  }
  for (int i = 1, x1, y1, x2, y2, z; i <= m; i++) {
    cin >> x1 >> y1 >> x2 >> y2 >> z;  // 傻逼题输入要老子七行
    x1 = ((__int128_t)lastans * z + x1) % (x + 1);
    y1 = ((__int128_t)lastans * z + y1) % (y + 1);
    x2 = ((__int128_t)lastans * z + x2) % (x + 1);
    y2 = ((__int128_t)lastans * z + y2) % (y + 1);
    x1 > x2 ? swap(x1, x2) : (void)0;
    y1 > y2 ? swap(y1, y2) : (void)0;
    int l = Find(x1) - 1, r = Find(x2) - 2;
    E ans1 = {}, ans2 = {};
    lastans = 1LL * (x2 - x1) * (y2 - y1);
    if (l >= 0) {
      ans1 = Ask(s[l], 1, y, y1 + 1, y2);
      ans1.mn && (ans1.ans = 0);
      lastans += ans1.ans;
    }
    if (r >= 0) {
      ans2 = Ask(s[r], 1, y, y1 + 1, y2);
      ans2.mn && (ans2.ans = 0);
      lastans -= ans2.ans;
    }
    if (l > 0) {
      E ans0 = Ask(s[l - 1], 1, y, y1 + 1, y2);
      ans0.mn && (ans0.ans = 0);
      lastans -= (ans1.ans - ans0.ans) / (p[l + 1] - p[l]) * (p[l + 1] - x1);
    }
    if (r < p.size() - 1) {
      E ans3 = Ask(s[r + 1], 1, y, y1 + 1, y2);
      ans3.mn && (ans3.ans = 0);
      lastans -= (ans3.ans - ans2.ans) / (p[r + 2] - p[r + 1]) * (x2 - p[r + 1]);
    }
    cout << lastans << '\n';
  }
  return 0;
}
