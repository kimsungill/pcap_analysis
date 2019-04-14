all : pcap_test

pcap_test: main.o out.o
	g++ -g -o pcap_test main.o out.o -lpcap

main.o: main.cpp out.h
	g++ -g -c -o main.o main.cpp

out.o: out.cpp out.h
	g++ -g -c -o out.o out.cpp

clean:
	rm -f pcap_test
	rm -f *.o

