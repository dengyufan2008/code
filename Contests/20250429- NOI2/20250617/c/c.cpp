#include "telepathy.h"

using namespace std;

const int kMaxN = 201;
struct V {
  int s, f;
  vector<int> e;
} v[kMaxN];
int n, o;
vector<int> l;

void FindRoot(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      FindRoot(x, i), v[x].s += v[i].s;
      mx = max(mx, v[i].s);
    }
  }
  if (max(mx, n - v[x].s) * 2 <= n) {
    l.push_back(x);
  }
}

void CalcF(int f, int x) {
  v[x].f = f;
  for (int i : v[x].e) {
    if (i != f) {
      CalcF(x, i);
    }
  }
}

vector<int> Aitana(int N, vector<int> A, vector<int> B, int S, int subtask) {
  n = N, o = S + 1;
  for (int i = 1; i <= n; i++) {
    v[i].e.clear();
  }
  for (int i = 0; i <= n - 2; i++) {
    v[A[i] + 1].e.push_back(B[i] + 1);
    v[B[i] + 1].e.push_back(A[i] + 1);
  }
  l.clear(), FindRoot(0, 1);
  CalcF(0, l[0]), v[l[0]].f = l.back();

  static vector<int> ans;
  ans.clear(), ans.push_back(o);
  for (int i = 1, s = 1; s <= n * 10;) {
    for (int t = i; t >= 1 && s <= n * 10; t--, s++) {
      o = v[o].f, ans.push_back(o);
    }
    i <<= 1;
    for (int t = i; t >= 1 && s <= n * 10; t--, s++) {
      ans.push_back(o);
    }
    i = i == 2 ? 3 : i << 1;
  }

  for (int &i : ans) {
    i--;
  }
  return ans;
}

vector<int> Bruno(int N, vector<int> A, vector<int> B, int S, int subtask) {
  n = N, o = S + 1;
  for (int i = 1; i <= n; i++) {
    v[i].e.clear();
  }
  for (int i = 0; i <= n - 2; i++) {
    v[A[i] + 1].e.push_back(B[i] + 1);
    v[B[i] + 1].e.push_back(A[i] + 1);
  }
  l.clear(), FindRoot(0, 1);
  CalcF(0, l[0]), v[l[0]].f = l.front();

  static vector<int> ans;
  ans.clear(), ans.push_back(o);
  for (int i = 1, s = 1; s <= n * 10;) {
    for (int t = i; t >= 1 && s <= n * 10; t--, s++) {
      ans.push_back(o);
    }
    i <<= 1;
    for (int t = i; t >= 1 && s <= n * 10; t--, s++) {
      o = v[o].f, ans.push_back(o);
    }
    i = i == 2 ? 3 : i << 1;
  }

  for (int &i : ans) {
    i--;
  }
  return ans;
}
