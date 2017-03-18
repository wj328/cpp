#include <iostream>
#include <string>
//using namespace std;//���Է��������ʱ�������δ������ռ䣬
//��Ϊ���ϵͳ�ṩ�ķ�����ͻ(���ǹ����)
using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
STL��׼ģ���
����  vector��������
������
�����㷨
*/

//��������� ʵ�ֹ���汾->���ض������� ��������� ��ʵ�ֵ�
/*
�õ�T���͵����ַ�����
1.ģ�����Ͳ���:template <typename T, typename ContainerIterator>
2.�������������������������ķ���
*/

template <typename ContainerIterator>
class reverse_iterator
{
public:
	typedef typename ContainerIterator::VALUE_TYPE T;//typename ��֪VALUE_TYPEΪһ����
	reverse_iterator(ContainerIterator it):_it(it){}
	bool operator!=(const reverse_iterator &src)
	{
		return _it!=src._it;
	}
	void operator++()//�ⲿ���䣬�ڲ��ı�
	{
		--_it;
	}
	T& operator*()
	{
		return *_it;
	}
	const T& operator*()const//ǰ�����const�кô�����Ȼ���Բ���
	{
		return *_it;
	}
	/*
	T* operator->()
	{
		return &*_it;
	}
	//ǰ����Բ���const
	const T* operator->()const//ǰ��const *_ptr���ܸı���ֵ
	{
		return &*_it;	
	}
	*/
	/*
	��operator->��������غ�������operator*����������_it

	1.return &operator*();
	2.���� *thisΪ����������һ������
	 * *this ���÷���������operator*��ʵ�ʲ���*_it������������operator*
	 �õ�һ���ڴ�����ֵ ��ȡ��ַ����T*����
	*/
	T* operator->()
	{
		return &**this;
	}
	//ǰ����Բ���const
	const T* operator->()const//ǰ��const *_ptr���ܸı���ֵ
	{
		return &**this;	
	}

private:
	ContainerIterator _it;
};

template <typename T>
class vector
{
public:
	typedef T VALUE_TYPE;
	class iterator;//���ǰ������
	typedef reverse_iterator<iterator> reverse_iterator;
	vector():_index(0),_size(1)
	{
		_pvec = new T[1];
		*_pvec = T(); //index����++,����֮������һ��0
	}
				//��ʼ��С     //Ĭ��ֵ
	vector(int initCapacity, T defaultVal = T())
		:_size(initCapacity),_index(0)
	{
		_pvec = new T[_size];
		for (int i=0; i<_size; ++i)
		{
			_pvec[_index++] = defaultVal;
		}
	}
	vector(T *first, T *last):_index(0)
	{
		_size = last - first;
		_pvec = new T[_size];
		for (; first != last; ++first)
		{
			_pvec[_index++] = *first;
		}
	}
	~vector()
	{
		delete []_pvec;
		_pvec = NULL;
	}
	void push_back(const T &val)
	{
		if (full())//���ó���������const
		{resize();}
		_pvec[_index++] = val;
	}
	void pop_back()
	{
		//�ǵ�Ҫ�п�,ûԪ�ؿɳ�
		if (empty())
		{
			return ;
		}
		--_index;
	}
	bool empty()const
	{
		return _index == 0;//
	}
	bool full()const
	{
		return _index == _size;
	}
	void resize()
	{
		T *ptmp = new T[_size*2];
		/*for (int i=0; i<_size; ++i)
		{
			ptmp[i] = _pvec[i];
		}*/
		memcpy(ptmp, _pvec, sizeof(T)*_size);
		delete []_pvec;
		_size = _size*2;
		_pvec = ptmp;
	}

	//���������
	class iterator
	{
	public:
		typedef T VALUE_TYPE;
		iterator(T *ptr):_ptr(ptr){}
		bool operator!=(const iterator &src)
		{
			return _ptr != src._ptr;
		}
		bool operator==(const iterator &src)
		{
			return _ptr == src._ptr;
		}
		bool operator<(const iterator &src)
		{
			return _ptr < src._ptr;
		}
		void operator++()
		{
			++_ptr;
		}
		T* operator++(T)
		{
			T *p = _ptr;
			_ptr++;
			return p;
		}
		void operator--()
		{
			--_ptr;
		}
		iterator operator-(int index)
		{
			return iterator(_ptr-index);
		}
		iterator operator+(int index)
		{
			return iterator(_ptr+index);
		}
		int operator-(const iterator &src)
		{
			return _ptr-src._ptr;
		}
		T& operator*()
		{
			return *_ptr;
		}
		const T& operator*()const
		{
			return *_ptr;
		}
		T* operator->()//���ر����ָ��
		{
			return _ptr;
		}
		//ǰ����Բ���const??
		const T* operator->()const
		{
			return _ptr;	
		}
	private:
		T *_ptr;
	};

