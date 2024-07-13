#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 2e5 + 1;

struct V {
  vector<int> e;  // 儿子列表
  int l, r;       // 在深搜序列中出现的始末位置
} v[kMaxN];
vector<int> l[kMaxN];  // 每个深度按照DFS序的节点列表
int n, m, x, q, u, d;

void T(int d, int x) {                                     // 深度d，当前节点x
  v[x].l = ++m;                                            // 分配起始位置
  l[d].push_back(m);                                       // 插入当前深度序列
  for (auto i = v[x].e.begin(); i != v[x].e.end(); i++) {  // 枚举儿子
    T(d + 1, *i);                                          // 遍历
  }
  v[x].r = ++m;  // 分配结束位置
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> x;
    v[x].e.push_back(i);
  }
  T(0, 1);
  cin >> q;
  while (q--) {
    cin >> u >> d;
    // 二分查找始末位置在对应深度中包含的节点数量
    cout << upper_bound(l[d].begin(), l[d].end(), v[u].r) - lower_bound(l[d].begin(), l[d].end(), v[u].l) << endl;
  }
  return 0;
}
