#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <random>
#include <string>

#include "telepathy.h"

namespace {
const int INVALID_X_LENGTH = 1;
const int INVALID_X_RANGE = 2;
const int INVALID_X_START = 3;
const int INVALID_X_PATH = 4;
const int INVALID_Y_LENGTH = 5;
const int INVALID_Y_RANGE = 6;
const int INVALID_Y_START = 7;
const int INVALID_Y_PATH = 8;
const int INVALID_MEET = 9;

std::mt19937_64 mt;
int case_id;
void WrongAnswer(int code) {
  printf("Case #%d: Wrong Answer [%d]\n", case_id, code);
}
int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  return x;
}
bool check_permutation(int N, const std::vector<int>& p) {
  std::vector<bool> f(N, false);
  for (int x : p) {
    if (!(0 <= x && x < N)) return false;
    if (f[x]) return false;
    f[x] = true;
  }
  return true;
}
bool check_tree(int N, const std::vector<int>& u, const std::vector<int>& v) {
  std::vector<std::vector<int>> G(N);
  for (int i = 0; i < N - 1; i++) {
    if (!(0 <= u[i] && u[i] < N)) {
      return false;
    }
    if (!(0 <= v[i] && v[i] < N)) {
      return false;
    }
    G[u[i]].push_back(v[i]);
    G[v[i]].push_back(u[i]);
  }
  std::vector<bool> vis(N, false);
  std::vector<int> st = {0};
  vis[0] = true;
  while (!st.empty()) {
    int u = st.back();
    st.pop_back();
    for (int i : G[u]) {
      if (!vis[i]) {
        vis[i] = true;
        st.push_back(i);
      }
    }
  }
  return (vis == std::vector<bool>(N, true));
}
std::string check_validness(int N, const std::vector<int>& u,
                            const std::vector<int>& v,
                            const std::vector<int>& p,
                            const std::vector<int>& q, int s, int t,
                            int subtask) {
  if (!(1 <= subtask && subtask <= 3)) return "1 <= subtask <= 3";
  if (!check_permutation(N, p)) return "p is not a permutation";
  if (!check_permutation(N, q)) return "q is not a permutation";
  if (!check_tree(N, u, v)) return "(u, v) does not form a tree";
  if (!(0 <= s && s < N && 0 <= t && t < N && s != t)) return "Invalid s or t";
  if (subtask == 1) {
    for (int i = 0; i < N; i++) {
      if (!(p[i] == i && q[i] == i)) {
        return "(p, q) does not meet the condition for subtask 1";
      }
    }
  }
  if (subtask == 2) {
    for (int i = 0; i < N - 1; i++) {
      if (!(u[i] == i && v[i] == i + 1)) {
        return "(u, v) does not meet the condition for subtask 2";
      }
    }
  }
  return "";
}
void shuffle_edge(int M, std::vector<int>& u, std::vector<int>& v) {
  for (int i = 0; i < M; i++) {
    if (mt() % 2 == 1) {
      std::swap(u[i], v[i]);
    }
    int x = mt() % (i + 1);
    std::swap(u[i], u[x]);
    std::swap(v[i], v[x]);
  }
}
int tree_distance(int N, const std::vector<int>& u, const std::vector<int>& v,
                  int s, int t) {
  std::vector<std::vector<int>> G(N);
  for (int i = 0; i < N - 1; i++) {
    G[u[i]].push_back(v[i]);
    G[v[i]].push_back(u[i]);
  }
  std::vector<int> dist(N, -1);
  dist[s] = 0;
  std::queue<int> que;
  que.push(s);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int i : G[u]) {
      if (dist[i] == -1) {
        dist[i] = dist[u] + 1;
        que.push(i);
      }
    }
  }
  return dist[t];
}
void run_scenario(int N, const std::vector<int>& u, const std::vector<int>& v,
                  const std::vector<int>& p, const std::vector<int>& q, int s,
                  int t, int subtask) {
  std::vector<int> invp(N), invq(N);
  for (int i = 0; i < N; i++) {
    invp[p[i]] = i;
    invq[q[i]] = i;
  }
  std::vector<int> A(N - 1), B(N - 1), C(N - 1), D(N - 1);
  std::vector<std::pair<int, int>> edges(N - 1);
  for (int i = 0; i < N - 1; i++) {
    A[i] = p[u[i]];
    B[i] = p[v[i]];
    C[i] = q[u[i]];
    D[i] = q[v[i]];
    edges[i] = std::minmax({u[i], v[i]});
  }
  shuffle_edge(N - 1, A, B);
  shuffle_edge(N - 1, C, D);
  int S = p[s];
  int T = q[t];
  std::sort(edges.begin(), edges.end());
  auto adjacent = [&](int a, int b) -> bool {
    return std::binary_search(edges.begin(), edges.end(), std::minmax({a, b}));
  };
  std::vector<int> x = Aitana(N, A, B, S, subtask);
  if (int(x.size()) != 10 * N + 1) return WrongAnswer(INVALID_X_LENGTH);
  for (int i = 0; i <= 10 * N; i++) {
    if (!(0 <= x[i] && x[i] < N)) return WrongAnswer(INVALID_X_RANGE);
  }
  if (!(x[0] == S)) return WrongAnswer(INVALID_X_START);
  for (int i = 0; i < 10 * N; i++) {
    if (!(x[i] == x[i + 1] || adjacent(invp[x[i]], invp[x[i + 1]]))) {
      return WrongAnswer(INVALID_X_PATH);
    }
  }
  std::vector<int> y = Bruno(N, C, D, T, subtask);
  if (int(y.size()) != 10 * N + 1) {
    return WrongAnswer(INVALID_Y_LENGTH);
  }
  for (int i = 0; i <= 10 * N; i++) {
    if (!(0 <= y[i] && y[i] < N)) {
      return WrongAnswer(INVALID_Y_RANGE);
    }
  }
  if (!(y[0] == T)) return WrongAnswer(INVALID_Y_START);
  for (int i = 0; i < 10 * N; i++) {
    if (!(y[i] == y[i + 1] || adjacent(invq[y[i]], invq[y[i + 1]]))) {
      return WrongAnswer(INVALID_Y_PATH);
    }
  }
  int meet = -1;
  for (int i = 0; i <= 10 * N; i++) {
    if (invp[x[i]] == invq[y[i]]) {
      meet = i;
      break;
    }
  }
  if (meet == -1) return WrongAnswer(INVALID_MEET);
  int dist = tree_distance(N, u, v, s, t);
  printf("Case #%d: Accepted %d %d %f\n", case_id, meet, dist, 1. * meet / dist);
}
}  // namespace

