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
void mysql_select(MYSQL *mysql);


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
	if (NULL != ptr) cout << ptr << endl;
	int ret = (int)mysql_get_server_version(&DbObj) ;
	cout << "get server version :" << ret << endl;
	cout << "character set: " <<  mysql_character_set_name(&DbObj) << endl;
//	mysql_hex_string_test(&DbObj);
	mysql_select(&DbObj);

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
//	cout << query << endl ; 

	*end++ = '\'';
	*end++ = ',';
	*end++ = '\'';
	end += mysql_real_escape_string(mysql, end, "0", 1);
	*end++ = '\'';
	*end++ = ')';

	cout << "insert sql : "<< query << endl ; 
 
	if(mysql_real_query(mysql, query, (unsigned int )(end - query)))
	{
		fprintf(stderr, "Failed to insert row, Error:%s\n",
			mysql_error(mysql));
	}
	
	
//	cout <<  mysql_info(mysql) << endl ;
}

void mysql_select(MYSQL *mysql)
{
	char query[128]; 
	char *end ; // end of query string

	end = strcpy(query, "SELECT * FROM test_table");
	int len = strlen(query);

	if(mysql_real_query(mysql, query, (unsigned int)(len)))
	{
			fprintf(stderr, "faild to select data from test_table: %s\n",
							mysql_error(mysql));
	}

	/* store result */
	MYSQL_RES * result = mysql_store_result(&DbObj);
	if (NULL == result )
	{
			cout << "fail!! mysql store result: "<< mysql_error(&DbObj) << endl;
	}
	else
	{
	/*fetch field */
	MYSQL_FIELD *field;

	while((field = mysql_fetch_field(result)))
	{
		cout << "field name : " << field->name << endl; 
	}
		/* fetch row */
		MYSQL_ROW row;
		unsigned int num_fields; // number of fields in each row
		unsigned int i;	

		num_fields = mysql_num_fields(result);	
		cout << "number of fields: " << num_fields << endl; 


		while((row = mysql_fetch_row(result)))
		{
			unsigned long *lengths;

			lengths = mysql_fetch_lengths(result);

			for(i = 0; i < num_fields; i++ )
			{
				cout << /*lengths[i] <<*/ "\t" << row[i]?row[i] : "NULL" ;			
			}
			cout << endl;			
		}

		/*clean up*/
		mysql_free_result(result);
	}
}
