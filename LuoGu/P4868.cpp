#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct H {
  int n, a[100001];

  void Add(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      a[i] += y;
    }
  }

  int Find(int x) {
    int ans = 0;
    for (int i = x; i; i -= i & -i) {
      ans += a[i];
    }
    return ans;
  }
} h;
int n;

int main() {
  
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
