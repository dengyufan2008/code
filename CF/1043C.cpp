#include <iostream>

using namespace std;

bool b[1001];
string s;

void Swap(int x) {
  b[x] = 1;
  for (int i = 0, j = x; i < j; i++, j--) {
    swap(s[i], s[j]);
  }
}

int main() {
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'a') {
      if (s[0] == 'a' && i > 0) {
        Swap(i - 1);
      }
      for (; s[i] == 'a'; i++) {
      }
      Swap(i - 1);
    }
  }
  for (int i = 0; i < s.size(); i++) {
    cout << b[i] << ' ';
  }
  return 0;
}
