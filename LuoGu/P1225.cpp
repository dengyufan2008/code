#include <iostream>

using namespace std;

struct A {
  int x, s, a, b, p;
} q[1 << 16];
int h, t, a[2];
bool b[1 << 16];

void Print(int x) {
  if (x) {
    Print(q[x].p);
    cout << q[x].a / 4 + 1 << q[x].a % 4 + 1 << q[x].b / 4 + 1 << q[x].b % 4 + 1 << '\n';
  }
}

int main() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        char c = getchar();
        while (c != '1' && c != '0') {
          c = getchar();
        }
        a[i] |= (c == '1') << j * 4 + k;
      }
    }
  }
  for (b[a[0]] = 1, q[t++] = {a[0], 0, 0, 0, 0}; h < t; h++) {
    if (q[h].x == a[1]) {
      cout << q[h].s << '\n';
      Print(h);
      break;
    }
    for (int i = 0; i < 15; i++) {
      int x = q[h].x >> i & 1, y = q[h].x >> i + 1 & 1, z = q[h].x >> i + 4 & 1;
      if (i % 4 != 3) {
        int c = q[h].x ^ x << i ^ y << i + 1 ^ y << i ^ x << i + 1;
        if (!b[c]) {
          b[c] = 1, q[t++] = {c, q[h].s + 1, i, i + 1, h};
        }
      }
      if (i < 12) {
        int c = q[h].x ^ x << i ^ z << i + 4 ^ z << i ^ x << i + 4;
        if (!b[c]) {
          b[c] = 1, q[t++] = {c, q[h].s + 1, i, i + 4, h};
        }
      }
    }
  }
  return 0;
}
