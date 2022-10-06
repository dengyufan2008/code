#include <bits/stdc++.h>
#include <conio.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

string path, opt;
class FUNCTION {
 private:
  char SmallWrite(char ch) {
    return ch >= 'A' && ch <= 'Z' ? ch + 32 : ch;
  }

 public:
  void HideMouse() {  // Not Recently Used
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
  }

  void SetColor(int ForgC, int BackC) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((BackC & 0x0F) << 4) + (ForgC & 0x0F));
  }

  pair<int, int> Read(int x) {
    int t = -1;
    for (; x < opt.size() && (opt[x] < '0' || opt[x] > '9'); x++) {
    }
    for (; x < opt.size() && opt[x] >= '0' && opt[x] <= '9'; x++) {
      t = max(t, 0) * 10 + opt[x] - '0';
    }
    return {t, x};
  }

  bool Chick(string s, int x = 0) {
    for (; opt[x] == ' '; x++) {
    }
    if (opt.size() - x < s.size()) {
      return 0;
    }
    for (int i = 0; i < s.size(); i++) {
      if (SmallWrite(s[i]) != SmallWrite(opt[i + x])) {
        return 0;
      }
    }
    return 1;
  }
} func;
class HELP {
 public:
  void Main() {
    // if (func.Chick("snake", 5)) {
    //   ;
    // } else if (func.Chick("tetris", 5)) {
    //   ;
    // } else
    if (func.Chick("minesweeper", 5)) {
      cout << "MINESWEEPER line col mine\n\n  line  The Number Of Lines.\n  col   The Number Of Columns.\n  mine  The Number Of Mines.\n";
    } else {
      if (opt.size() > 4) {
        cout << "I Think That You Mean \"help\".\n";
      }
      cout << "For More Information On A Specific Command, Type \"HELP COMMAND-NAME\".\n[0]  HELP         Check Out Command List.\n[1]  EXIT         Exit The Program.\n[2]  SNAKE        Try Finding Out All Mines!\n                  Wait For Designer To Play It!\n[3]  TETRIS       Keep Survive To Get Longer!\n                  Wait For Designer To Play It!\n[4]  MINESWEEPER  Clear Blocks As Much As You Can!\n                  Now Available!\n";
    }
  }
} help;
class MINESWEEPER {
 private:
  const int kMove[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
  int n, x, y, k, a[101][101];
  bool b[101][101], _b[101][101];

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
    func.SetColor(11, 0);
    for (int i = 0; i <= y; i++) {
      cout << setw(3) << i;
    }
    for (int i = 1; i <= x; i++) {
      cout << "\n";
      func.SetColor(11, 0);
      cout << setw(3) << i;
      for (int j = 1; j <= y; j++) {
        if (_b[i][j] && !c) {
          func.SetColor(10, 0);
          cout << setw(3) << "*";
        } else if (b[i][j]) {
          if (a[i][j] == 9) {
            func.SetColor(12, 0);
            cout << setw(3) << "#";
            flag = 1;
          } else {
            func.SetColor(a[i][j] ? a[i][j] : 9, 0);
            cout << setw(3) << a[i][j];
          }
        } else {
          func.SetColor(11, 0);
          cout << setw(3) << ".";
        }
      }
    }
    cout << "\n\n";
    func.SetColor(11, 0);
    return flag;
  }

  void Prepare() {
    system("cls");
    func.SetColor(11, 0);
    cout << "Spawning The Map...\n";
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
    cout << "Done!\nPress Any Key To Continue...\n";
    getch();
    system("cls");
  }

  void Playing() {
    int _x, _y, c;
    k = x * y;
    bool flag = 0;
    while (k) {
      if (Print(0)) {
        cout << "You Have Found Some Mines!\nGame Over!\n";
        return;
      }
      cout << "Please Input Command.\n0/1/2/3 For Mine/Mark/Quick Mine/Quick Mark One Place, x And y For The Coordinate Of The Place.\n";
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
    if (Print(0)) {
      cout << "You Have Found Some Mines!\nGame Over!\n";
      return;
    }
    func.SetColor(11, 0);
    for (int i = 1; i <= x; i++) {
      for (int j = 1; j <= y; j++) {
        if (!_b[_x][_y] && a[_x][_y] == 9 || _b[_x][_y] && a[_x][_y] != 9) {
          cout << "You Have Marked Some Wrong Mines!\nGame Over!\n";
          return;
        }
      }
    }
    cout << "You Have Marked Each Mine!\nYou Won The Game!\n";
  }

  void Ending() {
    bool flag;
    cout << "Want To Watch The Map?\nYes = 1, No = 0\n";
    cin >> flag;
    if (flag) {
      system("cls");
      fill(&b[0][0], &b[100][100] + 1, 1);
      Print(1);
      cout << "Press Any Key To Continue...\n";
      getch();
    }
    getchar();
    system("cls");
    cout << "LunarPursuer Gameset [Version 10.0.22621.608]\n(c) Seek Lunar Corporation. All Rights Reserved.\n";
    fill(&a[0][0], &a[100][100] + 1, 0);
    fill(&b[0][0], &b[100][100] + 1, 0);
    fill(&_b[0][0], &_b[100][100] + 1, 0);
  }

 public:
  void Main() {
    pair<int, int> p;
    p = func.Read(p.second);
    if ((x = p.first) == -1) {
      cout << "Incorrect Command!\nType \"help minesweeper\" To Check Out Regular.\n";
      return;
    }
    p = func.Read(p.second);
    if ((y = p.first) == -1) {
      cout << "Incorrect Command!\nType \"help minesweeper\" To Check Out Regular.\n";
      return;
    }
    p = func.Read(p.second);
    if ((n = p.first) == -1) {
      cout << "Incorrect Command!\nType \"help minesweeper\" To Check Out Regular.\n";
      return;
    }
    Prepare();
    Playing();
    Ending();
  }
} minesweeper;

int main() {
  system("title Gameset");
  system("cls");
  srand(time(0));
  cin.tie(0), cout.tie(0);
  path = string(getcwd(NULL, 0));
  func.SetColor(11, 0);
  cout << "LunarPursuer Gameset [Version 10.0.22621.608]\n(c) Seek Lunar Corporation. All Rights Reserved.\n";
  while (1) {
    cout << "\n" + path + "> ";
    getline(cin, opt);
    if (opt != "") {
      cout << '\n';
      if (func.Chick("help")) {
        help.Main();
      } else if (func.Chick("exit")) {
        break;
      }
      //  else if (func.Chick("snake")) {
      //    ;
      //  } else if (func.Chick("tetris")) {
      //    ;
      //  }
      else if (func.Chick("minesweeper")) {
        minesweeper.Main();
      } else {
        cout << "Incorrect Command!\nType \"help\" To Check Out Command List.\n";
      }
    }
  }
  cout << "Press Any Key To Continue...\n";
  getch();
  return 0;
}
/*
Game List:
Snake
Tetris
*/
