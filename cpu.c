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
};

struct times
{
    int p, art, but, wtt, tat, rnt;
};


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


void nonpreemptive()
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


void preemptive()
{
    int no_of_processes;
    printf("\nPreemptive Shortest Job First Algorithm\n");
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
    int shortest = 0;
    int complete = 0; // no of completed processes
    int finish = 0;
    int minimum = 100;
    int wait_time = 0;
    int turn_time = 0;
    int t = 0;     // cpu current time
    int check = 0; // checking if shortest time exists
    for (int i = 0; i < no_of_processes; i++)
        p[i].remaining_time = p[i].burst_time;

    while (complete != no_of_processes)
    {
        for (int j = 0; j < no_of_processes; j++)
        {
            if ((p[j].arrival_time <= t) && (p[j].remaining_time < minimum) && (p[j].remaining_time > 0))
            {
                minimum = p[j].remaining_time;
                shortest = j;
                check = 1;
            }
        }
        if (check == 0)
        {
            t++;
            continue;
        }

        p[shortest].remaining_time -= 1;
        minimum = p[shortest].remaining_time;
        if (minimum == 0)
            minimum = 100;
        if (p[shortest].remaining_time == 0)
        {
            complete++;
            check = 0;
            finish = t + 1;
            p[shortest].waiting_time = finish - p[shortest].burst_time - p[shortest].arrival_time;

            if (p[shortest].waiting_time < 0)
                p[shortest].waiting_time = 0;
        }

        t++;
    }
    for (int i = 0; i < no_of_processes; i++)
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;

    for (int i = 0; i < no_of_processes; i++)
    {
        turn_time += p[i].turnaround_time;
        wait_time += p[i].waiting_time;
    }
    printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");

    for (int i = 0; i < no_of_processes; i++)
    {
        printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].waiting_time);
    }

    float avg_wait = wait_time / no_of_processes;
    float avg_turn = turn_time / no_of_processes;
    printf("Average waiting time : %f \n", avg_wait);
    printf("Average turnaround time : %f \n", avg_turn);
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
        printf("\t 2. SJF (preemptive)\n");
        printf("\t 3. SJF (Non-Preemptive)\n");
        printf("\t 4. Round Robin\n");
        printf("\t 5. Exit\n");
        printf("Enter choice:  ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            preemptive();
            break;
        case 3:
            nonpreemptive();
            break;
        case 4:
            roundRobin();
            break;
        }
    }
}