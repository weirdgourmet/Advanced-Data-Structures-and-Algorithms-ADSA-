#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<string.h>
using namespace std;
class tnode
{
	tnode *left,*right;
	string word,meaning;
	public:
	friend class dtree;
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

class dtree
{
	tnode *root;
	public:
	dtree(){root=NULL;}
	tnode* getroot(){return(root);}
	void insert(tnode*);
	void update();
	void search();
	void del();
	void inorder(tnode*);
	void revino();
	void preorder(tnode*);
	tnode* getnode();
	void operator =(dtree);
};
void dtree::revino()
{
	if(root==NULL)
	{
		cout<<"Empty tree."<<endl;
		return;
	}
	tnode *t=root;
	queue s,s1;
	do
	{
		while(t!=NULL)
		{
			s.enq(t,0);
			t=t->left;
		}
		t=s.deq();
		s1.enq(t,0);
		t=t->right;
	}while(!s.empty()||t!=NULL);
	cout<<"Dictionary word in reverse order."<<endl;
	while(!s1.empty())
	{
		t=s1.deq();
		cout<<t->word<<"\t"<<t->meaning<<endl;
	}
}
	
void dtree::operator =(dtree d1)
{
	queue q,bq;
	tnode *k,*bk,*nnode,*bnode=d1.root;
	bool choice;
		nnode=new tnode;
		nnode->left=nnode->right=NULL;
		nnode->word=bnode->word;
		nnode->meaning=bnode->meaning;
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
			nnode->word=bk->left->word;
			nnode->meaning=bk->left->meaning;
			k->left=nnode;
			q.enq(nnode);
			bq.enq(bk->left);
		}
	
		choice=(bk->right!=NULL);
		if(choice)
		{
			nnode= new tnode;
			nnode->left=nnode->right=NULL;
			nnode->word=bk->right->word;
			nnode->meaning=bk->right->meaning;
			k->right=nnode;
			q.enq(nnode);
			bq.enq(bk->right);
		}
	}
}		
		
void dtree::inorder(tnode *r)
{
	if(r!=NULL)
	{
		inorder(r->left);
		cout<<r->word<<"\t"<<r->meaning<<endl;
		inorder(r->right);
	}
}
void dtree::preorder(tnode *r)
{
	if(r!=NULL)
	{
				cout<<r->word<<"\t"<<r->meaning<<endl;
		preorder(r->left);

		preorder(r->right);
	}
}
void dtree::update()
{
	cout<<"Enter word, meaning of which is to be updated."<<endl;
	string key;
	getline(cin,key);
	tnode *r=root;
	while(r!=NULL)
	{
		if(r->word==key)
		{
			cout<<"Enter new meaning."<<endl;
			getline(cin,r->meaning);
			return;
		}
		if(r->word<key)
			r=r->right;
		else
			r=r->left;
	}
	cout<<"Word not found."<<endl;
}
void dtree::search()
{
	cout<<"Enter word to be searched."<<endl;
	string key;
	getline(cin,key);
	tnode *r=root;
	while(r!=NULL)
	{
		if(r->word==key)
		{
			cout<<"Meaning of "<<key<<" : "<<endl;
			cout<<r->meaning<<endl;
			return;
		}
		if(r->word<key)
			r=r->right;
		else
			r=r->left;
	}
	cout<<"Meaning not found."<<endl;
}
		
void dtree::insert(tnode *nnode)
{
	if(root==NULL)
	{
		root=nnode;
		return;
	}
	tnode *r=root;
	while(1)
	{
		if(r->word>nnode->word)
		{
			if(r->left==NULL)
			{
				r->left=nnode;
				return;
			}
			r=r->left;
		}
		else if(r->word<nnode->word)
		{
			if(r->right==NULL)
			{
				r->right=nnode;
				return;
			}
			r=r->right;
		}
		else
		{
		cout<<"Word already present, cannot be added again.\nIf meaning of this word is to be updated, please select the update option."<<endl;
		return;
		}
	}
}
void dtree::del()
{
	cout<<"Enter the word to be deleted."<<endl;
	string delword;
	cin>>delword;
	tnode *p=NULL,*q,*t=root;
	while(t!=NULL)
	{
		if(t->word==delword)
		{
			
			if(t->left!=NULL)
			{
				q=t->left;
				p=t;
				while(q->right!=NULL)
				{
					p=q;
					q=q->right;
				}
				if(p==t)
					p->left=q->left;
				else
					p->right=q->left;
				t->word=q->word;
				t->meaning=q->meaning;
				delete(q);
				return;
			}
			else if(t->right!=NULL)
			{
				q=t->right;
				p=t;
				while(q->left!=NULL)
				{
					p=q;
					q=q->left;
				}
				if(p==t)
					p->right=q->right;
				else
					p->left=q->right;
				t->word=q->word;
				t->meaning=q->meaning;
				delete(q);
				return;
			}
			else
			{
				if(p!=NULL)
				{
					if(p->left==t)
						p->left=NULL;
					else
						p->right=NULL;
				}
				if(t==root)
					root=NULL;
				delete(t);
				return;	
			}
		}	
		else if(t->word>delword)
		{
			p=t;
			t=t->left;
		}
		else
		{
			p=t;
			t=t->right;
		}
	}
	cout<<"Word not found, cannot delete."<<endl;
}
tnode* dtree::getnode()
{
	tnode *n=new tnode;
	n->left=n->right=NULL;
	cout<<"Enter word."<<endl;
	cin>>n->word;
	cout<<"Enter meaning."<<endl;
	cin.ignore();
	getline(cin,n->meaning);
	return(n);
}
int main()
{
	dtree d,d2;
	int op=0;
	/*for(int i=0;i<10;i++)
		d.insert(d.getnode());	
	for(int j=0;j<1;j++)
		 d.search();
	 d.update();
	 d.search();
	 d.inorder(d.getroot());
	 d.revino();
	d2=d;
	d2.inorder(d2.getroot());*/

	while(op!=4)
	{
	cout<<"Select an option.\n1.Enter a new word.\n2.Search.\n3.Update.\n4.Exit"<<endl;
	cin>>op;
	if(op==1)
		d.insert(d.getnode());	
	else if(op==2)
		 d.search();
	else if(op==3)
		 d.update();
	else if(op==4)
		 break;
	else
		cout<<"Enter a valid choice."<<endl;
	}
	
	return 0;
}
