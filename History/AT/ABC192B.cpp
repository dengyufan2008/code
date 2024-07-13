#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kM[4] = {97, 122, 65, 90};

string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> s;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] < kM[(i & 1) * 2] || s[i] > kM[(i & 1) * 2 + 1]) {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;
  return 0;
}
