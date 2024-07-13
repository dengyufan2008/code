#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, x, a[100001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> x;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] != x) {
      cout << a[i] << " ";
    }
  }
  return 0;
}
