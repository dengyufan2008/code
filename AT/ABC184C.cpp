#include <bits/stdc++.h>
#define LL long long

using namespace std;

int r1, c1, r2, c2, ans;
bool flag = true;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> r1 >> c1 >> r2 >> c2;
  if (r1 == r2 && c1 == c2) {
    ans = 0;
  } else if (r1 + c1 == r2 + c2 || r1 - c1 == r2 - c2 || abs(r1 - r2) + abs(c1 - c2) <= 3) {
    ans = 1;
  } else if ((r1 + c1) % 2 == (r2 + c2) % 2) {
    ans = 2;
  } else {
    ans = 3;
    for (int i = -3; i <= 3 && flag; i++) {
      for (int j = -3; j <= 3; j++) {
        if (abs(i) + abs(j) <= 3) {
          if (r1 + c1 == r2 + i + c2 + j || r1 - c1 == r2 + i - c2 + j || abs(r1 - r2 + i) + abs(c1 - c2 + j) <= 3) {
            ans = 2;
            flag = false;
            break;
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
