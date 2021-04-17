#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;
char a, b, c;

void T(char a, char b, char c, int n) {
  if (n) {
    T(a, c, b, n - 1);
    printf("%c->%d->%c\n", a, n, b);
    T(c, b, a, n - 1);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  scanf("%d %c %c %c", &n, &a, &b, &c);
  T(a, b, c, n);
  return 0;
}
