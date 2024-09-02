#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Info {
  int id, p, _p;
  Info(int id = 0, int p = 0, int _p = 0) : id(id), p(p), _p(_p) {}
};

const int MAXN = 100000 + 5;
const ll mod = 998244353;
int n, cnt;
int a[MAXN];
int lx[MAXN][18], rx[MAXN][18];
ll lsum[MAXN << 2], lsum2[MAXN << 2], rsum[MAXN << 2], rsum2[MAXN << 2];
ll ans[MAXN], b[MAXN];
vector<Info> lv[MAXN * 10], rv[MAXN * 10];
map<int, int> mp;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int find(int g) {
  if (mp.find(g) == mp.end()) mp[g] = ++cnt;
  return mp[g];
}

void push_up(int x) {
  int ls = x << 1, rs = x << 1 | 1;
  lsum[x] = lsum[ls] + lsum[rs];
  rsum[x] = rsum[ls] + rsum[rs];
  lsum2[x] = lsum2[ls] + lsum2[rs];
  rsum2[x] = rsum2[ls] + rsum2[rs];
}

void build(int x, int l, int r) {
  if (l == r) {
    if (l == 0) {
      lsum[x] = 1;
    }
    if (r == n + 1) {
      rsum[x] = 1;
    }
    return;
  }
  int mid = (l + r) / 2;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  push_up(x);
}

ll qlsum(int x, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    return lsum[x];
  }
  int mid = (l + r) / 2;
  ll res = 0;
  if (L <= mid) {
    res += qlsum(x << 1, l, mid, L, R);
  }
  if (R > mid) {
    res += qlsum(x << 1 | 1, mid + 1, r, L, R);
  }
  return res;
}

ll qlsum2(int x, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    return lsum2[x];
  }
  int mid = (l + r) / 2;
  ll res = 0;
  if (L <= mid) {
    res += qlsum2(x << 1, l, mid, L, R);
  }
  if (R > mid) {
    res += qlsum2(x << 1 | 1, mid + 1, r, L, R);
  }
  return res;
}

void updl(int x, int l, int r, int p, ll v) {
  if (l == r) {
    lsum[x] = v;
    lsum2[x] = v * (n - p) % mod;
    return;
  }
  int mid = (l + r) / 2;
  if (p <= mid) {
    updl(x << 1, l, mid, p, v);
  } else {
    updl(x << 1 | 1, mid + 1, r, p, v);
  }
  lsum[x] = lsum[x << 1] + lsum[x << 1 | 1];
  lsum2[x] = lsum2[x << 1] + lsum2[x << 1 | 1];
}

ll qrsum(int x, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    return rsum[x];
  }
  int mid = (l + r) / 2;
  ll res = 0;
  if (L <= mid) {
    res += qrsum(x << 1, l, mid, L, R);
  }
  if (R > mid) {
    res += qrsum(x << 1 | 1, mid + 1, r, L, R);
  }
  return res;
}

ll qrsum2(int x, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    return rsum2[x];
  }
  int mid = (l + r) / 2;
  ll res = 0;
  if (L <= mid) {
    res += qrsum2(x << 1, l, mid, L, R);
  }
  if (R > mid) {
    res += qrsum2(x << 1 | 1, mid + 1, r, L, R);
  }
  return res;
}

void updr(int x, int l, int r, int p, ll v) {
  if (l == r) {
    rsum[x] = v;
    rsum2[x] = v * p % mod;
    return;
  }
  int mid = (l + r) / 2;
  if (p <= mid) {
    updr(x << 1, l, mid, p, v);
  } else {
    updr(x << 1 | 1, mid + 1, r, p, v);
  }
  rsum[x] = rsum[x << 1] + rsum[x << 1 | 1];
  rsum2[x] = rsum2[x << 1] + rsum2[x << 1 | 1];
}

void add(int l, int r, ll v) {
  b[l] += v;
  b[r + 1] -= v;
}

