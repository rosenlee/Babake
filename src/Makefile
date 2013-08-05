# make file for 

SOURCES = useMysqlApi.cpp
OBJECTS = useMysqlApi
CC = g++
MYSQL_CFLAG = -g -Wall $(mysql_config --cflags) $(mysql_config --libs)
CFLAG := -g -Wall
INCLUDE = -I/usr/include/mysql \
	-I ./		
MYSQL_LIB = -lmysqlclient -L/usr/lib/i386-linux-gnu $(mysql --libs)
LIB :=  -lpthread
TARGET := bin

#$(OBJECTS): $(SOURCES) 
#	$(CC) $(CFLAG) $(INCLUDE) $(LIB) -o $@ $^

.PHONY: all clean

all: $(TARGET) heap multis 

$(TARGET) : 
	@if [ ! -r $(TARGET) ] ; then mkdir -p $(TARGET) ; fi
			


heap:heap.cpp
	$(CC) $(CFLAG) $(INCLUDE) $(LIB) -o $@ $^
	cp heap $(TARGET)/

multis:multiThreads.cpp
	$(CC) $(CFLAG) $(INCLUDE) $(LIB) -o $@ $^
	cp multis $(TARGET)/


clean:
	@rm -rf $(TARGET)
