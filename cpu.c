#include <stdio.h>
#include <stdlib.h>
struct processes
{
    int arrival_time;
    int burst_time;
    int process_id;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
    int leave_time;
    int pid;
};

struct times
{
    int p, art, but, wtt, tat, rnt;
};
void print_gantt_chart(struct processes p[], int n)
{
    
    int i, j;
    int last = p[n-1].burst_time + ( n== 1 ? 0 : p[n-1].waiting_time);
    // printing top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
    // middle position
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time-1; j++) printf(" ");
        printf("p%d", p[i].pid);
        for(j=0; j<p[i].burst_time-1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // printing waiting time
    int minus = 0;
    for(i=0; i<n; i++) {
        if(p[i].waiting_time>9) printf(" ");
        printf("%d", p[i].waiting_time);
        if(p[i+1].waiting_time>9){
          minus = 1;
        }
        if(i+1 == n )  if (last>9) minus = 1;
        for(j=0; j<p[i].burst_time-minus; j++) printf("  ");

    }
    if(last>9) printf(" ");
    printf("%d\n", last);
}

void fcfs()
{
    int no_of_processes;
    printf("\nFirst Come First Served Algorithm\n");
    printf("Note -\n1. Arrival Time of at least on process should be 0\n2. CPU should never be idle\n");
    printf("Enter number of processes:  ");
    scanf("%d", &no_of_processes);
    printf("############################\n");
    struct processes *p = malloc(sizeof(struct processes) * no_of_processes);
    for (int i = 0; i < no_of_processes; i++)
    {
        printf("Enter Burst time of p[%d]:  ", i);
        scanf("%d", &p[i].burst_time);
        printf("Enter arrival time of p[%d]:  ", i);
        scanf("%d", &p[i].arrival_time);
        p[i].process_id = i;
        printf("############################\n");
    }
    int wait_time = 0;
    int turn_time = 0;
    for (int i = 0; i < no_of_processes; i++)
    {
        
        // printf(" %d \n",wait_time);
        p[i].waiting_time = wait_time;
        p[i].turnaround_time = wait_time + p[i].burst_time;
        turn_time += p[i].turnaround_time;
        wait_time += p[i].burst_time;
    }
    printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
    for (int i = 0; i < no_of_processes; i++)
    {
        printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].waiting_time);
    }
    int t_time = 0;
    for (int i = 0; i < no_of_processes; i++)
    {
        t_time += p[i].waiting_time;
    }
    float avg_wait = t_time / no_of_processes;
    float avg_turn = turn_time / no_of_processes;
    printf("Average waiting time : %f \n", avg_wait);
    printf("Average turnaround time : %f \n", avg_turn);
}

void sort(struct processes *p, int np)
{
    struct processes t;
    for (int i = 0; i < np - 1; i++)
    {
        for (int j = 0; j < np - i - 1; j++)
        {
            if (p[j + 1].burst_time < p[j].burst_time)
            {
                t = p[j + 1];
                p[j + 1] = p[j];
                p[j] = t;
            }
        }
    }
}

