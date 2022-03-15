#include "world.h"
int echo_world(int n, char **args)
{
    for (int i = 1; i < n; i++){
        printf("%s", tokens[i]);
        if(i!=n-1) printf(" ");
    }
    printf("\n");
    return 1;
}