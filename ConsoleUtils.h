#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

#define consoleArray(arr, format) do { \
    size_t _len = sizeof(arr) / sizeof((arr)[0]); \
    char mark = 0; \
    if (strcmp(format, "%c") == 0) mark = '\''; \
    else if (strcmp(format, "%s") == 0) mark = '\"'; \
    \
    printf("{ "); \
    for (size_t _i = 0; _i < _len; _i++) \
        printf("%c" format "%c%s", mark, (arr)[_i], mark, _i == _len - 1 ? " " : ", "); \
    printf("}\n"); \
} while (0)

struct ConsoleSize {
    unsigned int row, column;
};

struct ConsoleSize consoleGetSize(void)
{
    struct ConsoleSize size = {0, 0};
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        size.row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        size.column = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        size.row = w.ws_row;
        size.column = w.ws_col;
    #endif
    return size;
}