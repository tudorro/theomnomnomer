#include <windows.h>
#include <conio.h>

/* Move the cursor to X and Y */
void GotoXY(int x, int y);

/* Hides the cursor */
void hideCursor();

/* Show the cursor */
void showCursor();

/* Wipe screen */
void clearScreen();

/* Show a char at X and Y */
void putChar( int x, int y, char ch );

/* Show a string at X and Y */
void putStr( int x, int y, char *s );

/*
#define FOREGROUND_BLUE	1
#define FOREGROUND_GREEN	2
#define FOREGROUND_RED	4
#define FOREGROUND_INTENSITY	8
#define BACKGROUND_BLUE	16
#define BACKGROUND_GREEN	32
#define BACKGROUND_RED	64
#define BACKGROUND_INTENSITY	128
#define ENABLE_ECHO_INPUT 4
*/
enum COLOR {
         BLACK      = 0,
         GREY       = FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED,
         WHITE      = FOREGROUND_INTENSITY+GREY,
  INTENS_BLUE       = FOREGROUND_INTENSITY+FOREGROUND_BLUE,
  INTENS_GREEN      = FOREGROUND_INTENSITY+FOREGROUND_GREEN,
  INTENS_RED        = FOREGROUND_INTENSITY+FOREGROUND_RED,
         CYAN       = FOREGROUND_BLUE+FOREGROUND_GREEN,
  INTENS_CYAN       = FOREGROUND_INTENSITY+CYAN,
         MAGENTA    = FOREGROUND_RED+FOREGROUND_BLUE,
  INTENS_MAGENTA    = FOREGROUND_INTENSITY+MAGENTA,
         YELLOW     = FOREGROUND_RED+FOREGROUND_GREEN,
  INTENS_YELLOW     = FOREGROUND_INTENSITY+YELLOW,
         BG_BLACK   = 0,
         BG_GREY    = BACKGROUND_BLUE+BACKGROUND_GREEN+BACKGROUND_RED,
         BG_WHITE   = BACKGROUND_INTENSITY+BG_GREY,
  BG_INTENS_BLUE    = BACKGROUND_INTENSITY+BACKGROUND_BLUE,
  BG_INTENS_GREEN   = BACKGROUND_INTENSITY+BACKGROUND_GREEN,
  BG_INTENS_RED     = BACKGROUND_INTENSITY+BACKGROUND_RED,
         BG_CYAN    = BACKGROUND_BLUE+BACKGROUND_GREEN,
  BG_INTENS_CYAN    = BACKGROUND_INTENSITY+BG_CYAN,
         BG_MAGENTA = BACKGROUND_RED+BACKGROUND_BLUE,
  BG_INTENS_MAGENTA = BACKGROUND_INTENSITY+BG_MAGENTA,
         BG_YELLOW  = BACKGROUND_RED+BACKGROUND_GREEN,
  BG_INTENS_YELLOW  = BACKGROUND_INTENSITY+BG_YELLOW
};
/*
  Change the text color. Example:
  - setTextColor( BG_INTENS_YELLOW + INTENS_BLUE );
  will change to Intense Yellow background and intense blue text
*/
void setTextColor( int color );

/*
  Return 1 if the "key" key is pressed or 0 if not.
  "Key" can be
  VK_ESCAPE  - Esc
  VK_SHIFT   - Shift
  VK_CONTROL - Ctrl
  VK_MENU    - Alt
  VK_F1      - F1 (Works with other Fs)
  VK_UP      - up arrow
  VK_DOWN    - down arrow
  VK_LEFT    - left arrow
  VK_RIGHT   - right arrow
  and the keys from extraKeys.h
 */
int getKey( int key );
