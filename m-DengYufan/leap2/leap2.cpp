#include <iostream>
#define LL long long

using namespace std;

const int kMove[8][2] = {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}};
struct E {
  int f, px, py;
} e[366][366];
int n, a[366][366];

int main() {
  // freopen("leap2.in", "r", stdin);
  // freopen("leap2.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      e[i][j].f = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        
      }
    }
  }
  return 0;
}
