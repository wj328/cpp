#include <iostream>
#include <string>
//using namespace std;//测试反向迭代器时必须屏蔽此命名空间，
//因为会和系统提供的发生冲突(这是共享的)
using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
STL标准模板库
容器  vector向量容器
迭代器
泛型算法
*/

//反向迭代器 实现共享版本->由特定容器的 正向迭代器 来实现的
/*
得到T类型的两种方法：
1.模板类型参数:template <typename T, typename ContainerIterator>
2.由正向迭代器带过来，如下面的方法
*/

template <typename ContainerIterator>
class reverse_iterator
{
public:
	typedef typename ContainerIterator::VALUE_TYPE T;//typename 已知VALUE_TYPE为一类型
	reverse_iterator(ContainerIterator it):_it(it){}
	bool operator!=(const reverse_iterator &src)
	{
		return _it!=src._it;
	}
	void operator++()//外部不变，内部改变
	{
		--_it;
	}
	T& operator*()
	{
		return *_it;
	}
	const T& operator*()const//前面加上const有好处，当然可以不加
	{
		return *_it;
	}
	/*
	T* operator->()
	{
		return &*_it;
	}
	//前面可以不加const
	const T* operator->()const//前加const *_ptr不能改变其值
	{
		return &*_it;	
	}
	*/
	/*
	让operator->运算符重载函数依赖operator*，而不依赖_it

	1.return &operator*();
	2.如下 *this为反迭代器的一个对象
	 * *this 调用反迭代器的operator*，实际操作*_it调用正迭代器operator*
	 得到一个内存块里的值 再取地址就是T*类型
	*/
	T* operator->()
	{
		return &**this;
	}
	//前面可以不加const
	const T* operator->()const//前加const *_ptr不能改变其值
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
	class iterator;//类的前置声明
	typedef reverse_iterator<iterator> reverse_iterator;
	vector():_index(0),_size(1)
	{
		_pvec = new T[1];
		*_pvec = T(); //index不能++,加了之后会多打出一个0
	}
				//初始大小     //默认值
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
		if (full())//调用常方法不加const
		{resize();}
		_pvec[_index++] = val;
	}
	void pop_back()
	{
		//记得要判空,没元素可出
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

	//正向迭代器
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
		T* operator->()//返回本身的指针
		{
			return _ptr;
		}
		//前面可以不加const??
		const T* operator->()const
		{
			return _ptr;	
		}
	private:
		T *_ptr;
	};

	//正向迭代器
	iterator begin()
	{
		return iterator(_pvec);
	}
	iterator end()
	{
		return iterator(_pvec+_index);
	}

	//反向迭代器
	reverse_iterator rbegin()
	{
		return reverse_iterator(iterator(_pvec+_index-1));
		//reverse_iterator 成员变量为对象
	}
	reverse_iterator rend()
	{
		return reverse_iterator(iterator(_pvec-1));
	}

	//反向迭代器
	/*
	不这样写 而写为共享 的原因:可以看出反向迭代器的 运算符重载方法与
	正向迭代器的方法基本相同，所以我们 实现共享版本->由特定容器的正向
	迭代器来实现的	
	
	class reverse_iterator
	{
	public:
		reverse_iterator(T *ptr):_ptr(ptr){}
		bool operator!=(const reverse_iterator &src)
		{
			return _ptr != src._ptr;
		}
		void operator++()//外部不变，内部改变
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
	int _size;//内存的总大小
	int _index;//实际的数据个数
	    
	//防止发生浅拷贝
	vector(const vector<T>&);
	vector<T>& operator=(const vector<T>&);
};

/*
Test 给容器里面压入Test对象
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


//泛型算法实现  冒泡排序
/*
使用k://此处不能用last-Itj;因为底层两指针相减得到的是整形，
而我们没有提供参数为整形的iterator构造函数
*/
/*
template<typename RandomIterator>
void mysort(RandomIterator first, RandomIterator last)
{
	RandomIterator Iti = first;
	RandomIterator Itj = first;
	RandomIterator::VALUE_TYPE tmp;
	int k = 0;
	for (; Iti<last-1; ++Iti,++k)//++k不能放在循环内，因为走了一遍内层循环之后才加1
	{	
		for (Itj=first; Itj<last-k-1; ++Itj)
		{
			if (*Itj > *(Itj+1))//从小到大，从大到小需要改变此处的符号
			{
				tmp = *Itj;
				*Itj = *(Itj+1);
				*(Itj+1) = tmp;
			}
		}
	}
} 

//回调函数 处理从小到大,从大到小的问题,只需改变参数,函数头部必须写typename
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
//函数对象 通用排序
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
			//comp对象名
			if (comp(*Itj, *(Itj+1)))//调用operator()运算符重载函数
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

//一元函数对象，但是库里面只有二元函数对象，此时需要绑定器
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
	bool operator()(T value)//容器中拿到的值
	{
		return value==_val;
	}
private:
	T _val;
};
*/
//绑定器
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
	//只是为了编译通过，并不做什么
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