int main() {
  freopen("e.in", "r", stdin);
  freopen("e.ans", "w", stdout);
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) {
    lx[i][0] = a[i];
    rx[i][0] = a[i];
  }
  for (int j = 1; j < 18; j++) {
    for (int i = 1; i <= n; i++) {
      if (i - (1 << j) + 1 >= 1) {
        lx[i][j] = gcd(lx[i][j - 1], lx[i - (1 << (j - 1))][j - 1]);
      }
      if (i + (1 << j) - 1 <= n) {
        rx[i][j] = gcd(rx[i][j - 1], rx[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int p = i, g = a[i];
    while (p >= 1) {
      int _p = p;
      for (int j = 17; j >= 0; j--) {
        if (p - (1 << j) + 1 >= 1 && gcd(g, lx[p][j]) == g) {
          p = p - (1 << j);
        }
      }
      lv[find(g)].push_back(Info(i, p + 1, _p));
      g = gcd(g, a[p]);
    }
  }
  for (int i = 1; i <= n; i++) {
    int p = i, g = a[i];
    while (p <= n) {
      int _p = p;
      for (int j = 17; j >= 0; j--) {
        if (p + (1 << j) - 1 <= n && gcd(g, rx[p][j]) == g) {
          p = p + (1 << j);
        }
      }
      rv[find(g)].push_back(Info(i, p - 1, _p));
      g = gcd(g, a[p]);
    }
  }
  build(1, 0, n + 1);
  for (auto bp : mp) {
    int g = bp.first, id = bp.second;
    sort(lv[id].begin(), lv[id].end(), [&](Info a, Info b) {
      return a.id < b.id;
    });
    ll sum = 1;
    vector<int> vec;
    for (auto info : lv[id]) {
      int x = info.id, p = info.p, _p = info._p;
      vec.push_back(x);
      ll res = qlsum(1, 0, n + 1, 0, p - 1) * (_p - p + 1) + qlsum2(1, 0, n + 1, p, _p) - qlsum(1, 0, n + 1, p, _p) * (n - _p);
      res = (res % mod + mod) % mod;
      sum += res;
      updl(1, 0, n + 1, x, res);
    }
    sum %= mod;
    sort(rv[id].begin(), rv[id].end(), [&](Info a, Info b) {
      return a.id > b.id;
    });
    for (auto info : rv[id]) {
      int x = info.id, p = info.p, _p = info._p;
      vec.push_back(x);
      ll res = qrsum(1, 0, n + 1, p + 1, n + 1) * (p - _p + 1) + qrsum2(1, 0, n + 1, _p, p) - qrsum(1, 0, n + 1, _p, p) * _p;
      res = (res % mod + mod) % mod;
      updr(1, 0, n + 1, x, res);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int x = 0;
    for (auto _x : vec) {
      ll tmp = (qlsum(1, 0, n + 1, 0, _x - 1) % mod) * (qrsum(1, 0, n + 1, _x + 1, n + 1) % mod) % mod;
      ans[_x] += sum - tmp;
      if (_x - x > 1) {
        add(x + 1, _x - 1, (sum - (qlsum(1, 0, n + 1, 0, x) % mod) * (qrsum(1, 0, n + 1, _x, n + 1) % mod)) % mod);
      }
      x = _x;
    }
    if (x < n) {
      add(x + 1, n, sum - qlsum(1, 0, n + 1, 0, x));
    }
    for (auto info : lv[id]) {
      int x = info.id;
      updl(1, 0, n + 1, x, 0);
    }
    for (auto info : rv[id]) {
      int x = info.id;
      updr(1, 0, n + 1, x, 0);
    }
  }
  for (int i = 1; i <= n; i++) {
    b[i] += b[i - 1];
    ans[i] += b[i];
    ans[i] = (ans[i] % mod + mod) % mod;
    printf("%d\n", ans[i]);
  }
  return 0;
}
