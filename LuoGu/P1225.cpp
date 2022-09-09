#include <iostream>

using namespace std;

bool b[2][5][5];

int main() {
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < 5; j++) {
      for (int k = 1; k < 5; k++) {
        cin >> b[i][j][k];
      }
    }
  }
  
  return 0;
}
