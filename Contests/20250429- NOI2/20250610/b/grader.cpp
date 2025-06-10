#include <bits/stdc++.h>

#include "tree.h"
using namespace std;

namespace {

const int N = 110000;
int subtask, T;
stack<int> stk;
int n;
bool instk[N], ischk[N];
int cnt_push = 0;

void ensure(bool p, const char *err) {
  if (!p) {
    cout << err << "\n";
    exit(0);
  }
}

}  // namespace

void push(int u) {
  // fprintf(stderr,"push %d\n", u);
  cnt_push++;
  ensure(u >= 1 && u <= n, "Wrong Answer[1]");
  ensure(!instk[u], "Wrong Answer[1]");
  stk.push(u);
  instk[u] = true;
}

void pop() {
  ensure(!stk.empty(), "Wrong Answer[2]");
  int u = stk.top();
  // fprintf(stderr,"pop %d\n", u);
  stk.pop();
  instk[u] = false;
}

void check(int u) {
  // fprintf(stderr,"check %d\n", u);
  ensure(u >= 1 && u <= n, "Wrong Answer[3]");
  ensure(!ischk[u], "Wrong Answer[3]");
  ischk[u] = true;
}

int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
  scanf("%d%d", &T, &subtask);
  for (int tc = 0; tc < T; tc++) {
    scanf("%d", &n);
    vector<int> p(n - 1);
    for (int i = 0; i < n - 1; i++) {
      scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n; i++) {
      instk[i] = false;
      ischk[i] = false;
    }
    stk = stack<int>();
    cnt_push = 0;
    solve(n, p);
    for (int i = 1; i <= n; i++) {
      ensure(ischk[i], "Wrong Answer[4]");
    }
    printf("Q : %d\n", cnt_push);
  }
  return 0;
}
