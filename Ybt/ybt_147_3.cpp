#include <bits/stdc++.h>
using namespace std;
struct A {
  int id;
  float score;
} student[101];
bool comp(A x, A y) {
  return x.score > y.score;
}
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d %f", &student[i].id, &student[i].score);
  }
  sort(student + 1, student + n + 1, comp);
  printf("%d %g", student[k].id, student[k].score);
  exit(0);
}
