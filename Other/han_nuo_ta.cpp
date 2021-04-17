#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans;

void T(int l, int r, int n) {
  if(!n) {
    return;
  }
  int mid = 6 - l - r;
  T(l, mid, n - 1);
  cout << "[" << ++ans << "]Let No." << n << " item from " << l << " to " << r << endl;
  T(mid, r, n - 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> n;
  T(1, 3, n);
  return 0;
}
