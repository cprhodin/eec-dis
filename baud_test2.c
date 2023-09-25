#include <stdio.h>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("%s device speed\n\nSet speed for a serial device.\nFor instance:\n    %s /dev/ttyUSB0 250000\n", argv[0], argv[0]);
        return -1;
    }

    return 0;
}
