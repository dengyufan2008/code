#include <iostream>
#include <stack>

using namespace std;

int a, b, p;
bool ans[4001];
stack<int> s;

bool Q(int x, int y) {
  string s;
  cout << "? " << x << ' ' << y << endl;
  cout.flush();
  cin >> s;
  return s == "Y";
}

int main() {
  cin >> a >> b;
  if (a <= b) {
    cout << "Impossible";
    return 0;
  }
  for (p = 0; p < a + b - 1 && !Q(p, p + 1); p += 2) {
  }
  if (p >= a + b - 1) {
    s.push(p);
  } else {
    s.push(p), s.push(p + 1);
    for (int i = p + 2; i < a + b; i++) {
      if (Q(s.top(), i)) {
        s.push(i);
      } else {
        s.pop();
      }
    }
  }
  for (int i = 0; i < a + b; i++) {
    ans[i] = Q(s.top(), i);
  }
  cout << "! ";
  for (int i = 0; i < a + b; i++) {
    cout << ans[i];
  }
  cout.flush();
  return 0;
}
