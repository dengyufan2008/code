#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, a[100001];

int M(int l, int r) {
  if (l > r) {
    return 0;
  } else if (l == r) {
    return a[l];
  }
  int mn = 1e6, k = 0, p[100001] = {l - 1};
  for (int i = l; i <= r; i++) {
    mn = min(mn, a[i]);
  }
  for (int i = l; i <= r; i++) {
    a[i] -= mn;
    if (!a[i]) {
      p[++k] = i;
    }
  }
  p[++k] = r + 1;
  for (int i = 1; i <= k; i++) {
    mn += M(p[i - 1] + 1, p[i] - 1);
  }
  return mn;
}

int main() {
  freopen("poker.in", "r", stdin);
  freopen("poker.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cout << M(1, n) << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
