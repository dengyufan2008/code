#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n;
char a[300001], b[300001];
bool flag, turn[300001], same[300001];

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    flag = false;
    cin >> n >> a >> b;
    for (int i = 0, num = 0; i < n; i++) {
      num += (a[i] == '1' ? 1 : -1);
      turn[i] = (num == 0);
      same[i] = (a[i] == b[i]);
    }
    for (int i = n - 1, num = 0; i >= 0; i--) {
      if (num == same[i]) {
        num = (num + 1) % 2;
        if (!turn[i]) {
          flag = true;
          break;
        }
      }
    }
    if (!flag) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  return 0;
}
