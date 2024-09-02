#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

int t;
LL k, x, y;
bool odd, even;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    odd = even = 0;
    cin >> k >> x >> y;
    x > y ? swap(x, y) : void();
    LL z = y - x;
    x = (k + x - 1) / x;
    k %= y * 2, z %= y * 2;
    !k && (k = y * 2);
    if (k >= 1 && k <= y) {
      odd = 1;
    } else {
      even = 1;
    }
    if (z) {
      if (odd) {
        if (z < y) {
          even = (y - k) / z < x;
        } else {
          z = y * 2 - z;
          even = (k + z - 1) / z <= x;
        }
      } else if (even) {
        if (z < y) {
          odd = (y * 2 - k) / z < x;
        } else {
          z = y * 2 - z;
          odd = (k - y + z - 1) / z <= x;
        }
      }
    }
    cout << (odd ? "Yes\n" : "No\n");
    cout << (even ? "Yes\n" : "No\n");
  }
  return 0;
}
