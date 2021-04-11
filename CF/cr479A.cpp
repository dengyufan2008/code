#include <bits/stdc++.h>
#define LL long long

using namespace std;

int k, i, l, num;
string n;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  l = n.length();
  for (i = l - 1; i >= 0; i--) {
    if (num + n[i] + 1 - '0' < k) {
      num += n[i] + 1 - '0';
    } else {
      for (int j = 0; j < i; j++) {
        cout << n[j];
      }
      if (num + n[i] - '0' - k >= 0) {
        cout << num + n[i] - '0' - k;
      }
      return 0;
    }
  }
  return 0;
}
