CXX=g++
FLAGS=-O3 -pedantic -Wall -Werror -std=c++11
OFLAGS=$(FLAGS) -c

all: server client Makefile

server: server.o Database.o connection.o
	$(CXX) $(FLAGS) server.o  Database.o connection.o -pthread -lzmq -o server

Database.o: Database.h Database.cpp
	$(CXX) $(OFLAGS) Database.cpp -o Database.o

client: client.o connection.o
	$(CXX) $(FLAGS) client.o connection.o -lzmq -o client

server.o: server.cpp connection.h
	$(CXX) $(OFLAGS) server.cpp -pthread -lzmq -o server.o

client.o: client.cpp connection.h
	$(CXX) $(OFLAGS) client.cpp -lzmq -o client.o

connection.o: connection.h connection.cpp
	$(CXX) $(OFLAGS) connection.cpp -lzmq -o connection.o

clear:
	rm *.o server client
