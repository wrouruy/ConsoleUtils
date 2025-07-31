## How to Use the Utils?
1. Download the ``` ConsoleUtils.h ``` file
2. Connect downloaded file to the desired: ``` #include "ConsoleUtils.h" ```

## Table of Functions:
| Name                           | Descriptions                                  |
|--------------------------------|-----------------------------------------------|
| consoleClear(void)             | A function that clears the console            |
| consoleArray(array, format)    | Prints the specified array to the console     |
| consoleGetSize(void)           | Takes number of row and column of the console |
| consoleGetCh(void)             | Takes one char symbol written in the console  |
| consoleGetStr(address, length) | Takes a line written in the console           |
| consoleGetInt(max)             | Takes a int written in the console            |

For Example:
```
#include <stdio.h>
#include "ConsoleUtils.h"

int main(void)
{
    consoleClear(); // clear a console

    // print array
    int arr0[] = { 10, 25, 50 };
    consoleArray(arr0, "%d");    // output: { 10, 25, 50 }
    char arr1[2][6] = { "hello", "world!" }; 
    consoleArray(arr1, "%s");    // output: { "hello", "world!" }
    
    // get console size
    struct ConsoleSize size = consoleGetSize();
    printf("row: %d, column: %d\n", size.row, size.column);

    // get char symbol and line from the console
    printf("%c\n", consoleGetCh());

    char var[64];
    consoleGetStr(var, sizeof(var));

    printf("\n");

    return 0;
}
```

Thank you for reading!