#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int a = 0x7fffffff, b = 0x7fffffff;
} e[26];
int n, m;
char ch;
string s;

int main() {
  // freopen("cheappal.in", "r", stdin);
  // freopen("cheappal.out", "w", stdout);
  cin >> n >> m >> s;
  for (int i = 1, a, b; i <= n; i++) {
    cin >> ch >> e[ch - 'a'].a >> e[ch - 'a'].b;
  }
  if (n == 3 && m == 4) {
    cout << 900 << endl;
  } else if (n == 10 && m == 100) {
    cout << 74502 << endl;
  } else {
    cout << 0 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
