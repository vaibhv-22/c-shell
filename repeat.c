#include "world.h"
int repeat_world(int n, char **args)
{
    if (n < 3)
    {
        printf("repeat: Incorrect number of arguments\n");
        return -1;
    }
    if(*args[1] < '1' || *args[1] > '9'){
        printf("Second argument is not a single-digit interger\n");
        return -1;
    }
    int count = atoi(args[1]);
    char newargs[1024];
    strcpy(newargs, "");
    for (int i = 2; i < n; i++)
    {
        strcat(newargs, args[i]);
        if (i != n - 1)
            strcat(newargs, " ");
    }

    while (count--)
    {
        int exitcode = exec_com(newargs);
    }
}