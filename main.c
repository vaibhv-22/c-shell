#include "world.h"
void lp()
{
    while (0 < 1)
    {
        int no_commands = get_commands();
        for (int i = 0; i < no_commands; i++)
        {

            int exitcode = exec_com(commands[i]);
        }
    }
}
int main()
{

    fpid = 0;
    inithist();
    shellpid = getpid();
	shellpgid = getpgid(shellpid);
    signal(SIGINT, handler); // ctrl+c
    signal(SIGQUIT, handler); // ctrl+ \ */ 
    // signal(SIGTSTP, zhandler); // 
    signal(SIGTSTP, zhandler); // Ctrl + Z
    // signal(SIGPIPE,zhandler);
    // signal(SIGCHLD, child_exited);
    no_jobs = 0;
    head = NULL;
    getcwd(home, sizeof(home));
    lp();

    return 0;
}