#include <iostream>
#define LL long long

using namespace std;

int n, m;
pair<int, int> d[400001];

int main() {
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    Add(1, 1, n, i, i, x);
  }
  for (int i = 1, o, x, y, k; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      cin >> k;
      Add(1, 1, n, x, y, k);
    } else if (o == 2) {
      ;
    } else {
      ;
    }
  }
  return 0;
}
