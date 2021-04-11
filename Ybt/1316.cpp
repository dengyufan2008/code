#include <bits/stdc++.h>
using namespace std;
int num[1001];
void sum(int n) {
  if (num[n] != -1) {
    return;
  }
  num[n] = 1;
  for (int i = 1; i <= n / 2; i++) {
    sum(i);
    num[n] = num[n] + num[i];
  }
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    num[i] = -1;
  }
  sum(n);
  printf("%d", num[n]);
  exit(0);
}
