#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kTar = 549855;  // 目标状态
const int kPoint = 12;    // 目标状态的空位下标
const int kDeep = 15;     // 深度限制
const int kDir[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

struct E {                             // 状态属性集
  int s, p, g, h;                      // s状态，p空位下标，g当前代价，h估计代价
  bool operator<(const E &_e) const {  // 按照估计总代价建立小根堆
    return g + h > _e.g + _e.h;
  }
} e;
map<int, int> m;      // 分组
priority_queue<E> q;  // 堆
int t, x, y, s;
char c;

void CalcPrice(E &e) {                                                      // 计算状态e的估计代价
  e.h = 0;                                                                  // 初始化
  for (int i = 0; i < 24; i++) {                                            // 枚举每个位置
    e.h += i != e.p && ((e.s >> i & 1) != (kTar >> i & 1) || i == kPoint);  // 是棋子且不在位置上
  }
}

bool Push(E &e) {                                                 // 将状态加入堆
  CalcPrice(e);                                                   // 计算代价
  int x = e.s * 25 + e.p;                                         // 分组的压缩表示
  auto p = m.find(x);                                             // 查询分组
  if (e.g + e.h <= kDeep && (p == m.end() || p->second < e.g)) {  // 没有超出答案范围且更优
    m[x] = e.g;                                                   // 记录分组的最优值
    q.push(e);                                                    // 加入堆
  }
  return e.s == kTar && e.p == kPoint;  // 判断目标状态
}

int Search() {                                                          // 搜索答案
  q = priority_queue<E>();                                              // 初始化堆
  m.clear();                                                            // 初始化分组
  for (Push(e); !q.empty(); q.pop()) {                                  // 逐个处理最优先的状态
    for (int i = 0; i < 8; i++) {                                       // 枚举移动方向
      e = q.top(), x = e.p / 5 + kDir[i][0], y = e.p % 5 + kDir[i][1];  // 复制状态，计算空位移动后的坐标
      if (min(x, y) >= 0 && max(x, y) <= 4) {                           // 移动合法
        int a = e.s >> e.p & 1, b = e.s >> (x * 5 + y) & 1;             // 取出状态变化前后空位上的值
        e.s += ((b - a) << e.p) + ((a - b) << (x * 5 + y));             // 计算新状态
        e.p = x * 5 + y, e.g++;                                         // 记录空位的新位置，累加当前代价
        if (Push(e)) {                                                  // 加入状态
          return e.g;
        }
      }
    }
  }
  return -1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    e = {0, 0, 0};  // 初始化初始状态
    for (int i = 0; i < 25; i++) {
      cin >> c;
      e.s |= (c == '1') << i;  // 计算状态
      if (c == '*') {          // 记录空位
        e.p = i;
      }
    }
    cout << Search() << endl;
  }
  return 0;
}
