#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int main() {
  int hz, ms;
  while (1) {
    cout << "Please input hz:";
    cin >> hz;
    cout << "Please input ms:";
    cin >> ms;
    Beep(hz, ms);
    system("cls");
  }
  return 0;
}
