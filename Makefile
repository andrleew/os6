all: server client Makefile connection.h connection.cpp

server: server.o Database.o connection.h connection.cpp
	g++ -O3 -pedantic -Wall -Werror -std=c++11 server.o  Database.o -pthread -lzmq -o server

Database.o: Database.h Database.cpp
	g++ -O3 -pedantic -Wall -Werror -std=c++11 -c Database.cpp -o Database.o

client: client.o connection.h connection.cpp
	g++ -O3 -pedantic -Wall -Werror -std=c++11 client.o -lzmq -o client

server.o: server.cpp connection.h
	g++ -O3 -pedantic -Wall -Werror -std=c++11 server.cpp -pthread -lzmq -c -o server.o

client.o: client.cpp connection.h
	g++ -O3 -pedantic -Wall -Werror -std=c++11 client.cpp -lzmq -c -o client.o

clear:
	rm *.o server client
