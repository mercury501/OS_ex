#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



int main(void){
    int pid, status;
    char buffer[128];

    printf("%%");

    while (fgets(buffer, 128, stdin)){

        
        if (strstr(buffer, "exit") != NULL) //se il comando comincia con exit, termina la shell
            return 0;
        
        buffer[strlen(buffer) - 1] = 0;

        if ((pid = fork()) < 0){
            printf("ERRORE: fork\n");
            return 1;
        }

        else 
            if (pid == 0){ //processo figlio
                if (execlp(buffer, buffer, (char *)NULL == -1)) {
                    printf("ERRORE: execute\n");
                    return 1;
                }

            return 0;
        }

        if (pid == waitpid(pid, &status, 0) < 0){
            printf("ERRORE: waitpid\n");
            return 1;
        }

        printf("%%");
    }

}