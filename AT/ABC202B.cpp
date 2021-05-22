#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kM[10] = {0, 1, 0, 0, 0, 0, 9, 0, 8, 6};

int l;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> s;
  l = s.length();
  for (int i = l - 1; i >= 0; i--) {
    cout << kM[s[i] - '0'];
  }
  return 0;
}
