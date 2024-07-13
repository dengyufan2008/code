#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans;
string s, tmp, anss;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> s;
  for (int i = 0, num = 0; i < n; i++, num = 0) {
    tmp = s.substr(i, 2);
    for (int j = 0; j < n; j++) {
      if (s.substr(j, 2) == tmp) {
        num++;
      }
    }
    if(num > ans) {
      ans = num, anss = tmp;
    }
  }
  cout << anss;
  return 0;
}