	//���������
	iterator begin()
	{
		return iterator(_pvec);
	}
	iterator end()
	{
		return iterator(_pvec+_index);
	}

	//���������
	reverse_iterator rbegin()
	{
		return reverse_iterator(iterator(_pvec+_index-1));
		//reverse_iterator ��Ա����Ϊ����
	}
	reverse_iterator rend()
	{
		return reverse_iterator(iterator(_pvec-1));
	}

	//���������
	/*
	������д ��дΪ���� ��ԭ��:���Կ�������������� ��������ط�����
	����������ķ���������ͬ���������� ʵ�ֹ���汾->���ض�����������
	��������ʵ�ֵ�	
	
	class reverse_iterator
	{
	public:
		reverse_iterator(T *ptr):_ptr(ptr){}
		bool operator!=(const reverse_iterator &src)
		{
			return _ptr != src._ptr;
		}
		void operator++()//�ⲿ���䣬�ڲ��ı�
		{
			--_ptr;
		}
		T operator*()
		{
			return *_ptr;
		}
	private:
		T *_ptr;
	};
	*/
private:
	T *_pvec;
	int _size;//�ڴ���ܴ�С
	int _index;//ʵ�ʵ����ݸ���
	    
	//��ֹ����ǳ����
	vector(const vector<T>&);
	vector<T>& operator=(const vector<T>&);
};

/*
Test ����������ѹ��Test����
*/
class Test
{
public:
 	Test(string name = ""):_name(name){}
	void show()
	{
		cout<<"Test::show name:"<<_name<<endl;
	}
private:
	//char *_name;
	string _name;
};


//�����㷨ʵ��  ð������
/*
ʹ��k://�˴�������last-Itj;��Ϊ�ײ���ָ������õ��������Σ�
������û���ṩ����Ϊ���ε�iterator���캯��
*/
/*
template<typename RandomIterator>
void mysort(RandomIterator first, RandomIterator last)
{
	RandomIterator Iti = first;
	RandomIterator Itj = first;
	RandomIterator::VALUE_TYPE tmp;
	int k = 0;
	for (; Iti<last-1; ++Iti,++k)//++k���ܷ���ѭ���ڣ���Ϊ����һ���ڲ�ѭ��֮��ż�1
	{	
		for (Itj=first; Itj<last-k-1; ++Itj)
		{
			if (*Itj > *(Itj+1))//��С���󣬴Ӵ�С��Ҫ�ı�˴��ķ���
			{
				tmp = *Itj;
				*Itj = *(Itj+1);
				*(Itj+1) = tmp;
			}
		}
	}
} 

//�ص����� �����С����,�Ӵ�С������,ֻ��ı����,����ͷ������дtypename
template <typename RandomIterator>
void mysort(RandomIterator first, RandomIterator last, 
			bool (*func)(typename RandomIterator::VALUE_TYPE ,
			typename RandomIterator::VALUE_TYPE))
{
	RandomIterator Iti = first;
	RandomIterator Itj = first;
	RandomIterator::VALUE_TYPE tmp;
	int k = 0;
	for (; Iti<last-1; ++Iti,++k)
	{	
		for (Itj=first; Itj<last-k-1; ++Itj)
		{
			if ((*func)(*Itj, *(Itj+1)))
			{
				tmp = *Itj;
				*Itj = *(Itj+1);
				*(Itj+1) = tmp;
			}
		}
	}
} 
*/
//�������� ͨ������
template <typename RandomIterator, typename Compare>
void mysort(RandomIterator first, RandomIterator last, Compare comp)
{
	RandomIterator Iti = first;
	RandomIterator Itj = first;
	RandomIterator::VALUE_TYPE tmp;
	int k = 0;
	for (; Iti<last-1; ++Iti,++k)
	{	
		for (Itj=first; Itj<last-k-1; ++Itj)
		{
			//comp������
			if (comp(*Itj, *(Itj+1)))//����operator()��������غ���
			{
				tmp = *Itj;
				*Itj = *(Itj+1);
				*(Itj+1) = tmp;
			}
		}
	}
} 
/*
template <typename RandomIterator>
RandomIterator myfind(RandomIterator first, RandomIterator last, 
					 typename RandomIterator::VALUE_TYPE val)
{
	for (; first!=last; ++first)
	{
		if (*first == val)
		{
			return first;
		}
	}
	return last;
}

//һԪ�������󣬵��ǿ�����ֻ�ж�Ԫ�������󣬴�ʱ��Ҫ����
template <typename RandomIterator, typename Compare>
RandomIterator myfind(RandomIterator first, RandomIterator last, 
					  Compare comp)
{
	for (; first!=last; ++first)
	{
		if (comp(*first))
		{
			return first;
		}
	}
	return last;
}

template <typename T>
class GetFind
{
public:
	GetFind(T val):_val(val){}
	bool operator()(T value)//�������õ���ֵ
	{
		return value==_val;
	}
private:
	T _val;
};
*/
//����
template <typename RandomIterator, typename Compare>
RandomIterator myfind_if(RandomIterator first, RandomIterator last, 
					  Compare comp)
{
	for (; first!=last; ++first)
	{
		if (comp(*first))
		{
			return first;
		}
	}
	return last;
}

