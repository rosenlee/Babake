#include <iostream>
#include <algorithm>
#include "mysql.h"

using namespace std;

MYSQL DbObj; //handle
MYSQL_RES *pRes; // results
MYSQL_ROW sqlrow; //rows

int main()
{
	char tmp[255];
	mysql_init(&DbObj);
	if(!mysql_real_connect(&DbObj, "localhost", "root", "admin", "testdb", 0, NULL, 0))
	{
		cout << "mysql real connect error" << mysql_error(&DbObj) <<endl; 
		return 0;
	}
	else
	{
		cout << "mysql connect success!" << endl;
		mysql_close(&DbObj);
	}


	return 0;
}

