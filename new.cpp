#include <iostream>
using namespace std;

/*
�ڴ��
*/
#if 0
const int ITEM_SIZE=1000;

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();
	void addQue(const T &val);
	void delQue();
	T top()const;
	bool empty()const;
private:
	class QueueItem
	{
	public:
		QueueItem(T data=T());
		void* operator new(size_t size);
		void operator delete(void *ptr);

		static QueueItem *mpfreelist;//����������õ�
		T mdata;
		QueueItem *mpnext;
	};
	QueueItem *mpfront;
	QueueItem *mprear;
};

//mpfreelist�ĳ�ʼ��
template <typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::mpfreelist = NULL;

template <typename T>
Queue<T>::QueueItem::QueueItem(T data=T()):mdata(data),mpnext(NULL){}
/*
��Ƶ������ϵͳnew��deleteʱ������Ҫ �ڴ�أ����ٵ���ϵͳnew��delete�Ĵ���
�������ڴ���ǲ�������ڴ�й¶�ģ���mpfreelistָ���µģ����;ɵ�������ϵ��
�ͷŲ�������ڴ�й¶
�ڴ��һ�㲻�ͷţ����ǽ��̽�������ʱ��Դȫ���黹ϵͳ
*/
template <typename T>
void* Queue<T>::QueueItem::operator new(size_t size)
{
	QueueItem *p = mpfreelist;
	if (!mpfreelist)
	{
		cout<<"new"<<endl;//�鿴���˼����ڴ��

		
		//mpfreelist = new QueueItem[10000],new QueueItemʱ����new���أ��ݹ����
		int allocsize = ITEM_SIZE*size;
		mpfreelist = (QueueItem*)new char[allocsize];

		//�γ�����
		p = mpfreelist;
		for (; p<mpfreelist+ITEM_SIZE-1; ++p)
		{ 
			p->mpnext = p+1;//ָ���1�ǰ������ʹ�С���мӵ�
		}	
		p->mpnext = NULL;//���һ������ָ�����ÿ�(һֱ������ڴ����)
	}

	p = mpfreelist;
	mpfreelist = mpfreelist->mpnext;
	return p;
}

template <typename T>
void Queue<T>::QueueItem::operator delete(void *ptr)
{
	cout<<"delete"<<endl;
	if (ptr == NULL)
	{
		return;
	}

	QueueItem *p = (QueueItem *)ptr;
	p->mpnext = mpfreelist;
	mpfreelist = p;
}

template <typename T>
Queue<T>::Queue()
{
	mpfront = mprear = new QueueItem;
}

template <typename T>
Queue<T>::~Queue()
{
	QueueItem *pcur = mpfront;
	while (pcur != NULL)
	{
		mpfront = mpfront->mpnext;
		delete pcur;

		pcur = mpfront;
	}
}

template <typename T>
void Queue<T>::addQue(const T &val)
{
	QueueItem *ptmp = new QueueItem(val);

	mprear->mpnext = ptmp;
	mprear = ptmp;
}

template <typename T>
void Queue<T>::delQue()
{
	if (empty())
	{
		return;
	}
	
	QueueItem *pcur = mpfront->mpnext;
	if (pcur->mpnext == NULL)
	{
		mprear = mpfront;
	}

	mpfront->mpnext = pcur->mpnext;
	delete pcur;
}

template <typename T>
T Queue<T>::top()const
{
	return mpfront->mpnext->mdata;
}

template <typename T>
bool Queue<T>::empty()const
{
	return mpfront == mprear;
}

int main()
{
	Queue<int> queue;
	for (int i=10; i<20; ++i)
	{
		queue.addQue(i);
	}

	int tmp;
	for (int i=0; i<10; ++i)
	{
		tmp = queue.top();
		cout<<tmp<<endl;
		queue.delQue();
	}

	return 0;
} 
#endif
#if 0
/*
new,delete���������
����
*/
void* operator new(size_t size)
{
	void *p = NULL;
	if ((p = malloc(size)) == NULL)
		throw "";  // bad_alloc
	return p;
}

void operator delete(void *ptr)
{
	if (ptr == NULL)
		return ;
	free(ptr);
}

//sizeΪ����ռ���ܴ�С
void* operator new[](size_t size)
{
	void *p = NULL;
	if ((p = malloc(size)) == NULL)
		throw "";
	return p;
}

void operator delete[](void *ptr)
{
	if (ptr == NULL)
		return ;
	free(ptr);
}

int main()
{
	int *p = new int;
	delete p;

	int *q = new int[10];
	delete []q;

	return 0;
}
#endif

/*
[]�뵥������
��������
�Զ�������
inline release�汾 debug�汾
���ṩ����ʱnew[],main�����p��ͬ����֮
*/

class Test
{
public:
	Test(){cout<<"Test()"<<endl;}
	~Test(){cout<<"~Test()"<<endl;}
	void* operator new(size_t size)
	{
		void *p = NULL;
		if ((p = malloc(size)) == NULL)
			throw "";  // bad_alloc
		cout<<"new:"<<p<<endl;
		return p;
	}

	void operator delete(void *ptr)
	{
		if (ptr == NULL)
			return ;
		cout<<"delete ptr:"<<ptr<<endl;
		free(ptr);
	}

	void* operator new[](size_t size)
	{
		void *p = NULL;
		if ((p = malloc(size)) == NULL)
			throw "";
		cout<<"new[]:"<<p<<endl;
		return p;
	}

	void operator delete[](void *ptr)
	{
		if (ptr == NULL)
			return ;
		cout<<"delete[] ptr:"<<ptr<<endl;
		free(ptr);
	}
private:
	int ma;
};

/*
release�汾
delete []p:push  offset Test::~Test (0B91000h) 
delete q:push offset string "~Test()" (272154h) 
*/
int main()
{
	//Test *p = new Test;
	//cout<<"main:"<<p<<endl;
	//delete []p; //����delete[],�����鴦��,���ͷ���4�ֽ�

	//Test *q = new Test[10];
	//cout<<"main:"<<q<<endl;//��new[]��q��4,֮��,4byte��Ÿ���,ʵ�ʿ��ռ�44
	//delete q;//�ͷ�ʱ��q,ֻ�ͷ���40�ֽ�

	
	//��������ʼ��ַ,�������ڴ�й¶,����������
	Test *p = new Test;
	delete (char*)p;

	char *q = (char*)new Test;
	delete q;

	/*
	�ڴ��ͷ�������,�Ͳ��ṩ����(release�汾)�����һ��,ֻ�ǲ��ᱨ��
	int *p = new int;
	cout<<"main:"<<p<<endl;
	delete []p;

	int *q = new int[10];
	cout<<"main:"<<q<<endl;
	delete q;
	*/

	return 0;
}