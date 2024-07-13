#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct A {
  int d, s;
};
struct V {
  int x, y;
  char ch;
} v[501][5001];
int d, s, m = -1;
bool b[501][5001];
queue<A> q;

void Print(int x, int y) {
  if (y) {
    Print(v[x][y].x, v[x][y].y);
    cout << v[x][y].ch;
  }
}

int main() {
  cin >> d >> s;
  q.push({0, 0});
  while (!q.empty()) {
    A c = q.front();
    q.pop();
    for (int i = 0; i <= 9; i++) {
      if (c.s + i <= s && !b[(c.d * 10 + i) % d][c.s + i]) {
        b[(c.d * 10 + i) % d][c.s + i] = 1;
        q.push({(c.d * 10 + i) % d, c.s + i});
        v[(c.d * 10 + i) % d][c.s + i] = {c.d, c.s, (char)(i + '0')};
      }
    }
  }
  b[0][0] = 1;
  if (b[0][s]) {
    Print(0, s);
    cout << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}
