#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int tokenize_str(char *str, char **command) {    //divido il comando inserito in comandi, separati da uno spazio
    int i = 0;
    char *temp;

    
    temp = strtok(str, " ");

    while (temp != NULL) {
        command[i] = malloc(sizeof(char) * strlen(temp));   
        strcpy(command[i], temp);   //salvo la stringa corrente nell'array di comandi
        temp = strtok(NULL, " ");
        i++;
    }
    command[i - 1][strlen(command[i - 1]) - 1] = 0;
    return i;
}



int main(void) {
    int pid, status;
    char buffer[128];
    char ** command = malloc(sizeof(char *) * 128);   //alloco spazio per 128 puntatori stringa
    int commandNum;
    
    printf("%%");

    while (fgets(buffer, 128, stdin)) {
        commandNum = tokenize_str(buffer, command);
        command[commandNum] = NULL;

        
        if (strstr(command[0], "exit") != NULL) //se il comando comincia con exit, termina la shell
            return 0;
        
        if (strstr(command[0], "shinfo") != NULL) {
            printf("mercury shell!\n");
            break;
        }
        
        if ((pid = fork()) < 0){
            printf("ERRORE: fork\n");
            return 1;
        }

        else 
            if (pid == 0){ //processo figlio
                if (execvp(command[0], command) < 0) {  //execvp prende come primo argomento il comando, come secondo un array con comando + argomenti + NULL
                    printf("ERRORE: execute\n");
                    return 1;
                }

            return 0;
        }

        if (pid == waitpid(pid, &status, 0) < 0) {
            printf("ERRORE: waitpid\n");
            return 1;
        }

        printf("%%");
    }

}