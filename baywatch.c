#include "world.h"

int baywatch_world(int n, char **args){

    int time = atoi(args[1]);
    fd_set input_set;
    struct timeval timeout;

    /* Empty the FD Set */
    FD_ZERO(&input_set);
    /* Listen to the input descriptor */
    FD_SET(STDIN_FILENO, &input_set);

    if (!strcmp(args[2],"interrupt")){
        // Interupt
        printf("0\tCPU0\tCPU1\tCPU2\tCPU3\n");
        int k = 1;

        do {
            FILE *interrupt = fopen("/proc/interrupts", "r");       
            ssize_t reads;
            size_t len = 0;
            char * line = NULL;

            if (interrupt == NULL){
                perror("Error opening interrupt file: ");
                return 0;
            }

            int i = 0;

            while(i < 3 && (reads = getline(&line, &len, interrupt)) != -1) {
                i++;
            }
            long long int cpu0, cpu1, cpu2, cpu3;
            // printf("%s\n", line);

            sscanf(line, "%*lld: %lld %lld %lld %lld", &cpu0, &cpu1, &cpu2, &cpu3); 

            printf("%d\t%lld\t%lld\t%lld\t%lld\n", k, cpu0, cpu1, cpu2, cpu3);
            k++;

            fclose(interrupt);

            timeout.tv_sec = time;    // time seconds
            timeout.tv_usec = 0;    // 0 milliseconds
            select(1, &input_set, NULL, NULL, &timeout);
        }
        while(1);

        return 0;
    }
    if (!strcmp(args[2],"dirty")){
        // dirty

        do {
            FILE *meminfo = fopen("/proc/meminfo", "r");       
            ssize_t reads;
            size_t len = 0;
            char * line = NULL;

            if (meminfo == NULL){
                perror("Error opening meminfo file: ");
                return 0;
            }

            int i = 0;

            while(i < 17 && (reads = getline(&line, &len, meminfo)) != -1) {
                i++;
            }
            printf("%s", line);

            fclose(meminfo);

            timeout.tv_sec = time;    // time seconds
            timeout.tv_usec = 0;    // 0 milliseconds
            select(1, &input_set, NULL, NULL, &timeout);
        }
        while(1);
        return 0;
    }

    return 1;
}