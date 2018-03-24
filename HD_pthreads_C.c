/* C program to find hamming distance b/w
* two string
**using pthread
*Medium-Grained Code
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#include <pthread.h>

/*structure */
typedef struct {
  char **sA;
  char **sB;
  int **hd;
  int TotalHammingDistance;
  int lenA;
  int lenB;
  int lenI;
  int nthreads;

}Data;

Data d;

pthread_mutex_t mutex_ham_dist;

void *HamDistance(void *arg)
{

     int i, start, end, len ;
     long offset;
     int count;
     offset = (long)arg;

     len= (d.lenB)/(d.nthreads);
     start = offset*(len);
     end   = start + (len);

     int j=0,l=0;
    for (i=0; i<d.lenA ; i++)
     {
       for(j=start;j<end;j++){
         count=0;
         for(l=0;l<d.lenI;l++)
         {
           if(d.sA[i][l]!=d.sB[j][l]) {
             count++;

           }
         }
         pthread_mutex_lock (&mutex_ham_dist);
         d.hd[i][j]=count;
         //printf("(%d)",HamDist[i][j]);
         d.TotalHammingDistance+=count;
         pthread_mutex_unlock (&mutex_ham_dist);
       }
     }



    pthread_exit((void*) 0);

}


void PrintSomeMessage(char *p)
{
    printf("p: %s\n",p);
}

// driver code
int main(int argc,char **argv)
{
    //initialize sets' number and string's length
    if(argc<5)
      printf("|Not enough arguments as input..\n");
    else if(argc>5)
      printf("|Too many arguments...\n");
    else
      d.lenA=atoi(argv[1]),d.lenB=atoi(argv[2]),d.lenI=atoi(argv[3]),d.nthreads=atoi(argv[4]);

    int i=0,j=0,l=0;

    pthread_t threads[d.nthreads];
    pthread_attr_t attr;
    pthread_mutex_init(&mutex_ham_dist, NULL); //initialize mutex
    void *status;


    /*Allocate memory for two sets of strings*/
    char **setA = malloc(d.lenA * sizeof(char *)); // Allocate row pointers
    for(i = 0; i < d.lenA; i++)
      setA[i] = malloc((d.lenI+1) * sizeof(char));  // Allocate each row separately

    char **setB = malloc(d.lenB * sizeof(char *)); // Allocate row pointers
    for(i = 0; i < d.lenB; i++)
      setB[i] = malloc((d.lenI+1) * sizeof(char));  // Allocate each row separately

    // initialize matrices with random string (0 and 1)
    for (i=0;i<d.lenA;i++){
        for(j=0;j<d.lenI;j++){
            setA[i][j]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[rand() % 62];
        }
        setA[i][d.lenI]='\0';
    }

    for (i=0;i<d.lenB;i++){
        for(j=0;j<d.lenI;j++){
            setB[i][j]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[rand() % 62];
        }
        setB[i][d.lenI]='\0';
    }
    printf("\n setA setB ready \n" );


    //creation of m*n matrix to store all hamming distances and initialize it
    int **HamDist = malloc(d.lenA * sizeof(int *)); // Allocate row pointers
    for(i = 0; i < d.lenA; i++)
      HamDist[i] = malloc(d.lenB * sizeof(int));
    /*assign data to struct member var*/
    d.sA=setA;
    d.sB=setB;
    d.hd=HamDist;

    printf("\n HamDist set \n" );


    clock_t start=clock();
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int rv;
    /*spawn threads*/
    for(l=0;l<d.nthreads;l++)
      rv=pthread_create(&threads[l],&attr,HamDistance,(void*)l);
    if(rv)
      printf("\n|Errror pthread_create\n");

    pthread_attr_destroy(&attr);
    clock_t end =clock();
    double hamm_time=(double)(end-start)/CLOCKS_PER_SEC;

    /* Wait on the other threads */
   for(i=0; i<d.nthreads; i++)
   {
      pthread_join(threads[i], &status);
   }




    printf("\n|Total Hamming execution time= %f",hamm_time);
    printf("\n\n*|The Total Hamming Distance is: %d\n",d.TotalHammingDistance );
    /*destroy them all*/
    pthread_exit(NULL);

    return 0;
}
