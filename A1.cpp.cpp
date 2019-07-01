#include<iostream>
using namespace std;
class tnode
{
	int d;
	tnode *left,*right;
	public:
	friend class bintree;
};
class queue
{
	struct qnode
	{
	tnode* t;
	qnode *next;
	};
	qnode *front,*rear;
	public:
	void enq(tnode *t,bool qm=1);
	tnode* deq();
	bool empty();
	queue();
};
class bintree
{
	tnode *root;
	public:
	bintree(){root=NULL;}
	void create();
	void rpreorder(tnode*);
	void ipreorder();
	void rpostorder(tnode*);
	void ipostorder();
	tnode* mirror(tnode*);
	bintree getmirror();
	int getheight(tnode*);
	void leaves();
	void erase();
	void operator =(bintree);
	tnode* getroot(){return(root);}
};
queue::queue()
{
front=rear=NULL;
}
void queue::enq(tnode *temp,bool qm)
{
	qnode *n=new qnode;
	n->t=temp;
	n->next=NULL;
	if(front==NULL)
	{
		front=rear=n;
		return;
	}
	if(qm)
	{
		rear->next=n;
		rear=n;
	}
	else
	{
		n->next=front;
		front=n;
	}
}
tnode* queue::deq()
{
	qnode *n;
	tnode *p=front->t;
	n=front;
	front=front->next;
	delete(n);
	return(p);
}
bool queue::empty()
{
	if(front==NULL)
		return(1);
	return(0);
}
void bintree::create()
{
	queue q;
	tnode *k,*nnode;
	bool choice;
	if(root==NULL)
	{
		nnode=new tnode;
		nnode->left=nnode->right=NULL;
		cout<<"Enter root data."<<endl;
		cin>>nnode->d;
		root=nnode;
		q.enq(root);
	}
	while(!q.empty())
	{
		k=q.deq();
		cout<<"Do you want to insert left child of "<<k->d<<"?(1/0)"<<endl;
		cin>>choice;
		if(choice)
		{
			nnode= new tnode;
			nnode->left=nnode->right=NULL;
			cout<<"Enter data of left child"<<endl;
			cin>>nnode->d;
			k->left=nnode;
			q.enq(nnode);
		}
		cout<<"Do you want to insert right child of "<<k->d<<"?(1/0)"<<endl;
		cin>>choice;
		if(choice)
		{
			nnode= new tnode;
			nnode->left=nnode->right=NULL;
			cout<<"Enter data of right child"<<endl;
			cin>>nnode->d;
			k->right=nnode;
			q.enq(nnode);
		}
	}
}
void bintree::rpreorder(tnode *r)
{
	if(r!=NULL)
	{
		cout<<r->d<<"\t";
		rpreorder(r->left);
		rpreorder(r->right);
	}
}
void bintree::rpostorder(tnode *r)
{
	if(r!=NULL)
	{
		rpostorder(r->left);
		rpostorder(r->right);
		cout<<r->d<<"\t";
	}
}
void bintree::ipostorder()
{
	queue s1,s2;
	tnode *r=root;
	if(root==NULL)
	{
		cout<<"Empty Tree."<<endl;
		return;
	}
	cout<<"Postorder Traversal:  ";
	while(r!=NULL)
	{
		while(r!=NULL)
		{
			s2.enq(r,0);
			s1.enq(r,0);
			r=r->right;
		}
		while(!s1.empty()&&r==NULL)
		{
			r=s1.deq();
			r=r->left;
		}
	}
	while(!s2.empty())
	{
		cout<<s2.deq()->d<<"\t";
	}
	cout<<endl;
}
void bintree::erase()
{
	queue s1,s2;
	tnode *r=root;
	char c;
	if(root==NULL)
	{
		cout<<"Empty Tree."<<endl;
		return;
	}
	cout<<"Erase all the nodes of tree permanently?(y/n) ";
	cin>>c;
	if(c!='y')
		return;
	while(r!=NULL)
	{
		while(r!=NULL)
		{
			s2.enq(r,0);
			s1.enq(r,0);
			r=r->right;
		}
		while(!s1.empty()&&r==NULL)
		{
			r=s1.deq();
			r=r->left;
		}
	}
	while(!s2.empty())
	{
		delete(s2.deq());
	}
	root=NULL;
}
int bintree::getheight(tnode *r)
{
	int h,x,y;
	if(r==NULL)
		return(0);
	x=getheight(r->left);
	y=getheight(r->right);
	h=(x>y)?(x+1):(y+1);
	return(h);
}
tnode* bintree::mirror(tnode *r)
{
	if(r!=NULL)
	{
		tnode *nnode=new tnode;
		nnode->d=r->d;
		if(r->right!=NULL)
			nnode->left=mirror(r->right);
		else
			nnode->left=NULL;
		if(r->left!=NULL)
			nnode->right=mirror(r->left);
		else
			nnode->right=NULL;
		return(nnode);
	}
}


	bintree bintree::getmirror()
	{
	bintree b;
	b.root=mirror(this->root);
	return(b);
	}