template <typename InputIterator, typename OutputIterator>
void mycopy(InputIterator first, InputIterator last, OutputIterator dest)
{
	for (; first!=last; ++first)
	{
		*dest++ = *first;
	}
}

template <typename Container>
class back_insert
{
public:            
	typedef typename Container::VALUE_TYPE T;
	back_insert(Container &con):_con(con){}//&
	void operator=(T val)
	{
		_con.push_back(val);
	}
	//ֻ��Ϊ�˱���ͨ����������ʲô
	back_insert<Container> operator*()
	{
		return *this;
	}
	back_insert<Container> operator++(int)
	{
		return *this;
	}
private:
	Container &_con;
};

template <typename Container>
back_insert<Container> myback_insert(Container &con)
{
	return back_insert<Container>(con);
}

///////////////�ص�����////////////////////
/*
������֪���Ƚϵ���������
*/
bool compare_int_greater(int a, int b)
{
	return a>b;
}
bool compare_int_less(int a, int b)
{
	return a<b;
}
/*
ʹ�ú��������ԭ��:
1.�ص������õ��Ǻ���ָ�룬Ч�ʲ��ߣ�һ�����ᴦ��Ϊ��������
2.��Ҫ��¼���ñȽϺ����Ĵ���������Ҫ��ȫ�ֱ����˷ѿռ�
��������һ����ģ�壬��Ҫ�Ƚ���������(string)�����ṩ������
*/
///////////////��������////////////////////
//��Ԫ��������
template <typename T>
class CMyGreater
{
public:
	bool operator()(T a, T b)
	{
		return a>b;
	}
};

template <typename T>
class CMyLess
{
public:
	bool operator()(T a, T b)
	{
		return a<b;
	}
};

//����
template <typename Compare, typename T>
class CMyBind
{
public:
	typedef T VALUE;
	CMyBind(Compare comp, T val):_comp(comp), _val(val){}
	bool operator()(T val)
	{
		return _comp(val, _val);//_valΪ�󶨵�ֵ,valΪ��������ȡ�� bind
	}
private:
	Compare _comp;
	T _val;
};

//��CMyBind�ṩ����ģ�壬������������
template <typename Compare, typename T>
CMyBind<Compare, T> mybind(Compare comp, T a)
{
	return CMyBind<Compare, T>(comp, a);
}

//ȡ����
template <typename MyBind>
class CMyNot1
{
public:
	CMyNot1(MyBind bind):_bind(bind){}
	bool operator()(typename MyBind::VALUE val)
	{
		return !_bind(val);
	}
private:
	MyBind _bind;
};

//��CMyNot1�ṩ����ģ�壬����ʵ����������
template <typename MyBind>
CMyNot1<MyBind> mynot1(MyBind bind)
{
	return CMyNot1<MyBind>(bind);
}

