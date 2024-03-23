#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

constexpr int kMaxN = 1e1 + 1, kMaxL = 6;  // 1e5 + 1, 1300
class V {
 private:
  int c;
  bool w[kMaxL];

 public:
  bool E() { return !c; }

  bool W(int x) { return w[x]; }

  void R(int x) {
    if (w[x]) {
      c--, w[x] = 0;
    } else {
      c++, w[x] = 1;
    }
  }
} v[(kMaxN + kMaxL - 1) / kMaxL];
int n, m, t, a[kMaxN], d[kMaxN];

int Block(int x) { return x / t; }

int Num(int x) { return x - x / t * t; }

int Begin(int x) { return x / t * t; }

int End(int x) { return x / t * t + t - 1; }

void Input() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    d[i] = i;
  }
  t = sqrt(n * log2(n));
}

void Init() {
  bool c[kMaxN] = {};
  for (int i = n - 1; i >= 0; i--) {
    bool w = 0;
    for (int j = a[i]; j >= 1; j -= j & -j) {
      w ^= c[j];
    }
    w ? v[Block(i)].R(Num(i)) : (void)0;
    for (int j = a[i]; j <= n; j += j & -j) {
      c[j] ^= 1;
    }
  }
  for (int i = 0, j; (j = min(i + t, n)) && i < n; i = j) {
    sort(d + i, d + j, [](int x, int y) { return a[x] < a[y]; });
    for (int k = i + 1; k < j; k++) {
      if (v[Block(d[k - 1])].W(Num(d[k - 1]))) {
        v[Block(d[k])].R(Num(d[k]));
      }
    }
  }
}

int Find(int x, int y) {
  int l = x / t * t, r = l + t - 1;
  for (; r >= l && !~d[r]; r--) {
  }
  while (l <= r) {
    int mid = l + r >> 1;
    if (a[d[mid]] >= y) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

void Reverse(int l, int r, int x, int y) {
  if (l / t == r / t) {
    for (int i = Find(l / t, x), j = Find(l / t, y + 1); i < j; i++) {
      if (d[i] >= l && d[i] <= r) {
        v[Block(d[i])].R(Num(d[i]));
        if (i < End(l)) {
          v[Block(d[i + 1])].R(Num(d[i + 1]));
        }
      }
    }
  } else {
    for (int i = Find(l / t, x), j = Find(l / t, y + 1); i < j; i++) {
      if (i >= l && i <= End(l)) {
        v[Block(d[i])].R(Num(d[i]));
        if (i < End(l)) {
          v[Block(d[i + 1])].R(Num(d[i + 1]));
        }
      }
    }
    for (int i = Block(l) + 1; i < Block(r); i++) {
      v[i].R(Num(d[Find(i, x)])), v[i].R(Num(d[Find(i, y + 1)]));
    }
    for (int i = Find(r / t, x), j = Find(r / t, y + 1); i < j; i++) {
      if (i >= Begin(r) && i <= r) {
        v[Block(d[i])].R(Num(d[i]));
        if (i < End(r)) {
          v[Block(d[i + 1])].R(Num(d[i + 1]));
        }
      }
    }
  }
}

void Remove(int x, int y) {
  int p = Find(x / t, y) + 1;
  for (; p <= End(x) && ~d[p]; p++) {
    d[p - 1] = d[p];
  }
  d[p - 1] = -1;
}

void Modify(int x, int y) {
  int p = Find(x / t, y);
  for (int i = End(x); i > p; i--) {
    d[i] = d[i - 1];
  }
  d[p] = x;
}

void ReCalc(int x, int y) {
  int p = Find(Block(x), y);
  if (p == Begin(p)) {
    if (v[Block(d[p])].W(Num(d[p]))) {
      v[Block(d[p])].R(Num(d[p]));
    }
  } else {
    if (v[Block(d[p])].W(Num(d[p])) ^ v[Block(d[p - 1])].W(d[p - 1])) {
      v[Block(d[p])].R(Num(d[p]));
      if (p < End(p)) {
        v[Block(d[p + 1])].R(Num(d[p + 1]));
      }
    }
  }
  for (int i = x + 1; i <= End(x); i++) {
    if (a[i] < y) {
      v[Block(x)].R(Num(x));
    }
  }
  for (int i = Block(End(x) + 1); i <= Block(n - 1); i++) {
    int p = Find(i, y);
    if (v[i].W(d[p])) {
      v[Block(x)].R(Num(x));
    }
  }
}

int Length() {
  int p = Block(n - 1), ans = 0;
  for (; p >= 0 && v[p].E(); p--) {
    ans++;
  }
  ans *= t;
  for (p = End(p); v[Block(p)].W(Num(p)); p--) {
    ans++;
  }
  return ans;
}

void Calc() {
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    x--, y--;
    Reverse(min(x, y), max(x, y), min(a[x], a[y]) + 1, max(a[x], a[y]) - 1);
    Remove(x, a[x]), Remove(y, a[y]);
    swap(a[x], a[y]);
    Modify(x, a[x]), Modify(y, a[y]);
    ReCalc(x, a[x]), ReCalc(y, a[y]);
    cout << Length() << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input();
  Init();
  Calc();
  return 0;
}
