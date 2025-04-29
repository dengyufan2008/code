#include <bits/stdc++.h>

#include "memory.h"
using namespace std;

const int N = 1e5 + 5;

namespace {
int n, seed, A[N];
mt19937 rnd(123);
int cnt;
const int MAXQ = 3e5;

void ensure(bool p, const char *err) {
  if (!p) {
    printf("%s\n", err);
    exit(0);
  }
}
}  // namespace

pair<int, int> look(int x, int y) {
  ensure(x >= 1 && x <= n && y >= 1 && y <= n && x != y, "Wrong Answer [2]");
  cnt++;
  ensure(cnt <= MAXQ, "Wrong Answer [3]");
  if (rnd() & 1) swap(A[x], A[y]);
  pair<int, int> p(A[x], A[y]);
  if (rnd() & 1) swap(A[x], A[y]);
  // for (int i = 1; i <= n; i++) {  // CHICK
  //   cerr << A[i] << " \n"[i == n];
  // }
  return p;
}

double Score(int x) {
  if (x <= 0) return 1.0;
  if (x <= 10) return 0.9;
  if (x <= 1000) return 1.0 - 0.1 * log(x) / log(10);
  if (x <= 8000) return 0.7 - (x - 1000) * 1.0 / (36000 - x);
  if (x <= 8100) return 0.4;
  if (x <= 208000) return 0.25;
  return 0;
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
  vector<int> ans = memory(n);
  for (int i = 0; i < n; i++) {
    ensure(ans[i] == A[i + 1], "Wrong Answer [1]");
  }
  cerr << "C: " << cnt << '\n';  // CHICK
  printf("Score : %f\n", Score(cnt - 92000) * 100);
}
