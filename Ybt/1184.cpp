#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, num;
bool a[1001];

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1, tmp; i <= n; i++) {
    cin >> tmp;
    if (!a[tmp]) {
      num++;
      a[tmp] = true;
    }
  }
  cout << num << "\n";
  for (int i = 1; i <= 1000; i++) {
    if (a[i]) {
      cout << i << " ";
    }
  }
  return 0;
}
