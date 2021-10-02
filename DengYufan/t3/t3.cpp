#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  int n[3];
  priority_queue<pair<int, bool>> q[3];
} v[2];
int k[26];
bool b;  // 1:C 0:L
queue<pair<int, int>> q;

void Input(V &x, int d) {
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); i += 2) {
    x.q[k[s[i + 1] - 'A']].push({d * (s[i] - '0'), 0});
  }
}

void _Input() {
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); i += 2) {
    q.push({s[i] - '0', k[s[i + 1] - 'A']});
  }
}

int main() {
  freopen("t3.in", "r", stdin);
  freopen("t3.out", "w", stdout);
  k['T' - 'A'] = 1, k['B' - 'A'] = 2;
  Input(v[1], 1), Input(v[0], -1), _Input();
  if (v[1].q[1].empty()) {
    cout << "C\n2\n";
  } else if (v[1].q[1].top().first == 1) {
    cout << "L\n6\n";
  } else {
    cout << "C\n" << (v[1].n[0] + v[1].n[1] + v[1].n[2]) * 2 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
