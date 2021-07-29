#include <conio.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kR = 10;
const int kC = 20;
const int kM[7][2] = {{1, 4}, {2, 3}, {2, 3}, {2, 3}, {2, 2}, {2, 3}, {2, 3}};
const int kD[7][4][4] = {{{15, 0, 0, 0}, {2, 2, 2, 2}, {15, 0, 0, 0}, {2, 2, 2, 2}}, {{4, 14, 0, 0}, {4, 6, 4, 0}, {0, 14, 4, 0}, {4, 12, 4, 0}}, {{12, 4, 4, 0}, {0, 2, 14, 0}, {4, 4, 6, 0}, {0, 14, 8, 0}}, {{6, 4, 4, 0}, {0, 14, 2, 0}, {4, 4, 12, 0}, {0, 8, 14, 0}}, {{12, 12, 0, 0}, {12, 12, 0, 0}, {12, 12, 0, 0}, {12, 12, 0, 0}}, {{6, 12, 0, 0}, {4, 6, 2, 0}, {6, 12, 0, 0}, {4, 6, 2, 0}}, {{12, 6, 0, 0}, {2, 6, 4, 0}, {12, 6, 0, 0}, {2, 6, 4, 0}}};
int s;
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
  system("cls");
}

void Playing() {
  int mxh = -1;
  while (mxh < kR) {
    int c = rand() % 7, d = 0, x = 0, y = kC >> 1;
    while (!b[x + kM[c][d & 1]][y] && (kM[c][!(d & 1)] < 2 || !b[x + kM[c][d & 1]][y + 1]) && (kM[c][!(d & 1)] < 3 || !b[x + kM[c][d & 1]][y + 2]) && (kM[c][!(d & 1)] < 4 || !b[x + kM[c][d & 1]][y + 3])) {
      // Waiting for finishing
    }
  }
}

bool Ending() {
  bool flag;
  system("cls");
  PrintS("Game over!\nYour score is ");
  if (!s) {
    cout << 0;
    Sleep(50);
  }
  while (s) {
    cout << s % 10;
    Sleep(50);
  }
  PrintS(".\nAgain?\nYes = 1, No = 0\n");
  cin >> flag;
  system("cls");
  return flag;
}

int main() {
  HideMouse();
  system("title Russia blocks");
  cin.tie(0), cout.tie(0);
  do {
    Prepare();
    Playing();
  } while (Ending());
  return 0;
}
