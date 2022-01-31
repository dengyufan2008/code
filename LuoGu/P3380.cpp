#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kInf = 2147483647;
struct H {
  struct A {
    int v, k, c, s[2];
  };
  int s;
  vector<A> v = {{}};

  void Update(int p) {
    v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p != 0);
  }

  void Turn(int &p, bool b) {
    int q = v[p].s[b];
    v[p].s[b] = v[q].s[!b], v[q].s[!b] = p;
    Update(p), Update(q);
    p = q;
  }

  void Rebalance(int &p) {
    if (v[p].s[0] && v[p].k > v[v[p].s[0]].k) {
      Turn(p, 0);
    } else if (v[p].s[1] && v[p].k > v[v[p].s[1]].k) {
      Turn(p, 1);
    }
  }

  void Insert(int &p, int x) {
    if (!p) {
      p = v.size(), v.push_back({x, rand()});
    } else {
      Insert(v[p].s[v[p].v <= x], x);
    }
    Update(p), Rebalance(p);
  }

  int Replace(int &p) {
    int t = v[p].v;
    if (!v[p].s[1]) {
      p = v[p].s[0];
    } else {
      t = Replace(v[p].s[1]);
      Update(p);
    }
    return t;
  }

  void Delete(int &p, int x) {
    if (v[p].v == x) {
      if (!v[p].s[0] || !v[p].s[1]) {
        p = v[p].s[0] + v[p].s[1];
      } else {
        v[p].v = Replace(v[p].s[0]);
      }
    } else {
      Delete(v[p].s[v[p].v < x], x);
    }
    Update(p);
  }

  int FindRank(int p, int x) {
    if (!p) {
      return 0;
    }
    return v[p].v >= x ? FindRank(v[p].s[0], x) : FindRank(v[p].s[1], x) + v[v[p].s[0]].c + 1;
  }

  int FindPast(int p, int x) {
    if (!p) {
      return -kInf;
    }
    return v[p].v < x ? max(FindPast(v[p].s[1], x), v[p].v) : FindPast(v[p].s[0], x);
  }

  int FindNext(int p, int x) {
    if (!p) {
      return kInf;
    }
    return v[p].v > x ? min(FindNext(v[p].s[0], x), v[p].v) : FindNext(v[p].s[1], x);
  }
} h[200001];
int n, m, a[50001];

void Init() {
  for (int i = 1; i <= n * 4; i++) {
    h[i].Insert(h[i].s, kInf), h[i].Insert(h[i].s, -kInf);
  }
}

void Change(int p, int l, int r, int x, int y, bool b) {
  b ? h[p].Insert(h[p].s, y) : h[p].Delete(h[p].s, y);
  if (l < r) {
    int mid = (l + r) / 2;
    if (mid >= x) {
      Change(p * 2, l, mid, x, y, b);
    } else {
      Change(p * 2 + 1, mid + 1, r, x, y, b);
    }
  }
}

int FindRank(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    return h[p].FindRank(h[p].s, k);
  }
  int mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ans += FindRank(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    ans += FindRank(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  return ans;
}

int FindPast(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    return h[p].FindPast(h[p].s, k);
  }
  int mid = (l + r) / 2, ans = -2147483647;
  if (mid >= _l) {
    ans = max(ans, FindPast(p * 2, l, mid, _l, _r, k));
  }
  if (mid < _r) {
    ans = max(ans, FindPast(p * 2 + 1, mid + 1, r, _l, _r, k));
  }
  return ans;
}

int FindNext(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    return h[p].FindNext(h[p].s, k);
  }
  int mid = (l + r) / 2, ans = 2147483647;
  if (mid >= _l) {
    ans = min(ans, FindNext(p * 2, l, mid, _l, _r, k));
  }
  if (mid < _r) {
    ans = min(ans, FindNext(p * 2 + 1, mid + 1, r, _l, _r, k));
  }
  return ans;
}

int main() {
  srand(unsigned(time(0)));
  cin >> n >> m;
  Init();
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    Change(1, 1, n, i, a[i], 1);
  }
  for (int i = 1, o, x, y, k; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      cin >> k;
      cout << FindRank(1, 1, n, x, y, k) + 1 << '\n';
    } else if (o == 2) {
      cin >> k;
      int l = 0, r = 1e8, mid;
      while (l <= r) {
        mid = (l + r) / 2;
        if (FindRank(1, 1, n, x, y, mid) <= k) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      cout << r << '\n';
    } else if (o == 3) {
      Change(1, 1, n, x, a[x], 0), Change(1, 1, n, x, y, 1);
      a[x] = y;
    } else if (o == 4) {
      cin >> k;
      cout << FindPast(1, 1, n, x, y, k) << '\n';
    } else {
      cin >> k;
      cout << FindNext(1, 1, n, x, y, k) << '\n';
    }
  }
  return 0;
}
