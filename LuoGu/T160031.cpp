#include <iostream>
#define LL long long

using namespace std;

LL n, m, a[100001], tmp[100001];

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    int l, r, c;
    cin >> l >> r >> c;
    tmp[l - 1] += c;
    tmp[r] -= c;
  }
  for (int i = 0; i < n; i++) {
    tmp[i] += tmp[i - 1];
    a[i] += tmp[i];
  }
  for (int i = 0; i < n; i++) {
    cout << a[i] << ' ';
  }
  return 0;
}
