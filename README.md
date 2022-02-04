# *DengYufan's Blog*

## *Write In The First*
- Star Me If You Like. It's Free, And Will Make Me Happy For A Long Time.

## *Important Time*
- Start Coding : 2019.8.16
- Sign Up In Luogu : 2019.9.15
- Orange Name In Luogu : 2021.10.21
- CSP Jenior Second Prize : 2020
- CSP Jenior First Prize : 2021
- CSP Senior Second Prize : 2021
- Still Updating

## *Accounts*
- Luogu : dengyufan
- USACO : dengyuf1
- Codeforces : dengyufan
- Atcoder : dengyufan2008
- Github : dengyufan2008
- Focus On Me If You Like

## *Websites*
- [Luogu](http://www.luogu.com.cn)
- [USACO](https://train.usaco.org)
- [Codeforces](https://codeforces.com)
- [AtCoder](https://atcoder.jp)
- [C++Info](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)
- [Github](https://github.com)
- Still Updating

## *Economic Things*
- C++14 Compile : g++ -std=c++14 -Wl, --stack=0x10000000 -o code.cpp code.exe
- Still Updating

## *Code*
*Quick Read For Integer*
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
*Quick Print For Integer*
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

## *Last Update : 2022.2.04*
