#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 10;
const int kL = 5;

struct E {   // 状态的属性
  int d, l;  // 方向、距离
};
map<string, E> m;  // 状态与属性的映射
queue<string> q;   // 队列
string t[kMaxN][2], a, b;
int n, ans;

bool Push(string s, E e) {          // 记录状态，判断出解
  auto p = m.find(s);               // 查询状态
  if (p == m.end()) {               // 新状态
    m[s] = e;                       // 记录状态
    q.push(s);                      // 加入队列
  } else if (p->second.d != e.d) {  // 不同方向的状态
    ans = p->second.l + e.l;
    return 1;
  }
  return 0;
}

bool Search() {  // 搜索答案
  if (a == b) {  // 不用转换
    return 1;
  }
  for (Push(a, {0, 0}), Push(b, {1, 0}); !q.empty(); q.pop()) {             // 宽搜
    string s = q.front();                                                   // 当前状态
    E e = m.find(s)->second;                                                // 当前状态的属性
    if (e.d < kL) {                                                         // 状态需要扩展
      for (int i = 0; i < n; i++) {                                         // 枚举转移规则
        for (int j = 0; j <= (int)s.size() - (int)t[i][e.d].size(); j++) {  // 枚举子串
          if (s.substr(j, t[i][e.d].size()) == t[i][e.d]) {                 // 子串匹配
            string _s = s;
            _s.replace(j, t[i][e.d].size(), t[i][!e.d]);  // 转换子串
            if (Push(_s, {e.d, e.l + 1})) {               // 记录状态，判断出解
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b;
  for (; cin >> t[n][0]; n++) {  // 读入转换规则
    cin >> t[n][1];
  }
  if (Search()) {
    cout << ans;
  } else {
    cout << "NO ANSWER!";
  }
  return 0;
}
