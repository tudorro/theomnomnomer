#include <stdlib.h>
#include "textutil.h"

void GotoXY(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
  HANDLE hOut;
  CONSOLE_CURSOR_INFO ConCurInf;

  hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  ConCurInf.dwSize = 10;
  ConCurInf.bVisible = FALSE;

  SetConsoleCursorInfo(hOut, &ConCurInf);
}

void showCursor(){
  HANDLE hOut;
  CONSOLE_CURSOR_INFO ConCurInf;

  hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  ConCurInf.dwSize = 10;
  ConCurInf.bVisible = TRUE;

  SetConsoleCursorInfo(hOut, &ConCurInf);
}

void putChar( int x, int y, char ch ) {
  GotoXY(x, y);
  _putch(ch);
}

void putStr( int x, int y, char *s ) {
  GotoXY(x, y);
  _cprintf(s);
}

int getKey( int key ) {
  return (GetAsyncKeyState(key) & 0x8000) > 0;
}

void setTextColor( int color ) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
  system("cls");
}