void sortart(struct times a[], int pro)
{
    int i, j;
    struct times temp;
    for (i = 0; i < pro; i++)
    {
        for (j = i + 1; j < pro; j++)
        {
            if (a[i].art > a[j].art)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    return;
}

/*
void sort_rem(struct processes *p, int np)
{
    struct processes t;
    for (int i = 0; i < np - 1; i++)
    {
        for (int j = 0; j < np - i - 1; j++)
        {
            if (p[j + 1].remaining_time < p[j].remaining_time)
            {
                t = p[j + 1];
                p[j + 1] = p[j];
                p[j] = t;
            }
        }
    }
}
*/


void sjf()
{
    int no_of_processes;
    printf("\nShortest Job First Algorithm\n");
    printf("Note -\n1. Arrival Time of at least on process should be 0\n2. CPU should never be idle\n");
    printf("Enter number of processes:  ");
    scanf("%d", &no_of_processes);
    printf("############################\n");
    struct processes *p = malloc(sizeof(struct processes) * no_of_processes);
    for (int i = 0; i < no_of_processes; i++)
    {
        printf("Enter Burst time of p[%d]:  ", i);
        scanf("%d", &p[i].burst_time);
        printf("Enter arrival time of p[%d]:  ", i);
        scanf("%d", &p[i].arrival_time);
        p[i].process_id = i;
        printf("############################\n");
    }
    sort(p, no_of_processes);
    int wait_time = 0;
    int turn_time = 0;
    for (int i = 0; i < no_of_processes; i++)
    {   
        p[i].pid = i+1;
        // printf(" %d \n",wait_time);
        p[i].waiting_time = wait_time;
        p[i].turnaround_time = wait_time + p[i].burst_time;
        turn_time += p[i].turnaround_time;
        wait_time += p[i].burst_time;
    }
    printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
    for (int i = 0; i < no_of_processes; i++)
    {
        printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].waiting_time);
    }
    int t_time = 0;
    for (int i = 0; i < no_of_processes; i++)
    {
        t_time += p[i].waiting_time;
    }
    float avg_wait = t_time / no_of_processes;
    float avg_turn = turn_time / no_of_processes;
    printf("Average waiting time : %f \n", avg_wait);
    printf("Average turnaround time : %f \n", avg_turn);
    print_gantt_chart(p, no_of_processes);
    printf("##########################################################################################################\n");
}

void roundRobin()
{
    int i, j, pro, time, remain, flag = 0, ts;
    float avgwt = 0, avgtt = 0;
    printf("\nRound Robin Scheduling Algorithm\n");
    printf("Note -\n1. Arrival Time of at least on process should be 0\n2. CPU should never be idle\n");
    printf("Enter Number Of Processes : ");
    scanf("%d", &pro);
    printf("############################\n");
    struct times a[pro];
    remain = pro;
    for (i = 0; i < pro; i++)
    {
        printf("Enter Burst time of p[%d]:  ", i);
        scanf("%d", &a[i].but);
        printf("Enter arrival time of p[%d]:  ", i);
        scanf("%d", &a[i].art);
        a[i].p = i;
        a[i].rnt = a[i].but;
        printf("############################\n");
    }
    sortart(a, pro);
    printf("Enter Time Slice OR Quantum Number : ");
    scanf("%d", &ts);
    printf("\n***************************************\n");
    printf("Gantt Chart\n");
    printf("0");
    for (time = 0, i = 0; remain != 0;)
    {
        if (a[i].rnt <= ts && a[i].rnt > 0)
        {
            time = time + a[i].rnt;
            printf(" -> [P%d] <- %d", a[i].p, time);
            a[i].rnt = 0;
            flag = 1;
        }
        else if (a[i].rnt > 0)
        {
            a[i].rnt = a[i].rnt - ts;
            time = time + ts;
            printf(" -> [P%d] <- %d", a[i].p, time);
        }
        if (a[i].rnt == 0 && flag == 1)
        {
            remain--;
            a[i].tat = time - a[i].art;
            a[i].wtt = time - a[i].art - a[i].but;
            avgwt = avgwt + time - a[i].art - a[i].but;
            avgtt = avgtt + time - a[i].art;
            flag = 0;
        }
        if (i == pro - 1)
            i = 0;
        else if (a[i + 1].art <= time)
            i++;
        else
            i = 0;
    }
    printf("\n\n");
    printf("***************************************\n");
    printf("Pro\tArTi\tBuTi\tTaTi\tWtTi\n");
    printf("***************************************\n");
    for (i = 0; i < pro; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", a[i].p, a[i].art, a[i].but, a[i].tat, a[i].wtt);
    }
    printf("***************************************\n");
    avgwt = avgwt / pro;
    avgtt = avgtt / pro;
    printf("Average Waiting Time : %.2f\n", avgwt);
    printf("Average Turnaround Time : %.2f\n", avgtt);
    return;
}


void main()
{
    int choice;
    while (choice != 5)
    {
        printf("\t\t Main Menu \n");
        printf("\t 1. First Come First Serve(FCFS)\n");
        printf("\t 2. SJF\n");
        printf("\t 3. Round Robin\n");
        printf("\t 4. Exit\n");
        printf("Enter choice:  ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            roundRobin();
            break;
        }
    }
}
