#include <iostream>
#include <stack>

using namespace std;

int a, b;
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
  for (int i = 0; i < a + b; i++) {
    if (s.empty() || Q(s.top(), i)) {
      s.push(i);
    } else {
      s.pop();
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
