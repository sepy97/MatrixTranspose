gcc -std=c11 uniproctranspose.c -o uniproc.out -lpthread
gcc -std=c11 finetranspose.c -o fine.out -lpthread

./uniproc.out 8 

./fine.out 8 2
