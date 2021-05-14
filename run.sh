rm *.csv

gcc -std=c11 uniproctranspose.c -o uniproc.out -lpthread
gcc -std=c11 finetranspose.c -o fine.out -lpthread
gcc -std=c11 coarsetranspose.c -o coarse.out -lpthread

for n in 8 100 1000 10000
do

./uniproc.out $n >> uniproc.csv 

for t in 2 4 8 16 32 64
do

./fine.out $n $t >> fine.csv
echo '\n' >> fine.csv

done
done

for t in 2 4 8 16 32 64
do

for d in 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 
do

./coarse.out 10000 $t $d >> coarse.csv
echo '\n' >> coarse.csv

done
done
