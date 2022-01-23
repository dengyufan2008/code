#include <iostream>
#define LL long long

using namespace std;

struct A {
  int b, x, y;
} a[101];
int n, f[101];

int GetRoot(int x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].b >> a[i].x >> a[i].y;
    f[i] = i;
    if (a[i].b == 1) {
      for (int j = 1; j < i; j++) {
        if (a[i].b == 1 && a[i].x < a[j].x && a[j].x < a[i].y || a[i].x < a[j].y && a[j].y < a[i].y) {
          f[GetRoot(i)] = GetRoot(j);
        }
      }
    } else {
      cout << (GetRoot(a[i].x) == GetRoot(a[i].y) ? "YES\n" : "NO\n");
    }
  }
  return 0;
}
