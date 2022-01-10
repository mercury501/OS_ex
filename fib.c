//Un processo P scrive i primi 30 numeri di Fibonacci e poi termina.
//In presenza di un control c immesso da tastiera, P dovrà chiedere all’utente se deve continuare la sua esecuzione o terminare e regolarsi di conseguenza.

#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

void chiedi(int sig) {
    char c[2];
    printf("\nricevuto segnale di interruzione, inserire c per continuare e s per stoppare\n");
    scanf("%s", c);
    if(*c == 'c') 
        signal(SIGINT,chiedi);
    else { 
        printf("processo terminato da tastiera\n"); 
        exit(1);
    }
}

int fib(int n) {
    sleep(0.04);
    if(n<=1)
        return n;
    else 
        return (fib(n-1)+fib(n-2));
}

int main() {
    printf("il segnale SIGINT corrisponde a %d\n",SIGINT);
    signal(SIGINT,chiedi);

    for(int i=0;i<=30;i++)         
        printf("fib %d = %d\n", i, fib(i));
    
}