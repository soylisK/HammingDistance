/* C program to find hamming distance b/w
* two string
*Sequential Code
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>



void PrintSomeMessage(char *p)
{
    printf("p: %s\n",p);
}

// driver code
void main(int argc,char **argv)
{
    //initialize sets' number and string's length
    int m=atoi(argv[1]),n=atoi(argv[2]),I=atoi(argv[3]);
    int i=0,j=0,l=0,TotalHammingDistance=0;

    //creation of 2-dimentional matrices for setA and setB
    //  char setA[m][I+1];
    //  char setB[n][I+1];
  char **setA = malloc(m * sizeof(char *)); // Allocate row pointers
  for(i = 0; i < m; i++)
    setA[i] = malloc((I+1) * sizeof(char));  // Allocate each row separatel

  char **setB = malloc(n * sizeof(char *)); // Allocate row pointers
  for(i = 0; i < n; i++)
    setB[i] = malloc((I+1) * sizeof(char));  // Allocate each row separatel

    // initialize matrices with random string (0 and 1)
    for (i=0;i<m;i++){
        for(j=0;j<I;j++){
            setA[i][j]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[rand() % 62];
        }
        setA[i][I]='\0';
    }

    for (i=0;i<n;i++){
        for(j=0;j<I;j++){
            setB[i][j]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[rand() % 62];
        }
        setB[i][I]='\0';
    }
    printf("\n setA setB ready \n" );


    //creation of m*n matrix to store all hamming distances and initialize it
    int **HamDist = malloc(m * sizeof(int *)); // Allocate row pointers
    for(i = 0; i < m; i++)
      HamDist[i] = malloc(n * sizeof(int));

    printf("\n HamDist set \n" );
    int count=0;
    clock_t start=clock();
    //Calculate hamming distance for all combinations of the strings
    for (i=0;i<m;i++){
        for(j=0;j<n;j++){
          count=0;
          for(l=0;l<strlen(setB[j]);l++)
          {
            if(setA[i][l]!=setB[j][l]) {
              count++;

            }
          }
          HamDist[i][j]=count;
          //printf("(%d)",HamDist[i][j]);
          TotalHammingDistance+=HamDist[i][j];
        }
    }
    clock_t end =clock();
    double hamm_time=(double)(end-start)/CLOCKS_PER_SEC;




    printf("\n|Total Hamming execution time= %f",hamm_time);
    printf("\n\n*|The Total Hamming Distance is: %d\n",TotalHammingDistance );
}
