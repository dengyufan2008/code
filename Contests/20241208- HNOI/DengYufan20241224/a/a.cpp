#include <iostream>

#include "vector.h"

using namespace std;

const int kMaxN = 2001, kMaxL = 14;
vector<int> o, u, w[kMaxL];
vector<vector<int>> ans;

vector<vector<int>> solve(int n, int k, int q) {  // 14 choose 7
  o.resize(1);
  for (int i = 0; i < 1 << kMaxL; i++) {
    if (__builtin_popcount(i) == kMaxL >> 1) {
      o.push_back(i);
    }
  }
  for (int i = 0; i < kMaxL; i++) {
    u.clear();
    for (int j = 1; j <= n; j++) {
      if (o[j] >> i & 1) {
        u.push_back(j);
      }
    }
    if (!u.empty()) {
      w[i] = query(u);
    } else {
      w[i].resize(k);
    }
  }
  for (int i = 1; i <= n; i++) {
    u.clear(), u.resize(k);
    for (int j = 0; j < kMaxL; j++) {
      if (o[i] >> j & 1 ^ 1) {
        for (int l = 0; l < k; l++) {
          u[l] = max(u[l], w[j][l]);
        }
      }
    }
    ans.push_back(u);
  }
  return ans;
}
