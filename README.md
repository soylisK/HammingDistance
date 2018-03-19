#1 step
chmod +x run.sh

#2 step
./run.sh ##compiles and create .o for each case

#3 step
#how to run executable files
./executable_name n m I nthreads  ##arguments (n m I nthreads)


##executable_names
HD --hamming distance siquential
hdoa --hamming distance openmp case A
hdob --hamming distance openmp case B
hdoc --hamming distance openmp case C

hdpa --hamming distance pthreads case A
hdpb --hamming distance pthreads case B
hdpc --hamming distance pthreads case C


##read block comments in each .c file for more information about cases (A,B,C)
##ignore warning for casting (void*) in pthread
