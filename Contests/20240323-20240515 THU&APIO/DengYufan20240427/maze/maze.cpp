#include <fstream>
#define LL long long

using namespace std;

ifstream cin("maze.in");
ofstream cout("maze.out");

const int kMod = 998244353;
int t;
LL n, m, ans;

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

int PopCount(LL x) {
  const static unsigned LL w = -1, w0 = w / 3, w1 = w / 5;
  const static unsigned LL w2 = w / 17, w3 = w / 257;
  const static unsigned LL w4 = w / 65537, w5 = w / 4294967297;
  x = (x & w0) + (x >> 1 & w0);
  x = (x & w1) + (x >> 2 & w1);
  x = (x & w2) + (x >> 4 & w2);
  x = (x & w3) + (x >> 8 & w3);
  x = (x & w4) + (x >> 16 & w4);
  x = (x & w5) + (x >> 32 & w5);
  return x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    ans = 0, n--, m--;
    for (LL i = max(n - 60, 0LL); i <= n; i++) {
      ans = max(ans, i + m + 1 - PopCount(i ^ m ^ (i + m)));
    }
    cout << Pow(2, ans % (kMod - 1)) << '\n';
  }
  return 0;
}
