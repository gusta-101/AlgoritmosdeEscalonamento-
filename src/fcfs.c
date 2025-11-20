
#include <stdio.h>

int main() {
    
    // Note que os tempos de chegada (0, 1, 2) já estão em ordem!
    
    int n = 3; // O número de processos que vamos simular
    
    int pid[] =       {1, 2, 3};  // IDs dos processos
    int temp_cheg[] = {0, 1, 2};  // Tempos de Chegada (AT)
    int temp_exec[] = {20, 2, 3}; // Tempos de Execução (BT)
    
    // Arrays vazios para guardar os resultados
    int tcomplete[n];  // Tempo de Conclusão (CT)
    int treturn[n];    // Tempo de Retorno (TAT)
    int espera[n];     // Tempo de Espera (WT)
    
    float total_espera = 0;
    float total_treturn = 0;

    printf("--- Iniciando Simulação FCFS (Versão Simples) ---\n\n");

    // --- PASSO 1: CALCULAR O PRIMEIRO PROCESSO (i = 0) ---
    // O primeiro processo é especial, ele não espera por ninguém.
    
    // Conclusão = Chegada + Execução
    tcomplete[0] = temp_cheg[0] + temp_exec[0];
    
    // Retorno = Conclusão - Chegada
    treturn[0] = tcomplete[0] - temp_cheg[0];
    
    // Espera = Retorno - Execução
    espera[0] = treturn[0] - temp_exec[0];
    
    // Acumula os totais
    total_espera += espera[0];
    total_treturn += treturn[0];

    // --- PASSO 2: CALCULAR O RESTANTE (i = 1 até n-1) ---
    for (int i = 1; i < n; i++) {
        
        // Esta é a lógica principal do FCFS!
        // A "Hora de Início" do processo 'i' é a hora que o
        // processo 'i-1' (o anterior) terminou.
        int startTime = tcomplete[i-1];
        
        // ...MAS, e se o processo 'i' chegar DEPOIS que o 'i-1' terminou?
        // (Ex: 'i-1' termina em 10, mas 'i' só chega em 15)
        // A CPU ficaria ociosa. O 'startTime' real deve ser o maior
        // entre a chegada de 'i' e a conclusão de 'i-1'.
        
        if (temp_cheg[i] > tcomplete[i-1]) {
            startTime = temp_cheg[i];
        }
        
        // Agora calculamos os tempos para o processo 'i'
        
        // Conclusão = Hora de Início + Execução
        tcomplete[i] = startTime + temp_exec[i];
        
        // Retorno = Conclusão - Chegada
        treturn[i] = tcomplete[i] - temp_cheg[i];
        
        // Espera = Retorno - Execução
        espera[i] = treturn[i] - temp_exec[i];
        
        // Acumula os totais
        total_espera += espera[i];
        total_treturn += treturn[i];
    }

    // --- PASSO 3: IMPRIMIR RESULTADOS ---
    printf("PID\t Chegada (AT)\t Execução (BT)\t Conclusão (CT)\t Retorno (TAT)\t Espera (WT)\n");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %d\n",
               pid[i], 
               temp_cheg[i], 
               temp_exec[i], 
               tcomplete[i], 
               treturn[i], 
               espera[i]);
    }
    printf("------------------------------------------------------------------------------------------\n");

    // --- PASSO 4: IMPRIMIR MÉDIAS ---
    printf("\nTempo Médio de Espera (Average WT): %.2f\n", (total_espera / n));
    printf("Tempo Médio de Retorno (Average TAT): %.2f\n", (total_treturn / n));

    return 0;
}