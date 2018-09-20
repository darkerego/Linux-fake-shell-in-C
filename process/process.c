#include "process.h"

void forkIt(char ** argv)
{
int status;
pid_t pid = fork();
if(pid != 0)
{
//printf("Begin Parent\n");
waitpid(pid,&status,0);
//printf("End Parent\n");
//execvp(argv[0],argv);
//printf("P2\n");
}
else
{
//printf("Begin Child\n");
int res = execvp(argv[0],argv);
exit(res);
printf("Child: execvp has been called. This should never print.\n");
}
//printf("End Fork\n");
return;
}
