#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
    printf("PID del processo: %d\n", getpid());

    printf("PID del processo padre: %d\n", getppid());

    pid_t value = fork();   //fork crea un processo figlio identico al padre, e continua da lì. fork restituisce il pid dell figlio al padre, e 0 al figlio.

    if (value < 0)
        printf("Errore nella syscall fork\n");
    else
        if (value == 0)
            printf("Child, value == %d\n", value);
        else
            printf("Parent, value == %d\n", value);
    
    return 0;
}