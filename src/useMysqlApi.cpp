#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include "mysql.h"
#include <mysql/mysql.h>
#include <string.h>

using namespace std;

MYSQL DbObj; //handle
MYSQL_RES *pRes; // results
MYSQL_ROW sqlrow; //rows

void mysql_hex_string_test(MYSQL *mysql);


int main()
{
	char tmp[255];
	mysql_init(&DbObj);
	if(!mysql_real_connect(&DbObj, "localhost", "root", "admin", "testdb", 0, NULL, 0))
	{
		cout << "mysql real connect error" << mysql_error(&DbObj) <<endl; 
		return 0;
	}

	cout << "mysql connect success!" << endl;
	const char *ptr = mysql_info(&DbObj) ;
	cout << ptr << endl;
	int ret = (int)mysql_get_server_version(&DbObj) ;
	cout << "get server version :" << ret << endl;
//	cout << mysql_get_server_version(&DbObj) << endl;
	mysql_hex_string_test(&DbObj);




	mysql_close(&DbObj);


	return 0;
}

void mysql_hex_string_test(MYSQL *mysql)
{
	char query[1000];
	char *end;

	end = strcpy(query, "insert into test_table values(");	
	int len = 	strlen(query);
	end = &query[len];
	*end++ = '\''; 
	end += mysql_real_escape_string(mysql, end, "tunes", 5);
	cout << query << endl ; 

	*end++ = '\'';
	*end++ = ',';
	*end++ = '\'';
	end += mysql_real_escape_string(mysql, end, "0", 16);
	*end++ = '\'';
	*end++ = ')';

	cout << "iinsert sql : "<< query << endl ; 
 
	if(mysql_real_query(mysql, query, (unsigned int )(end - query)))
	{
		fprintf(stderr, "Failed to insert row, Error:%s\n",
			mysql_error(mysql));
	}
	
	
	cout <<  mysql_info(mysql) << endl ;
}