void bintree::leaves()
{
	if(root==NULL)
	{
		cout<<"Empty tree."<<endl;
		return;
	}
	int l=0,m=0;
	tnode* r=root;
	queue s;
	while(r)
	{
		while(r)
		{
			if(r->left==NULL&&r->right==NULL)
				l++;
			else
				m++;
			s.enq(r,0);
			r=r->left;
		}
		while(!s.empty()&&r==NULL)
		{
			r=s.deq();
			r=r->right;
		}
	}
	cout<<"Number of leaves:"<<l<<"\nNumber of branches:"<<m<<endl;
}
void bintree::ipreorder()
{
	queue s1;
	tnode *r=root;
	if(root==NULL)
	{
		cout<<"Empty Tree."<<endl;
		return;
	}
	cout<<"Preorder Traversal:  ";
	while(r!=NULL)
	{
		while(r!=NULL)
		{
			cout<<r->d<<"\t";
			if(r->right!=NULL)
				s1.enq(r->right,0);
			r=r->left;
		}
		if(!s1.empty())
		{
			r=s1.deq();
		}
	}
	cout<<endl;
}
void bintree::operator =(bintree b)
{
	queue q,bq;
	tnode *k,*bk,*nnode,*bnode=b.root;
	bool choice;
		nnode=new tnode;
		nnode->left=nnode->right=NULL;
		nnode->d=bnode->d;
		root=nnode;
		q.enq(root);
		bq.enq(bnode);
	while(!bq.empty())
	{
		k=q.deq();
		bk=bq.deq();
		choice=(bk->left!=NULL);
		if(choice)
		{
			nnode= new tnode;
			nnode->left=nnode->right=NULL;
			nnode->d=bk->left->d;
			k->left=nnode;
			q.enq(nnode);
			bq.enq(bk->left);
		}
	
		choice=(bk->right!=NULL);
		if(choice)
		{
			nnode= new tnode;
			nnode->left=nnode->right=NULL;
			nnode->d=bk->right->d;
			k->right=nnode;
			q.enq(nnode);
			bq.enq(bk->right);
		}
	}
}
int main()
{
	bintree tr,tr1;
	tr.create();
	tr.ipreorder();
	cout<<"Recursive Preorder Traversal:  ";
	tr.rpreorder(tr.getroot());
	cout<<endl;
	tr.ipostorder();
	cout<<"Recursive Postorder Traversal: ";
	tr.rpostorder(tr.getroot());
	cout<<endl;
	cout<<"Height of tree is: "<<tr.getheight(tr.getroot())<<endl;
	tr.leaves();
	cout<<endl;
	cout<<"Copied tree."<<endl;
	tr1=tr;
	tr1.ipostorder();
	tr1.erase();
	tr1.ipostorder();
	cout<<"Creating Mirror tree."<<endl;
	tr1=tr.getmirror();
	cout<<"Preorder Traversal of mirror tree."<<endl;
	tr1.rpreorder(tr1.getroot());
	cout<<endl;
	return 0;
}





/*OUTPUT:
owner@owner-Inspiron-3520:~$ cd 2269_ADSL
owner@owner-Inspiron-3520:~/2269_ADSL$ g++ assign1.cpp
owner@owner-Inspiron-3520:~/2269_ADSL$ ./a.out
Enter root data.
1
Do you want to insert left child of 1?(1/0)
1
Enter data of left child
2
Do you want to insert right child of 1?(1/0)
1
Enter data of right child
3
Do you want to insert left child of 2?(1/0)
1
Enter data of left child
4
Do you want to insert right child of 2?(1/0)
1 
Enter data of right child
4
Do you want to insert left child of 3?(1/0)
0
Do you want to insert right child of 3?(1/0)
1
Enter data of right child
6
Do you want to insert left child of 4?(1/0)
1
Enter data of left child
7
Do you want to insert right child of 4?(1/0)
0
Do you want to insert left child of 4?(1/0)
0
Do you want to insert right child of 4?(1/0)
1
Enter data of right child
8
Do you want to insert left child of 6?(1/0)
0
Do you want to insert right child of 6?(1/0)
0
Do you want to insert left child of 7?(1/0)
0
Do you want to insert right child of 7?(1/0)
0
Do you want to insert left child of 8?(1/0)
0
Do you want to insert right child of 8?(1/0)
0
Preorder Traversal:  1	2	4	7	4	8	3	6	
Recursive Preorder Traversal:  1	2	4	7	4	8	3	6	
Postorder Traversal:  7	4	8	4	2	6	3	1	
Recursive Postorder Traversal: 7	4	8	4	2	6	3	1	
Height of tree is: 4
Number of leaves:3
Number of branches:5

Copied tree.
Postorder Traversal:  7	4	8	4	2	6	3	1	
Erase all the nodes of tree permanently?(y/n) y
Empty Tree.
Creating Mirror tree.
Preorder Traversal of mirror tree.
1	3	6	2	4	8	4	7	
*/
