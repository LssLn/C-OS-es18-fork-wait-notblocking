#include <sys/types.h>
#include <sys/wait.h> // vi è definita La macro WIFEXITED(stat_v)
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    char * message;
    int n,stat_val,exit_code;

    pid=fork();

    switch(pid){
        case -1: 
            //errore
            perror("fork errore\n");
            exit(1);
            break;
        case 0:
            //figlio
            message = "Child";
            n=3;
            exit_code=37;
            break;
        default:
            //padre
            message = "Father";
            n=5;
            exit_code = 0;
            break;
    }

    for(;n>0;n--){
        printf("\npid: %d\n",getpid());
        puts(message);
        sleep(1);
    }

    if(pid!=0){ //padre
        pid_t child_pid;
        child_pid = waitpid(pid,&stat_val,WNOHANG);
        //WNOHANG non blocca il padre e torna 0 se il figlio non ha ancora terminato, il pid del figlio altrimenti. -1 errore
        if(child_pid){
            printf("Child has finished : PID %d\n",child_pid);
            if(WIFEXITED(stat_val)) //WIFEXITED(stat_val) e' !=0 se il figlio ha terminato normalmente
                printf("Child exited with code %d\n",WEXITSTATUS(stat_val));
            else
                printf("Child terminated abnormally\n");
        }
    }

    exit(exit_code);
}