template <typename Container>
void ShowContainer(Container &con)
{
	Container::iterator it = con.begin();
	for (; it!=con.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

int main()
{

	vector<int> vec1;
	vec1.push_back(10);
	vec1.push_back(15);
	vec1.push_back(13);
	vec1.push_back(19);
	vec1.push_back(17);

	//cout<<typeid(vec1).name()<<endl;
	cout<<"-----���������-----"<<endl;
	ShowContainer(vec1);

	cout<<"-----���������-----"<<endl;
	vector<int>::reverse_iterator rit = vec1.rbegin();
	for (; rit!=vec1.rend(); ++rit)
	{
		cout<<*rit<<" ";
	}
	cout<<endl;

#if 0
	vector<int> vec2;//û�пռ�
	// �����͵�����
	//mycopy(vec1.begin(), vec1.end(), vec2.begin());

	mycopy(vec1.begin(), vec1.end(), myback_insert(vec2));
	ShowContainer(vec2);

	//bind1nd,bind2nd�ѵ�һ/����������
	cout<<"-----����myfind_if------"<<endl;
	//vector<int>::iterator it12 = myfind_if(vec1.begin(),
	//vec1.end(), CMyBind<CMyGreater<int>,int>(CMyGreater<int>(), 11));
	vector<int>::iterator it12 = myfind_if(vec1.begin(),
								vec1.end(), mybind(CMyLess<int>(), 11));
	if (it12 == vec1.end())					//һԪ�������� 10
	{
		cout<<"δ�ҵ�"<<endl;
	}
	else
	{
		cout<<"�ҵ���һ����11�����:"<<*it12<<endl;
	}

	//��һԪ/��Ԫ����ȡ��
	cout<<"------not1/not2ȡ����------"<<endl;
	vector<int>::iterator it13 = myfind_if(vec1.begin(),
		vec1.end(), mynot1(mybind(CMyLess<int>(), 11)));
	//��CMyLessͬ����ô���11�ĵ�һ��ֵ 15
	if (it13 == vec1.end())					
	{
		cout<<"δ�ҵ�"<<endl;
	}
	else
	{
		cout<<"�ҵ���һ����11�����:"<<*it13<<endl;
	}

	cout<<"-----���������-----"<<endl;
	vector<int>::reverse_iterator rit = vec1.rbegin();
	for (; rit!=vec1.rend(); ++rit)
	{
		cout<<*rit<<" ";
	}
	cout<<endl;
	
	Test t1("test1");
	Test t2("test2");
	Test t3("test3");
	vector<Test> vec2;
	vec2.push_back(t1);
	vec2.push_back(t2);
	vec2.push_back(t3);

	cout<<"-----Test�������-----"<<endl;
	vector<Test>::iterator it2 = vec2.begin();
	for (; it2!=vec2.end(); ++it2)
	{
		//��operator[] operator*������ʽ��ͬ
		//it2.operator->(show())
		//����Ϊ (it2.operator->())->show() ǰ����Test*����

		//it2�ײ���һָ��
		it2->show();  
	}
	
	cout<<"-----Test�������-----"<<endl;
	vector<Test>::reverse_iterator rit2 = vec2.rbegin();
	for (; rit2!= vec2.rend(); ++rit2)
	{
		rit2->show();
	}

	cout<<"-----�����㷨ð������-----"<<endl;
	//��С������
	mysort(vec1.begin(), vec1.end());
	ShowContainer(vec1);

	//�ص�����
	mysort(vec1.begin(), vec1.end(), &compare_int_less);  
	ShowContainer(vec1);

	cout<<"------mysort��������------"<<endl;
	mysort(vec1.begin(), vec1.end(), CMyGreater<int>());
	ShowContainer(vec1);

	cout<<"------myfind------"<<endl;
	vector<int>::iterator it10 = myfind(vec1.begin(),
		vec1.end(), 19);//��д��������Ҫ�ı���ҵ�ֵҲֻ��ı���õ�
	if (it10 == vec1.end())
	{
		cout<<"δ�ҵ�"<<endl;
	}
	else
	{
		cout<<"�ҵ�19,index:"<<it10-vec1.begin()<<endl;
	}

	cout<<"-----һԪ��������myfind------"<<endl;
	vector<int>::iterator it11 = myfind(vec1.begin(),
		vec1.end(), GetFind<int>(25));
	if (it11 == vec1.end())
	{
		cout<<"δ�ҵ�"<<endl;
	}
	else
	{
		cout<<"�ҵ�19"<<endl;
	}
#endif
	return 0;
}