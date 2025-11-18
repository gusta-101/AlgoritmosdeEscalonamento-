#include <stdio.h>

int main() {
    int n, i, j;

    printf("Quantidade de processos: ");
    scanf("%d", &n);

    int burst[n], process[n];
    int waiting[n], turnaround[n];

    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Tempo de execucao do processo P%d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (burst[j] < burst[i]) {
                int temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    waiting[0] = 0;
    for (i = 1; i < n; i++) {
        waiting[i] = 0;
        for (j = 0; j < i; j++) {
            waiting[i] += burst[j];
        }
    }

    for (i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
    }

    printf("\nProcesso\tBurst\tEspera\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\n", process[i], burst[i], waiting[i], turnaround[i]);
    }

    return 0;
}