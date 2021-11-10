#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char ** tokenize_str(char *str){    //divido il comando inserito in comandi, separati da uno spazio
    int i = 0;
    char *temp;
    char ** command = malloc(sizeof(char *) * 6);   //alloco spazio per 6 puntatori stringa
    
    temp = strtok(str, " ");

    while (temp != NULL){
        command[i] = malloc(sizeof(char) * strlen(temp));   
        strcpy(command[i], temp);   //salvo la stringa corrente nell'array di comandi
        temp = strtok(NULL, " ");
        i++;
    }
    command[i - 1][strlen(command[i - 1]) - 1] = 0;
    return command;
}

int main(void){
    int pid, status;
    char buffer[128];

    
    printf("%%");

    while (fgets(buffer, 128, stdin)){
        char **command = tokenize_str(buffer);


        if (strstr(command[0], "exit") != NULL) //se il comando comincia con exit, termina la shell
            return 0;
        
        if ((pid = fork()) < 0){
            printf("ERRORE: fork\n");
            return 1;
        }

        else 
            if (pid == 0){ //processo figlio
                if (execlp(command[0], command[0], command[1], command[2], command[3], command[4], command[5], NULL) < 0) {
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