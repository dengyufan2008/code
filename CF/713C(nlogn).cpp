#include <iostream>
#include <queue>
#define LL long long

using namespace std;

LL n, ans;
priority_queue<int> q;

int main() {
  cin >> n;
  for (LL i = 1, x; i <= n; i++) {
    cin >> x;
    x -= i;
    q.push(x);             // 此时最右侧 k = 0, b = ans.
    if (x < q.top()) {     // 影响到了最右侧 b, 需要更新 ans.
      q.push(x);           // 此时最右侧 k = 1, 次右侧 k = 0.
      ans += q.top() - x;  // 故最右侧 b := b + (当前位置到最右侧交点的距离).
      q.pop();             // 最右侧 k = 1, 故应删除.
    }
  }
  cout << ans;
  return 0;
}
