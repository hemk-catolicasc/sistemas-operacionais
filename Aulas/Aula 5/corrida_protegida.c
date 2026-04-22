#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int contador = 0;
pthread_mutex_t mutex; // Mutex para proteger o acesso ao contador

void* incrementar(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar o contador
        contador++;
        pthread_mutex_unlock(&mutex); // Desbloqueia o mutex
    }
    return NULL;
}
int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex
    pthread_create(&t1, NULL, incrementar, NULL);
    pthread_create(&t2, NULL, incrementar, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex); // Destroi o mutex
    printf("Valor final do contador: %d\n", contador);
    return 0;
}
 
 