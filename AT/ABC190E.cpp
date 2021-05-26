#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, k, a[100001], b[100001], c[18];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i];
  }
  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> c[i];
  }
  
  return 0;
}
