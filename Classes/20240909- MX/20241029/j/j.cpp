#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 3e5 + 1, kB = 550;
int n, m;

class H {
  LL a[kMaxN], t[kMaxN / kB + 1], s[kMaxN / kB + 1];

 public:
  void Init() {
    for (int i = 0; i < n; i++) {
      cin >> a[i], s[i / kB] += a[i];
    }
  }

  void Modify(int x, int w) {
    int o = x / kB;
    s[o] -= a[x], a[x] = w - t[o], s[o] += a[x];
  }

  void Add(int x, LL w) { a[x] += w, s[x / kB] += w; }

  void Add(int l, int r, LL w) {
    int lo = l / kB, ro = r / kB;
    if (lo == ro) {
      for (int i = l; i <= r; i++) {
        a[i] += w, s[lo] += w;
      }
    } else {
      for (int i = lo * kB + kB - 1; i >= l; i--) {
        a[i] += w, s[lo] += w;
      }
      for (int i = ro * kB; i <= r; i++) {
        a[i] += w, s[ro] += w;
      }
      for (int i = lo + 1; i < ro; i++) {
        t[i] += w, s[i] += w * (LL)kB;
      }
    }
  }

  LL Ask(int l, int r) {
    int lo = l / kB, ro = r / kB;
    LL ans = 0;
    if (lo == ro) {
      for (int i = l; i <= r; i++) {
        ans += a[i] + t[lo];
      }
    } else {
      for (int i = lo * kB + kB - 1; i >= l; i--) {
        ans += a[i] + t[lo];
      }
      for (int i = ro * kB; i <= r; i++) {
        ans += a[i] + t[ro];
      }
      for (int i = lo + 1; i < ro; i++) {
        ans += s[i];
      }
    }
    return ans;
  }
} h;

class T {
  struct V {
    int l, r;
    bool o;
    LL w;
    bool operator<(const V &v) const {
      return l < v.l;
    }
  };
  vector<V> v;

 public:
  void Init() { v.push_back({0, n - 1, 1, 0}); }
  void Erase(auto p) { h.Add(p->l, p->r, p->w), v.erase(p); }

  void Erase(auto l, auto r) {
    for (auto i = l; i != r; i++) {
      h.Add(i->l, i->r, i->w);
    }
    v.erase(l, r);
  }

  void ChangeL(auto &p, int x) {
    if (p->l < x) {
      h.Add(p->l, x - 1, p->w);
    } else if (p->l > x) {
      h.Add(x, p->l - 1, -p->w);
    }
    p->l = x;
  }

  void ChangeR(auto &p, int x) {
    if (p->r < x) {
      h.Add(p->r + 1, x, -p->w);
    } else if (p->r > x) {
      h.Add(x + 1, p->r, p->w);
    }
    p->r = x;
  }

  void Modify(int x, bool o) {
    auto p = --upper_bound(v.begin(), v.end(), V{x, 0, 0, 0});
    if (p->o == o) {
      return;
    }
    if (p->l == p->r) {
      if (x == 0) {
        auto r = p;
        r++, ChangeL(r, x), Erase(p);
      } else if (x == n - 1) {
        auto l = p;
        l--, ChangeR(l, x), Erase(p);
      } else {
        auto l = p, r = p;
        l--, r++, ChangeL(r, l->l), Erase(l, r);
      }
    } else if (p->l == x) {
      ChangeL(p, x + 1);
      if (x == 0) {
        v.insert(v.begin(), {0, 0, o, 0});
      } else {
        ChangeR(--p, x);
      }
    } else if (p->r == x) {
      ChangeR(p, x - 1);
      if (x == n - 1) {
        v.insert(v.end(), {n - 1, n - 1, o, 0});
      } else {
        ChangeL(++p, x);
      }
    } else {
      vector<V> _v = {{x, x, o, 0}, {x + 1, p->r, !o, 0}};
      ChangeR(p, x - 1), v.insert(++p, _v.begin(), _v.end());
    }
  }

