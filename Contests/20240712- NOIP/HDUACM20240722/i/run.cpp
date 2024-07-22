#include <ctime>
#include <iostream>
#define Prob "i"

using namespace std;

int main() {
  system("g++ -std=c++14 -O2 -Wl,--stack=0x40000000 dat.cpp -o dat");
  system("g++ -std=c++14 -O2 -Wl,--stack=0x40000000 " Prob ".cpp -o " Prob);
  system("g++ -std=c++14 -O2 -Wl,--stack=0x40000000 std.cpp -o std");
  auto s = clock();
  for (int i = 1;; i++) {
    cout << "Case #" << i << ":\n";
    system("dat.exe");
    s = clock();
    system(Prob ".exe");
    cout << "Solution Runtime: " << clock() - s << "ms\n";
    s = clock();
    system("std.exe");
    cout << "STD Runtime:      " << clock() - s << "ms\n\n";
    if (system("fc " Prob ".out " Prob ".ans /A")) {
      break;
    }
  }
  return 0;
}
