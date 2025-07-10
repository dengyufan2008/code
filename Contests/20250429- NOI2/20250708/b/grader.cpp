#include <bits/stdc++.h>
#include "perm.h"

namespace {
constexpr int STRATEGY_FIX = 1, STRATEGY_ADAPTIVE_MULTIPLE = 2;
constexpr int MAX_N = (int)1E5 + 10, SINGLE_QUERY_LIM = (int)1E7,
              TOTAL_ROUND_LIM = (int)1E7, TOTAL_QUERY_LIM = (int)3E8;
constexpr double EPS = 1E-9;
bool is_main_tests;
int subtask, n;
int cnt_query, cnt_round, current_case, full_score;
double max_rate;
void print_testcase() {
  if (current_case)
    std::cout << " (testcase " << current_case << ")";
  std::cout << std::endl;
}
void report_result(double score, const std::string& msg) {
  if (score < EPS)
    std::cout << "Wrong answer" << std::endl;
  else if (score > full_score - EPS)
    std::cout << "Accepted" << std::endl;
  else
    std::cout << "Partially correct (" + std::to_string(score) + " points)"
              << std::endl;
  std::cout << msg;
  print_testcase();
  exit(0);
}
void ensure(bool condition, int t) {
  if (!condition)
    report_result(0, "Wrong answer [" + std::to_string(t) + "]");
}
int next(int p) {
  if (p == n)
    return 1;
  return p + 1;
}
int prev(int p) {
  if (p == 1)
    return n;
  return p - 1;
}
int p[MAX_N], q[MAX_N], vis[MAX_N], ans;
void init() {
  scanf("%d%d", &subtask, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    q[p[i]] = i;
  }
}
int flip(int u) {
  u = q[u];
  if (vis[u] ^= 1) {
    ans += vis[u - 1] + vis[u + 1];
  } else {
    ans -= vis[u - 1] + vis[u + 1];
  }
  return ans || (vis[1] && vis[n]);
}
void mincyc(std::vector<int>& c) {
  if (c.size() <= 1)
    return;
  std::rotate(c.begin(), std::min_element(c.begin(), c.end()), c.end());
  if (c[1] > c.back()) {
    std::reverse(c.begin() + 1, c.end());
  }
}
void check(std::vector<int> c1, std::vector<int> c2) {
  mincyc(c1);
  mincyc(c2);
  ensure(c1 == c2, 5);
}
double f(double x) {
  return std::min(std::max(std::log2(x), 0.0), 8.0);
}
double lambda(int t, int Q) {
  return std::max(0.0, 1 - 0.1 * (f(t / 18.0) + f(Q / 1.5E7)));
}
}  // namespace

std::vector<bool> query(const std::vector<int>& idx) {
  const int N = idx.size();
  ensure(idx.size() <= SINGLE_QUERY_LIM, 1);
  cnt_round += 1;
  cnt_query += N;
  ensure(cnt_round <= TOTAL_ROUND_LIM, 2);
  ensure(cnt_query <= TOTAL_QUERY_LIM, 3);
  std::vector<bool> ret(N);
  for (int i = 0; i < N; i++) {
    int u = idx[i];
    ensure(1 <= u && u <= n, 4);
    ret[i] = flip(u);
  }
  return ret;
}

int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
  init();
  std::vector<int> cyc = solve(n, subtask);
  check(cyc, std::vector<int>(p + 1, p + n + 1));
  full_score = 100;
  report_result(full_score * lambda(cnt_round, cnt_query),
                "Correct answers (cnt_round = " + std::to_string(cnt_round) +
                    ", cnt_query = " + std::to_string(cnt_query) + ")");
  return 0;
}
