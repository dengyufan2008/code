#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 1e5 + 1;
const int kMaxK = 17;
const int kInf = 1 << 28;

struct V {        // 点
  vector<int> p;  // 邻点
  int d[kMaxK];   // 到Ci的距离
} v[kMaxN];

queue<int> q;
int c[kMaxK], f[kMaxK][1 << kMaxK];
int n, m, k, x, y, ans = kInf;

void W(int o) {                                                // 求所有点到Co的距离
  for (v[c[o]].d[o] = 0, q.push(c[o]); !q.empty(); q.pop()) {  // 处理队列
    int x = q.front();
    for (int i = 0; i < v[x].p.size(); i++) {  // 枚举邻点
      int y = v[x].p[i];
      if (v[y].d[o] == kInf) {      // 尚未到过
        v[y].d[o] = v[x].d[o] + 1;  // 记录距离
        q.push(y);                  // 加入队列
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  fill(v[0].d, v[0].d + kMaxK, kInf);  // 初始化
  fill(v + 1, v + 1 + n, v[0]);
  for (int i = 1; i <= m; i++) {
    cin >> x >> y;
    v[x].p.push_back(y);
    v[y].p.push_back(x);
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> c[i];
    W(i);                               // 求距离
    fill(f[i], f[i] + (1 << k), kInf);  // 初始化状态
    f[i][1 << i] = 1;                   // 初始状态
  }
  for (int i = 0; i < 1 << k; i++) {  // 枚举点集
    for (int j = 0; j < k; j++) {     // 枚举结尾点编号
      for (int p = 0; p < k; p++) {   // 枚举下一个点
        f[p][i | (1 << p)] = min(f[p][i | (1 << p)], f[j][i] + v[c[j]].d[p]);
      }
    }
  }
  for (int i = 0; i < k; i++) {  // 寻找答案
    ans = min(ans, f[i][(1 << k) - 1]);
  }
  cout << (ans == kInf ? -1 : ans);
  return 0;
}
