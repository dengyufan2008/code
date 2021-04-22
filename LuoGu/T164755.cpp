#include <bits/stdc++.h>

using namespace std;

long long int n, t, a[100001], x, i, step;

int Find(int start, int step) {
  if (a[start] == x) {
    return start;
  }
  if (!step) {
    return 0;
  }
  if (a[start + (1 << step)] < x) {
    return Find(start + (1 << step), step - 1);
  } else {
    return Find(start, step - 1);
  }
}

int main() {
  cin >> n >> t;
  for (step = 20; (1 << step) > n; step--) {
    ;
  }
  for (i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (i = 1; i <= t; i++) {
    cin >> x;
    cout << Find(0, step) << endl;
  }
  return 0;
}
