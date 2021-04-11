#include <bits/stdc++.h>
using namespace std;
struct A {
  char name[21];
  int score;
} student[20];
bool comp(A x, A y) {
  return x.score > y.score;
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s %d", student[i].name, &student[i].score);
  }
  sort(student + 1, student + n + 1, comp);
  for (int i = 1; i <= n; i++) {
    printf("%s %d\n", student[i].name, student[i].score);
  }
  exit(0);
}
