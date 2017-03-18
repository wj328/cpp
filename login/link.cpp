#if 0 
#include<iostream>
using namespace std;

class Node
{
public:
	Node(int data=0):_data(data),_pnext(NULL){}
private:
	int _data;
	Node* _pnext;

	friend class CLink;
};

class CLink
{
public:
	CLink()
	{
		_phead = new Node;//Í·½áµã
	}

	~CLink()
	{
		Node *pcur = _phead;
		while (pcur != NULL)
		{
			_phead = _phead->_pnext;
			delete pcur;
			pcur = _phead;
		}
	}

	void InsertHead(int val)
	{
		Node *ptmp = new Node(val);
		ptmp->_pnext = _phead->_pnext;
		_phead->_pnext = ptmp;
	}

	void InsertTail(int val)
	{
		Node *ptmp = new Node(val);
		Node *pcur = _phead;
		while (pcur->_pnext != NULL)
		{
			pcur = pcur->_pnext;
		}
		pcur->_pnext = ptmp;
	}

	void Show()
	{
		Node *pcur = _phead->_pnext;
		while (pcur != NULL)
		{
			cout<<pcur->_data<<" "<<endl;
			pcur = pcur->_pnext;
		}
	}
private:
	Node *_phead;
};

int main()
{
	CLink link;
	link.InsertHead(10);
	link.Show();
	return 0;
}

#endif