#include <conio.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kR = 10;
const int kC = 20;
bool b[kR][kC];

void SetColor(int ForgC, int BackC) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((BackC & 0x0F) << 4) + (ForgC & 0x0F));
}

void PrintS(string s) {
  for (int i = 0; i < s.length(); i++) {
    cout << s[i];
    Sleep(50);
  }
}

void HideMouse(void) {
  CONSOLE_CURSOR_INFO cursor_info = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Print() {
  for (int i = 0; i < kC + 2; i++) {
    cout << "_";
  }
  cout << endl;
  for (int i = 0; i < kR; i++) {
    cout << "|";
    for (int j = 0; j < kC; j++) {
      cout << (b[i][j] ? "O" : " ");
    }
    cout << "|" << endl;
  }
  cout << "|";
  for (int i = 1; i < kC + 1; i++) {
    cout << "_";
  }
  cout << "|" << endl;
}

void Prepare() {
  srand(time(0));
  fill(&b[0][0], &b[kR - 1][kC - 1] + 1, 0);
  system("cls");
  SetColor(11, 0);
  PrintS("Welcome to the Russia blocks game by DengYufan!\nPress any key to continue...\n");
  getch();
  Print();
}

void Playing() {
}

bool Ending() {
}

int main() {
  HideMouse();
  system("title Russia_blocks");
  cin.tie(0), cout.tie(0);
  do {
    Prepare();
    Playing();
  } while (Ending());
  return 0;
}
