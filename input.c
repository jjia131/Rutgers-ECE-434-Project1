/**
 * C program to create a file and write data into file.
 */

#include <stdio.h>
#include <stdlib.h>


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[] )
{
    /* Variable to store user content */
    int L = atoi(argv[1]);
    int H = atoi(argv[2]);
    /* File pointer to hold reference to our file */
    FILE * file;

    /* 
     * Open file in w (write) mode. 
     * "***.txt" is complete path to create file
     */
    file = fopen("input.txt", "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(file == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    int location[H];
    int j = 0;
    for(int i = 0;i<H;++i){
        location[i] = rand()%L;
    }
    qsort(location, H, sizeof(int), cmpfunc);
    for(int i = 0;i<L;++i){
        if(location[j]==i){
            fprintf (file,"%d\n",-1); 
            ++j;
        }
        else{
            fprintf (file,"%d\n", rand()%5000); 
        }
    }
    
    return 0;
}