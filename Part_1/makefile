CC = g++
FLAGS = -Wall -std=c++11
OBJECTS = classic_hash.o curve.o curve_ops.o data_ops.o distance_ops.o general_hash.o hash_f.o lsh.o main.o minmax.o rand_utils.o search_ops.o

all : main

main : $(OBJECTS)
	$(CC) $(FLAGS) -o mainexec classic_hash.o curve.o curve_ops.o data_ops.o distance_ops.o general_hash.o hash_f.o lsh.o main.o minmax.o rand_utils.o search_ops.o

classic_hash.o : classic_hash.cpp
	$(CC) $(FLAGS) -c classic_hash.cpp -o classic_hash.o

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

lsh.o : lsh.cpp
	$(CC) $(FLAGS) -c lsh.cpp -o lsh.o

main.o : main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o

minmax.o : minmax.cpp
	$(CC) $(FLAGS) -c minmax.cpp -o minmax.o

rand_utils.o : rand_utils.cpp
	$(CC) $(FLAGS) -c rand_utils.cpp -o rand_utils.o

search_ops.o : search_ops.cpp
	$(CC) $(FLAGS) -c search_ops.cpp -o search_ops.o

.PHONY : clean
clean :
	rm $(OBJECTS) mainexec
