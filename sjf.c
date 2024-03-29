/**
 * Shortest Job First Algorithm
 * (Non-preemptive)
 */

#include <stdio.h>

int mat[10][6];

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrange_arrival(int num, int mat[][6])
{
    // Sort the processes by arrival time (use Bubble sort)
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num - i - 1; j++)
            if (mat[j][1] > mat[j + 1][1])
                for (int k = 0; k < 5; k++)
                    swap(&mat[j][k], &mat[j + 1][k]);
}

void completion_time(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for (int i = 1; i < num; i++)
    {
        temp = mat[i - 1][3];
        int low = mat[i][2];
        for (int j = i; j < num; j++)
        {
            if (temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for (int k = 0; k < 6; k++)
            swap(&mat[val][k], &mat[i][k]);
    }
}

int main()
{
    int n, temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("...Enter the process IDs...\n");

    for (int i = 0; i < n; i++)
    {
        printf("...Process %d...\n", i + 1);
        printf("Enter process ID: ");
        scanf("%d", &mat[i][0]);
        printf("Enter Arrival Time: ");
        scanf("%d", &mat[i][1]);
        printf("Enter Burst Time: ");
        scanf("%d", &mat[i][2]);
    }

    printf("Original Order:\n");
    printf("Process ID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t\t%d\n", mat[i][0], mat[i][1], mat[i][2]);

    arrange_arrival(n, mat);
    completion_time(n, mat);
    printf("After applying SJF Algo:\n");
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][4], mat[i][5]);

    return 0;
}
