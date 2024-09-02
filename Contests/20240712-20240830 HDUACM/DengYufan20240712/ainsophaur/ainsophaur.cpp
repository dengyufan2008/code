#include <fstream>
#define LL long long

using namespace std;

ifstream cin("ainsophaur.in");
ofstream cout("ainsophaur.out");

const int kMaxM = 2001, kMod = 998244353;
int n, m;
LL fact[kMaxM], _fact[kMaxM];
class I {
 public:
  LL r, i;
  I operator+(I x) {
    return {(r + x.r) % kMod, (i + x.i) % kMod};
  }
  I operator*(LL x) {
    return {r * x % kMod, i * x % kMod};
  }
  I operator*(I x) {
    return {(r * x.r - i * x.i) % kMod, (r * x.i + i * x.r) % kMod};
  }
} w;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

I Pow(I x, int y) {
  I ans = {1, 0};
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x;
    }
    x = x * x;
  }
  return ans;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m, n <<= 2;
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= m; j++) {
      LL t = C(m, i) * C(m, j) % kMod;
      w = w + Pow({i + j - m, j - i}, n) * t;
    }
  }
  w.r = w.r * Pow(4, kMod - 1 - m) % kMod;
  cout << (w.r + kMod) % kMod << '\n';
  return 0;
}
