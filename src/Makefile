# make file for 

SOURCES = useMysqlApi.cpp
OBJECTS = useMysqlApi
CC = g++
CFLAG = -g -Wall
INCLUDE = -I/usr/include/mysql
LIB = -lmysqlclient -L/usr/lib/i386-linux-gnu


$(OBJECTS): $(SOURCES) 
	$(CC) $(CFLAG) $(INCLUDE) $(LIB) -o $@ $^
