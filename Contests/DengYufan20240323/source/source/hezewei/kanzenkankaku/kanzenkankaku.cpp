/*
 * @Author: hezewei && 365424368@qq.com
 * @Date: 2024-03-23 08:22:01
 * @LastEditTime: 2024-03-23 10:16:45
 * @FilePath: \hezewei\kanzenkankaku\kanzenkankaku.cpp
 * Copyright (c) 2024 by hezewei, All Rights Reserved.
 */
// kanzenkankaku

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 3011;

int n, c, ans = 1, lst = kMaxN;
int a[kMaxN], nxt[kMaxN];
pair<int, int> tr[kMaxN << 2];
int s[kMaxN];
vector<int> v[kMaxN];

pair<int, int> chk(pair<int, int> a, pair<int, int> b) {
  if (a.first == b.first) {
    return {a.first, a.second + b.second};
  } else {
    return min(a, b);
  }
}

void build(int l, int r, int x) {
  if (l == r) {
    tr[x] = {a[l], 1};
  } else {
    int mid = (l + r) >> 1;
    build(l, mid, x * 2), build(mid + 1, r, x * 2 + 1);
    tr[x] = chk(tr[x * 2], tr[x * 2 + 1]);
  }
}

pair<int, int> Find(int l, int r, int L, int R, int x) {
  if (L <= l && r <= R) {
    return tr[x];
  } else if (L <= r && l <= R) {
    int mid = (l + r) >> 1;
    auto tmp1 = Find(l, mid, L, R, x * 2);
    auto tmp2 = Find(mid + 1, r, L, R, x * 2 + 1);
    return chk(tmp1, tmp2);
  }
  return {kMaxN, -1};
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  freopen("kanzenkankaku.in", "r", stdin);
  freopen("kanzenkankaku.out", "w", stdout);
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    a[i] = s[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; i + j <= n + 1; j++) {
      sort(s + i, s + i + j);
      for (int _i = 1; _i <= n; _i++) {
        for (int _j = _i + 1; _j <= n; _j++) {
          int k = 0;
          for (; _i + k < _j - k; k++) {
            if (s[_i + k] != s[_j - k]) {
              break;
            }
          }
          if (_i + k >= _j - k) {
            ans = max(ans, _j - _i + 1);
          }
        }
      }
      for (int k = 0; k < j; k++) {
        s[i + k] = a[i + k];
      }
    }
  }

  cout << ans << '\n';
  return 0;
}