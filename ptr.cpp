#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>
using namespace std;
//using std::tr1::shared_ptr;

/*
����ָ��
1.�ص㣺ջ�ϵĶ��������������Զ�����
����ָ�����Ҫ���ڶ���
�����ü���(ǿ����ָ��) :���� ѭ������ʱ�������� �����֤��A B��
*/

/*
����ģʽ:��������ֻ������һ������
���� ˽�л����캯�� �����û��Ͳ�������߶������
*/

class CHeapTable
{
public:
	//��ȡ��������ĵ�ַ �������� ���Բ������ڶ��� Ϊstatic
	static CHeapTable* getInstance()//instanceʵ��
	{
		static CHeapTable table;//���ù��캯�� static��ʼ��ֻһ��
		return &table;
	}
	//��������㷨������ ��ptr��ƥ��Ľ�㣿
	void addRef(void *ptr)
	{
		#if 0
		vector<Node>::iterator it = vec.begin();
		for (; it != vec.end(); ++it)
		{
			if (ptr == it->mpaddr)
			{
				cout<<"add"<<endl;
				it->mcount++;
				return ;
			}
		}
		#endif
		
		vector<Node>::iterator it = find(vec.begin(), vec.end(), ptr);
		if (it != vec.end())
		{
			cout<<"Ref"<<endl;
			it->mcount++;
			return ;
		}

		vec.push_back(*(new Node(ptr)));
	}

	void delRef(void *ptr)
	{
		vector<Node>::iterator it = vec.begin();
		for(; it != vec.end(); ++it)
		{
			if (ptr == it->mpaddr)
			{
				cout<<"del"<<endl;
				it->mcount--;
			}
		}
	}

	int getRef(void *ptr)
	{
		vector<Node>::iterator it = vec.begin();
		for (; it != vec.end(); ++it)
		{
			if (ptr == it->mpaddr)
			{
				return it->mcount;
			}
		}
		//throw "";�����
		return 0;//�ͷ�mptr == NULL ����Ķ��� 		
	}
private:
	CHeapTable(){}
	struct Node
	{
		Node(void *ptr = NULL):mpaddr(ptr),mcount(1){}
		//��find�ṩ==�����������(*frist == ptr)
		bool operator==(const Node &src)
		{
			return mpaddr == src.mpaddr;
		}
		void *mpaddr;
		int mcount;
	};
	vector<Node> vec;
};

//��getRef() == 0ʱ ˵���������һ��ʹ����Դ�� Ҫ��������
template <typename T>
class CSmartPtr
{
public:
	CSmartPtr(T *ptr = NULL):mptr(ptr)
	{
		if (mptr != NULL)
		{
			addRef();
		}
	}
	CSmartPtr(const CSmartPtr<T> &src):mptr(src.mptr)
	{
		if (mptr != NULL)
		{
			addRef();
		}
	}
	CSmartPtr<T>& operator=(const CSmartPtr<T> &src)
	{
		if (&src == this)
		{
			return *this;
		}

		delRef();
		if (0 == getRef())
		{
			delete mptr;
		}

		mptr = src.mptr;
		if (mptr != NULL)
		{
			addRef();
		}
	}
	~CSmartPtr()
	{
		delRef();
		if (0 == getRef())
		{
			delete mptr;
			mptr = NULL;
		}
	}

	T& operator*()
	{
		return *mptr;
	}
	const T& operator*()const
	{
		return *mptr;
	}
	T* operator->()
	{
		return mptr;
	}
	T* operator->()const
	{
		return mptr;
	}
	//��mptr���ӣ�����������Դ
	/*
	void addRef(){mheaptable.addRef(mptr);}
	void delRef(){mheaptable.delRef(mptr);}
	int getRef(){return mheaptable.getRef(mptr);}
	*/
	void addRef(){mheaptable->addRef(mptr);}
	void delRef(){mheaptable->delRef(mptr);}
	int getRef(){return mheaptable->getRef(mptr);}
private:
	T *mptr;
	//static CHeapTable mheaptable;
	static CHeapTable *mheaptable;
};

//template <typename T>
//CHeapTable CSmartPtr<T>::mheaptable = CHeapTable();

template <typename T>
CHeapTable* CSmartPtr<T>::mheaptable = CHeapTable::getInstance();

class Test
{
public:
	Test(){cout<<"Test()"<<endl;}
	~Test(){cout<<"~Test()"<<endl;}
	void func()
	{
		cout<<"Test::func"<<endl;
	}
};

int main()
{
	CSmartPtr<Test> pointer1(new Test);
	CSmartPtr<Test> pointer2(pointer1);
	
	//CSmartPtr<int> pointer2(new int);
	//*pointer2 = 20;
	pointer2->Test::func();

	CSmartPtr<Test> pointer3(new Test);
	pointer3 = pointer2;

	/*
	��������:��ͬ����ʵ������CSmartPtr������static ��(��������)
	�ڶ���(char)ɨ��addRef ��δ�ҵ���ͬ�� �������¿�һ�ڵ� �ܹ���������
	�������ͷŵ���ͬһ���ڴ� 
	�������: 
	1.ȫ�ֵ�CHeapTable mheaptable;//��������
	2.�õ���ģʽ���
	*/
	
	int *p = new int;
	CSmartPtr<int> pointer4(p);
	CSmartPtr<char> pointer5((char*)p);

	return 0;
}

#if 0

//�������˵�ԭ���� �ṩ��Ϊǿ����ָ�� 
class B;
class A
{
public:
	A(){cout<<"A()"<<endl;}
	~A(){cout<<"~A()"<<endl;}
	CSmartPtr<B> _ptrb;
	//shared_ptr<B> _ptrb; 
};

class B
{
public:
	B(){cout<<"B()"<<endl;}
	~B(){cout<<"~B()"<<endl;}
	CSmartPtr<A> _ptra;
	//shared_ptr<A> _ptra;//���ʹ��boost���е�����ָ�룿	
};

int main()
{
	//shared_ptr<A> pa(new A());
	//shared_ptr<B> pb(new B());
	CSmartPtr<A> pa(new A());
	CSmartPtr<B> pb(new B());

	pa->_ptrb = pb;
	pb->_ptra = pa;
	return 0;
}

#endif
#if 0
/*
����:�ڶ��Ͽ��˼��οռ� ����Ҫ ������־λ
��������ֻ������һ��
*/
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T *ptr = NULL):mptr(ptr)
	{	
		++flag;
		cout<<flag<<endl;
	}
	~CSmartPtr()
	{
		--flag;
		cout<<flag<<endl;
		if (flag == 0)
		{
			delete mptr;
		}
	}

	T& operator*()
	{
		return *mptr;
	}
	const T& operator*()const
	{
		return *mptr;
	}
	T* operator->()
	{

		return mptr;
	}
	const T* operator->()const
	{
		return mptr;
	}
private:
	T *mptr;
	static int flag;
};

template <typename T>
int CSmartPtr<T>::flag = 0;

class Test
{
public:
	Test(){cout<<"Test()"<<endl;}
	~Test(){cout<<"~Test()"<<endl;}
	void func()
	{
		cout<<"Test::func"<<endl;
	}
};

int main()
{
	CSmartPtr<Test> pointer1(new Test);
	CSmartPtr<Test> pointer2(pointer1);
	//*pointer2 = 20;
	//pointer2->Test::func();

	CSmartPtr<Test> pointer3(new Test);
	pointer3 = pointer2;

	return 0;
}
#endif
