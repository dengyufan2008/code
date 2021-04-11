#include <iostream>
#define LL long long

using namespace std;

const int kMax = 1e9 + 7;
int a, b;

LL FastPow(LL a, LL b) {
  LL tmp = a, ans = 1;
  for (LL i = 1; i <= b; i = i << 1) {
    if (b & i) {
      ans = ans * tmp % kMax;
    }
    tmp = tmp * tmp % kMax;
  }
  return ans;
}

int main() {
  cin >> a >> b;
  cout << FastPow(a, b) << "\n";
  return 0;
}
