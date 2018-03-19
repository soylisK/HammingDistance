#sequential code
gcc -o hd HD.c

#OPENMP case of hamming dist
gcc -W -Wall -Wextra -fopenmp -o hdob HD_openmpB.c
gcc -W -Wall -Wextra -fopenmp -o hdoa HD_openmpA.c
gcc -W -Wall -Wextra -fopenmp -o hdoc HD_openmpC.c

#Pthreads case of hamming dist
gcc -W -Wall -Wextra -pthread -o hdpa HD_pthreads_A.c
gcc -W -Wall -Wextra -pthread -o hdpb HD_pthreads_B.c
gcc -W -Wall -Wextra -pthread -o hdpc HD_pthreads_C.c
