#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, ans;
bool a[9][9], b[9];
char ch;

void S(int d, int s) {
  ans += s == k;
  if (d > n || s >= k) {
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (a[d][i] && !b[i]) {
      b[i] = true;
      S(d + 1, s + 1);
      b[i] = false;
    }
  }
  S(d + 1, s);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  while (1) {
    ans = 0;
    cin >> n >> k;
    if (n == -1 && k == -1) {
      break;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> ch;
        a[i][j] = ch == '#';
      }
    }
    S(1, 0);
    cout << ans << endl;
  }
  return 0;
}
