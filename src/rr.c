#include <stdio.h>

int main() {
    int n, quantum;

    // Entrada de dados
    printf("Quantidade de processos: ");
    scanf("%d", &n);

    printf("Quantum: ");
    scanf("%d", &quantum);

    int burst[n], restante[n], tempo = 0, finalizados = 0;

    // Lendo o tempo de CPU de cada processo
    for (int i = 0; i < n; i++) {
        printf("Burst do processo P%d: ", i+1);
        scanf("%d", &burst[i]);
        restante[i] = burst[i];  // copia para controle
    }

    printf("\n--- Execução Round Robin ---\n");

    // Loop principal do Round Robin
    while (finalizados < n) {
        for (int i = 0; i < n; i++) {

            // Só executa quem ainda não terminou
            if (restante[i] > 0) {

                // Define quanto o processo vai rodar nessa rodada
                int exec = (restante[i] > quantum) ? quantum : restante[i];

                // Mostra o que está acontecendo
                printf("P%d executou %d unidades de tempo\n", i+1, exec);

                tempo += exec;          // soma no tempo total
                restante[i] -= exec;    // reduz o tempo que falta

                // Se terminou, conta como finalizado
                if (restante[i] == 0)
                    finalizados++;
            }
        }
    }

    printf("\nTempo total de execução: %d\n", tempo);
    return 0;
}
