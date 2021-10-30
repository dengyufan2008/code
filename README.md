# *DengYufan's Blog*

## *Writed in the First*
- Nothing is better than fail, and nothing is better than success.
- The mother of success is to be hard-working.

## *Important Time*
- Start Coding : 2019.8.16
- Registing in Luogu : 2019.9.15
- Gold Name in Luogu : 2021.10.21
- CSP Jenior Second Grade : 2020
- CSP Jenior First Grade : 2021
- CSP Senior Second Grade : 2021
- Still Updating

## *Accounts*
- Luogu : dengyufan
- USACO : dengyuf1
- Codeforces : dengyufan
- Atcoder : dengyufan2008
- Github : dengyufan2008
- Focus on me if you like

## *Websites*
- [Luogu](http://www.luogu.com.cn)
- [USACO](https://train.usaco.org)
- [Codeforces](https://codeforces.com)
- [AtCoder](https://atcoder.jp)
- [C++Info](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)
- [Github](https://github.com)
- Still Updating

## *Economic Things*
- C++14 Compile : g++ -std=c++14 -Wl, --stack=0x10000000 -o code.exe code.exe
- Still Updating

## *Code*
*Quick Read for integer*
```c++
int Read() {
  int f(1), x(0);
  char ch(getchar());
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch > '/' && ch < ':') {
    x = (x << 3) + (x << 1) + (ch - '0');
    ch = getchar();
  }
  return f * x;
}
```
*Quick Print for integer*
```c++
void Print(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) {
    Print(x / 10);
  }
  putchar(x % 10 + 48);
}
```
*Runtime*
```c++
#include <ctime>

cout << "Runtime:" << clock() / 1000.0 << "s\n";
```
*Still Updating*

- - - - - -

Last Update : 2021.10.23
