#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const __int128_t kMul = 25214903917, kMask = 281474976710655;
__int128_t x, z, _i, _j, s[6], _s[3];

__int128_t Input() {
  __int128_t x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}

void Output(__int128_t x) {
  if (x < 0) {
    x = -x;
    putchar('-');
  }
  if (x > 9) {
    Output(x / 10);
  }
  putchar(x % 10 + '0');
}

int main() {
  cout << "Please input the seed of the world." << endl;
  s[0] = Input();
  cout << "Please input x and z of the chunk." << endl;
  x = Input(), z = Input();
  s[1] = s[0] ^ kMul & kMask;
  for (int i = 2; i <= 5; i++) {
    s[i] = (s[i - 1] * kMul + 11) & kMask;
  }
  for (int i = 2; i <= 5; i++) {
    s[i] = i & 1 ? s[i] << 16 >> 32 : s[i] >> 16 << 32;
  }
  _i = (s[2] + s[3]) | 1, _j = (s[4] + s[5]) | 1, _s[0] = (((16 * x * _i + 16 * z * _j) ^ s[0]) + 60009) ^ kMul & kMask;
  for (int i = 1; i <= 2; i++) {
    _s[i] = (_s[i - 1] * kMul + 11) & kMask;
  }
  cout << "The diamonds is at x:", Output((_s[1] >> 44) + 16 * x), cout << " z:", Output((_s[2] >> 44) + 16 * z), cout << endl;
  system("pause");
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
   return 0;
}
