#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1, kMaxM = 3, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int n, m, d, a[kMaxN];
LL ans;

struct Matrix {
  LL w[kMaxM][kMaxM];
};

void Mul(Matrix &ans, Matrix &x, Matrix &y) {
  for (int i = 0; i < kMaxM; i++) {
    for (int j = i; j < kMaxM; j++) {
      ans.w[i][j] = 0;
      for (int k = i; k <= j; k++) {
        ans.w[i][j] += x.w[i][k] * y.w[k][j];
      }
      ans.w[i][j] %= kMod;
    }
  }
}

const Matrix kTrans[3][3] = {
    {{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}},
     {{{0, 1, 0}, {0, 1, 0}, {0, 0, 1}}},
     {{{1, 1, 0}, {0, 2, 0}, {0, 0, 2}}}},
    {{{{1, 0, 0}, {0, 1, 1}, {0, 0, 0}}},
     {{{0, 1, 0}, {0, 1, 1}, {0, 0, 0}}},
     {{{1, 1, 0}, {0, 2, 2}, {0, 0, 0}}}},
    {{{{2, 0, 0}, {0, 2, 1}, {0, 0, 1}}},
     {{{0, 2, 0}, {0, 2, 1}, {0, 0, 1}}},
     {{{2, 2, 0}, {0, 4, 2}, {0, 0, 2}}}},
};

class Seg {
  Matrix v[kMaxN << 1];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = kTrans[a[l]][a[d + l]];
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    Mul(v[p], v[p << 1], v[p << 1 | 1]);
  }

  void Update(int p, int l, int r, int x) {
    if (l == r) {
      v[p] = kTrans[a[l]][a[d + l]];
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Update(p << 1, l, mid, x);
    } else {
      Update(p << 1 | 1, mid + 1, r, x);
    }
    Mul(v[p], v[p << 1], v[p << 1 | 1]);
  }

 public:
  void Init() { Init(1, 1, d - 1); }
  void Update(int x) { Update(1, 1, d - 1, x > d ? x - d : x); }
  LL Ask() { return v[1].w[0][2]; }
} seg;

int U(char c) { return (c == '1') + (c == '?') * 2; }

void Init() {
  for (int i = 1; i <= n; i++) {
    a[i] == 2 && (ans = ans * 2 % kMod);
  }
  a[d] == 2 && (ans = ans * kInv2 % kMod);
  seg.Init();
}

void Change(int x, int y) {
  if (x == d) {
    a[x] = y;
  } else {
    a[x] == 2 && (ans = ans * kInv2 % kMod);
    a[x] = y;
    a[x] == 2 && (ans = ans * 2 % kMod);
    seg.Update(x);
  }
}

LL Calc() {
  if (a[d] == 0) {
    return seg.Ask();
  } else if (a[d] == 1) {
    return ans;
  } else {
    return (seg.Ask() + ans) % kMod;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c, a[i] = U(c);
  }
  d = n + 1 >> 1, ans = 1, Init();
  cout << Calc() << '\n';
  for (int i = 1, x; i <= m; i++) {
    static char c;
    cin >> x >> c, Change(x, U(c));
    cout << Calc() << '\n';
  }
  return 0;
}
