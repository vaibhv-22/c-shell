#include "world.h"
int pinfo_world(int n, char **args)
{

    char pinfo_path[BUF_PWD];
    char p_path[BUF_PWD];
    char status, expath[BUF_PWD], pname[BUF_PWD];
    int pid, mem = 0;
    int len = 0;
    if (n >= 2)
        sprintf(p_path, "/proc/%s/", args[1]);
    else
    {
        char tmp[1024] = "/proc/self/";
        strcpy(pinfo_path, "");
        int j = 0;
        for (; tmp[j] != '\0'; ++j)
            p_path[j] = tmp[j];
        p_path[j] = '\0';
    }

    strcpy(pinfo_path, p_path);
    strcat(pinfo_path, "stat");

    FILE *stat = fopen(pinfo_path, "r");
    if (stat == NULL)
    {
        perror("statfile Error:");
        return 0;
    }
    fscanf(stat, "%d %s %c", &pid, pname, &status);
    fclose(stat);

    strcat(pinfo_path, "m");

    FILE *statm = fopen(pinfo_path, "r");
    if (statm == NULL)
    {
        perror("statfile Error:");
        return 0;
    }
    fscanf(statm, "%d", &mem);
    fclose(statm);

    strcpy(pinfo_path, p_path);
    strcat(pinfo_path, "exe");

    int sz = sizeof(expath);
    readlink(pinfo_path, expath, sz);
    torelative(expath);
    if (strlen(expath) >= strlen(home) && strncmp(expath, home, strlen(home)) == 0)
        sprintf(expath, "~%s", expath + strlen(home));
    char tmp1 = 'R';
    char tmp2 = 'S';
    // printf("%d\n", pid);
    if (n == 1)
    {
        if (status == tmp1 || status == tmp2)
        {
            printf("pid -> %d\nStatus -> %c+\nMemory -> %d\nExecutable Path -> %s\n", pid, status, mem, expath);
            return 1;
        }
    }
    printf("pid -> %d\nStatus -> %c\nMemory -> %d\nExecutable Path -> %s\n", pid, status, mem, expath);
    return 1;
}