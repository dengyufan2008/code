#include <bits/stdc++.h>

#include "evolution2.h"
using namespace std;

void ensure(bool p, const char *err) {
  if (!p) {
    cout << err << endl;
    exit(0);
  }
}

vector<int> Y;
vector<int> REV;
vector<int> PAR;
int N;
int C;

int compare(int a, int b) {
  ensure(0 <= a && a < N && 0 <= b && b < N, "Wrong Answer [1]");
  ensure(a != b, "Wrong Answer [2]");
  C++;
  return REV[a] < REV[b];
}

int main() {
  int tc;
  assert(scanf("%d", &tc) == 1);
  for (int t = 0; t < tc; t++) {
    assert(scanf("%d", &N) == 1);
    PAR.resize(N);
    REV.resize(N);
    Y.resize(N);
    C = 0;
    for (int i = 1; i < N; i++) {
      assert(scanf("%d", &PAR[i]) == 1);
    }
    for (int i = 0; i < N; i++) {
      assert(scanf("%d", &Y[i]) == 1);
      REV[Y[i]] = i;
    }
    vector<int> U(N - 1);
    vector<int> V(N - 1);
    for (int i = 1; i < N; i++) {
      U[i - 1] = Y[PAR[i]];
      V[i - 1] = Y[i];
    }
    vector<int> X = recover(N, U, V);
    ensure(X.size() == N, "Wrong Answer [3]");
    printf("C : %d\n", C);
    for (int i = 0; i < N; i++) {
      printf("%d ", X[i]);
    }
    printf("\n");
  }
}
