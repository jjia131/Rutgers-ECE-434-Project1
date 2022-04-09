#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void main(int argc, char *argv[])  
{
    
    int L = atoi(argv[1]);
    int H = atoi(argv[2]);
    char line[6];
    int data[L];
    int NP = atoi(argv[3]);
    int X = atoi(argv[4]);
    FILE* file = fopen("input1M.txt", "r"); /* should check the result */
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *f = fopen("1c_result_1M.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        data[i] = atoi(line);
        ++i;
    }

    //timer begin
    double time_spent = 0.0;
    clock_t begin = clock();

    //average
    int sum = 0;
    float average;
    //maximum
    int Max;
    char str[100];

    //fork() system call for multiprocessing
    pid_t pid1 = fork();
    int status;
    int count = 0;
    int count1 = 0;
    while(count<NP){
        int pid = fork();
        if(pid ==0){
            sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
            fprintf (f,"%s\n", str); 
            //do search
            for(int i = count*L/(NP*X);i<(count+1)*L/(NP*X);++i){
                if(data[i] == -1){
                    sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                    fprintf (f,"%s\n", str); 
                }
            }
            while(count1<X){
                int pid = fork();
                if(pid ==0){
                    sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
                    fprintf (f,"%s\n", str); 
                    //do search
                    for(int i = count1*L/(NP*X);i<(count1+1)*L/(NP*X);++i){
                        if(data[i] == -1){
                            sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                            fprintf (f,"%s\n", str); 
                        }
                    }
                    exit(0);
                }
                else{
                    waitpid(pid,&status,WUNTRACED);
                }
                ++count1;
            }
            exit(0);
        }
        else{
            waitpid(pid,&status,WUNTRACED);
        }
        ++count;
    }
    //maximum 
    qsort(data, L, sizeof(int), cmpfunc);
    Max = data[L-1];

    //average
    for(int i = 0;i<L;++i){
        sum = sum + data[i];
    }
    average = sum/L;

    sprintf(str,"AVG = %f", average);
    fprintf (f,"%s\n", str); 
    sprintf(str,"MAX = %d", Max);
    fprintf (f,"%s\n", str); 
    
    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds \n", time_spent);
    fclose(file);
}