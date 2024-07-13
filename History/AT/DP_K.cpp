#include <iostream>
#define LL long long

using namespace std;

int n, k, a[101];
bool f[100001];

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      f[i] |= (i >= a[j] && !f[i - a[j]]);
    }
  }
  cout << (f[k] ? "First" : "Second") << endl;
  return 0;
}
