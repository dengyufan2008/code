#include <iostream>
#include <queue>

using namespace std;

struct V {
  int s, w, d;
  bool b;
  vector<pair<int, int>> e;
} v[10001];
int n, m, r = 1, s, q[101];
bool ans[101], b[10000001];
vector<int> d;
queue<int> l;

void GetRoot(int f, int x) {  // 寻找重心 O(n)
  v[x].s = 1, v[x].w = 0;
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      GetRoot(x, i.first);
      v[x].s += v[i.first].s, v[x].w = max(v[x].w, v[i.first].s);  // 更新子节点数 最大子树节点数
    }
  }
  if ((v[x].w = max(v[x].w, s - v[x].s)) <= s / 2) {  // 根据性质更新重心
    r = x;
  }
}

void CalcD(int f, int x) {  // 计算子节点到当前重心距离 ΣO(n)
  d.push_back(v[x].d);      // 记录当前节点到重心距离
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      v[i.first].d = v[x].d + i.second;  // 更新距离
      CalcD(x, i.first);
    }
  }
}

void Divide() {  // 淀粉质 O(logn)
  v[r].b = 1;
  b[0] = 1, l.push(0);
  for (auto i : v[r].e) {
    if (!v[i.first].b) {
      v[i.first].d = i.second;
      CalcD(r, i.first);
      for (int j : d) {                 // 取出距离
        for (int k = 1; k <= m; k++) {  // 处理询问 O(m)
          if (q[k] >= j) {
            ans[k] |= b[q[k] - j];  // 更新答案
          }
        }
      }
      for (int j : d) {
        if (j <= 1e7) {         // 洛谷专用防爆特判
          l.push(j), b[j] = 1;  // 加入队列 标记存在
        }
      }
      d.clear();
    }
  }
  while (!l.empty()) {
    b[l.front()] = 0, l.pop();  // 撤销操作
  }
  for (auto i : v[r].e) {
    if (!v[i.first].b) {
      s = v[i.first].s, GetRoot(r, i.first), GetRoot(0, r), Divide();  // 继续淀粉质
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i];
  }
  s = n, GetRoot(0, 1), GetRoot(0, r), Divide();
  for (int i = 1; i <= m; i++) {
    cout << (ans[i] ? "AYE\n" : "NAY\n");
  }
  return 0;
}
