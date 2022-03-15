#include "world.h"
int redirect(int n, char** args){
    // for(int i=0; i<n;i++){
    //     printf("%d = %s\n",i,args[i]);
    // }
    int out = -1, in = -1, append = -1;
    for(int i=0;i<n;i++){
        if(!strcmp(args[i], ">"))
            out = i;
        if(!strcmp(args[i], ">>"))
            append = i;
        if(!strcmp(args[i], "<"))
            in = i;
    }
    if(out >= 0){
        args[out] = NULL;
        int fd = open(args[out+1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if(fd < 0){
            perror("Unable to open the output file.");
            return n-2;
        }
        args[out+1] = NULL;
        dup2(fd, 1);
        close(fd);
    }

    if(append >= 0){
        args[append] = NULL;

        int fd = open(args[append+1], O_RDWR | O_APPEND | O_CREAT, 0644);
        if(fd < 0){
            perror("Unable to open the output file.");
            return n-2;
        }
        args[append+1] = NULL;
        dup2(fd, 1);
        close(fd);
    }

    if(in >= 0){
        // printf("%s,%s\n", args[in], args[in+1]);
        strcpy(args[in], args[in+1]);
        args[in+1] = NULL;
        n--;
    }
    //if(out >= 0 || append >= 0 || in >= 0)
    if(out >= 0 || append >= 0)
        n-=2;

    return n;
}