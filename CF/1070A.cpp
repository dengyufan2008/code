#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct A{
  int d, s;
  string ans;
};
int d, s;
bool b[501][5001];
queue<A> q;

int main() {
  cin >> d >> s;
  q.push({0, 0, ""});
  while (!q.empty()) {
    A c = q.front();
    q.pop();
    if (c.s > s || b[c.d][c.s]) {
      continue;
    }
    if (c.s == s && !c.d) {
      cout << c.ans << endl;
      return 0;
    }
    b[c.d][c.s] = 1;
    for (int i = 0; i <= 9; i++) {
      q.push({(c.d * 10 + i) % d, c.s + i, c.ans + (char)(i + '0')});
    }
  }
  cout << -1 << endl;
  return 0;
}
