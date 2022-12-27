#include <stdio.h>
#include <stdlib.h>
double average_waiting_time;
int total_waiting_time;
#define MAX_PROCESS 100
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
struct Process
{
    int pid, arrival_time, burrst_time, waiting_time, turn_around_time, run_time;
};
int num_process, remain, flag = 0, ts, choice, i;
float avg_waiting_time = 0, avg_turnarround_time = 0;

void Print_Gantt_Chart(struct Process a[]);
void sort_arrival_time(struct Process a[], int num_process);
void print_table(struct Process a[]);
void calculate_waiting_time(struct processes p[], int n)
{
    int i;
    total_waiting_time = 0;
    p[0].waiting_time = 0;
    for (i = 1; i < n; i++)
    {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        total_waiting_time += p[i].waiting_time;
    }
}
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

}
void sortForSJF(struct processes *p, int np)
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

void SortForFCFS(struct processes p[], int np)
{
    struct processes t;
    for (int i = 0; i < np - 1; i++)
    {
        for (int j = 0; j < np - i - 1; j++)
        {
            if (p[j + 1].arrival_time < p[j].arrival_time)
            {
                t = p[j + 1];
                p[j + 1] = p[j];
                p[j] = t;
            }
        }
    }
}

void fcfs()
{
    int no_of_processes;
    printf("\nFirst Come First Served Algorithm\n");
    printf("Note -\n1. Arrival Time of at least on process should be 0\n2. CPU should never be idle\n");
    printf("Enter number of processes:  ");
    scanf("%d", &no_of_processes);
    printf("**********************************\n");
    struct processes *p = malloc(sizeof(struct processes) * no_of_processes);
    for (int i = 0; i < no_of_processes; i++)
    {
        printf("Enter Burst time of p[%d]:  ", i);
        scanf("%d", &p[i].burst_time);
        printf("Enter arrival time of p[%d]:  ", i);
        scanf("%d", &p[i].arrival_time);
        p[i].pid = i;
        printf("**********************************\n");
    }
    int wait_time = 0;
    int turn_time = 0;
    SortForFCFS(p, no_of_processes);
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
    print_gantt_chart(p, no_of_processes);
}



void sjf()
{
    struct processes p[MAX_PROCESS];
    int n, i, j;
    puts("SHORTEST JOB FIRST SCHEDULING ALGORITHM");
    puts("=======================================");

    printf("Enter total process: ");
    scanf("%d", &n);
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
    }

    sortForSJF(p, n);
    calculate_waiting_time(p, n);

    average_waiting_time = (double)((double)total_waiting_time / (double)n);

    puts("");
    printf("Average Waiting Time: %.2lf\n", average_waiting_time);

    printf("Gantt Chart:\n");
    print_gantt_chart(p, n);
    printf("*****************************************************************************************************\n");
}

void roundRobin()
{
    printf("Round Robin Scheduling Algorithm\n");
    printf("Note -\n1. Arrival Time of at least on process should be 0\n2. CPU should never be idle\n");

    printf("To Run The Default Dataset choose (1) \nTo Enter User's Dataset Choose (2)\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        struct Process a[5] =
            {{0, 0, 5, 0, 0, 5},
             {1, 5, 10, 0, 0, 10},
             {2, 10, 25, 0, 0, 25},
             {3, 5, 10, 0, 0, 10},
             {4, 10, 15, 0, 0, 15}};
        remain = 5;
        ts = 5;
        num_process = 5;
        sort_arrival_time(a, 5);
        Print_Gantt_Chart(a);
        print_table(a);
    }

    if (choice == 2)
    {
        printf("Enter Number Of Processes : ");
        scanf("%d", &num_process);
        struct Process a[num_process];
        remain = num_process;

        for (int i = 0; i < num_process; i++)
        {
            printf("Enter arrival time and Burst time for Process P%d : ", i);
            scanf("%d%d", &a[i].arrival_time, &a[i].burrst_time);
            a[i].pid = i;
            a[i].run_time = a[i].burrst_time;
        }
        printf("Enter Time Slice : ");
        scanf("%d", &ts);
        sort_arrival_time(a, num_process);
        Print_Gantt_Chart(a);
        print_table(a);
    }

    return;
}

