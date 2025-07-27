## How to Use the Utils?
1. Download the ``` ConsoleUtils.h ``` file
2. Connect downloaded file to the desired: ``` #include "ConsoleUtils.h" ```

For Example:
```
#include "ConsoleUtils.h"

int main(void)
{
    consoleClear(); // clear a console

    // get console size
    struct ConsoleSize size = consoleGetSize();
    printf("row: %d, column: %d", size.row, size.column)
    return 0;
}
```
