#include <bits/stdc++.h>
#define LL long long

using namespace std;

int h, w, a[2001][2001];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> ch;
      a[i][j] = (ch == '+' ? 1 : -1);
    }
  }
  
  return 0;
}
