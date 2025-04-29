#include <bits/stdc++.h>

#include "lines.h"
using namespace std;

namespace {

const int N = 110;
int subtask;
int n, _a[N], _b[N], qmax, qmin;
int cnt = 0;
bool is_report = false;

void ensure(bool p, const char *err) {
  if (!p) {
    printf("%s\n", err);
    exit(0);
  }
}

double score(int q) {
  if (q > qmax) {
    return 0;
  } else if (q <= qmin) {
    return 1;
  } else {
    return 1.0 - 0.7 * double(q - qmin) / double(qmax - qmin);
  }
}

long double compute_query(long double x, long double y) {
  long double sum = 0;
  for (int i = 0; i < n; i++)
    sum += fabsl(_a[i] * x - y + _b[i]) / sqrtl(_a[i] * _a[i] + 1);
  return sum;
}

}  // namespace

long double query(long double x, long double y) {
  cnt++;
  ensure(cnt <= qmax, "Wrong Answer [1]");
  if (!isfinite(x) || !isfinite(y) || fabs(x) > 1e12 || fabs(y) > 1e12) {
    ensure(false, "Wrong Answer [2]");
  }
  return compute_query(x, y);
}

void report(std::vector<int> a, std::vector<int> b) {
  ensure(a.size() == n && b.size() == n, "Wrong Answer [3]");
  is_report = true;
  vector<pair<int, int>> ans(n);
  vector<pair<int, int>> out(n);
  for (int i = 0; i < n; i++) {
    ans[i] = make_pair(_a[i], _b[i]);
    out[i] = make_pair(a[i], b[i]);
  }

  sort(ans.begin(), ans.end());
  sort(out.begin(), out.end());

  for (int i = 0; i < n; i++) {
    ensure(ans[i] == out[i], "Wrong Answer [4]");
    // ensure(ans[i].first == out[i].first, "Wrong Answer [4]");  // CHICK
  }
  printf("Query : %d\n", cnt);
  printf("Score : %f\n", score(cnt));
}

int main() {
  // freopen("b.in", "r", stdin);  // CHICK
  scanf("%d", &subtask);
  scanf("%d%d%d", &n, &qmax, &qmin);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &_a[i], &_b[i]);
  }
  solve(n, subtask);
  ensure(is_report, "Wrong Answer [5]");
  return 0;
}
