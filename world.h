#ifndef HEADER
#define HEADER

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>
#include <sys/select.h>
// #include <readline/history.h>
// #include <readline/readline.h>
#include <signal.h>

#define BUF_PWD 1024
#define BUF_USR 1024
#define BUF_HST 1024
#define BUF_HOM 1024
#define BUF_PMT 1024
#define BUF_NCM 128
#define BUF_COM 1024
#define BUF_TOK 1024
#define HASH_MAX 8192
#define BUF_ENV 1024
char his_path[200];
char pwd[BUF_PWD];
int jobs_world(int n, char** args);
char u_name[1014];
char host[BUF_PWD];
char home[BUF_HOM];
char prompt[BUF_PMT];
int shellpid,shellpgid;
char *commands[BUF_COM];
int exec_com(char * command);
int exec_pipe(char *command);
char *tokens[BUF_TOK];
int flag_hash[256];
int (*cmd_functions[HASH_MAX])(int, char **);
void exhis();
void addhis(char *cmd);
int init_cmd(char *command);
void inithist();
void handler(int sig);
void zhandler(int sig);
void dhandler(int sig);
void torelative(char *path);
int exit_world();
int pwd_world();
int echo_world(int n, char **args);
int cd_world(int n, char **args);
int clear_world();
struct hist
{
    char history[20][100];
    int histins;
    int histed;
};
int sig_world(int n, char **args);
int set_ls();
int bg;
int fg_world(int n,char **args);
int bg_world(int n,char **args);
int baywatch_world(int n, char **args);
int replay_world(int n,char ** args);
struct hist his;
int ls_world(int n, char **args);
int cd_world_2(char *args);
int pinfo_world(int n, char **args);
int repeat_world(int n, char **args);
void child_exited(int n);
int execute_program(char *command);
int history_world(int n, char **args);
int bg_world(int n, char **args);
int fg_world(int n, char **args);
void calculate_hash();
void update();
char *get_prompt();
void local_history(char *cmd);
int get_commands();
int tokenize(char *command);
int extract_flags(int n, char **args);
int redirect(int n, char **args);
int exec_com(char *command);
int no_jobs;
struct Job *nth_node(int n);
struct Job
{
    int pid;
    char command[BUF_COM];
    struct Job *next;
};
struct SortingJob{
    int cnt;
    char status[15];
    char command[BUF_COM];
    int pid;
};
struct SortingJob sorting_job[100];
struct Job *head;
struct Job *newJob(int pid, char *cmd);
void appendJob(int pid, char *cmd);
int delJob(int pid);

void merge_sort_lol(struct Job* sorting_job, int count);
void merge_sort(struct Job* sorting_job, struct Job* left, struct Job* right, int count);
int fpid;
#endif