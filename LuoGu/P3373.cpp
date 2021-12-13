#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int a, t, d;  // AddMark, TimeMark, Data
} v[100001];
int n, m, p;

void Add(int s, int x, int y, int k, int l, int r) {
  
}

void Time(int s, int x, int y, int k, int l, int r) {

}

int Ask(int s, int x, int y, int l, int r) {

}

int main() {
  cin >> n >> m >> p;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    Add(1, i, i, x, 1, n);
  }
  for (int i = 1, c, x, y, k; i <= m; i++) {
    cin >> c;
    if (c == 1) {
      cin >> x >> y >> k;
      Time(1, x, y, k, 1, n);
    } else if (c == 2) {
      cin >> x >> y >> k;
      Add(1, x, y, k, 1, n);
    } else {
      cin >> x >> y;
      cout << Ask(1, x, y, 1, n) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
