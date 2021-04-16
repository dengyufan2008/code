#include <bits/stdc++.h>
#define LL long long

using namespace std;

int x, n, h, t, a[2001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> x;
  while (x--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    h = 1, t = n;
    while (h <= t) {
      for (; a[h] % 2; h++) {
      }
      for (; !(a[t] % 2); t--) {
      }
      if(h <= t) {
        swap(a[h], a[t]);
      }
      h++, t--;
    }
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " ";
    }
    cout << endl;
  }
  return 0;
}
