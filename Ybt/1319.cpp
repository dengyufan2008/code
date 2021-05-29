#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, tot, t[1001], l[1001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> t[i];
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return t[i] < t[j];
  });
  for (int i = 1; i <= n; i++) {
    tot += t[l[i]] * (n - i);
    cout << l[i] << " ";
  }
  cout << endl << fixed << setprecision(2) << (double)tot / (double)n << endl;
  return 0;
}
