#include "stdio.h"
#include "mysql.h"  // mysql-devel

/*
�������mysql_fetch_row�������鿴���ݡ��������㽫���һ��MYSQL_ROWָ��ָ�������е�һ�С�   MYSQL_ROWָ����һ�򵥵��ַ������顣���е��������ͱ�ת�����ַ����͵��ͻ��ˡ�   
mysql_num_fields�����������㷵�ص�����������Լ�������mysql_fetch_rowֱ��������һ����ָ���Եõ���ѯ�е�ÿһ�С�   
ע����������������û�м���п�ָ����С�����㲻ʹ�÷ǿ��еı���ô�������һ�������е����Ƿ�Ϊ�ա�һ����ʹ�����һ���������������ͷ�������ͨ��   mysql_free_result   ����ɡ�   
������mysql_close���ر�������ݿ�֮������ӡ�   
�鿴���������Ե���int   mysql_num_rows(MYSQL_RES   *result)����ɡ�   
�����ִ��һ��UPDATE��   INSERT   ����   DELETE   ��ѯ���������int   mysql_affected_rows   ��������ж��������ݱ���Ӱ�쵽��   
*/

//ʵ��C�����������ݿ⣬�������裬1,��ʼ�����Ӿ���ṹ��2.ʵ�ʽ�������
//shared_ptr weak_ptr
 int main()
{
	MYSQL * con;
	MYSQL_RES *res;//�����ݿⷵ�صĽ����
	MYSQL_ROW row;
 
	char tmp[400];//���SQL���

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
	//mysql* mysql_init(mysql*); NULL ����һ��ָ���·�������Ӿ���ṹ��ָ��
	//����һ�����еĽṹ������ṹ�ᱻ���³�ʼ��������ʱ����NULL
    /*mysql* mysql_real_connect(mysql* connection,const char* sever_host,const char* sql_user_name,
								const char* sql_password,const char* db_name,unsigned ont port_number,
								const char* unix_socket_name,unsigned int flags);
								������������mysql��װ��Ĭ�������й�����޷����ӣ��򷵻�NULL
	��������:1.����mysql�ṹ�ĵ�ַcon	2.��������������IP��ַ����ΪNULL��
	"localhost",���ӽ�����Ϊ�뱾�����������ӣ�Ҳ��Ϊsocket/�ܵ���	3.�û���mysql��¼IP
	4.�û�������	5.���ݿ�����	6.�˿ں�/0,ȡ����2	7.NULL����ʹ��socket/�ܵ���	8.ͨ��Ϊ0,����һЩ����*/
	if ( con !=NULL && mysql_real_connect(con,dbip,dbuser,dbpasswd,dbname,3306,NULL,0) )
	{ 
		 if (!mysql_select_db(con,dbname))//int mysql_select_db(mysql* con,const char *db);�ɹ�ʱ����0
		{ 
			printf("Select successfully the database!\n"); 
	          
			con ->reconnect = 1; 
		
			query = "set names \'GBK\'";//��ֹ����
			rt=mysql_real_query(con,query,strlen(query));//����SQL���
			/*int mysql_real_query(MYSQL *mysql, const char *query, unsigned int length)��
			  ִ����queryָ���SQL��ѯ����Ӧ����length�ֳ����ַ�������ѯ�����ɵ�����SQL�����ɣ�
			  ��Ӧ������������һ����ֹ�ķֺţ����ڶ��ڶ����ƵĲ�ѯ(����"\0")��Ч�ʱ�mysql_query��
			  (�����ַ����Ĵ�������strlen())���ɹ��Ļ�����0
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
     
	  //sprintf(tmp,"update %s set ��Ʒ=\'%s\',����=%d,�ɽ�=%d,�ǵ�=%d,���=%d,����=%d,�Ƿ�=%f,ʱ��=\'%s\' where  %s",tablename,goods,sold,deal,fluctuate,buy,total,delta,time,UpdateCon);
      sprintf(tmp,"insert into %s values(%s,%d,%d)",tablename,"null",x,y); 

      //MessageBoxA(NULL,tmp,tmp,MB_OK);
      //mysql_query(con,tmp);
     
      rt=mysql_real_query(con,tmp,strlen(tmp));
      if (rt)
      {
          printf("Error making query: %s !!!\n",mysql_error(con));
               /*char* mysql_error(MYSQL * connection);�����ı�������Ϣ����Ϣ��д���ڲ���̬�ڴ�ռ�
			   unsigned int mysql_errno(MYSQL* connection);���ش�����
			   */
      }
      else
      {
          printf("%s executed!!!\n",tmp);
      }
      
      sprintf(tmp,"select * from %s",tablename);
      
      rt=mysql_real_query(con,tmp,strlen(tmp));//��������ѯ�͸�������
      if (rt)
      {
          printf("Error making query: %s !!!\n",mysql_error(con));
      } 
      else
      {
          printf("%s executed!!!\n",tmp);
      }
      
      res = mysql_store_result(con);//�ӷ�������ý����
           //MYSQL_RES* mysql_store_result(MYSQL *connection)�������淵�ص�����
           //MYSQL_RES* mysql_use_result(MYSQL *connection);һ�η���һ�����ݣ�������
   	   while(row = mysql_fetch_row(res)) //rowָ��ÿ�У����飩������ΪNULL������� 
      {  
		for(t=0;t<mysql_num_fields(res);t++)//�����������㷵�ص�����
		{
			printf("%s  ",row[t]);  
		}  
        printf(".............\n");  
        count ++;
      }
      printf("number of rows %d\n",count)       
      printf("mysql_free_result...\n");  
      mysql_free_result(res);  /*void mysql_free_result(MYSQL_RES * result) �ͷŽ����*/
      mysql_close(con);//void mysql_close(mysql* connection)�ر�����
      return 0;
   }