![](https://count.getloli.com/get/@748437?theme=gelbooru)
![](https://www.ipip5.com/ipimg/)
![](https://luogu.wao3.cn/api/practice?id=250810&dark_mode=true)
![](https://luogu.wao3.cn/api/guzhi?id=250810&scores=100,29,4,93,30&dark_mode=true)
# *DengYufan's Introduction*

## *Write In The First*
- Star Me If You Like. It's Free, And Will Make Me Happy For A Long Time.

## *Important Time*
- Start Coding : 2019.8.16

- Sign Up In Luogu : 2019.9.15

- Orange Name In Luogu : 2021.10.21

- CSP Jenior Second Prize : 2020

- CSP Jenior First Prize : 2021

- CSP Senior Second Prize : 2021

- First AC of Black Problem:2022.7.24

- Red Name in LuoGu:2022.9.7

## *Accounts*
- Luogu : dengyufan

- USACO : dengyuf1

- Codeforces : dengyufan

- Atcoder : dengyufan2008

- Github : dengyufan2008

- Focus On Me If You Like

## *Websites*
- [Luogu](http://www.luogu.com.cn)

- [USACO](https://train.usaco.org)

- [Codeforces](https://codeforces.com)

- [AtCoder](https://atcoder.jp)

- [C++Info](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)

- [Github](https://github.com)

- [OI-Wiki](https://oiwiki.com)

## *Economic Things*
- C++14 Compile : g++ -std=c++14 -Wl, --stack=0x10000000 -o code.cpp code.exe

## *Code*
- Quick Read For Integer
```c++
int Read() {
  int f(1), x(0);
  char ch(getchar());
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch > '/' && ch < ':') {
    x = (x << 3) + (x << 1) + (ch - '0');
    ch = getchar();
  }
  return f * x;
}
```

- Quick Print For Integer
```c++
void Print(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) {
    Print(x / 10);
  }
  putchar(x % 10 + 48);
}
```

- Runtime
```c++
#include <ctime>

cout << "Runtime:" << clock() / 1000.0 << "s\n";
```

- SegTree
```c++
pair<LL, LL> a[400001];

void Pushdown(LL p, LL l, LL r) {
  LL mid = (l + r) / 2;
  a[p * 2].first += (mid - l + 1) * a[p].second;
  a[p * 2 + 1].first += (r - mid) * a[p].second;
  a[p * 2].second += a[p].second;
  a[p * 2 + 1].second += a[p].second;
  a[p].second = 0;
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    a[p].first += (r - l + 1) * k, a[p].second += k;
    return;
  }
  Pushdown(p, l, r);
  LL mid = (l + r) / 2;
  if (mid >= _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  a[p].first = a[p * 2].first + a[p * 2 + 1].first;
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return a[p].first;
  }
  Pushdown(p, l, r);
  LL mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ans += Ask(p * 2, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Ask(p * 2 + 1, mid + 1, r, _l, _r);
  }
  return ans;
}
```

- Treap
```c++
template <class T, int kMaxN>  // You SHOULD call the function Init() before using the treap.
class Treap {
 private:
  struct V {
    int s, k, l, r;
    T d;
  } v[kMaxN];
  int n, m, s;
  T mx, mn;
  void Update(int &p) {
    v[p].s = v[v[p].l].s + v[v[p].r].s + (p != 0);
  }
  void Left(int &p) {
    int q = v[p].r;
    v[p].r = v[q].l, v[q].l = p;
    Update(p), Update(q);
    p = q;
  }
  void Right(int &p) {
    int q = v[p].l;
    v[p].l = v[q].r, v[q].r = p;
    Update(p), Update(q);
    p = q;
  }
  void Rebalance(int &p) {
    if (v[p].l && v[v[p].l].k < v[p].k) {
      Right(p);
    } else if (v[p].r && v[v[p].r].k < v[p].k) {
      Left(p);
    }
  }
  void Insert(int &p, T x) {
    if (!p) {
      v[p = ++m].d = x, v[p].k = rand();
    } else {
      Insert(x < v[p].d ? v[p].l : v[p].r, x);
    }
    Update(p), Rebalance(p);
  }
  T Replace(int &p) {
    T c = v[p].d;
    if (!v[p].r) {
      p = v[p].l;
    } else {
      c = Replace(v[p].r);
      Update(p);
    }
    return c;
  }
  void Delete(int &p, T x) {
    if (v[p].d == x) {
      if (!v[p].l || !v[p].r) {
        p = v[p].l + v[p].r;
      } else {
        v[p].d = Replace(v[p].l);
      }
    } else {
      Delete(x < v[p].d ? v[p].l : v[p].r, x);
    }
    Update(p);
  }
  int FindRank(int &p, T x) {
    if (!p) {
      return 0;
    }
    return v[p].d < x ? FindRank(v[p].r, x) + v[v[p].l].s + 1 : FindRank(v[p].l, x);
  }
  T FindVal(int &p, int x) {
    if (v[v[p].l].s + 1 == x) {
      return v[p].d;
    }
    return v[v[p].l].s < x ? FindVal(v[p].r, x - v[v[p].l].s - 1) : FindVal(v[p].l, x);
  }
  T FindLast(int &p, T x) {
    if (!p) {
      return mn;
    }
    return v[p].d < x ? max(v[p].d, FindLast(v[p].r, x)) : FindLast(v[p].l, x);
  }
  T FindNext(int &p, T x) {
    if (!p) {
      return mx;
    }
    return x < v[p].d ? min(v[p].d, FindNext(v[p].l, x)) : FindNext(v[p].r, x);
  }

 public:
  const T operator[](int x) { return FindVal(s, x); }
  void Init(T minv, T maxv) { srand(time(0)), mn = minv, mx = maxv; }
  void Insert(T x) { Insert(s, x); }
  void Delete(T x) { Delete(s, x); }
  int FindRank(T x) { return FindRank(s, x) + 1; }
  T FindLast(T x) { return FindLast(s, x); }
  T FindNext(T x) { return FindNext(s, x); }
  bool Empty() { return !n; }
  int Size() { return n; }
};
```

- Splay
```c++
template <class T, int kMaxN>  // Run The Function Init() Before Using It!
class Splay {
 private:
  struct V {
    T v;
    int d, c, s[2];
  } v[kMaxN];
  int m, s;
  T kMin, kMax;
  vector<bool> l;
  void Update(int p) {
    v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p != 0) * v[p].d;
  }
  void Turn(int &p, bool b) {
    int q = v[p].s[b];
    v[p].s[b] = v[q].s[!b], v[q].s[!b] = p;
    Update(p), Update(q);
    p = q;
  }
  void Rebalance(int &p, T x) {
    if (v[p].v != x) {
      l.push_back(v[p].v < x);
      Rebalance(v[p].s[v[p].v < x], x);
      Turn(p, l.back());
      l.pop_back();
    }
  }
  void Insert(int &p, T x) {
    if (!p || !(v[p].v < x) && !(x < v[p].v)) {
      !p && (p = ++m);
      v[p].v = x, v[p].d++;
      Rebalance(s, v[p].v);
    } else {
      Insert(v[p].s[v[p].v < x], x);
    }
    Update(p);
  }
  int Replace(int &p) {
    int t = p;
    if (!v[p].s[1]) {
      p = v[p].s[0];
    } else {
      t = Replace(v[p].s[1]);
      Update(p);
    }
    return t;
  }
  void Delete(int &p, T x) {
    if (!(v[p].v < x) && !(x < v[p].v)) {
      if (!--v[p].d) {
        if (!v[p].s[0] || !v[p].s[1]) {
          p = v[p].s[0] + v[p].s[1];
        } else {
          int t = Replace(v[p].s[0]);
          v[p].v = v[t].v, v[p].d = v[t].d;
        }
      } else {
        Rebalance(s, v[p].v);
      }
    } else {
      Delete(v[p].s[v[p].v < x], x);
    }
    Update(p);
  }
  int FindRank(int p, T x) {
    if (!(v[p].v < x) && !(x < v[p].v)) {
      return v[v[p].s[0]].c + 1;
    }
    return FindRank(v[p].s[v[p].v < x], x) + (v[p].v < x) * (v[v[p].s[0]].c + v[p].d);
  }
  T FindVal(int p, int x) {
    if (v[v[p].s[0]].c < x && !(v[v[p].s[0]].c + v[p].d < x)) {
      Rebalance(s, v[p].v);
      return v[p].v;
    }
    return FindVal(v[p].s[v[v[p].s[0]].c + v[p].d < x], x - (v[v[p].s[0]].c + v[p].d < x) * (v[v[p].s[0]].c + v[p].d));
  }
  T FindPast(int p, T x) {
    if (!p) {
      return kMin;
    }
    return v[p].v < x ? max(FindPast(v[p].s[1], x), v[p].v) : FindPast(v[p].s[0], x);
  }
  T FindNext(int p, T x) {
    if (!p) {
      return kMax;
    }
    return x < v[p].v ? min(FindNext(v[p].s[0], x), v[p].v) : FindNext(v[p].s[1], x);
  }

 public:
  T operator[](int x) { return FindVal(s, x); }
  int Size() { return m; }
  void Init(T mn, T mx) { kMin = mn, kMax = mx; }
  void Insert(int x) { Insert(s, x); }
  void Delete(int x) { Delete(s, x); }
  int FindRank(int x) {
    Rebalance(s, x);
    return FindRank(s, x);
  }
  T FindPast(T x) {
    T c = FindPast(s, x);
    return c;
    Rebalance(s, c);
  }
  T FindNext(T x) {
    T c = FindNext(s, x);
    return c;
    Rebalance(s, c);
  }
};
```

## *Last Update : 2022.10.13*
