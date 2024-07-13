#include <iostream>
#define LL long long

using namespace std;

int n, mx1, mx2, a[200001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] > a[mx1]) {
      mx2 = mx1, mx1 = i;
    } else if (a[i] > a[mx2]) {
      mx2 = i;
    }
  }
  cout << mx2 << endl;
  return 0;
}
