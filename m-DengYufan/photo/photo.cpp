#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n;

int main() {
  freopen("phtot.in", "r", stdin);
  freopen("photo.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cout << i * 10 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
