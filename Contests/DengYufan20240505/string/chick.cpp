#include <iostream>

using namespace std;

long long n;

bool C(long long n) {
  for (long long i = 2; i * i <= n; i++) {
    if (!(n % i)) {
      return 0;
    }
  }
  return 1;
}

int main() {
  cin >> n;
  for (long long &i = n; !C(i); i++) {
  }
  cout << n << '\n';
  return 0;
}