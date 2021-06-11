#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, k, n, a[101];
bool b[101];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = n - 1; i; i--) {
      for (int j = i; j < n; j++) {
        if (a[j] > a[j + 1] && !b[j]) {
          swap(a[j], a[j + 1]);
          b[j] = true;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " ";
    }
    cout << endl;
    fill(&b[0], &b[100] + 1, false);
  }
  return 0;
}
