#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t pid = getpid();

    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    char data[30];
    strftime(data, sizeof(data), "%d/%m/%Y", t);

    FILE *f = fopen("relatorio_so.txt", "w");
    if (!f) {
        perror("Erro ao criar arquivo");
        exit(1);
    }

    fprintf(f, "Aluno: Lucas\n");
    fprintf(f, "Data: %s\n", data);
    fprintf(f, "PID do processo: %d\n", pid);
    fprintf(f, "Teste pratico de interacao com o kernel\n");

    fclose(f);

    pid_t filho = fork();

    if (filho < 0) {
        perror("Erro no fork");
        exit(1);
    }

    if (filho == 0) {
        printf("Processo filho em execucao. PID = %d\n", getpid());

        int vetor[10];
        for (int i = 0; i < 10; i++)
            vetor[i] = i;

        printf("Conteudo do vetor:\n");
        for (int i = 0; i < 10; i++)
            printf("%d ", vetor[i]);
        printf("\n");

        FILE *f = fopen("relatorio_so.txt", "r");
        if (!f) {
            perror("Erro ao abrir arquivo");
            exit(1);
        }

        printf("\nConteudo do arquivo:\n");
        char linha[256];
        while (fgets(linha, sizeof(linha), f))
            printf("%s", linha);

        fclose(f);
        exit(0);

    } else {
        wait(NULL);

        printf("Processo pai em execucao. PID = %d\n", getpid());

        int vetor[10];
        for (int i = 0; i < 10; i++)
            vetor[i] = i;

        printf("Conteudo do vetor:\n");
        for (int i = 0; i < 10; i++)
            printf("%d ", vetor[i]);
        printf("\n");

        FILE *f = fopen("relatorio_so.txt", "r");
        if (!f) {
            perror("Erro ao abrir arquivo");
            exit(1);
        }

        printf("\nConteudo do arquivo:\n");
        char linha[256];
        while (fgets(linha, sizeof(linha), f))
            printf("%s", linha);

        fclose(f);
    }

    return 0;
}