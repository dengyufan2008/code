#include <iostream>
#define LL long long

using namespace std;

int n;
bool b[101][101];

int main() {
  cin >> n;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x;
    while (x--) {
      cin >> y;
      b[i][y] = 1;
    }
  }
  
  return 0;
}
