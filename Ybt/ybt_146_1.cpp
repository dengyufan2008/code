#include <bits/stdc++.h>
using namespace std;
struct A {
  int score;
  char name[21];
} student[101];
int main() {
  int n, max = -1, maxn;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %s", &student[i].score, student[i].name);
    if (student[i].score > max) {
      max = student[i].score;
      maxn = i;
    }
  }
  printf("%s", student[maxn].name);
  exit(0);
}
