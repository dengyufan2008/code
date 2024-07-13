#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  cout << (n & 1 ? "Black" : "White") << endl;
  return 0;
}
