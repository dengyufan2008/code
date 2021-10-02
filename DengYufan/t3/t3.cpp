#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  int n;
  priority_queue<pair<int, int>> q;
} c, l, d;
int k[26];

void Input(V &x, int d) {
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); i += 2) {
    x.q.push({d == 0 ? s.length() - i : 0, (k[s[i + 1] - 'A'] + s[i] - '0') * (d == 0 ? 1 : d)});
  }
}

int main() {
  // freopen("t3.in", "r", stdin);
  // freopen("t3.out", "w", stdout);
  k['T' - 'A'] = 9, k['B' - 'A'] = 18;
  Input(c, 1), Input(l, -1), Input(d, 0);
  
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
