#include <fstream>

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

int t, a, b, c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> a >> b >> c;
    while ((a & 1 ^ 1) && (b & 1 ^ 1) && (c & 1 ^ 1)) {
      a >>= 1, b >>= 1, c >>= 1;
    }
    cout << (a & b & c & 1 ? "NO\n" : "YES\n");
  }
  return 0;
}
