CC = g++
FLAGS = -Wall -std=c++11
OBJECTS = assignment.o curve.o curve_ops.o data_ops.o distance_ops.o general_hash.o hash_f.o hashtable_init.o initialization.o lsh.o main.o mean_curves.o minmax.o rand_utils.o range_assign.o silhouette.o sort.o update.o

all : main

main : $(OBJECTS)
	$(CC) $(FLAGS) -o cluster $(OBJECTS)

assignment.o : assignment.cpp
	$(CC) $(FLAGS) -c assignment.cpp -o assignment.o

curve.o : curve.cpp
	$(CC) $(FLAGS) -c curve.cpp -o curve.o

curve_ops.o : curve_ops.cpp
	$(CC) $(FLAGS) -c curve_ops.cpp -o curve_ops.o

data_ops.o : data_ops.cpp
	$(CC) $(FLAGS) -c data_ops.cpp -o data_ops.o

distance_ops.o : distance_ops.cpp
	$(CC) $(FLAGS) -c distance_ops.cpp -o distance_ops.o

general_hash.o : general_hash.cpp
	$(CC) $(FLAGS) -c general_hash.cpp -o general_hash.o

hash_f.o : hash_f.cpp
	$(CC) $(FLAGS) -c hash_f.cpp -o hash_f.o

hashtable_init.o : hashtable_init.cpp
	$(CC) $(FLAGS) -c hashtable_init.cpp -o hashtable_init.o

initialization.o : initialization.cpp
	$(CC) $(FLAGS) -c initialization.cpp -o initialization.o

lsh.o : lsh.cpp
	$(CC) $(FLAGS) -c lsh.cpp -o lsh.o

main.o : main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o

mean_curves.o : mean_curves.cpp
	$(CC) $(FLAGS) -c mean_curves.cpp -o mean_curves.o

minmax.o : minmax.cpp
	$(CC) $(FLAGS) -c minmax.cpp -o minmax.o

rand_utils.o : rand_utils.cpp
	$(CC) $(FLAGS) -c rand_utils.cpp -o rand_utils.o

range_assign.o : range_assign.cpp
	$(CC) $(FLAGS) -c range_assign.cpp -o range_assign.o

silhouette.o : silhouette.cpp
	$(CC) $(FLAGS) -c silhouette.cpp -o silhouette.o

sort.o : sort.cpp
	$(CC) $(FLAGS) -c sort.cpp -o sort.o

update.o :update.cpp
	$(CC) $(FLAGS) -c update.cpp -o update.o

.PHONY : clean
clean :
	rm $(OBJECTS) cluster
