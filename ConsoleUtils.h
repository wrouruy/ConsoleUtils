#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <termios.h>
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

void consoleBool(bool boolean)
{
    printf("%s\n", boolean ? "true" : "false");
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

char consoleGetCh(void)
{
    #ifdef _WIN32
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;

        // Disable buffering
        GetConsoleMode(hInput, &mode);
        SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

        INPUT_RECORD input;
        DWORD read;

        unsigned char result;        
        while(1) {
            ReadConsoleInput(hInput, &input, 1, &read);
            if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
                result = input.Event.KeyEvent.uChar.AsciiChar;
                break;
            }
        }

        SetConsoleMode(hInput, mode);
        return result;
    #else
        struct termios old_tio, new_tio;
        unsigned char result;

        // save current settings of terminal
        tcgetattr(STDIN_FILENO, &old_tio);

        // set new settings
        new_tio = old_tio;
        new_tio.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

        // read symbol
        result = getchar();

        // fix settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

        return result;
    #endif
}

void consoleGetStr(char *address, unsigned int length)
{
    unsigned int i = 0;
    char ch;

    while (i < length - 1) {
        ch = consoleGetCh();
        if (ch == '\n') break;

        address[i++] = ch;
        printf("%c", ch);
    }
    address[i] = '\0';
}

int getDigitCount(int max) {
    int digits = 1;
    while (max >= 10) {
        max /= 10;
        digits++;
    }
    return digits;
}
int consoleGetInt(int max)
{
    char result[getDigitCount(max) + 1];
    char resultPlusCh[getDigitCount(max) + 2];
    char ch;
    int i = 0;

    result[0] = '\0';

    while (true) {
        ch = consoleGetCh();
        snprintf(resultPlusCh, sizeof(resultPlusCh), "%s%c", result, ch);

        if (ch == '\n') break;

        if (!(ch >= '0' && ch <= '9') || atoi(resultPlusCh) > max) {
            continue;
        }

        result[i++] = ch;
        result[i] = '\0';

        printf("%c", ch);
    }

    return atoi(result);
}