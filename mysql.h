#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>
#include <iostream>
using namespace std;

#include "memcached.h"

class CMySQL
{
public:
	CMySQL(char *ip, unsigned short port,
		char *user, char *pwd);
	~CMySQL();
	void initMemcached();

	bool queryUser(char *name, char *pwd);
	bool queryRegister(char *name, char *pwd);
private:
	MYSQL *mpcon;
	MYSQL_RES *mpres;
	MYSQL_ROW mrow;
	CMemcached *mpMemcached;
};

#endif