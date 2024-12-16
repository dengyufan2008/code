#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

int n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n;) {
    if (i == n || i + 1 == n) {
      cout << 1 << '\n';
      return 0;
    }
    i = (i << 1 | 1) + (i & 1);
  }
  cout << 0 << '\n';
  return 0;
}
