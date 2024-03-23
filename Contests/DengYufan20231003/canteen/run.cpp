#include <iostream>
#define Prob "canteen"

using namespace std;

int main() {
  for (int i = 1;; i++) {
    cout << "Case #" << i << ":\n";
    system("data.exe");
    system(Prob ".exe");
    system("std.exe");
    if (system("fc " Prob ".out " Prob ".ans")) {
      break;
    }
  }
  return 0;
}
