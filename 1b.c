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

    FILE* file = fopen("input1M.txt", "r"); /* should check the result */
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *f = fopen("1b_result_1M.txt", "w");
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
    //child
    if(pid1==0){
        sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
        fprintf (f,"%s\n", str); 
        for(int i = 0;i<L/6;++i){
            if(data[i] == -1){
                sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                fprintf (f,"%s\n", str); 
            }
        }
        pid_t pid2 = fork();
        //child
        if(pid2==0){ 
            sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
            fprintf (f,"%s\n", str); 
            for(int i = L/6;i<2*L/6;++i){
                if(data[i] == -1){
                    sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                    fprintf (f,"%s\n", str); 
                }
            }
                        pid_t pid3 = fork();
                        //child
                        if(pid3==0){ 
                            sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
                            fprintf (f,"%s\n", str); 
                            for(int i = 2*L/6;i<3*L/6;++i){
                                if(data[i] == -1){
                                    sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                                    fprintf (f,"%s\n", str); 
                                }
                            }
                            exit(1);
                        }
                        //parent
                        else{ 
                            for(int i = 3*L/6;i<4*L/6;++i){
                                if(data[i] == -1){
                                    sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                                    fprintf (f,"%s\n", str); 
                                }
                            }
                            exit(1);
                            waitpid(pid2,&status, WUNTRACED);
                        }            
            exit(1);
        }
        //parent
        else{ 
            for(int i = 4*L/6;i<5*L/6;++i){
                if(data[i] == -1){
                    sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                    fprintf (f,"%s\n", str); 
                }
            }
            exit(1);
            waitpid(pid2,&status, WUNTRACED);
        }
    }
    //main parent
    else{
        sprintf(str,"Hi I am main parent %d", getpid());
        fprintf (f,"%s\n", str); 
        for(int i = 5*L/6;i<L;++i){
                if(data[i] == -1){
                    sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),i);
                    fprintf (f,"%s\n", str); 
                }
        }
        waitpid(pid1,&status, WUNTRACED);
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
    
    // char str[80];
    // sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
    // fprintf (f,"%s\n", str); 
    // for(int i=0;i<H;++i){
    //     sprintf(str,"Hi I am process %d and I found the hidden key in position A[%d]", getpid(),location[i]);
    //     fprintf (f,"%s\n", str); 
    // }
    
    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds \n", time_spent);
    fclose(file);
}