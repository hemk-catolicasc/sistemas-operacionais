#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, getpid, getppid, sleep
#include <sys/types.h>  // tipo pid_t

int main() {
    pid_t pid = fork();  // cria um novo processo (filho)

    if (pid < 0) {
        perror("Falha no fork");  // imprime o motivo do erro do sistema
        return 1;
    }

    if (pid == 0) {
        // Processo filho
        printf("Filho: PID = %d, PPID = %d\n", getpid(), getppid());  // mostra PID do filho e do pai
        printf("Filho Encerrando...\n");
        exit(0);  // encerra o processo filho com sucesso
    } else {
        // Processo pai
        printf("Pai: PID = %d, filho criado com PID = %d\n", getpid(), getppid());  // mostra PID do pai e (aqui) PPID
        printf("Pai vai dormir por 30 segundos sem chamar wait()...\n");
        printf("Durante esse tempo o processo filho se tornará um processo zumbi.\n");
        sleep(30);  // pausa o pai por 30 segundos
    }
    return 0;
}