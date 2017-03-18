#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
/*
����
1.��¼
2.ע��
3.�˳�
*/

class DB
{
public:
	DB()
	{
		_phead = new Node;
	}
	~DB()
	{
		Node *pcur = _phead;
		while (pcur != NULL)
		{
			_phead = _phead->_pnext;
			delete pcur;
		}
		pcur = _phead;
	}
	bool CheckUserMes(char *name, char *pwd)
	{
		Node *p = _phead->_pnext;
		while (p != NULL)
		{
			if (strcmp(p->_name, name)==0 && strcmp(p->_pwd, pwd)==0)
			{
				return true;
			}
			p = p->_pnext;
		}
		return false;
	}
	bool CheckUserName(char *name)
	{
		Node *p = _phead->_pnext;
		while (p != NULL)
		{
			if (strcmp(p->_name, name)==0)
			{
				return true;
			}
			p = p->_pnext;
		}
		return false;
	}
	void WriteUserMes(char *name, char *pwd)
	{
		Node *pnode = new Node(name, pwd);
		pnode->_pnext = _phead->_pnext;
		_phead->_pnext = pnode;
		/*pnode->_pnext = pnode->GetNode();
		pnode->SetNode();*/
	}
private:
	struct Node
	{
		Node():_pnext(NULL){}//ͷ���
		Node(char *name, char*pwd):_pnext(NULL)
		{
			strcpy(_name, name);
			strcpy(_pwd, pwd);
		}
		//void SetNode(Node *pnode)
		//{
		//	_phead->_pnext = pnode;
		//}
		//Node* GetNode()
		//{
		//	return _phead->_pnext;
		//}
		char _name[20];
		char _pwd[20];
		Node *_pnext;
	};
	//Node* GetUserPtr(char* name);
	Node* _phead;
};

class CGUI
{
public:
	CGUI():_running(true){}
	void Run();
	void ShowMenu()
	{
		cout<<"==========="<<endl;
		cout<<"1.��¼"<<endl;
		cout<<"2.ע��"<<endl;
		cout<<"3.�˳�"<<endl;
		cout<<"==========="<<endl;
	}

	void DoLogin()
	{
		cout<<"username:";
		gets(_name);
		cout<<"userpwd:";
		gets(_pwd);

		if (_db.CheckUserMes(_name, _pwd))
		{
			cout<<"��¼�ɹ�"<<endl;
			return;
		}
		cout<<"username������"<<endl;
	}

	void DoRegister()
	{
		cout<<"username:";
		gets(_name);

		if (_db.CheckUserName(_name))
		{
			cout<<"�û����Ѵ���"<<endl;
			return;
		}

		cout<<"userpwd:";
		gets(_pwd);

		_db.WriteUserMes(_name, _pwd);
		cout<<"ע��ɹ�"<<endl;
	}

	void Exit()
	{
		exit (0);
	}
private:
	char _name[20];
	char _pwd[20];
	int _running;//��������
	DB _db;
};

//������
typedef enum
{
	_LOGIN_ = 1,
	_REGISTER_,
	_EXIT_
};
typedef void (CGUI::*PFUNC)();

typedef struct _FuncTable
{
	int choice;
	PFUNC pfunc;
}FuncTable;

FuncTable gTable[3]=
{
	{_LOGIN_, &CGUI::DoLogin},
	{_REGISTER_, &CGUI::DoRegister},
	{_EXIT_, &CGUI::Exit}
};
int length = sizeof(gTable)/sizeof(gTable[0]);

void CGUI::Run()
{
	while(_running)
	{
		int choice;
		ShowMenu();
		cout<<"��ѡ����:";
		cin>>choice;	//����\n
		getchar();

		if (choice<1 || choice>3)
		{
			cout<<"��Ч������������"<<endl;
		}
		//switch(choice)
		//{
		//case 1:
		//	break;
		//case 2:
		//	break;
		//case 3:
		//	break;
		//}
		//������
		for (int i=0; i<length; ++i)
		{
			if (choice == gTable[i].choice)
			{
				(this->*gTable[i].pfunc)();
			}
		}
	}
}

//��������Ҳ����ָ�����������
//DB::Node* DB::GetUserPtr(char* name)
//{
//	Node *pcur = _phead->_pnext;
//	return pcur;
//}

int main()
{
	CGUI test;
	test.Run();
	return 0;
}