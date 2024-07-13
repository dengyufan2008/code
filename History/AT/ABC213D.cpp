#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  priority_queue<int> e;
} v[200001];
int n;

void S(int f, int x) {
  cout << x << " ";
  while (!v[x].e.empty()) {
    if (-v[x].e.top() != f) {
      S(x, -v[x].e.top());
      cout << x << " ";
    }
    v[x].e.pop();
  }
}

int main() {
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push(-y), v[y].e.push(-x);
  }
  S(0, 1);
  return 0;
}
