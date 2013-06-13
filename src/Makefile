# make file for 

SOURCES = useMysqlApi.cpp
OBJECTS = useMysqlApi
CC = g++
MYSQL_CFLAG = -g -Wall $(mysql_config --cflags) $(mysql_config --libs)
CFLAG := -g -Wall
INCLUDE = -I/usr/include/mysql \
	-I ./		
MYSQL_LIB = -lmysqlclient -L/usr/lib/i386-linux-gnu $(mysql --libs)
LIB := 

#$(OBJECTS): $(SOURCES) 
#	$(CC) $(CFLAG) $(INCLUDE) $(LIB) -o $@ $^

heap:heap.cpp
	$(CC) $(CFLAG) $(INCLUDE) $(LIB) -o $@ $^
