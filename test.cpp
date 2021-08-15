#include <iostream>
#define LL long long

using namespace std;

const int kN[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
struct E {
  int d, px, py;
  bool f;
  char ch;
} e[3001][3001];
int t, n, m;
string ans;

int main() {
  cin >> t >> n >> m;
  while (t--) {
    cin >> n >> m;
    fill(&e[0][0], &e[3000][3000] + 1, (E){0, 0, 0, 0, ' '});
    e[0][0].f = 1, ans = "";
    for (int i = 1; i <= n; i++)
  }
  return 0;
}
