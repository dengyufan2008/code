#include <iostream>
#define LL long long

using namespace std;

int n;
bool b[101][101];

int main() {
  cin >> n;
  for (int i = 1, j; i <= n; i++) {
    for (cin >> j; j; cin >> j) {
      b[i][j] = 1;
    }
  }
  
  return 0;
}