int main(int argc, char* argv[]) {
  if (!(argc == 1 || argc == 2)) {
    fprintf(stderr, "usage: %s [<seed>]", argv[0]);
    exit(1);
  }
  if (argc == 2) {
    try {
      const long long seed = std::stoll(argv[1]);
      mt = std::mt19937_64(seed);
    } catch (const std::exception& e) {
      fprintf(stderr, "Invalid seed: %s\n", argv[1]);
      exit(1);
    }
  }
  int subtask = read_int();
  int Q = read_int();
  std::vector<int> N(Q), s(Q), t(Q);
  std::vector<std::vector<int>> p(Q), q(Q), u(Q), v(Q);
  for (int i = 0; i < Q; i++) {
    N[i] = read_int();
    u[i].resize(N[i] - 1);
    v[i].resize(N[i] - 1);
    for (int j = 0; j < N[i] - 1; j++) {
      u[i][j] = read_int();
      v[i][j] = read_int();
    }
    p[i].resize(N[i]);
    q[i].resize(N[i]);
    for (int& x : p[i]) x = read_int();
    for (int& x : q[i]) x = read_int();
    s[i] = read_int();
    t[i] = read_int();
  }
  for (int i = 0; i < Q; i++) {
    std::string err =
        check_validness(N[i], u[i], v[i], p[i], q[i], s[i], t[i], subtask);
    if (!err.empty()) {
      fprintf(stderr, "Input does not satisfy the constraints: %s\n",
              err.c_str());
      exit(1);
    }
  }
  for (int i = 0; i < Q; i++) {
    case_id = i;
    run_scenario(N[i], u[i], v[i], p[i], q[i], s[i], t[i], subtask);
  }
  return 0;
}
