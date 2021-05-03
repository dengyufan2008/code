/*
ID: dengyuf1
TASK: ride
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int al, bl, an = 1, bn = 1;
char a[7], b[7];

int main() {
  freopen("ride.in", "r", stdin);
  freopen("ride.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b;
  al = strlen(a), bl = strlen(b);
  for (int i = 0; i < al; i++) {
    an *= a[i] - 'A' + 1;
  }
  for (int i = 0; i < bl; i++) {
    bn *= b[i] - 'A' + 1;
  }
  cout << (an % 47 == bn % 47 ? "GO" : "STAY") << endl;
  return 0;
}
