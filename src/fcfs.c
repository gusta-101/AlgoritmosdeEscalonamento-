/*
 * Algoritmo de Escalonamento First-Come, First-Served (FCFS)
 * Este código simula o escalonador FCFS, calculando os tempos de
 * espera e retorno (turnaround) para um conjunto de processos.
 */
#include <stdio.h>
#include <stdlib.h> // Para a função qsort

// Define a estrutura de um processo
typedef struct {
    int pid;      // ID do Processo
    int temp_cheg;       // Tempo de Chegada (Arrival Time)
    int temp_exec;       // Tempo de Execução (Burst Time)
    
    // Resultados que serão calculados
    int espera;       // Tempo de Espera (Waiting Time)
    int treturn;      // Tempo de Retorno (Turnaround Time)
    int tcomplete;       // Tempo de Conclusão (Completion Time)
} Process;

/**
 * @brief Função de comparação para o qsort.
 * Compara dois processos com base no seu tempo de chegada (temp_cheg).
 */
int compareArrival(const void* a, const void* b) {
    // Converte os ponteiros void* de volta para Process*
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    // Retorna a diferença; qsort ordena em ordem crescente
    return (p1->temp_cheg - p2->temp_cheg);
}

/**
 * @brief Encontra o maior entre dois inteiros.
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief Calcula todos os tempos (espera, retorno, conclusão)
 * para um array de processos usando o algoritmo FCFS.
 * @param proc Array de processos.
 * @param n Número de processos no array.
 */
void findFCFSTimes(Process proc[], int n) {
    float total_espera = 0;
    float total_treturn = 0;
    
    // 1. Ordena os processos pelo Tempo de Chegada (temp_cheg)
    // O FCFS *exige* que os processos sejam tratados na ordem em que chegam.
    qsort(proc, n, sizeof(Process), compareArrival);

    printf("--- Iniciando Simulação FCFS ---\n\n");

    // 2. Calcula os tempos para o primeiro processo (i = 0)
    // O primeiro processo da fila (após ordenar) é um caso especial
    // pois não tem ninguém antes dele.
    
    // O tempo de conclusão é simplesmente sua chegada + sua execução
    proc[0].tcomplete = proc[0].temp_cheg + proc[0].temp_exec;
    
    // O tempo de retorno é o tempo total (conclusão - chegada)
    proc[0].treturn = proc[0].tcomplete - proc[0].temp_cheg;
    
    // O tempo de espera é (tempo de retorno - tempo de execução)
    proc[0].espera = proc[0].treturn - proc[0].temp_exec;

    // Adiciona aos totais para calcular a média
    total_espera += proc[0].espera;
    total_treturn += proc[0].treturn;

    // 3. Calcula os tempos para os processos restantes (i = 1 até n-1)
    for (int i = 1; i < n; i++) {
        // O processo 'i' só pode começar *depois* que o processo 'i-1' terminar.
        // O tempo de início (startTime) é o maior valor entre:
        //   a) A hora que este processo 'i' chegou (proc[i].temp_cheg)
        //   b) A hora que o processo anterior 'i-1' terminou (proc[i-1].tcomplete)
        int startTime = max(proc[i].temp_cheg, proc[i - 1].tcomplete);
        
        // O tempo de conclusão é o (tempo de início + tempo de execução)
        proc[i].tcomplete = startTime + proc[i].temp_exec;
        
        // Tempo de retorno = (conclusão - chegada)
        proc[i].treturn = proc[i].tcomplete - proc[i].temp_cheg;
        
        // Tempo de espera = (tempo de retorno - tempo de execução)
        proc[i].espera = proc[i].treturn - proc[i].temp_exec;

        // Acumula os totais
        total_espera += proc[i].espera;
        total_treturn += proc[i].treturn;
    }

    // 4. Imprime a tabela de resultados
    printf("PID\t Chegada (AT)\t Execução (BT)\t Conclusão (CT)\t Retorno (TAT)\t Espera (WT)\n");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %d\n",
               proc[i].pid, proc[i].temp_cheg, proc[i].temp_exec, proc[i].tcomplete, proc[i].treturn, proc[i].espera);
    }
    printf("------------------------------------------------------------------------------------------\n");

    // 5. Imprime as médias
    printf("\nTempo Médio de Espera (Average WT): %.2f\n", (total_espera / n));
    printf("Tempo Médio de Retorno (Average TAT): %.2f\n", (total_treturn / n));
}

// ----------------------------------------------------------------
// Função Main
// ----------------------------------------------------------------
int main() {
    // Define os processos para a simulação
    // {PID, Tempo de Chegada, Tempo de Execução}
    Process proc[] = {
        {1, 0, 20}, // P1 (Longo)
        {2, 1, 2},  // P2 (Curto)
        {3, 2, 3}   // P3 (Curto)
    };
    
    // Calcula o número de processos no array
    int n = sizeof(proc) / sizeof(proc[0]);

    // Chama a função principal do FCFS
    findFCFSTimes(proc, n);

    return 0; // Indica que o programa terminou com sucesso
}