///////////////回调函数////////////////////
/*
调用者知道比较的数的类型
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
使用函数对象的原因:
1.回调函数用的是函数指针，效率不高，一定不会处理为内联函数
2.如要记录调用比较函数的次数，必须要设全局变量浪费空间
函数对象一定是模板，若要比较其他类型(string)可以提供特例化
*/
///////////////函数对象////////////////////
//二元函数对象
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

//绑定器
template <typename Compare, typename T>
class CMyBind
{
public:
	typedef T VALUE;
	CMyBind(Compare comp, T val):_comp(comp), _val(val){}
	bool operator()(T val)
	{
		return _comp(val, _val);//_val为绑定的值,val为从容器中取的 bind
	}
private:
	Compare _comp;
	T _val;
};

//给CMyBind提供函数模板，进行类型推演
template <typename Compare, typename T>
CMyBind<Compare, T> mybind(Compare comp, T a)
{
	return CMyBind<Compare, T>(comp, a);
}

//取反器
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

//给CMyNot1提供函数模板，进行实参类型推演
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
	cout<<"-----正向迭代器-----"<<endl;
	ShowContainer(vec1);

	cout<<"-----反向迭代器-----"<<endl;
	vector<int>::reverse_iterator rit = vec1.rbegin();
	for (; rit!=vec1.rend(); ++rit)
	{
		cout<<*rit<<" ";
	}
	cout<<endl;

#if 0
	vector<int> vec2;//没有空间
	// 插入型迭代器
	//mycopy(vec1.begin(), vec1.end(), vec2.begin());

	mycopy(vec1.begin(), vec1.end(), myback_insert(vec2));
	ShowContainer(vec2);

	//bind1nd,bind2nd把第一/二个参数绑定
	cout<<"-----绑定器myfind_if------"<<endl;
	//vector<int>::iterator it12 = myfind_if(vec1.begin(),
	//vec1.end(), CMyBind<CMyGreater<int>,int>(CMyGreater<int>(), 11));
	vector<int>::iterator it12 = myfind_if(vec1.begin(),
								vec1.end(), mybind(CMyLess<int>(), 11));
	if (it12 == vec1.end())					//一元函数对象 10
	{
		cout<<"未找到"<<endl;
	}
	else
	{
		cout<<"找到第一个比11大的数:"<<*it12<<endl;
	}

	//给一元/二元对象取反
	cout<<"------not1/not2取反器------"<<endl;
	vector<int>::iterator it13 = myfind_if(vec1.begin(),
		vec1.end(), mynot1(mybind(CMyLess<int>(), 11)));
	//用CMyLess同样求得大于11的第一个值 15
	if (it13 == vec1.end())					
	{
		cout<<"未找到"<<endl;
	}
	else
	{
		cout<<"找到第一个比11大的数:"<<*it13<<endl;
	}

	cout<<"-----反向迭代器-----"<<endl;
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

	cout<<"-----Test正向迭代-----"<<endl;
	vector<Test>::iterator it2 = vec2.begin();
	for (; it2!=vec2.end(); ++it2)
	{
		//和operator[] operator*解析方式不同
		//it2.operator->(show())
		//解析为 (it2.operator->())->show() 前面是Test*类型

		//it2底层是一指针
		it2->show();  
	}
	
	cout<<"-----Test反向迭代-----"<<endl;
	vector<Test>::reverse_iterator rit2 = vec2.rbegin();
	for (; rit2!= vec2.rend(); ++rit2)
	{
		rit2->show();
	}

	cout<<"-----泛型算法冒泡排序-----"<<endl;
	//从小到大排
	mysort(vec1.begin(), vec1.end());
	ShowContainer(vec1);

	//回调函数
	mysort(vec1.begin(), vec1.end(), &compare_int_less);  
	ShowContainer(vec1);

	cout<<"------mysort函数对象------"<<endl;
	mysort(vec1.begin(), vec1.end(), CMyGreater<int>());
	ShowContainer(vec1);

	cout<<"------myfind------"<<endl;
	vector<int>::iterator it10 = myfind(vec1.begin(),
		vec1.end(), 19);//不写函数对象要改变查找的值也只需改变调用点
	if (it10 == vec1.end())
	{
		cout<<"未找到"<<endl;
	}
	else
	{
		cout<<"找到19,index:"<<it10-vec1.begin()<<endl;
	}

	cout<<"-----一元函数对象myfind------"<<endl;
	vector<int>::iterator it11 = myfind(vec1.begin(),
		vec1.end(), GetFind<int>(25));
	if (it11 == vec1.end())
	{
		cout<<"未找到"<<endl;
	}
	else
	{
		cout<<"找到19"<<endl;
	}
#endif
	return 0;
}