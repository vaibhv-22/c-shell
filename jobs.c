#include "world.h"
void merge(struct SortingJob arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct SortingJob L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].command,R[j].command)<=0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(struct SortingJob arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int jobs_world(int n, char **args){
    // sorting_job[BUF];
    struct Job* i = head;
    // printf("com = %s\n",i->command);
    int count = -1;
    while(i){
         
        count++;
        char procpath[BUF_PWD];
        sprintf(procpath, "/proc/%d/stat", i->pid);
        // printf("pid = %d ,path =  %s\n", i->pid, procpath);
        FILE *stat = fopen(procpath, "r");
        if(stat == NULL){
            printf("Infomation not available for PID: %d\n", i->pid);
            i = i->next;
            continue;
        }
        
        int pid;
        char s, pname[BUF_PWD];

        fscanf(stat, "%d %s %c", &pid, pname, &s);
        fclose(stat);
        
        char status[8]; 
        if(s == 'S' || s == 'R')
            strcpy(status, "Running");
        else if(s == 'T')
            strcpy(status, "Stopped");
        sorting_job[count].cnt = count;
        sorting_job[count].pid = pid;
        strcpy(sorting_job[count].command, i->command);
        strcpy(sorting_job[count].status, status);
        // sorting_job[count-1].status = status;
        // sorting_job[count-1].command = i->command;
        // printf("[%d] %s %s [%d]\n", count, status, i->command, i->pid);
        i = i->next;
    }
    mergeSort(sorting_job, 0,count);
    int lol1 = 'r',lol2 = 's';
    if(flag_hash[lol1]){
        for(int i = 0; i <= count; i++){
        if(sorting_job[i].status[0] == 'R')
            printf("[%d] %s %s [%d]\n", sorting_job[i].cnt+1, sorting_job[i].status, sorting_job[i].command, sorting_job[i].pid);
        }
        return 1;
    } else if(flag_hash[lol2]){
        for(int i = 0; i <= count; i++){
        if(sorting_job[i].status[0] == 'S')
            printf("[%d] %s %s [%d]\n", sorting_job[i].cnt+1, sorting_job[i].status, sorting_job[i].command, sorting_job[i].pid);
        }
        return 1;
    } 
    for(int i = 0; i <= count; i++){
        printf("[%d] %s %s [%d]\n", sorting_job[i].cnt+1, sorting_job[i].status, sorting_job[i].command, sorting_job[i].pid);
    }
    return 1;
}