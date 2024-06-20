#include <fstream>
#define LL long long

using namespace std;

ifstream cin("p.in");
ofstream cout("p.out");

const int kMaxN = 1e6 + 1, kMaxL = 20;
struct H {
  int pw;
  LL fact, _fact;
} h[kMaxN];
int t, p, n, a[4], d[4][4];

void Add(LL &x, LL y) { x = (x + y) % p; }

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

class P {
 public:
  LL f[4];

  P() {
    f[0] = f[1] = f[2] = f[3] = 0;
  }

  P(LL f0, LL f1, LL f2, LL f3) {
    f[0] = f0, f[1] = f1, f[2] = f2, f[3] = f3;
  }

  P operator+(P x) {
    P ans;
    for (int i = 0; i < 4; i++) {
      ans.f[i] = (f[i] + x.f[i]) % p;
    }
    return ans;
  }

  P operator<<(LL x) {
    P ans;
    for (int i = 0; i < 4; i++) {
      ans.f[i + x & 3] = f[i];
    }
    return ans;
  }

  P operator*(LL x) {
    P ans;
    for (int i = 0; i < 4; i++) {
      ans.f[i] = f[i] * x % p;
    }
    return ans;
  }

  P operator*(P x) {
    P ans;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        Add(ans.f[i + j & 3], f[i] * x.f[j]);
      }
    }
    return ans;
  }

  P operator^(LL y) {
    P x = *this, ans(1, 0, 0, 0);
    for (LL i = 1; i <= y; i <<= 1) {
      if (i & y) {
        ans = ans * x;
      }
      x = x * x;
    }
    return ans;
  }
} ans;

void CalcFact() {
  int _r;
  LL pw[kMaxL], s[kMaxN], t[kMaxN];
  pw[0] = 1;
  for (int &i = _r = 1; i < kMaxL; i++) {
    pw[i] = pw[i - 1] * p;
    if (pw[i] >= kMaxN) {
      break;
    }
  }
  h[0] = {0, 1, 1};
  for (int i = 1; i < kMaxN; i++) {
    int l = 0, r = _r;
    while (l <= r) {
      int mid = l + r >> 1;
      if (mid <= _r && !(i % pw[mid])) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    h[i] = h[i - 1], h[i].pw += r;
    h[i].fact = h[i].fact * (i / pw[r]) % p;
  }
  s[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    s[i] = s[i - 1] * h[i].fact % p;
  }
  t[kMaxN - 1] = Pow(s[kMaxN - 1], p - 2);
  for (int i = kMaxN - 1; i > 0; i--) {
    t[i - 1] = t[i] * h[i].fact % p;
  }
  for (int i = 1; i < kMaxN; i++) {
    h[i]._fact = s[i - 1] * t[i] % p;
  }
}

void CalcAns(int o) {
  LL b[4] = {};
  P w(o, 0, 0, 0);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      b[j] += d[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    w.f[0] = w.f[0] * h[a[i]].fact % p;
    for (int j = 0; j < 4; j++) {
      w.f[0] = w.f[0] * h[d[i][j]]._fact % p;
    }
  }
  int q = (d[1][3] + d[3][1]) + 3 * (d[1][1] + d[3][3]) & 3;
  q = q + 2 * (d[1][2] + d[2][1] + d[2][3] + d[3][2]) & 3;
  w = w << q;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      P p(1, 0, 0, 0);
      p.f[i + j & 3] += 1;
      w = w * (p ^ b[i] * b[j]);
    }
  }
  for (int i = 0; i < 4; i++) {
    P p(1, 0, 0, 0);
    p.f[i + i & 3] += 1;
    w = w * (p ^ b[i] * (b[i] - 1) / 2);
  }
  ans = ans + w;
}

void S(int x, int b0, int b1, int b2, int b3, int o) {
  if (x == 4) {
    CalcAns(o);
    return;
  }
  for (int &i = d[x][0] = 0; i <= b0 && i <= a[x]; i++) {
    for (int &j = d[x][1] = 0; j <= b1 && i + j <= a[x]; j++) {
      for (int &k = d[x][2] = 0; k <= b2 && i + j + k <= a[x]; k++) {
        int &l = d[x][3] = a[x] - i - j - k;
        if (l <= b3 && h[i].pw + h[j].pw + h[k].pw + h[l].pw == h[a[x]].pw) {
          S(x + 1, b0 - i, b1 - j, b2 - k, b3 - l, o);
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> p;
  CalcFact();
  while (t--) {
    cin >> n >> a[0] >> a[1] >> a[2] >> a[3];
    ans = P();
    S(0, 0, 1, n, 1, 1);
    S(0, n, 1, 0, 1, 1);
    S(0, 0, 1, 0, 1, p - 1);
    int q = p - 1 - 1LL * n * (n + 3) / 2 % (p - 1);
    cout << (ans.f[0] - ans.f[2] + p) * Pow(2, q) % p << '\n';
  }
  return 0;
}
