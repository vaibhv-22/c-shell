#include "world.h"
int ls_world(int n, char **args)
{
    char cdpath[BUF_PWD];
    struct dirent *dp;
    DIR *dir;
    char items[BUF_PWD][BUF_PWD];
    int no_items = 0;
    if (n == 1)
    {
        set_ls();
    }
    else
    {
        for (int i = 1; i < n; i++)
        {
            printf("%s:\n", args[i]);
            cd_world_2(args[i]);
            set_ls();
        }
    }
    return 1;
}
int set_ls()
{
    char cdpath[BUF_PWD];
    struct dirent *dp;
    DIR *dir;
    char items[BUF_PWD][BUF_PWD];
    int no_items = 0;
    char tmp[BUF_PWD];
    dir = opendir(".");
    while ((dp = readdir(dir)) != NULL)
    {
        if ((dp->d_name[0] == '.' && flag_hash['a']) || dp->d_name[0] != '.')
        {
            strcpy(items[no_items], dp->d_name);
            no_items++;
        }
    }

    struct stat fileStat;
    struct passwd *pws;
    struct group *grp;
    int total = 0;
    for (int i = 0; i < no_items; i++)
    {
        if (flag_hash['l'])
        {
            if (stat(items[i], &fileStat) < 0)
                continue;
            total += fileStat.st_blocks;
        }
    }
    if (flag_hash['l'])
        printf("total: %d\n", total / 2);
    for (int i = 0; i < no_items; i++)
    {
        if (flag_hash['l'])
        {

            if (stat(items[i], &fileStat) < 0)
                continue;
            pws = getpwuid(fileStat.st_uid);
            grp = getgrgid(fileStat.st_gid);
            int x = fileStat.st_mode;
            // total+=filestat.st_blocks;
            if (S_ISDIR(x))
                printf("d");
            else
                printf("-");
            if (S_IRUSR & x)
                printf("r");
            else
                printf("-");
            if (S_IWUSR & x)
                printf("w");
            else
                printf("-");
            if (S_IXUSR & x)
                printf("x");
            else
                printf("-");
            if (S_IRGRP & x)
                printf("r");
            else
                printf("-");
            if (S_IWGRP & x)
                printf("w");
            else
                printf("-");
            if (S_IXGRP & x)
                printf("x");
            else
                printf("-");
            if (S_IROTH & x)
                printf("r");
            else
                printf("-");
            if (S_IWOTH & x)
                printf("w");
            else
                printf("-");
            if (S_IXOTH & x)
                printf("x");
            else
                printf("-");
            printf("%2ld%9s%9s%6ld %.12s %s\n", fileStat.st_nlink, pws->pw_name, grp->gr_name, fileStat.st_size, ctime(&fileStat.st_mtime) + 4, items[i]);
        }
        else
            printf("%s\n", items[i]);
    }
    chdir(pwd);
}