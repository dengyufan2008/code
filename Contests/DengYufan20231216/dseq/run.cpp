#include <ctime>
#include <iostream>
#define Prob "dseq"

using namespace std;

int main() {
  auto s = clock();
  for (int i = 1;; i++) {
    cout << "Case #" << i << ":\n";
    system("data.exe");
    s = clock();
    system(Prob ".exe");
    cout << "Solution Runtime: " << clock() - s << "ms\n";
    s = clock();
    system("std.exe");
    cout << "STD Runtime:      " << clock() - s << "ms\n\n";
    if (system("fc " Prob ".out " Prob ".ans")) {
      break;
    }
  }
  return 0;
}
