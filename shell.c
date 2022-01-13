#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define CC_NUM 4

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

bool check_for_custom_command(char ** comm_arr, int len, char * str) {
    int i,k;

    for (i = 0; i < len; i++) 
        if (strstr(str, comm_arr[i]))
            break;
    
    
    if (i == len)
        return false;
    
    switch(i) {
        case 0:
            exit(0);
        case 1:
            printf("mercury shell!\n");
            break;
        case 2:
            printf("%d\n", getpid());
            break;
        case 3:
            for (k = 0; k < len; k++)
                printf("%s ", comm_arr[k]);
            printf("\n");
            break;
        default:
            printf("ERROR\n");
            break;
    }

    return true;
    
}

int main(void) {
    char* custom_commands[CC_NUM] = {"exit", "shinfo", "printpid", "help"};
    int cc_len = CC_NUM;
    int pid, status;
    char buffer[128];
    char ** command = malloc(sizeof(char *) * 128);   //alloco spazio per 128 puntatori stringa
    int commandNum;
    
    printf("%%");

    while (fgets(buffer, 128, stdin)) {
        commandNum = tokenize_str(buffer, command);
        command[commandNum] = NULL;

        if (!check_for_custom_command(custom_commands, cc_len, command[0])) {
            
            if ((pid = fork()) < 0) { //creiamo un nuovo processo
                printf("ERRORE: fork\n");
                return 1;
            }
            
            if (pid == 0) { //processo figlio
                if (execvp(command[0], command) < 0) {  //execvp prende come primo argomento il comando, come secondo un array con comando + argomenti + NULL
                    printf("ERRORE: execute\n");
                    return 1;
                }

            return 0;
            }
        }

        if (pid == waitpid(pid, &status, 0) < 0) {
            printf("ERRORE: waitpid\n");
            return 1;
        }
        
        printf("%%");
    }

}