#include <fstream>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("dice.in");
ofstream cout("dice.out");

const LLL kMaxP = 61, kMaxN = 2e18, kInf = 4e36;
LLL n, a, b, ans;

LLL Read() {
  static LL x;
  cin >> x;
  return x;
}

LLL Pow(LLL x, LLL y) {
  LLL ans = 1;
  for (LLL i = 1; i <= y; i++) {
    if (ans * x > kMaxN) {
      return kMaxN;
    }
    ans *= x;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  n = Read(), a = Read(), b = Read(), ans = kInf;
  for (LLL i = 1; i < kMaxP; i++) {
    for (LLL j = 0; j < kMaxP; j++) {
      LLL l = 2, r = n;
      while (l <= r) {
        LLL mid = l + r >> 1;
        if (Pow(mid, i) * Pow(mid + 1, j) <= n) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = min(ans, (i + j) * (a + l * b) - i * b);
    }
  }
  cout << (LL)ans << '\n';
  return 0;
}
