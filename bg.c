#include "world.h"

int bg_world(int n, char** args){

    if(n != 2){
        printf("bg: Incorrect number of arguments\n");
        return 0;
    }
    int jobno = atoi(args[1]);
    // printf("%d %d\n",jobno , no_jobs);
    if(jobno > no_jobs){
        printf("bg: No such job exists\n");
        return 0;
    }
    struct Job* temp = nth_node(jobno);
    kill(temp->pid, SIGCONT);
    return 1;
}