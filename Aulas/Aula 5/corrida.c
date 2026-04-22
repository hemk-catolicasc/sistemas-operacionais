#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
int contador = 0;

void* incrementar(void* arg) { // Função que incrementa o contador
    for (int i = 0; i < 100000; i++) {
    contador++;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, incrementar, NULL);
    pthread_create(&t2, NULL, incrementar, NULL); // Cria duas threads que incrementam o contador
    pthread_join(t1, NULL);
    pthread_join(t2, NULL); // Espera as threads terminarem
    printf("Valor final do contador: %d\n", contador); // Resultado deveria ser 200.000, mas vai ser menor devido a condição de corrida
    return 0;
}