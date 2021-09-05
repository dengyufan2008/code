#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

inline int Input() {
  register int x(0), f;
  register char ch = getchar();
  f = ch == '-' ? -1 : 1;
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch - '0');
    ch = getchar();
  }
  return f * x;
}

int main() {
  cout << Input() << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
