#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_usr (int signo){
    if (signo == SIGUSR1)
        printf("Ricevuto SIGUSR1!\n");
    else if (signo == SIGUSR2)
        printf("Ricevuto SIGUSR2!\n");

}

int main(void){

    if (signal(SIGUSR1, sig_usr) == SIG_ERR)    {
        printf("ERRORE SISTEMA SIGUSR1!\n");
        return 1;
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)    {
        printf("ERRORE SISTEMA SIGUSR2!\n");
        return 1;
    }

    while (-1)
        pause();

}