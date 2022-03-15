#include "world.h"

int cd_world(int n, char **args)
{
    char cdpath[BUF_PWD];
    if (n == 1)
        strcpy(cdpath, home);
    else if (n > 2)
    {
        printf("cd: too many arguments\n");
        return 1;
    }
    else if (args[1][0] == '~')
        strcpy(cdpath, home);
    else
        strcpy(cdpath, args[1]);
    if (chdir(cdpath) < 0)
        perror("cd Error");
    return 1;
}

int cd_world_2(char *args)
{
    char cdpath[BUF_PWD];
    strcpy(cdpath, args);
    if (strcmp(cdpath, "~") == 0)
        strcpy(cdpath, home);
    if (chdir(cdpath) < 0)
        perror("cd Error");
    return 1;
}