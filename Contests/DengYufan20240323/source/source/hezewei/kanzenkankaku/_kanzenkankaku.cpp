/*
 * @Author: hezewei && 365424368@qq.com
 * @Date: 2024-03-23 08:22:01
 * @LastEditTime: 2024-03-23 10:00:42
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
pair<int, int> s[kMaxN];
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
    cin >> s[i].first;
    s[i].second = i;
  }
  sort(s + 1, s + n + 1);
  for (int i = 1, cnt = 0; i <= n; i++) {
    if (s[i].first == lst) {
      nxt[v[cnt].back()] = s[i].second;
      s[i].first = s[i - 1].first;
    } else {
      lst = s[i].first;
      s[i].first = ++cnt;
    }
    v[cnt].push_back(s[i].second);
  }
  sort(s + 1, s + n + 1, [](auto a, auto b) { return a.second < b.second; });
  for (int i = 1; i <= n; i++) {
    a[i] = s[i].first;
  }
  build(1, n, 1);
  for (int i = 1; i <= n; i++) {
    int j = i - 1, Max = i;
    while (j) {
      if (a[j] == a[i]) {
        nxt[j] = nxt[nxt[j + 1]];
        ans = max(ans, Max - j + 1);
      } else if (a[j] < a[j + 1] && j + 1 < i) {
        break;
      } else if (nxt[j] == 0) {
        break;
      } else {
        Max = max(Max, nxt[j]);
        auto tmp = Find(1, n, i + 1, Max, 1);
        int Min = tmp.second;
        if ((tmp.first == a[i] && Min + j - i + 1 + i == Max) || Max - i == i - j) {
          while (Max < n && a[Max + 1] == tmp.first) {
            Max++;
          }
          ans = max(ans, Max - j + 1);
        }
      }
      j--;
    }
  }
  cout << ans << '\n';
  return 0;
}