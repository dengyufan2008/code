#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 1e5 + 2, kMaxL = 17, kMod = 998244353;
struct V {
  int l, r, x, gcd;
};
struct E {
  int x, gcd;
  LL w;
};
int n, a[kMaxL][kMaxN], lg[kMaxN];
vector<V> v;
vector<E> e1, e2;

class Seg {
  struct V {
    LL w, wi;
  } v[kMaxN << 2];

  void Pushup(int p, int l, int r) {
    v[p].w = (v[p << 1].w + v[p << 1 | 1].w) % kMod;
    v[p].wi = v[p << 1].w * (r - l + 1 >> 1);
    v[p].wi = (v[p].wi + v[p << 1].wi + v[p << 1 | 1].wi) % kMod;
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p].w = !l, v[p].wi = 0;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    Pushup(p, l, r);
  }

  void Change(int p, int l, int r, int x, int w) {
    if (l == r) {
      v[p].w = w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, w);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, w);
    }
    Pushup(p, l, r);
  }

  LL Ask(int p, int l, int r, int x) {
    if (r <= x) {
      return v[p].w;
    }
    int mid = l + r >> 1;
    LL ans = Ask(p << 1, l, mid, x);
    if (mid < x) {
      ans = (ans + Ask(p << 1 | 1, mid + 1, r, x)) % kMod;
    }
    return ans;
  }

  V AskV(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      V x = AskV(p << 1, l, mid, _l, _r);
      V y = AskV(p << 1 | 1, mid + 1, r, _l, _r);
      return {(x.w + y.w) % kMod, (x.wi + y.wi + x.w * (_r - mid)) % kMod};
    } else if (mid >= _l) {
      return AskV(p << 1, l, mid, _l, _r);
    } else {
      return AskV(p << 1 | 1, mid + 1, r, _l, _r);
    }
  }

 public:
  void Init() { Init(1, 0, n); }
  void Change(int x, LL w) { Change(1, 0, n, x, w); }
  LL Ask(int l, int r) {
    return (Ask(1, 0, n, l - 1) * (r - l + 1) + AskV(1, 0, n, l, r).wi) % kMod;
  }
} seg;

int Gcd(int x, int y) {
  return y ? Gcd(y, x % y) : x;
}

int RangeGcd(int l, int r) {
  int t = lg[r - l + 1];
  return Gcd(a[t][l], a[t][r - (1 << t) + 1]);
}

void Calc() {
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = a[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        a[i][j] = Gcd(a[i][j], a[i - 1][j + (1 << i - 1)]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j >= 1;) {
      int l = 1, r = j, gcd = RangeGcd(j, i);
      while (l <= r) {
        int mid = l + r >> 1;
        if (RangeGcd(mid, i) != gcd) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      v.push_back({l, j, i, gcd}), j = r;
    }
  }
  sort(v.begin(), v.end(), [](V i, V j) {
    return i.gcd < j.gcd || i.gcd == j.gcd && i.x < j.x;
  });
  for (int i = 0, j = 0; i < v.size(); i = j) {
    seg.Init();
    for (; j < v.size() && v[i].gcd == v[j].gcd; j++) {
      LL w = seg.Ask(v[j].l, v[j].r);
      seg.Change(v[j].x, w), e1.push_back({v[j].x, v[i].gcd, w});
    }
  }
}

void CalcAns() {
  int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
  LL w1[kMaxN], w2[kMaxN];
  for (; i1 < e1.size() || i2 < e2.size(); i1 = j1, i2 = j2) {
    for (; j1 < e1.size() && e1[i1].gcd == e1[j1].gcd; j1++) {
    }
    for (; j2 < e2.size() && e2[i2].gcd == e2[j2].gcd; j2++) {
    }
    if (i1 < e1.size() && i2 < e2.size() && e1[i1].gcd == e2[i2].gcd) {
      w1[0] = e1[i1].w, w2[j2 - i2 - 1] = e2[j2 - 1].w;
      for (int k = i1 + 1; k < j1; k++) {
        w1[k - i1] = (w1[k - i1 - 1] + e1[k].w) % kMod;
      }
      for (int k = j2 - 2; k >= i2; k--) {
        w2[k - i2] = (w2[k - i2 + 1] + e2[k].w) % kMod;
      }
      for (int k1 = i1, k2 = i2; k1 < j1 || k2 < j2;) {
        if (k1 < j1 && k2 < j2 && e1[k1].x + 1 == e2[k2].x) {
          ;
        } else if (k1 < j1 && (k2 >= j2 || e1[k1].x + 1 < e2[k2].x)) {
          ;
        } else {
          ;
        }
      }
    } else if (i1 < e1.size() && (i2 >= e2.size() || e1[i1].gcd < e2[i2].gcd)) {
      ;
    } else {
      ;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[0][i];
  }
  Calc(), v.clear(), reverse(a[0] + 1, a[0] + n + 1);
  e1.swap(e2), Calc(), e1.swap(e2);
  for (E &i : e2) {
    i.x = n - i.x + 1;
  }
  sort(e1.begin(), e1.end(), [](E i, E j) {
    return i.gcd < j.gcd || i.gcd == j.gcd && i.x < j.x;
  });
  sort(e2.begin(), e2.end(), [](E i, E j) {
    return i.gcd < j.gcd || i.gcd == j.gcd && i.x < j.x;
  });
  CalcAns();
  return 0;
}
