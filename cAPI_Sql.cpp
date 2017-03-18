#include "stdio.h"
#include "mysql.h"  // mysql-devel

/*
你可以用mysql_fetch_row函数来查看数据。这样做你将获得一个MYSQL_ROW指针指向数据中的一行。   MYSQL_ROW指针是一简单的字符串数组。所有的数据类型被转换成字符串送到客户端。   
mysql_num_fields函数将告诉你返回的列数。你可以继续调用mysql_fetch_row直到它返回一个空指针以得到查询中的每一行。   
注意在这个例子里，我们没有检查有空指针的列。如果你不使用非空列的表，那么你必须检查一个特殊行的列是否为空。一旦你使用完毕一个结果集，你必须释放它。这通过   mysql_free_result   来完成。   
最后调用mysql_close来关闭你和数据库之间的连接。   
查看结果集你可以调用int   mysql_num_rows(MYSQL_RES   *result)来完成。   
如果你执行一个UPDATE，   INSERT   或者   DELETE   查询，你可以用int   mysql_affected_rows   来查出共有多少行数据被你影响到。   
*/

//实现C语言连接数据库，两个步骤，1,初始化连接句柄结构，2.实际进行连接
//shared_ptr weak_ptr
 int main()
{
	MYSQL * con;
	MYSQL_RES *res;//从数据库返回的结果集
	MYSQL_ROW row;
 
	char tmp[400];//存放SQL语句

	char dbuser[30]="root"; 
	char dbpasswd[30]="apple";
	char dbip[30]="localhost";
	char dbname[50]="excel";
	char tablename[50]="test";
	char *query=NULL;

	int x;
	int y;
	int rt;//return value
	unsigned int t;
	
	int count = 0;
	
	printf("input x,y\n");
	scanf("%d,%d",&x,&y);
	fflush(stdin);
	printf("input over\n");
	con = mysql_init((MYSQL*)0);
	//mysql* mysql_init(mysql*); NULL 返回一个指向新分配的链接句柄结构的指针
	//传递一个已有的结构，这个结构会被重新初始化。出错时返回NULL
    /*mysql* mysql_real_connect(mysql* connection,const char* sever_host,const char* sql_user_name,
								const char* sql_password,const char* db_name,unsigned ont port_number,
								const char* unix_socket_name,unsigned int flags);
								后两个参数和mysql安装的默认设置有关如果无法链接，则返回NULL
	参数解析:1.已有mysql结构的地址con	2.必须是主机名或IP地址，若为NULL或
	"localhost",连接将被视为与本地主机的连接（也可为socket/管道）	3.用户的mysql登录IP
	4.用户的密码	5.数据库名称	6.端口号/0,取决于2	7.NULL（不使用socket/管道）	8.通常为0,可有一些设置*/
	if ( con !=NULL && mysql_real_connect(con,dbip,dbuser,dbpasswd,dbname,3306,NULL,0) )
	{ 
		 if (!mysql_select_db(con,dbname))//int mysql_select_db(mysql* con,const char *db);成功时返回0
		{ 
			printf("Select successfully the database!\n"); 
	          
			con ->reconnect = 1; 
		
			query = "set names \'GBK\'";//防止乱码
			rt=mysql_real_query(con,query,strlen(query));//发送SQL语句
			/*int mysql_real_query(MYSQL *mysql, const char *query, unsigned int length)；
			  执行由query指向的SQL查询，它应该是length字长的字符串，查询必须由单个的SQL语句组成，
			  不应该在语句后增加一个终止的分号，用于对于二进制的查询(包含"\0")，效率比mysql_query快
			  (对于字符串的处理不调用strlen())；成功的话返回0
			  int mysql_query(MYSQL *connection,const char*query);
			*/
			if (rt)
			{         
               printf("Error making query: %s !!!\n",mysql_error(con));
            }
            else
            {
                printf("query %s succeed!\n",query);
            }   
	  }     
      else
      {
          MessageBoxA(NULL,"Unable to connect the database,check your configuration!","",NULL);
     
      }
     
	  //sprintf(tmp,"update %s set 商品=\'%s\',卖出=%d,成交=%d,涨跌=%d,买进=%d,总量=%d,涨幅=%f,时间=\'%s\' where  %s",tablename,goods,sold,deal,fluctuate,buy,total,delta,time,UpdateCon);
      sprintf(tmp,"insert into %s values(%s,%d,%d)",tablename,"null",x,y); 

      //MessageBoxA(NULL,tmp,tmp,MB_OK);
      //mysql_query(con,tmp);
     
      rt=mysql_real_query(con,tmp,strlen(tmp));
      if (rt)
      {
          printf("Error making query: %s !!!\n",mysql_error(con));
               /*char* mysql_error(MYSQL * connection);返回文本错误信息，信息被写进内部静态内存空间
			   unsigned int mysql_errno(MYSQL* connection);返回错误码
			   */
      }
      else
      {
          printf("%s executed!!!\n",tmp);
      }
      
      sprintf(tmp,"select * from %s",tablename);
      
      rt=mysql_real_query(con,tmp,strlen(tmp));//函数将查询送给服务器
      if (rt)
      {
          printf("Error making query: %s !!!\n",mysql_error(con));
      } 
      else
      {
          printf("%s executed!!!\n",tmp);
      }
      
      res = mysql_store_result(con);//从服务器获得结果集
           //MYSQL_RES* mysql_store_result(MYSQL *connection)立即保存返回的数据
           //MYSQL_RES* mysql_use_result(MYSQL *connection);一次返回一行数据，不保存
   	   while(row = mysql_fetch_row(res)) //row指向每行（数组），最终为NULL代表结束 
      {  
		for(t=0;t<mysql_num_fields(res);t++)//函数将告诉你返回的列数
		{
			printf("%s  ",row[t]);  
		}  
        printf(".............\n");  
        count ++;
      }
      printf("number of rows %d\n",count)       
      printf("mysql_free_result...\n");  
      mysql_free_result(res);  /*void mysql_free_result(MYSQL_RES * result) 释放结果集*/
      mysql_close(con);//void mysql_close(mysql* connection)关闭连接
      return 0;
   }