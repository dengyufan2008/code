#include <bits/stdc++.h>

#include "coins.h"

namespace {

int n;
int k;
int weighs = 0;
std::vector<int> a;

}  // namespace

long long weigh(std::vector<int> p) {
  if (p.size() != n) {
    std::cout << "Wrong answer [1]: size of p should be n\n";
    std::exit(0);
  }

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    if (p[i] < 0 || p[i] > a[i]) {
      std::cout << "Wrong answer [2]: p[i] should be between 0 and a[i]\n";
      std::exit(0);
    }
    ans += 1LL * p[i] * (5 + (i == k));
  }
  weighs++;
  return ans;
}

int main() {
  freopen("a.in", "r", stdin);  // CHICK
  freopen("a.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int ans = solve(a);

  if (ans < 0 || ans >= n) {
    std::cout << "Wrong answer [3]: answer should be between 0 and n-1\n";
    return 0;
  }
  if (k != ans) {
    std::cout << "Wrong answer [4]: incorrect answer\n";
    return 0;
  }
  std::cout << weighs << '\n';  // CHICK
  // std::cout << "Correct! Number of weighs: " << weighs << "\n";  // CHICK
  // std::cout << clock() << '\n';
  // std::cout << "Correct!\n";

  return 0;
}
