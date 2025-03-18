#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1, kMaxM = 7, kMod = 998244353;
int n, m, q;
string s;

struct A {
  LL a[kMaxM][kMaxM];
} a[kMaxM];

class Seg1 {
  A v[kMaxN << 2];

  void Pushup(int p) {
    for (int i = 0; i < kMaxM; i++) {
      for (int j = 0; j < kMaxM; j++) {
        v[p].a[i][j] = 0;
        for (int k = 0; k < kMaxM; k++) {
          v[p].a[i][j] = (v[p].a[i][j] + v[p << 1].a[i][k] * v[p << 1 | 1].a[k][j]) % kMod;
        }
      }
    }
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = a[s[l] - 'a' + 1];
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    Pushup(p);
  }

  void Change(int p, int l, int r, int x, int y) {
    if (l == r) {
      v[p] = a[y];
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    Pushup(p);
  }

 public:
  void Init() { Init(1, 1, n); }
  void Change(int x, char c) { Change(1, 1, n, x, c - 'a' + 1); }
  LL Ask() {
    LL ans = 0;
    for (int i = 0; i < kMaxM; i++) {
      ans = (ans + v[1].a[0][i]) % kMod;
    }
    return ans;
  }
} seg1;

class Seg2 {
  struct V {
    int l[kMaxM], r[kMaxM];
    A a;
  } v[kMaxN << 2];

  void Tag(int p, int x, int y) {
    v[p] = v[0], v[p].l[y] = v[p].r[y] = x;
    v[p].a.a[y][y] = 1;
  }

  void Pushup(int p) {
    for (int i = 1; i < kMaxM; i++) {
      v[p].l[i] = v[p << 1].l[i] ? v[p << 1].l[i] : v[p << 1 | 1].l[i];
      v[p].r[i] = v[p << 1 | 1].r[i] ? v[p << 1 | 1].r[i] : v[p << 1].r[i];
    }
    for (int i = 1; i < kMaxM; i++) {
      for (int j = 1; j < kMaxM; j++) {
        v[p].a.a[i][j] = 0;
        if (v[p << 1].l[i] && v[p << 1 | 1].r[j]) {
          for (int k = 1; k < kMaxM; k++) {
            for (int l = 1; l < kMaxM; l++) {
              if ((!v[p << 1].r[l] || v[p << 1].r[l] <= v[p << 1].r[k]) &&
                  (!v[p << 1 | 1].l[k] || v[p << 1 | 1].l[l] <= v[p << 1 | 1].l[k])) {
                v[p].a.a[i][j] = (v[p].a.a[i][j] + v[p << 1].a.a[i][k] * v[p << 1 | 1].a.a[l][j]) % kMod;
              }
            }
          }
        } else if (!v[p << 1 | 1].r[j]) {
          v[p].a.a[i][j] = v[p << 1].a.a[i][j];
        } else {
          v[p].a.a[i][j] = v[p << 1 | 1].a.a[i][j];
        }
      }
    }
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      return Tag(p, l, s[l] - 'a' + 1);
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    Pushup(p);
  }

  void Change(int p, int l, int r, int x, int y) {
    if (l == r) {
      return Tag(p, l, y);
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    Pushup(p);
  }

 public:
  void Init() { Init(1, 1, n); }
  void Change(int x, char c) { Change(1, 1, n, x, c - 'a' + 1); }
  LL Ask() {
    LL ans = 1;
    for (int i = 1; i < kMaxM; i++) {
      for (int j = 1; j < kMaxM; j++) {
        ans = (ans + v[1].a.a[i][j]) % kMod;
      }
    }
    return ans;
  }
} seg2;

void Init() {
  for (int i = 1; i < kMaxM; i++) {
    for (int j = 0; j < kMaxM; j++) {
      a[i].a[j][i] = a[i].a[j][j] = 1;
    }
  }
  seg1.Init(), seg2.Init();
}

void Change(int x, char c) {
  seg1.Change(x, c), seg2.Change(x, c);
}

LL Ask() {
  return (seg1.Ask() - seg2.Ask() + kMod) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q >> s, s = '~' + s;
  Init(), cout << Ask() << '\n';
  for (int i = 1, x; i <= q; i++) {
    static char c;
    cin >> x >> c, Change(x, c);
    cout << Ask() << '\n';
  }
  return 0;
}
