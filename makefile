CC = g++
CFLAGS = -O2 -Wall -pedantic `mysql_config --cflags`
LIBS = -lm -lnsl `mysql_config --libs`

#test: test_1.o
#	$(CC) -o test test_1.o $(CFLAGS) $(LIBS)
#test_1.o: test_1.c
all:
	$(CC)  test_1.c -o test $(CFLAGS) $(LIBS)
clean:
	rm -f test*.o

#install: test
#    cp test /usr/bin

