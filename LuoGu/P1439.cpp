#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

int n, tmp[100001], p[100001], f[100001], l[100001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> tmp[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    p[i] = tmp[p[i]];
  }
  for (int i = 1; i <= n; i++) {
    int c = lower_bound(l, l + f[i - 1], p[i]) - l;
    f[i] = c + 1;
    l[c] = p[i];
  }
  cout << f[n] << endl;
  return 0;
}
