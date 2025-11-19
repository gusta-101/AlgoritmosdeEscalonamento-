#include <stdio.h>

struct Processo {
    int id;
    int tempoExecucao;   // Burst Time
    int prioridade;      
};

int main() {
    int quantidade, i, j;

    printf("Quantidade de processos: ");
    scanf("%d", &quantidade);

    struct Processo processos[quantidade];

    // Entrada dos dados dos processos
    for (i = 0; i < quantidade; i++) {
        processos[i].id = i + 1;

        printf("\nProcesso %d\n", processos[i].id);
        printf("Tempo de execução: ");
        scanf("%d", &processos[i].tempoExecucao);

        printf("Prioridade (quanto menor o número, maior a prioridade): ");
        scanf("%d", &processos[i].prioridade);
    }

    // Ordenando os processos por prioridade
    for (i = 0; i < quantidade - 1; i++) {
        for (j = i + 1; j < quantidade; j++) {
            if (processos[j].prioridade < processos[i].prioridade) {

                struct Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }

    int tempoEspera = 0;
    int tempoResposta = 0;

    printf("\nOrdem de execução (Priority Scheduling):\n");
    printf("Processo\tPrioridade\tExecução\tEspera\tTurnaround\n");

    for (i = 0; i < quantidade; i++) {

        int esperaAtual = tempoEspera;
        int turnaroundAtual = esperaAtual + processos[i].tempoExecucao;

        printf("P%d\t\t%d\t\t%d\t\t%d\t%d\n",
               processos[i].id,
               processos[i].prioridade,
               processos[i].tempoExecucao,
               esperaAtual,
               turnaroundAtual);

        tempoEspera += processos[i].tempoExecucao;
        tempoResposta += turnaroundAtual;
    }

    return 0;
}
