#include <bits/stdc++.h>
#define LL long long

using namespace std;

short a[10001], b[10001], len;
string n;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  len = n.length();
  for (int i = 0; i < len; i++) {
    b[len - i] = a[len - i] = n[i];
  }

  return 0;
}
