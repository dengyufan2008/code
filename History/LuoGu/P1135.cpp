#include <iostream>
#define LL long long

using namespace std;

struct A {
  int floor, step;
} table[40001];

int n, a, b, k[201], h, t;
bool flag[201];

void Bfs(int floor, int step) {
  if (floor < 1 || floor > n || flag[floor]) {
    return;
  }
  if (floor == b) {
    cout << step;
    exit(0);
  }
  flag[floor] = true;
  table[++t].floor = floor;
  table[t].step = step;
}

int main() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    cin >> k[i];
  }
  table[1].floor = a, table[1].step = 0;
  Bfs(table[1].floor, table[1].step);
  for (h = 1, t = 1; h <= t; h++) {
    Bfs(table[h].floor + k[table[h].floor],
        table[h].step + 1);
    Bfs(table[h].floor - k[table[h].floor],
        table[h].step + 1);
  }
  cout << -1;
  return 0;
}
