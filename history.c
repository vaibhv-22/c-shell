#include "world.h"
void exhis()
{
    FILE *histfile;
    histfile = fopen(his_path, "wb");
    fwrite(&his, sizeof(struct hist), 1, histfile);
    fclose(histfile);
    exit(0);
}
void addhis(char *cmd)
{
    if(strcmp(his.history[(his.histins + 19 )% 20],cmd) ==0) return;
    strcpy(his.history[his.histins % 20], cmd);
    his.histins++;
}
void inithist()
{
    char currentdir[1024];
    char temp[15];
    getcwd(currentdir, sizeof(currentdir));
    strcat(currentdir, "/history.txt");
    strcpy(his_path, currentdir);
    FILE *hfile;
    hfile = fopen(his_path, "rb");
    if (hfile == NULL)
    {
        his.histins = 0;
        his.histed = 0;
    }
    else
    {
        fread(&his, sizeof(struct hist), 1, hfile);
        fclose(hfile);
    }
}
int history_world(int n, char **args)
{
    int hist = 0;
    if (n == 1)
    {
        hist = 10;
    }
    else
    {
        hist = atoi(args[1]);
    }
    for (int i = hist; i > 0; i--)
    {
        int k = his.histins - i;
        k = (k + 20) % 20;
        int len2 = strlen(his.history[k]);
        if (his.history[k] != NULL && len2 != 0)
            printf("%s\n", his.history[k]);
    }
    return 1;
}