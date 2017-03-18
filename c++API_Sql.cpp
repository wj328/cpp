#include "mysql.h"
#include <iostream>
using namespace std;

CMySQL::CMySQL(char *ip, unsigned short port,
			   char *user, char *pwd)
			   :mpcon(NULL), mpres(NULL), mpMemcached(NULL)
{
	mpcon = mysql_init((MYSQL*)0);
	if(mpcon == NULL)
	{
		cout<<"mysql init error"<<endl;
		exit(-1);
	}

	if(!mysql_real_connect(mpcon, ip, user, pwd, NULL,5000,NULL,0))
	{
		cout<<"mysql connect error"<<endl;
		exit(-1);
	}

	if(mysql_select_db(mpcon, "chat"))
	{
		cout<<"mysql select db error"<<endl;
		exit(-1);
	}

	cout<<"start memcached module..."<<endl;
	initMemcached();
	cout<<"start memcached module success!"<<endl;
}

CMySQL::~CMySQL()
{
	if(mpres != NULL)
		mysql_free_result(mpres);  
	if(mpcon != NULL)
		mysql_close(mpcon);
}

void CMySQL::initMemcached()
{
	mpMemcached = new CMemcached("127.0.0.1", 6000);
	if(mpMemcached == NULL)
	{
		cout<<"start memcached module error!"<<endl;
		exit(-1);
	}
}

bool CMySQL::queryUser(char *name, char *pwd)
{
	//query memcached
	char *value = mpMemcached->queryKey(name);
	if(value != NULL)
	{
		if(strcmp(pwd, value) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// query mysql
	char sql[100]={0};
	sprintf(sql, "select * from user where name='%s' and pwd='%s';", name, pwd);

	if(mysql_real_query(mpcon,sql,strlen(sql)))
	{
		return false;
	}
	mpres = mysql_store_result(mpcon);
	while(mrow = mysql_fetch_row(mpres))
	{
		if(strcmp(name, mrow[0]) == 0)
		{
			if(strcmp(pwd, mrow[1]) == 0)
			{
				mpMemcached->saveValue(name, pwd);
				return true;
			}
		}
	}

	return false;
}
bool CMySQL::queryRegister(char *name, char *pwd)
{
	//query memcached
	char *value = mpMemcached->queryKey(name);
	if(value != NULL)
	{
		return false;
	}

	// query mysql
	char sql[100]={0};
	sprintf(sql, "select * from user where name='%s';", name);

	if(mysql_real_query(mpcon,sql,strlen(sql)))
	{
		return false;
	}
	mpres = mysql_store_result(mpcon);
	while(mrow = mysql_fetch_row(mpres))
	{
		if(strcmp(name, mrow[0]) == 0)//用户名已存在
		{
			return false;
		}
	}

	sprintf(sql, "insert into user values('%s','%s');", name, pwd);

	if(mysql_real_query(mpcon,sql,strlen(sql)))//执行SQL语句
	{
		return false;
	}

	return true;
}