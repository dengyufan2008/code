// 同 20240506 好题分享 T3
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("m.in");
ofstream cout("m.out");

LL n, x, y, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> x >> y;
  if (n & 1) {
    for (int i = 0; i < 20 && 1 << i <= x && 1 << i <= y; i++) {
      if (y >> i & 1) {
        for (int j = y; j >= 1 << i; j = j - 1 & y) {
          if (j >> i & 1) {
            LL a = x - (1 << i), b = n * j - (1 << i);
            ans ^= ((a & b) == a) << i;
          }
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
