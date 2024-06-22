#include <fstream>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

class TheCowDivOne {
#define LL long long

  static const int kMaxN = 1001, kMod = 1e9 + 7;
  int n, k;
  LL inv[kMaxN];

  int Gcd(int x, int y) {
    return y ? Gcd(y, x % y) : x;
  }

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

  LL Calc(int x) {
    int y = x;
    LL ans = x;
    for (int i = 2; i * i <= y; i++) {
      if (!(y % i)) {
        ans = ans / i * (i - 1);
        while (!(y % i)) {
          y /= i;
        }
      }
    }
    if (y > 1) {
      ans = ans / y * (y - 1);
    }
    for (int i = (n - k) / x + 1; i * x <= n; i++) {
      ans = ans * i % kMod;
    }
    for (int i = 1; i * x <= k; i++) {
      ans = ans * inv[i] % kMod;
    }
    return k / x & 1 ? (kMod - ans) % kMod : ans;
  }

 public:
  int find(int N, int K) {
    n = N, k = K, inv[1] = 1;
    for (int i = 2; i <= k; i++) {
      inv[i] = inv[kMod % i] * (kMod - kMod / i) % kMod;
    }
    int m = Gcd(n, k), ans = 0;
    for (int i = 1; i * i <= m; i++) {
      if (!(m % i)) {
        ans = (ans + Calc(i)) % kMod;
        if (i * i < m) {
          ans = (ans + Calc(m / i)) % kMod;
        }
      }
    }
    ans = ans * Pow(n) % kMod;
    return k & 1 ? (kMod - ans) % kMod : ans;
  }

#undef LL
};

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int n, k;
  cin >> n >> k;
  cout << TheCowDivOne().find(n, k) << '\n';
  return 0;
}
