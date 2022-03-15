#include "world.h"
int sig_world(int n, char **args){
    struct Job* temp;
    int jobno = 0; 
    // printf("HERElol\n");
    if(n != 3){
        printf("sig: Incorrect number of arguments\n");
        return 0;
    }
    int len = strlen(args[1]); 
    for (int i = 0; i < len; i++) 
          jobno = jobno * 10 + (int)args[1][i] - 48; 
    int sig = 0; 
    // jobno--;
    int len2 = strlen(args[2]); 
    for (int i = 0; i < len2; i++) 
          sig = sig * 10 + (int)args[2][i] - 48; 
    temp = nth_node(jobno);
    if(temp == NULL){
        printf("sig: No such job exists\n");
        return 1;
    }
    // fpid = temp->pid;
    if(kill(temp->pid, sig) < 0){
        perror("");
        return 0;
    }
    return 1;
}