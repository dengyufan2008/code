#include <windows.h>

#include <iostream>

#include "game.h"

typedef __int128_t LLL;

using namespace std;

Game game;

void PrintChar(int i, int play_round, LLL alice_chess, LLL bob_chess, LLL magic, LLL attack_chess) {
  if ((alice_chess | bob_chess) >> i & 1) {
    if (alice_chess >> i & 1) {  // red
      if (magic >> i & 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                BACKGROUND_INTENSITY | BACKGROUND_RED);
      } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED);
      }
    } else {  // blue
      if (magic >> i & 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                BACKGROUND_INTENSITY | BACKGROUND_BLUE);
      } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_BLUE);
      }
    }
    cout << 'o';
  } else if (attack_chess >> i & 1) {
    if (play_round & 1) {  // red
      if (magic >> i & 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                BACKGROUND_INTENSITY | BACKGROUND_RED);
      } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED);
      }
    } else {  // blue
      if (magic >> i & 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                BACKGROUND_INTENSITY | BACKGROUND_BLUE);
      } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_BLUE);
      }
    }
    cout << 'x';
  } else {  // white
    if (magic >> i & 1) {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                              BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    } else {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                              FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    cout << '.';
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Print(int play_round,
           int alice_life, int bob_life,
           LLL alice_chess, LLL bob_chess,
           LLL magic, LLL attack_chess,
           int lastcoor) {
  system("cls"), cout << "   ";
  for (int i = 0; i + 1 < 9; i++) {
    cout << i << "  ";
  }
  cout << "8\n";
  for (int i = 0; i < lastcoor - lastcoor % 9 + 9; i++) {
    if (!(i % 9)) {
      cout << i / 9 << "  ";
    }
    PrintChar(i, play_round, alice_chess, bob_chess, magic, attack_chess);
    if (i % 9 < 8) {
      cout << "  ";
    } else if (i / 9 < lastcoor / 9) {
      cout << "\n\n";
    } else {
      cout << '\n';
    }
  }
  if (lastcoor >= 0 && lastcoor < 9 * 9) {
    for (int i = 0; i < lastcoor % 9; i++) {
      cout << "   ";
    }
    cout << "   ^\n";
  } else {
    cout << '\n';
  }
  for (int i = lastcoor - lastcoor % 9 + 9; i < 9 * 9; i++) {
    if (!(i % 9)) {
      cout << i / 9 << "  ";
    }
    PrintChar(i, play_round, alice_chess, bob_chess, magic, attack_chess);
    if (i % 9 < 8) {
      cout << "  ";
    } else {
      cout << "\n\n";
    }
  }
  cout << "Alice Life:" << alice_life << "  Bob Life:" << bob_life << '\n';
}

int main() {
  game.Init(), Print(0, 6, 6, 0, 0, 0, 0, -1);
  for (int play_round = 1;; play_round++) {
    static int coor_x, coor_y, alice_life, bob_life;
    static LLL alice_chess, bob_chess, magic, attack_chess;
    for (int tmp = -1; tmp == -1;) {
      cout << (play_round & 1 ? "Alice" : "Bob") << ", Take Your Turn: ";
      cin >> coor_x >> coor_y;
      tmp = game.Operate(coor_x, coor_y);
    }
    int coor = coor_x * 9 + coor_y;
    game.Status(alice_life, bob_life, alice_chess, bob_chess, magic, attack_chess);
    Print(play_round, alice_life, bob_life, alice_chess, bob_chess, magic, attack_chess, coor);
    if (alice_life <= 0 || bob_life <= 0) {
      cout << "Congratulations, " << (play_round & 1 ? "Alice" : "Bob") << "!\n";
      break;
    }
  }
  return 0;
}
