#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 101;
int n, a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, p = 0; i <= n; i++) {
    cin >> x;
    if (p < x) {
      for (; p < x; a[++p] = 1) {
      }
    } else {
      a[x]++, p = x;
    }
    for (int j = 1; j <= x; j++) {
      cout << a[j];
    }
    cout << " \n"[i == n];
  }
  return 0;
}
