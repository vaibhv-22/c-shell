#include "world.h"

void torelative(char *path)
{
    if (strlen(path) >= strlen(home))
    {
        if (strncmp(path, home, strlen(home)) == 0)
        {
            sprintf(path, "~%s", path + strlen(home));
        }
    }
}

void update()
{
    struct utsname uname_pointer;
    struct passwd *p = getpwuid(getuid());
    char *name = p->pw_name;
    strcpy(u_name, name);

    getcwd(pwd, sizeof(pwd));

    uname(&uname_pointer);

    gethostname(host, sizeof(host));
}
char *get_prompt()
{

    char p[4000], path[1024];

    update();

    strcpy(path, pwd);
    torelative(path);

    sprintf(p, "<\x1b[34m%s\x1b[0m@\x1b[34m%s\x1b[32m:%s\x1b[0m> ", u_name, host, path);

    strcpy(prompt, p);
    // printf("%s", prompt);
    return prompt;
}

int get_commands()
{
    char *pr = get_prompt();
    printf("%s", pr);
    // char *cmds = readline(pr);
    // char cmds[1024];
    char *cmds = (char *)malloc(sizeof(char) * 1024);
    for(int i = 0; i < 1024; i++)
        cmds[i] = '\0';
    long unsigned length_of_cmd = 0;
    int char_read = getline(&cmds, &length_of_cmd, stdin);
    if(char_read < 0){
        printf("^D -----> logout\n");
        exit(0);
    }
    int length2 = (int)strlen(cmds);
    cmds[length2 - 1] = '\0';
    int n = 0;

    if (cmds == NULL)
    {
        printf("\n");
        return 0;
    }
    // add_history(cmds);
    addhis(cmds);
    char *ptr;
    commands[0] = strtok_r(cmds, ";", &ptr);
    cmds = NULL;
    while (commands[n] != NULL)
        commands[++n] = strtok_r(cmds, ";", &ptr);
    return n;
}

int tokenize(char *command)
{

    char *com = malloc(sizeof(char) * 1024);
    strcpy(com, command);
    char *ptr;
    tokens[0] = strtok_r(com, " \t\n\r\a", &ptr);
    com = NULL;
    int no_of_tokens = 0;
    while (tokens[no_of_tokens] != NULL)
        tokens[++no_of_tokens] = strtok_r(com, " \t\n\r\a", &ptr);

    return no_of_tokens;
}

int extract_flags(int n, char **args)
{
    int k1 = 'a', k2 = 'l',k3='r',k4='s';
    flag_hash[k1] = 0;
    flag_hash[k2] = 0;
    flag_hash[k3] = 0;
    flag_hash[k4] = 0;
    int new_n = 0;

    for (int i = 0; i < n; i++)
    {
        if (args[i][0] != '-')
        {
            strcpy(args[new_n], args[i]);
            new_n++;
        }
        else
        {
            if (args[i][1] == 'r') flag_hash[k3] = 1;
            if (args[i][1] == 's') flag_hash[k4] = 1; 
            for (int j = 1; j < strlen(args[i]); j++)
            {
                if (args[i][j] == 'a')
                {
                    flag_hash[k1] = 1;
                }
                else if (args[i][j] == 'l')
                {
                    flag_hash[k2] = 1;
                }
            }
        }
    }
    return new_n;
}

