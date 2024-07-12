#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

int m;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> m >> m;
  cout << (m ? "Alice" : "Bob");
  return 0;
}
