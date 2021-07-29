#include <conio.h>
#include <windows.h>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

const int kMove[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int n, x, y, k, a[101][101];
bool b[101][101], _b[101][101];

void SetColor(int ForgC, int BackC) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((BackC & 0x0F) << 4) + (ForgC & 0x0F));
}

void PrintS(string s) {
  for (int i = 0; i < s.length(); i++) {
    cout << s[i];
    Sleep(50);
  }
}

void HideMouse() {
  CONSOLE_CURSOR_INFO cursor_info = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Bfs(int _x, int _y) {
  struct A {
    int x, y;
  };
  queue<A> q;
  for (q.push({_x, _y}); !q.empty(); q.pop()) {
    A c = q.front();
    if (c.x < 1 || c.y < 1 || c.x > x || c.y > y || b[c.x][c.y] || _b[c.x][c.y]) {
      continue;
    }
    b[c.x][c.y] = 1, k--;
    if (!a[c.x][c.y]) {
      for (int i = 0; i <= 7; i++) {
        q.push({c.x + kMove[i][0], c.y + kMove[i][1]});
      }
    }
  }
}

bool Print(bool c) {
  bool flag = 0;
  SetColor(11, 0);
  for (int i = 0; i <= y; i++) {
    cout << setw(3) << i;
  }
  for (int i = 1; i <= x; i++) {
    cout << "\n";
    SetColor(11, 0);
    cout << setw(3) << i;
    for (int j = 1; j <= y; j++) {
      if (_b[i][j] && !c) {
        SetColor(10, 0);
        cout << setw(3) << "*";
      } else if (b[i][j]) {
        if (a[i][j] == 9) {
          SetColor(12, 0);
          cout << setw(3) << "#";
          flag = 1;
        } else {
          SetColor(a[i][j] ? a[i][j] : 9, 0);
          cout << setw(3) << a[i][j];
        }
      } else {
        SetColor(11, 0);
        cout << setw(3) << ".";
      }
    }
  }
  cout << "\n\n";
  SetColor(11, 0);
  return flag;
}

void Prepare() {
  system("cls");
  srand(time(0));
  SetColor(11, 0);
  PrintS("Welcome to the mining game by DengYufan!\nPlease input n.\nThe number of the mines.\n");
  cin >> n;
  PrintS("Please input x and y.\nThe size of the map.\n");
  cin >> x >> y;
  PrintS("Spawning the map...\n");
  Sleep(500);
  for (int i = 1, _x, _y; i <= n;) {
    _x = rand() % x + 1, _y = rand() % y + 1;
    if (a[_x][_y] != 9) {
      a[_x][_y] = 9;
      i++;
      for (int j = 0; j <= 7; j++) {
        if (a[_x + kMove[j][0]][_y + kMove[j][1]] != 9) {
          a[_x + kMove[j][0]][_y + kMove[j][1]]++;
        }
      }
    }
  }
  PrintS("Done!\nPress any key to continue...\n");
  getch();
  system("cls");
}

void Playing() {
  int _x, _y, c;
  k = x * y;
  bool flag = 0;
  while (k) {
    if (Print(0)) {
      PrintS("You have found some mines!\nGame over!\n");
      return;
    }
    PrintS("Please input command.\n");
    if (!flag && (flag = 1)) {
      PrintS("0/1/2/3 for mine/mark/quick mine/quick mark one place, x and y for the coordinate of the place.\n");
    }
    cin >> c >> _x >> _y;
    if (!c) {
      Bfs(_x, _y);
    } else if (c == 1 && !b[_x][_y]) {
      _b[_x][_y] ^= 1, k -= _b[_x][_y] ? 1 : -1;
    } else if (c == 2) {
      int d = 0;
      for (int i = 0; i <= 7; i++) {
        if (_x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
          d += _b[_x + kMove[i][0]][_y + kMove[i][1]];
        }
      }
      for (int i = 0; i <= 7; i++) {
        if (d == a[_x][_y] && b[_x][_y] && _x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
          Bfs(_x + kMove[i][0], _y + kMove[i][1]);
        }
      }
    } else if (c == 3) {
      int d = 0;
      for (int i = 0; i <= 7; i++) {
        if (_x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
          d += !b[_x + kMove[i][0]][_y + kMove[i][1]];
        }
      }
      for (int i = 0; i <= 7; i++) {
        if (d == a[_x][_y] && b[_x][_y] && !b[_x + kMove[i][0]][_y + kMove[i][1]] && _x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
          _b[_x + kMove[i][0]][_y + kMove[i][1]] = 1, k--;
        }
      }
    }
    system("cls");
  }
  SetColor(11, 0);
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      if (!_b[_x][_y] && a[_x][_y] == 9 || _b[_x][_y] && a[_x][_y] != 9) {
        PrintS("You have marked some wrong mines!\nGame over!\n");
        return;
      }
    }
  }
  PrintS("You have marked each mine!\nYou won the game!\n");
}

bool Ending() {
  bool flag;
  PrintS("Want to watch the map?\nYes = 1, No = 0\n");
  cin >> flag;
  system("cls");
  if (flag) {
    fill(&b[0][0], &b[100][100] + 1, 1);
    Print(1);
  }
  PrintS("Again?\nYes = 1, No = 0.\n");
  cin >> flag;
  system("cls");
  fill(&a[0][0], &a[100][100] + 1, 0);
  fill(&b[0][0], &b[100][100] + 1, 0);
  fill(&_b[0][0], &_b[100][100] + 1, 0);
  return flag;
}

int main() {
  HideMouse();
  system("title Mining");
  cin.tie(0), cout.tie(0);
  do {
    Prepare();
    Playing();
  } while (Ending());
  return 0;
}
