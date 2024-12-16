#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMaxM = 3e5 + 1;
int n;
LL s, ans;

class Bit {
  LL d[kMaxM];

 public:
  void Add(int x, int y) {
    for (int i = x; i < kMaxM; i += i & -i) {
      d[i] += y;
    }
  }

  LL Ask(int x) {
    LL ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += d[i];
    }
    return ans;
  }

  void Add(int l, int r, int x) {
    Add(l, x), Add(r + 1, -x);
  }

  LL Ask(int l, int r) {
    return Ask(r) - Ask(l - 1);
  }
} bit1, bit2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    // i % x
    s += x, bit1.Add(x, 1), ans += s;
    for (int j = x; j < kMaxM; j += x) {
      ans -= 1LL * j * bit1.Ask(j, min(j + x - 1, kMaxM - 1));
    }
    // x % i
    for (int j = x; j < kMaxM; j += x) {
      bit2.Add(j, min(j + x - 1, kMaxM - 1), j);
    }
    ans += 1LL * i * x - bit2.Ask(x);
    cout << ans << " \n"[i == n];
  }
  return 0;
}
