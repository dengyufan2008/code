#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct E {
  char a, b;
} e[16];
int k;
string n, d;
set<string> s;

void S(int x) {
  if (x == n.length()) {
    s.insert(d);
  }
  S(x + 1);
  for (int i = 1; i <= k; i++) {
    if (e[i].a == n[x]) {
      d[x] = e[i].b;
      S(x + 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= k; i++) {
    cin >> e[i].a >> e[i].b;
  }
  d = n;
  S(0);
  cout << s.size() << endl;
  return 0;
}
