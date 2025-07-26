#include <stdlib.h>

#ifdef _WIN32
   #include <windows.h>
#else
   #include <sys/ioctl.h>
   #include <unistd.h>
#endif

void consoleClear(void)
{
   fflush(stdout);
   #ifdef _WIN32
      system("cls");
   #elif __linux__
      system("clear");
   #elif __APPLE__
      system("clear");
   #endif
}

struct ConsoleSize {
   unsigned int row, column;
};

struct ConsoleSize consoleGetSize(void)
{
   struct ConsoleSize size = {0, 0};
   #ifdef _WIN32
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      size.row = csbi.srWindow.Bottom - csbi.srWindow.To
p + 1;
      size.column = csbi.srWindow.Right - csbi.srWindow.Left + 1;
   #else
      struct winsize w;
      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
      size.row = w.ws_row;
      size.column = w.ws_col;
   #endif
   return size;
}
