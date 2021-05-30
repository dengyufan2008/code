#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, a[801][801];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  
  return 0;
}
