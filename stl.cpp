#if 0

#include <iostream>
#include <algorithm>//�����㷨
#include <functional>//��������
#include <vector>
#include <string> 
using namespace std;

//ContainerΪ����
template <typename Container>
void ShowContainer(Container &con)
{
	Container::iterator it = con.begin();//Container<T> ģ��
	for (; it!=con.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

int main()
{
	//1.
	vector<int> vec1;
	for (int i=0; i<15; ++i)
	{
		vec1.push_back(rand()%100);
	}
	ShowContainer(vec1);

	//2.��С������
	sort(vec1.begin(), vec1.end());	
	ShowContainer(vec1);

	//ʹ�ú������� �ɴ�С��
	sort(vec1.begin(), vec1.end(), greater<int>());	
	ShowContainer(vec1);

	//��һ��С��50����������ӡ���������ð�����greater
	vector<int>::iterator it1 = find_if(vec1.begin(), vec1.end(), bind1st(greater<int>(), 50));
	if (it1 == vec1.end())
	{
		cout<<"do not exit"<<endl;
	}
	else
	{
		cout<<"exit:"<<*it1<<endl;
	}

	vector<int>::iterator it2 = find_if(vec1.begin(), vec1.end(), not1(bind2nd(greater<int>(), 50)));
	if (it2 == vec1.end())
	{
		cout<<"do not exit"<<endl;
	}
	else
	{
		cout<<"exit:"<<*it2<<endl;
	}

	//��һ��С��50 ���ð��� less ��ȡ����
	vector<int>::iterator it3 = find_if(vec1.begin(), vec1.end(), bind2nd(less<int>(), 50));
	if (it3 == vec1.end())
	{
		cout<<"do not exit"<<endl;
	}
	else
	{
		cout<<"exit:"<<*it3<<endl;
	}

	vector<int>::iterator it4 = find_if(vec1.begin(), vec1.end(), not1(bind1st(less<int>(), 50)));
	if (it4 == vec1.end())
	{
		cout<<"do not exit"<<endl;
	}
	else
	{
		cout<<"exit:"<<*it4<<endl;
	}
	
	//copy
	vector<int> vec2;
	copy(vec1.begin(), vec1.end(), back_inserter(vec2));
	
	//����vec2�а�40����С˳�����  ԭ��С������                  bind2nd(greater<int>(), 40)
	vector<int>::iterator it5 = find_if(vec2.begin(), vec2.end(), bind1st(less<int>(), 40));
	vec2.insert(it5, 40);
	ShowContainer(vec2);

	//����vec2�а�40����С˳�����  ԭ�ɴ�С��                  bind1st(greater<int>(), 40)
	//vector<int>::iterator it6 = find_if(vec2.begin(), vec2.end(), bind2nd(less<int>(), 40));
	//vec2.insert(it6, 40);
	//ShowContainer(vec2);

	//ɾ50-60֮���һ����[)
	vector<int>::iterator it7 = find_if(vec2.begin(), vec2.end(), bind2nd(greater<int>(), 50));
	if (it7 == vec2.end() || *it7 >= 60)
	{
		cout<<"��Ԫ�ؿ�ɾ"<<endl;
		exit(0);
	}
	vec2.erase(it7);
	ShowContainer(vec2);

	//ɾ30-60֮�������� ��С������
	vector<int>::iterator it8 = find_if(vec2.begin(), vec2.end(), bind2nd(greater<int>(), 30));
	vector<int>::iterator it9 = find_if(vec2.begin(), vec2.end(), bind2nd(greater<int>(), 60));
	if (it8 == vec2.end())
	{
		cout<<"��Ԫ�ؿ�ɾ"<<endl;
		exit(0);
	}
	vec2.erase(it8, it9);
	ShowContainer(vec2);

	//�ɴ�С��[)
	//vector<int>::iterator it11 = find_if(vec2.begin(), vec2.end(), bind2nd(less<int>(), 30));
	//vector<int>::iterator it12 = find_if(vec2.begin(), vec2.end(), bind2nd(less<int>(), 60));
	//if (it12 == vec2.end())
	//{
	//	cout<<"��Ԫ�ؿ�ɾ"<<endl;
	//	exit(0);
	//}
	//vec2.erase(it12, it11);////ע��
	//ShowContainer(vec2);

	//�󳤶ȼ����
	cout<<vec2.size()<<endl;
	vec2.clear();

	ShowContainer(vec2);//Ϊ��

	return 0;
}
#endif


/*
��׼������˳�򣬹���������ʹ�ã�
*/
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include <hash_map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <stack>
using namespace std;


//�������⣺multimap[]��������أ�<string>ʵ������������������
#if 0
/*
����������
1.stack�ײ�ʵ��deque
2.queue�ײ�ʵ��deque
3.priority_queue
���ȼ����У�Ĭ��less,�ײ�ʵ��vector
greater<int>:��ԽС���ȼ�Խ�ߣ����ڶ�ͷ
less<int>�෴
*/
int main()
{
  	queue<int> que;
	que.push(23);
	que.push(12);
	que.push(19);
	while (!que.empty())
	{
		cout<<que.front()<<" ";
		que.pop();
	}
	cout<<endl;

	stack<int> sta;
	sta.push(32);
	sta.push(23);
	sta.push(54);
	sta.push(21);
	while (!sta.empty())
	{
		cout<<sta.top()<<" ";
		sta.pop();
	}
	cout<<endl;

	//priority_queue<int> prique;
	priority_queue<int, vector<int>, greater<int>> prique;
	prique.push(12);
	prique.push(2);
	prique.push(15);
	prique.push(9);
	
	while(!prique.empty())
	{
		cout<<prique.top()<<" ";
		prique.pop();
	}
	cout<<endl;
	return 0;
}
#endif

#if 0
/*
vector
make_heap
*/
template <typename Container>
void ShowContainer(const Container &con)
{
	Container::const_iterator it = con.begin();
	for(; it != con.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

int main()
{
	
	//vector
	vector<int> vec;
	for (int i=0; i<10; ++i)
	{
		vec.push_back(rand()%100+2);
	}
	vec.push_back(1000);
	ShowContainer(vec);
/*
	vector<int> vec2;
	//back_inserter(vec2)ֱ�����Ǹ�������,����front_inserter��Ϊvectorֻ��push_back
	//Ҳ����дΪvec2.begin(),��Ĭ�Ϲ��첻���ռ�
	//copy(vec.begin(), vec.end(), back_inserter(vec2));
	copy(vec.begin(), vec.end(), inserter(vec2, vec2.begin()));
	copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	vec2.clear();

	cout<<"istream vec3 data:"<<endl;
	vector<string> vec3;
	//���ֹͣ���룿��������ʵ����������һ����int��ֹͣ����
	copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(vec3));
	copy(vec3.begin(), vec3.end(), ostream_iterator<string>(cout, " "));

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout," "));
	//ֱ�ӽ�vec��ʼ����β�������Ļ
	//��intʵ����,�������cout,��" ",ÿ���һ����һ���ַ�
	cout<<endl;
*/
	//������<algorithm>
	make_heap(vec.begin(), vec.end(), greater<int>());//С����
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;

	make_heap(vec.begin(), vec.end(), less<int>());//�����
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;

	vec.push_back(2000);
	push_heap(vec.begin(), vec.end(), less<int>());//���������
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	
	//����Ԫ�ػ������,���µ��������
	pop_heap(vec.begin(), vec.end(), less<int>());
	vec.pop_back();
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;

	return 0;
}
#endif 
#if 0
/*
map  pair(key, val)
multimap
*/
int main()
{
	//map
	map<int, string> mymap;
	
	//make_pair��pair��ĺ���ģ�壬���ݲ�������
	mymap.insert(make_pair(10, "hello"));
	mymap.insert(make_pair(29, "world"));
	mymap.insert(make_pair(20, "aaaa"));//��ֵ����һ����ͬ,û�в��ȥ
	mymap[27] = "wowowo";

	//������������Ϊû��->���������
	//copy(mymap.begin(), mymap.end(), ostream_iterator<int, string>(cout, " "));
	map<int, string>::iterator it = mymap.begin();
	for (; it != mymap.end(); ++it)
	{
		//key:it->first,val:it-->second
		cout<<"key:"<<it->first<<"val:"<<it->second;
		cout<<endl;
	}
	
	mymap.erase(20);
	map<int, string>::iterator it2 = mymap.find(27);
	if (it2 != mymap.end())
	{
		mymap.erase(it2);
	}

	it = mymap.begin();
	for (; it != mymap.end(); ++it)
	{
		//key:it->first,val:it-->second
		cout<<"key:"<<it->first<<"val:"<<it->second;
		cout<<endl;
	}

	//multimap
	multimap<int, string, greater<int>> myMultiMap;//�ı�����ʽ
	myMultiMap.insert(make_pair(20, "jijiji"));
	myMultiMap.insert(make_pair(30, "gegege"));
	myMultiMap.insert(make_pair(30, "dadada"));

	//myMultiMap.erase(30);
	//myMultiMap[30] = "lalala";//û��[]��������أ�����
	multimap<int, string, greater<int>>::iterator it3 = myMultiMap.begin();
	for (; it3 != myMultiMap.end(); ++it3)
	{
		cout<<it3->first<<" "<<it3->second;
		cout<<endl;
	}
	return 0;
}
#endif

/*
//�ײ�������������������:Ĭ����С��������less
set
multiset
*/
int main()
{
	set<int> set1;
	set1.insert(10);
	set1.insert(14);
	set1.insert(30);
	set1.insert(23);
	set1.insert(21);
	set1.insert(30);//δ����
	
	copy(set1.begin(), set1.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	cout<<set1.size()<<endl;//5

	multiset<int,greater<int>> myset;//�ı�����ʽ
	//int����һ���ַ�����ֹͣ����
	//copy(istream_iterator<int>(cin), istream_iterator<int>(), inserter(myset, myset.begin()));
	//copy(myset.begin(), myset.end(), ostream_iterator<int>(cout, " "))

	myset.insert(10);
	myset.insert(20);
	myset.insert(30);
	myset.insert(20);
	copy(myset.begin(), myset.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;

	cout<<"================"<<endl;

	cout<<myset.count(20)<<endl;//��20�ĸ���
	//myset.erase(20);
	multiset<int, greater<int>>::iterator it = myset.find(20);//ֻ�ܲ��ҵ���һ��
	if (it != myset.end())
	{
		myset.erase(it);
	}
	copy(myset.begin(), myset.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	
	cout<<"================"<<endl;
	
	myset.insert(79);
	cout<<myset.count(20)<<endl;
	copy(myset.begin(), myset.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	cout<<"================"<<endl;
	//set  list
	list<int> mylist;
	//front_inserterΪ��front_insert_iterator�ĺ���ģ��
	copy(myset.begin(), myset.end(), front_inserter(mylist));
	copy(mylist.begin(), mylist.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	return 0;
 }
