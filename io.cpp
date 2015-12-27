
#include "io.hpp"

using namespace std;

struct termios t;

void off(void)
{
  tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
  t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
  tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

void on(void)
{
  tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
  t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
  tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

bool echo( bool on = true )
{
  struct termios settings;

  if (tcgetattr( STDIN_FILENO, &settings )) return false;

  if (on) settings.c_lflag |= ECHO;
  else    settings.c_lflag &= ~(ECHO);

  return 0 == tcsetattr( STDIN_FILENO, TCSANOW, &settings );
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void startIo()
{
  off();
  echo(false);
}

void endIo()
{
  on();
  echo(true);
}

bool hasKey()
{
  return kbhit();
}

Key getKey()
{
  char ch = getchar();
  if (ch == '\033') { // if the first value is esc
    getchar(); // skip the [
    switch(getchar()) { // the real value
    case 'A':
      return {.type = Arrow, .arrowKey = Up};
    case 'B':
      return {.type = Arrow, .arrowKey = Down};
    case 'C':
      return {.type = Arrow, .arrowKey = Left};
    case 'D':
      return {.type = Arrow, .arrowKey = Right};
    default:
      return {.type = Unknown};
    }
  }else{
    return {.type = Char,.ch = ch};
  }
}
