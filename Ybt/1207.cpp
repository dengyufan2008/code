#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int lh, rh, ans;
  scanf("%lld%lld", &lh, &rh);
  if (lh < rh) {
    long long int temp;
    temp = lh;
    lh = rh;
    rh = temp;
  }
  ans = lh % rh;
  while (ans != 0) {
    lh = rh;
    rh = ans;
    ans = lh % rh;
  }
  printf("%lld", rh);
  return 0;
}
