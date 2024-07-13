/*
ID: dengyuf1
TASK: numtri
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int r, a[1001][1001];

int main() {
  freopen("numtri.in", "r", stdin);
  freopen("numtri.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> r;
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= i; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = r - 1; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      a[i][j] += max(a[i + 1][j], a[i + 1][j + 1]);
    }
  }
  cout << a[1][1] << endl;
  return 0;
}