void SRTF () {
    printf("\n---------------------------------Shortest Remaining Time First SIMULATION-------------------------------------------");
    int a[10], b[10], x[10];
    int waiting[10], turnaround[10], completion[10];
    int i, j, smallest, count = 0, time, n;
    double avg = 0, tt = 0, end;
    printf("\nEnter the number of Processes: ");
    scanf("%d", &n);
    printf("\n----------------------------------------------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\nEnter arrival time of process %d (At least 0):  ", i + 1);
        scanf("%d", &a[i]);
    }
    printf("\n----------------------------------------------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\nEnter burst time of process %d (max 99):  ", i + 1);
        scanf("%d", &b[i]);
    }
    printf("\n----------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
        x[i] = b[i];

    b[9] = 100;
    for (time = 0; count != n; time++)
    {
        smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (a[i] <= time && b[i] < b[smallest] && b[i] > 0)
            {
                smallest = i;
                // printf("First: b[%d] = %d, time = %d\t\t", smallest, b[smallest], time);
            }
        }
        b[smallest]--;
        // printf("Second: b[%d] = %d, time = %d", smallest, b[smallest], time);
        if (b[smallest] == 0)
        {
            count++;
            end = time + 1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }

    printf("pid \t burst \t arrival \twaiting \tturnaround \tcompletion");
    printf("\n----------------------------------------------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\n %d \t   %d \t %d\t\t%d   \t\t%d\t\t%d", i + 1, x[i], a[i], waiting[i], turnaround[i], completion[i]);
        printf("\n----------------------------------------------------------------------------");
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }

    printf("\nWaiting Time=%lf\nTurnAround Time=   %lf", avg, tt);
    printf("\n----------------------------------------------------------------------------");
    printf("\nAverage waiting time = %lf\n", avg / n);
    printf("\nAverage Turnaround time = %lf", tt / n);
    printf("\n\n\n*******************************THE END***************************************\n");
    return ;
}

int main()
{
    int choice;
    while (choice != 5)
    {
        printf("\t\t Main Menu \n");
        printf("\t 1. FCFS\n");
        printf("\t 2. SJF\n");
        printf("\t 3. SRTF\n");
        printf("\t 4. R-R\n");
        printf("\t 5. Exit\n");
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
            SRTF();
            break;
        case 4:
            roundRobin();
            break;
        }
    }
}

void sort_arrival_time(struct Process a[], int num_process)
{
    int i, j;
    struct Process temp;
    for (i = 0; i < num_process; i++)
    {
        for (j = i + 1; j < num_process; j++)
        {
            if (a[i].arrival_time > a[j].arrival_time)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    return;
}

void Print_Gantt_Chart(struct Process a[])
{
    printf("\n***************************************\n");
    printf("Gantt Chart\n");
    printf("0");
    int i = 0, time = 0;
    while (remain != 0)
    { // check if the current process's current run_time is less than or equals time slice, which means that this
        // is the last slice for that process and finish
        if (a[i].run_time <= ts && a[i].run_time > 0)
        {
            time += a[i].run_time;
            printf(" -> [P%d] <- %d", a[i].pid, time);
            a[i].run_time = 0;
            flag = 1;
        }
        // if the current process's run time is greater than tje time slice, then this prcoess needs one or more time
        // slices to complete
        else if (a[i].run_time > 0)
        {
            a[i].run_time -= ts;
            time += ts;
            printf(" -> [P%d] <- %d", a[i].pid, time);
        }
        // the process enters this conditon if it's completed, and then we reduce the number of active process, and calculate
        // the turn_around by using formula time completion - arrival time
        if (a[i].run_time == 0 && flag == 1)
        {
            remain--;
            a[i].turn_around_time = time - a[i].arrival_time;
            a[i].waiting_time = time - a[i].arrival_time - a[i].burrst_time;
            avg_waiting_time = avg_waiting_time + time - a[i].arrival_time - a[i].burrst_time;
            avg_turnarround_time = avg_turnarround_time + time - a[i].arrival_time;
            flag = 0;
        }
        // Start again from the beginning of the struct array
        if (i == num_process - 1)
            i = 0;
        else if (a[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }
}

void print_table(struct Process a[])
{
    printf("\n\n");
    printf("***************************************************************************\n");
    printf("|Process | Arrival_Time |  Burrst_Time |  Turn_Around_Time  |Waiting_Time\n|");
    printf("***************************************************************************\n");
    for (i = 0; i < num_process; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t  %d\n", a[i].pid, a[i].arrival_time, a[i].burrst_time, a[i].turn_around_time, a[i].waiting_time);
    }
    printf("***************************************************************************\n");
    avg_waiting_time /= num_process;
    avg_turnarround_time /= num_process;
    printf("Average Waiting Time : %.2f\n", avg_waiting_time);
    printf("Average Turn Around Time : %.2f\n", avg_turnarround_time);
}

