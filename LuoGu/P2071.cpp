#include <iostream>
#define LL long long

using namespace std;

int n, k, ans, b[4001], v[4001];
bool l[4001][4001];

bool T(int x) {
  if (b[x] != k) {
    b[x] = k;
    for (int i = 1; i <= n * 2; i++) {
      if (l[x][i] && (!v[i] || T(v[i]))) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n;
  for (int i = 1, x, y; i <= n * 2; i++) {
    cin >> x >> y;
    l[i][x] = l[i][y] = l[i][x + n] = l[i][y + n] = 1;
  }
  for (int i = 1; i <= n * 2; i++) {
    k++, ans += T(i);
  }
  cout << ans;
  return 0;
}
