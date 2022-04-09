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
    
    // int L = atoi(argv[1]);
    // int H = atoi(argv[2]);
    // char line[6];
    // int data[L];

    FILE* file = fopen("input.txt", "r"); /* should check the result */
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(0);
    }

    FILE *f = fopen("1b_result.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(0);
    }

    // int i = 0;
    // while (fgets(line, sizeof(line), file)) {
    //     data[i] = atoi(line);
    //     ++i;
    // }

    //timer begin
    double time_spent = 0.0;
    clock_t begin = clock();
    int count = 0;
    int status;
    char str[100];
    while(count<NP){
        int pid = fork();
        if(pid ==0){
            sprintf(str,"Hi I am process %d and my parent is %d", getpid(),getppid());
            fprintf (f,"%s\n", str); 
            exit(0);
        }
        else{
            waitpid(pid,&status,WUNTRACED);
        }
       // ++count;
    }

    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    //time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("The elapsed time is %f seconds \n", time_spent);
    fclose(file);
    fclose(f);
}