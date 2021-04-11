#include <bits/stdc++.h>
using namespace std;
struct A {
  char id[10];
  int age;
} illmen1[100], illmen2[100];
bool comp(A x, A y) {
  return x.age > y.age;
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s %d", illmen1[i].id, &illmen1[i].age);
    illmen2[i] = illmen1[i];
  }
  sort(illmen1 + 1, illmen1 + n + 1, comp);
  for (int i = 1; illmen1[i].age >= 60; i++) {
    printf("%s\n", illmen1[i].id);
  }
  for (int i = 1; i <= n; i++) {
    if (illmen2[i].age < 60) {
      printf("%s\n", illmen2[i].id);
    }
  }
  exit(0);
}
