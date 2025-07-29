## How to Use the Utils?
1. Download the ``` ConsoleUtils.h ``` file
2. Connect downloaded file to the desired: ``` #include "ConsoleUtils.h" ```

## Table of Functions:
| Name                        | Descriptions                                  |
|-----------------------------|-----------------------------------------------|
| consoleClear(void)          | A function that clears the console            |
| consoleArray(array, format) | prints the specified array to the console     |
| consoleGetSize(void)        | takes number of row and column of the console |

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

    return 0;
}
```

Thank you for reading!