#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 1e5, kB = 318, kMod = 1e9 + 7;
int t, n, m;

class Blk {
  int _n, a[kMaxN], t[kB], w[kB][kB * 2];

  void ReBuild(int o) {
    int l = o * kB, r = min(l + kB, n);
    for (int i = 1; i < kB * 2; i++) {
      w[o][i] = -1;
    }
    for (int i = l; i < r; i++) {
      a[i] += t[o];
    }
    t[o] = 0;
    for (int i = r - 1; i >= l; i--) {
      if (abs(a[i]) + 1 < kB) {
        w[o][a[i] + kB] = i;
      }
    }
  }

 public:
  void Init() {
    _n = (n - 1) / kB + 1;
    for (int i = 0; i < n; i++) {
      a[i] = 0;
    }
    for (int i = 0; i < _n; i++) {
      t[i] = 0, w[i][kB] = i * kB;
      for (int j = 1; j < kB; j++) {
        w[i][j] = -1;
      }
      for (int j = kB + 1; j < kB * 2; j++) {
        w[i][j] = -1;
      }
    }
  }

  int Ask(int x) { return a[x] + t[x / kB]; }

  int Find(int x, int k) {
    int o = x / kB, _x = o * kB + kB;
    for (int i = x; i < min(_x, n); i++) {
      if (a[i] + t[o] == k) {
        return i;
      }
    }
    for (int i = o + 1; i < _n; i++) {
      int p = w[i][k - t[i] + kB];
      if (p != -1) {
        return p;
      }
    }
    return n;
  }

  void Add(int l, int r, int k) {
    int lo = l / kB, ro = r / kB;
    int _l = lo * kB + kB, _r = ro * kB;
    if (lo == ro) {
      for (int i = l; i <= r; i++) {
        a[i] += k;
      }
      return ReBuild(lo);
    }
    for (int i = l; i < _l; i++) {
      a[i] += k;
    }
    for (int i = _r; i <= r; i++) {
      a[i] += k;
    }
    ReBuild(lo), ReBuild(ro);
    for (int i = lo + 1; i < ro; i++) {
      t[i] += k;
      if (abs(t[i]) + 1 >= kB) {
        ReBuild(i);
      }
    }
  }
} blk;

class Calc {
  LL lst, ans;

 public:
  void Init() { lst = ans = 0; }

  void Add(int l, int k) {  // r = n
    ans += (n - l) * k, lst += k;
  }

  LL Ask() {
    return (ans + lst * (lst + 1) / 2) % kMod;
  }
} calc;

void AddSuf(int x, int k) {
  int p = min(blk.Find(x, 0), blk.Find(x, -k));
  if (p < n) {
    blk.Add(x, p, k), calc.Add(p + 1, k);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    blk.Init(), calc.Init();
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      AddSuf(x, 1), AddSuf(y, -1);
      cout << calc.Ask() << '\n';
    }
  }
  return 0;
}