void child_exited(int n)
{
    // printf("HERElol2\n");
    int status;
    pid_t wpid = waitpid(-1, &status, WNOHANG);
    // printf(" STATUS = %d\nbg = %d\n",status,bg);
    if (wpid > 0 && WIFEXITED(status))
    {
        delJob(wpid);
        // char * pss = get_prompt();
        printf("\n");
        printf("Process with pid %d exited normally", wpid);
        printf("\n");
    }
    if (wpid > 0 && !WIFEXITED(status))
    {
        delJob(wpid);
        printf("\n");
        printf("Process with pid %d exited due to abnormally", wpid);
        printf("\n");
        // char *pr = get_prompt();
        // printf("%s", pr);
        // char * pss = get_prompt();
        
    }
}
int init_cmd(char *command)
{
    int no_tokens = tokenize(command);
    int savestdout = dup(1);
    no_tokens = redirect(no_tokens, tokens);
    if(no_tokens == -1)
        return -1;
    int exitcode = 0;
    bg = 0;
    if (no_tokens == -1)
        return -1;
    no_tokens = extract_flags(no_tokens, tokens);
    if (strcmp(tokens[0], "cd") == 0)
    {
        exitcode = cd_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "echo") == 0)
    {
        exitcode = echo_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "clear") == 0)
    {
        exitcode = clear_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "quit") == 0)
    {
        exitcode = exit_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "exit") == 0)
    {
        exitcode = exit_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "ls") == 0)
    {
        exitcode = ls_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "pinfo") == 0)
    {
        exitcode = pinfo_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "repeat") == 0)
    {
        exitcode = repeat_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "history") == 0)
    {
        int exitcode = history_world(no_tokens, tokens);
    }
    else if (strcmp(tokens[0], "pwd") == 0)
    {
        exitcode = pwd_world();
    } else if(strcmp(tokens[0] , "jobs") == 0){
        exitcode = jobs_world(no_tokens,tokens);
    } else if(strcmp(tokens[0] , "sig") == 0){
        exitcode = sig_world(no_tokens,tokens);
    } else if(strcmp(tokens[0] , "fg") == 0){
        exitcode = fg_world(no_tokens,tokens);
    } else if(strcmp(tokens[0] , "bg") == 0){
        exitcode = bg_world(no_tokens,tokens);
    // } else if(strcmp(tokens[0] , "baywatch") == 0){
    //     exitcode = baywatch_world(no_tokens,tokens);
    // } else if(strcmp(tokens[0] , "replay") == 0){
    //     exitcode = replay_world(no_tokens,tokens);
    }
    else
        exitcode = -1;
    // printf("exit = %d\n" , exitcode);
    if (exitcode != -1){
        dup2(savestdout,1);
        return exitcode;
    }
    // printf("YHA NHI AAYA HU\n");
    // vi
    // vii

    pid_t pid = fork();
    int status;
    if (strcmp(tokens[no_tokens - 1], "&") == 0)
    {
        no_tokens = no_tokens - 1;
        tokens[no_tokens] = NULL;
        bg = 1;
    }
    if (pid > 0)
    {
        if (bg == 1)
        {
            char com[BUF_COM];
            int len = strlen(command);
            strncpy(com, command, len - 2);
            com[len - 2] = '\0';
            appendJob(pid, com);
            printf("%d", pid);
            printf("\n");
            // child_exited(1);
            signal(SIGCHLD, child_exited);
        }
        else
        {
            int pd = pid;
            fpid = pd;
            waitpid(pd, &status, WUNTRACED);
            if (WIFSTOPPED(status))
            {
                appendJob(pd, command);
            }
            fpid = 0;
        }
    }
    else if (pid == 0)
    {
        if (bg == 1)
            setpgid(0, 0);
        int proc = execvp(tokens[0], tokens);
        if (proc == -1)
            perror("Error executing:");
        return -1;
    }
    else if (pid < 0)
    {
        perror("Fork failed:");
        return 0;
    }
    dup2(savestdout,1);
    return 1;
}
int exec_com(char * command){
    int no_pipes = 0;
    char* pipes[BUF_COM]; 

    int savestdout = dup(1);
    int savestdin = dup(0);
    pipes[0] = strtok(command, "|");

    while(pipes[no_pipes] != NULL)
        pipes[++no_pipes] = strtok(NULL, "|");
    if(no_pipes == 1)
        return execute_program(pipes[0]);

    for(int i=0;i<no_pipes;i++){
        if(i == no_pipes - 1){
            dup2(savestdout,1);
            execute_program(pipes[i]);
        }
        else
            exec_pipe(pipes[i]);
            
    }

    dup2(savestdin,0);
    dup2(savestdout,1);
    return 0;
}
int exec_pipe(char *command){

    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0){
        dup2(fd[1], 1);
        execute_program(command);
        abort();
    }

    else if (pid > 0){
        dup2(fd[0], 0);
        close(fd[1]);
    }

    close(fd[0]);
    close(fd[1]);
}
int execute_program(char *command)
{

    int no_tokens = tokenize(command);
    int savestdout = dup(1);
    // no_tokens = redirect(no_tokens, tokens);
    // if(no_tokens == -1)
    //     return -1;
    no_tokens = extract_flags(no_tokens, tokens);
    init_cmd(command);

    return 1;
}

struct Job *nth_node(int n)
{
    struct Job *temp = head;
    int tmp = n - 1;
    while (tmp--)
    {
        if (temp == NULL)
            return NULL;
        else
            temp = temp->next;
    }
    return temp;
}

struct Job* newJob(int pid, char* cmd){
    struct Job* temp = (struct Job*)malloc(sizeof(struct Job));
    temp->pid = pid;
    strcpy(temp->command, cmd);
    temp->next = NULL;
    return temp;
}

void appendJob(int pid, char *cmd)
{
    struct Job *new = newJob(pid, cmd);

    if (head != NULL)
    {
        struct Job *i = head;
        while (i->next)
            i = i->next;
        i->next = new;
    }
    else
    {
        head = new;
    }
    no_jobs++;
}
void zhandler(int sig)
{
    int pid = getpid();
    int currgpid = getpgid(pid);

    // char* temp = mallify; forn(i) temp[i] = '\0';
    // sprintf(temp,"pid and currpgid is %d %d\n",pid,currgpid);
    // write(2,temp,30);
    printf("\n");
    if(shellpgid != currgpid){
        kill(pid,SIGTSTP);
    }

    // else{
        // char *pr = get_prompt();
        // printf("%s", pr);
    // }

}
void handler(int sig)
{
    // signal(sig, SIG_IGN);
    kill(SIGINT, 0);
    printf("\n");
    // printf("PD: %d\n", fpid);
    // if (fpid)
    //     kill(fpid, sig);
}
void dhandler(int sig){
    exit(0);
}
int delJob(int pid){
    no_jobs--;
    struct Job* temp = head;
    
    if(temp->pid == pid){
        head = temp->next;
        free(temp);
        return 1;
    }
    while(temp->next){
        if(temp->next->pid == pid){
            struct Job* n = temp->next->next;
            free(temp->next);
            temp->next = n;
            return 1;
        }
        temp = temp->next;
    }
    return 1;
}
