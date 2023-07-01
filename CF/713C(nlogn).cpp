#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const LL kInf = 1e18;
LL n, a[3001], b[3001] = {-kInf}, l[3001];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> b[i];
    b[i] -= i, l[i] = i;
  }
  sort(l + 1, l + n + 1, [](LL i, LL j) { return b[i] < b[j]; });
  for (LL i = 1; i <= n; i++) {
    a[l[i]] = a[l[i - 1]] + (b[l[i]] != b[l[i - 1]]);
  }
  
  return 0;
}
