/*
ID: dengyuf1
TASK: friday
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kM[13] = {0, 3, 3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2};

int n, d = 3, a[7];

bool C(int y) {
  return y % 100 && !(y % 4) || !(y % 400);
}

int main() {
  freopen("friday.in", "r", stdin);
  freopen("friday.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1900; i < 1900 + n; i++) {
    for (int j = 1; j <= 12; j++) {
      d = (d + (kM[j] ? kM[j] : C(i))) % 7;
      a[d]++;
    }
  }
  for (int i = 0; i <= 5; i++) {
    cout << a[(i + 6) % 7] << " ";
  }
  cout << a[5] << endl;
  return 0;
}
