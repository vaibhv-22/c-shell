#include "world.h"
int fg_world(int n,char **args)
{    
    if(n != 2){
        printf("fg: Incorrect number of arguments\n");
        return 0;
    }
    int jobno = atoi(args[1]);
    struct Job* temp = nth_node(jobno);
    if(jobno > no_jobs){
        printf("fg: No such job exists\n");
        return 1;
    }
    signal(SIGCHLD, SIG_IGN);
    kill(temp->pid, SIGCONT);
    fpid = temp->pid; 
    int status;
    struct Job j = *temp;
    delJob(fpid);
    waitpid(j.pid, &status, WUNTRACED);
    fpid = 0;
    if(WIFSTOPPED(status))
        appendJob(j.pid,j.command);
    //signal(SIGCHLD, handler);
    return 1;
}