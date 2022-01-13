#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void print_pids() {
    printf("PID del processo corrente: %d\n", getpid());

    printf("PID del processo padre: %d\n", getppid());
}

int main(void) {
    pid_t child1 = -1, child2 = -1;

    printf("Processo base\n");
    print_pids();

    child1 = fork();   //fork crea un processo figlio identico al padre, e continua da lì. fork restituisce il pid dell figlio al padre, e 0 al figlio.
    
    if (child1 != 0)    //nel caso child1 fosse uguale a 0,  skippa il fork del secondo processo, siamo nel primo figlio
        child2 = fork();
    
    if (child1 == 0) {   //se child1 è 0, siamo nel primo figlio, stampa i pid di padre e figlio
        printf("Processo figlio\n");
        print_pids();
        return 0;
    }

    else if (child2 == 0) { //se child2 è 0, siamo nel secondo figlio, stampa la somma del suo pid + quello del padre
        printf("P pid + my pid = %d\n", (getpid() + getppid()));
        return 0;
    }
    else {  //se arriviamo fin qui, siamo nel processo padre, aspettiamo che terminino i due figli e stampiamo i loro pid
        waitpid(child1);
        waitpid(child2);
        printf("I due child processes hanno terminato, child 1: %d, child 2: %d\n", child1, child2);
    }

    return 0;
}