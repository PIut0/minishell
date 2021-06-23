#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (execve("/usr/bin/env", argv, NULL) < 0)
        printf("ERROR\n");
    // if (execve("/bin/ls", argv, NULL) < 0)
    //     printf("ERROR\n");
}