  void Insert(int l, int r) {
    if (l == 0 && r == n - 1) {
      Erase(v.begin(), v.end()), v.push_back({0, n - 1, 1, 0});
    } else if (l == 0) {
      auto p = --upper_bound(v.begin(), v.end(), V{r + 1, 0, 0, 0});
      if (p->o) {
        ChangeL(p, 0), Erase(v.begin(), p);
      } else {
        ChangeL(p, r + 1), Erase(v.begin(), p), v.insert(v.begin(), {l, r, 1, 0});
      }
    } else if (r == n - 1) {
      auto p = --lower_bound(v.begin(), v.end(), V{l, 0, 0, 0});
      if (p->o) {
        ChangeR(p, n - 1), Erase(++p, v.end());
      } else {
        ChangeR(p, l - 1), Erase(++p, v.end()), v.insert(v.end(), {l, r, 1, 0});
      }
    } else {
      auto p = --lower_bound(v.begin(), v.end(), V{l, 0, 0, 0});
      auto q = --upper_bound(v.begin(), v.end(), V{r + 1, 0, 0, 0});
      if (p == q) {
        if (!p->o) {
          vector<V> _v = {{l, r, 1, 0}, {r + 1, p->r, 0, 0}};
          ChangeR(p, l - 1), v.insert(++p, _v.begin(), _v.end());
        }
      } else {
        Erase(++p, q);
        p = --lower_bound(v.begin(), v.end(), V{l, 0, 0, 0});
        q = --upper_bound(v.begin(), v.end(), V{r + 1, 0, 0, 0});
        ChangeR(p, l - 1), ChangeL(q, r + 1);
        if (p->o && q->o) {
          ChangeR(p, q->r), Erase(q);
        } else if (!p->o && !q->o) {
          v.insert(q, {l, r, 1, 0});
        } else {
          p->o ? ChangeR(p, r) : ChangeL(q, l);
        }
      }
    }
  }

  void Update1() {
    for (V &i : v) {
      i.o ? i.w++ : 0;
    }
  }

  void Update2() {
    for (V &i : v) {
      i.o ? i.w += i.r - i.l + 1 : 0;
    }
  }

  LL Ask(int l, int r) {
    auto p = --upper_bound(v.begin(), v.end(), V{l, 0, 0, 0});
    auto q = --upper_bound(v.begin(), v.end(), V{r, 0, 0, 0});
    if (p == q) {
      return p->w * (r - l + 1);
    } else {
      LL ans = p->w * (p->r - l + 1) + q->w * (r - q->l + 1);
      for (p++; p != q; p++) {
        ans += p->w * (p->r - p->l + 1);
      }
      return ans;
    }
  }

  void Move() {
    static vector<V> _v;
    // _v = v;
    // for (V i : _v) {
    //   if (!i.o && i.l > 0) {
    //     Modify(i.l - 1, 0), h.Modify(i.l - 1, -Ask(i.l - 1, i.l - 1));
    //   }
    // }
    V p = {0, -1};
    for (V i : v) {
      if (i.o && i.r < n - 1) {
        if (i.l < i.r) {
          i.r--, p.r >= 0 ? _v.push_back(p) : void(), p = i, h.Modify(i.r + 1, 0);
        } else {
          h.Modify(i.l, 0);
        }
      } else if (!i.o && i.l) {
        i.l--, h.Add(i.l, -i.w);
        if (p.r + 1 == i.l && !p.o) {
          p.r = i.r, h.Add(i.l, i.r, i.w - p.w);
        } else {
          p.r >= 0 ? _v.push_back(p) : void(), p = i;
        }
      } else {
        p.r >= 0 ? _v.push_back(p) : void(), p = i;
      }
    }
    p.r >= 0 ? _v.push_back(p) : void();
    v.swap(_v), _v.clear();
  }
} t;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, t.Init(), h.Init();
  for (int i = 0, x, y, z; i < m; i++) {
    cin >> x;
    if (x == 1) {
      cin >> x >> y, x--;
      t.Modify(x, y), h.Modify(x, y - t.Ask(x, x));
    } else if (x == 2) {
      cin >> x >> y >> z, x--, y--;
      t.Insert(x, y), h.Add(x, y, z);
    } else if (x == 3) {
      t.Update1();
    } else if (x == 4) {
      t.Update2();
    } else {
      cin >> x >> y, x--, y--;
      cout << t.Ask(x, y) + h.Ask(x, y) << '\n';
    }
    t.Move();
  }
  return 0;
}
