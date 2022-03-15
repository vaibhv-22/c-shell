#include "world.h"

int replay_world(int n,char ** args){
    int p = atoi(args[n-2]);
    int q = atoi(args[n-1]);
    printf("%d %d\n",p,q);
    char * cmdo;
    // strcat(cmdo,"");
    for(int i=0; i<n;i++){
        // strcat(cmdo,args[i]);
        // strcat(cmdo," ");
        printf("->%s\n",args[i]);
    }
    // printf("%s\n",cmdo);
    for(int i = 0; i < q/p; i++){
        // sleep(p);
        // execute_program(p,args);
        // printf("\n");
        // init_cmd(cmdo);
    }
    // sleep(q%p);
    return 1;
}