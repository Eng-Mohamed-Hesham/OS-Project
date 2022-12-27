#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int n;

struct process
{
    int pid, AT, BT, WT, TAT, RT, CT;
} Q1[10], Q2[10], Q3[10], list[30];

void sortByArrival()
{
    struct process temp;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (Q1[i].AT > Q1[j].AT)
            {
                temp = Q1[i];
                Q1[i] = Q1[j];
                Q1[j] = temp;
            }
}

void print_gantt_chart(struct process p[], int n)
{
    int i, j;
    int last = p[n-1].BT + ( n== 1 ? 0 : p[n-1].WT);
    // printing top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].BT; j++) printf("-----");
        printf(" ");
    }
    printf("\n|");
    // middle position
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].BT-1; j++) printf(" ");
        printf("p%d", p[i].pid);
        for(j=0; j<p[i].BT-1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].BT; j++) printf("-----");
        printf(" ");
    }
    printf("\n");

    // printing waiting time
    int minus = 0;
    for(i=0; i<n; i++) {
        if(p[i].WT>9) printf(" ");
        printf("%d", p[i].WT);
        if(p[i+1].WT>9){
          minus = 1;
        }
        if(i+1 == n )  if (last>9) minus = 1;
        for(j=0; j<p[i].BT-minus; j++) printf("  ");

    }
    if(last>9) printf(" ");
    printf("%d\n", last);
}

int main()
{
    int i, j, k = 0, idx = 0, r = 0, time = 0, tmsc1 = 5, tmsc2 = 8, flag = 0;
    char c;
    int proid = ((float)rand() / (float)(RAND_MAX)) * 100;
    printf("Enter no of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++, c++, proid++)
    {
        Q1[i].pid = proid;
        printf("\nEnter the arrival time and burst time of process P%c: ", Q1[i].pid);
        scanf("%d%d", &Q1[i].AT, &Q1[i].BT);
        Q1[i].RT = Q1[i].BT;
    }
    
    sortByArrival();
    
    time = Q1[0].AT;
    for (i = 0; i < n; i++)
    {
        if (Q1[i].RT <= tmsc1) 
        {
            time += Q1[i].RT; //from arrival time of first process to completion of this process
            Q1[i].RT = 0;
            Q1[i].WT = time - Q1[i].AT - Q1[i].BT; // amount of time process has been waiting in the first queue
            Q1[i].TAT = time - Q1[i].AT; // amount of time to execute the process
            // choose Q1[i] as current running process from First Queue with time slice = 5 sec
            list[idx++] = Q1[i];
        }
        else // process moves to queue 2 with time slice = 8
        {
            Q2[k].WT = time;
            time += tmsc1;
            Q1[i].RT -= tmsc1;
            Q2[k].BT = Q1[i].RT;
            Q2[k].RT = Q2[k].BT;
            Q2[k].pid = Q1[i].pid;
            k++;
            flag = 1;
        }
    }
    if (flag == 1)
    {
        for (i = 0; i < k; i++)
        {
            if (Q2[i].RT <= tmsc2)
            {
                time += Q2[i].RT;/*from arrival time of first process +BT of this process*/
                Q2[i].RT = 0;
                Q2[i].WT = time - tmsc1 - Q2[i].BT;/*amount of time process has been waiting in the ready queue*/
                Q2[i].TAT = time - Q2[i].AT;/*amount of time to execute the process*/
                // choose Q2[i] as current running process from Second Queue with time slice = 8 sec
                list[idx++] = Q2[i];
            }
            else/*process moves to queue 3 with FCFS*/
            {
                Q3[r].AT = time;
                time += tmsc2;
                Q2[i].RT -= tmsc2;
                Q3[r].BT = Q2[i].RT;
                Q3[r].RT = Q3[r].BT;
                Q3[r].pid = Q2[i].pid;
                r = r + 1;
                flag = 2;
            }
        }
    }

    if (flag == 2)
    {
        for (i = 0; i < r; i++)
        {
            if (i == 0)
                Q3[i].CT = Q3[i].BT + time - tmsc1 - tmsc2;
            else
                Q3[i].CT = Q3[i - 1].CT + Q3[i].BT;

        }
        for (i = 0; i < r; i++)
        {
            Q3[i].TAT = Q3[i].CT;
            Q3[i].WT = Q3[i].TAT - Q3[i].BT;
            list[idx++] = Q3[i];
        }
    }
    puts("\n");

    print_gantt_chart(list, idx);
}
