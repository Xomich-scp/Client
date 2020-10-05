all: client

client: Base_class.o Client_main.o TCP_class.o UDP_class.o
	g++ Base_class.o Client_main.o TCP_class.o UDP_class.o -o client

Base_class.o: Base_class.cpp
	g++ -c Base_class.cpp

Client_main.o:
	g++ -c Client_main.cpp

TCP_class.o:
	g++ -c TCP_class.cpp

UDP_class.o:
	g++ -c UDP_class.cpp

clean:
	rm -rf *.o hello
