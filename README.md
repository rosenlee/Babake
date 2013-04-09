Babake
======

this  is a learning project

Usage:
name# g++ useMysqlApi.cpp -o useMysqlApi -lmysqlclient -I/usr/include/mysql
or

g++ useMysqlApi.cpp -o useMysqlApi $(mysql_config --cflags) $(mysql_config --libs)
