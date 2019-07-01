#include<iostream>
#include<cstring>
using namespace std;
class gvertex;
class gedge
{
	gedge *next;
	int wt;
	gvertex *d;
	public:
	gedge(){next=NULL;}
	friend class gvertex;
	friend class graph;
};
class gvertex
{
	gedge *h;
	gvertex *v;
	string city;
	bool visit;
	int *deg;
	public:
	gvertex(){v=NULL;}
	friend class gedge;
	friend class graph;
};
class graph
{
	gvertex *head;
	bool de;
	int cntv;
	public:
	void create();
	void getv();
	void gete();
	void rmvv();
	void rmve();
	bool insertv(string);
	bool inserte(string,string,int);
	bool delv(string);
	bool dele(string,string);
	void BFS();
	void DFS();
	void printdeg();
};
class queue
{
	struct qnode
	{
	gvertex *t;
	qnode *next;
	};
	qnode *front,*rear;
	public:
	void enq(gvertex *t,bool qm=1);
	gvertex* deq();
	bool empty();
	queue();
};
queue::queue()
{
front=rear=NULL;
}
void queue::enq(gvertex *temp,bool qm)
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
gvertex* queue::deq()
{
	qnode *n;
	gvertex *p=front->t;
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
bool graph::insertv(string s)
{
	gvertex *vptr,*nv=new gvertex;
	nv->city=s;
	nv->h=NULL;
	nv->v=NULL;
	if(de)
	{
		nv->deg=new int[2];
		nv->deg[0]=nv->deg[1]=0;
	}
	else
	{
		nv->deg=new int[1];
		nv->deg[0]=0;
	}
	if(head==NULL)
	{
		head=nv;
		return(1);
	}
	for(vptr=head;vptr->city!=s&&vptr->v!=NULL;vptr=vptr->v);
	if(vptr->city==s)
		return(0);
	vptr->v=nv;
	cntv++;
	return(1);
}
void graph::getv()
{
	string s;
	cout<<"Enter name of the city."<<endl;
	cin>>s;
	if(!insertv(s))
		cout<<"City already exists."<<endl;
}
void graph::gete()
{
	string s,dest;
	int w;
	bool b;
	cout<<"Enter name of the city 1."<<endl;
	cin>>s;
	cout<<"Enter name of the city 2."<<endl;
	cin>>dest;
	cout<<"Enter cost of fuel required."<<endl;
	cin>>w;
	b=inserte(s,dest,w);
	if(!de&&b)
	inserte(dest,s,w);
}
bool graph::inserte(string s,string dest,int w)
{
	gvertex *vptr;
	gedge *eptr;
	for(vptr=head;vptr!=NULL;vptr=vptr->v)
	{
	if(vptr->city==dest)
		break;
	}
	if(vptr==NULL)
	{
		cout<<"City "<<dest<<" not found."<<endl;
		return(0);
	}
	gedge *ne=new gedge;
	ne->wt=w;
	ne->d=vptr;
	for(vptr=head;vptr->city!=s&&vptr->v!=NULL;vptr=vptr->v);
	if(vptr->city==s)
	{
		ne->next=NULL;
		if(vptr->h==NULL)
		{
			vptr->h=ne;
			if(de)
			{
				vptr->deg[1]++;
				ne->d->deg[0]++;
			}
			else
				vptr->deg[0]++;
			return(1);
		}
		for(eptr=vptr->h;eptr->d->city!=dest&&eptr->next!=NULL;eptr=eptr->next);
		if(eptr->d->city==dest)
			return(0);
		eptr->next=ne;
		if(de)
		{
			vptr->deg[1]++;
			ne->d->deg[0]++;
		}
		else
			vptr->deg[0]++;
		return(1);
	}
	else
		cout<<"City "<<s<<" not found."<<endl;
		return(0);
}
void graph::printdeg()
{
	gvertex *vptr;
	if(de)
	{
		cout<<"City\tIndegree\tOutdegree"<<endl;
		for(vptr=head;vptr!=NULL;vptr=vptr->v)
			cout<<vptr->city<<"\t"<<vptr->deg[0]<<"\t"<<vptr->deg[1]<<endl;
	}
	else
	{
		cout<<"City\tDegree"<<endl;
		for(vptr=head;vptr!=NULL;vptr=vptr->v)
			cout<<vptr->city<<"\t"<<vptr->deg[0]<<endl;
	}
}
void graph::create()
{
	head=NULL;
	cout<<"Enter 1 for directed graph, 0 for undirected graph."<<endl;
	cin>>de;
	cntv=0;
}
void graph::BFS()
{
	queue q;
	gedge *eptr;
	gvertex *vptr;
	cout<<"Breadth First Traversal of graph:"<<endl;
	for(vptr=head;vptr!=NULL;vptr=vptr->v)
		vptr->visit=0;
	vptr=head;
	vptr->visit=1;
	q.enq(vptr);
	do
	{
		vptr=q.deq();
		cout<<vptr->city<<"\t";
		
		for(eptr=vptr->h;eptr!=NULL;eptr=eptr->next)
		{
			if(!eptr->d->visit)
			{
				eptr->d->visit=1;
				q.enq(eptr->d);
			}
		}
		
		
	}while(!q.empty());
	cout<<endl;
}
void graph::DFS()
{
	queue q;
	gedge *eptr;
	gvertex *vptr;
	cout<<"Depth First Traversal of graph:"<<endl;
	for(vptr=head;vptr!=NULL;vptr=vptr->v)
		vptr->visit=0;
	vptr=head;
	vptr->visit=1;
	q.enq(vptr);
	do
	{
		vptr=q.deq();
		cout<<vptr->city<<"\t";
		
		for(eptr=vptr->h;eptr!=NULL;eptr=eptr->next)
		{
			if(!eptr->d->visit)
			{
				eptr->d->visit=1;
				q.enq(eptr->d,0);
			}
		}
		
	}while(!q.empty());
	cout<<endl;
}
bool graph::delv(string s1)
{
	gvertex *vptr,*dptr;
	gedge *eptr,*e1ptr;
	if(head==NULL)
		return(0);
	if(head->city==s1)
	{
		dptr=head;
		head=head->v;
	}
	else
	{
		for(vptr=head;vptr->v->city!=s1&&vptr->v->v!=NULL;vptr=vptr->v);
		if(vptr->v->city==s1)
		{
			dptr=vptr->v;
			vptr->v=vptr->v->v;
		}
		else
			return(0);
	}
	for(vptr=head;vptr!=NULL;vptr=vptr->v)
	{
		if(vptr==dptr)
		{
			for(;vptr->h!=NULL;)
			{
				e1ptr=vptr->h;
				vptr->h=vptr->h->next;
				e1ptr->d->deg[0]--;
				cout<<"HELLO"<<endl;
				delete(e1ptr);
			}
			continue;
		}
		if(vptr->h==NULL)
			continue;
		if(vptr->h->d==dptr)
		{
			e1ptr=vptr->h;
			vptr->h=vptr->h->next;
			if(de)
				vptr->deg[1]--;
			else
				vptr->deg[0]--;
			delete(e1ptr);
			continue;
		}
		for(eptr=vptr->h;eptr->next!=NULL;eptr=eptr->next)
			if(eptr->next->d==dptr)
			{
				e1ptr=eptr->next;
				eptr->next=eptr->next->next;
				if(de)
					vptr->deg[1]--;
				else
					vptr->deg[0]--;
				delete(e1ptr);
				break;
			}
	}
	delete(dptr);
	return(1);
}
bool graph::dele(string s1,string s2)
{
	gvertex *vptr;
	gedge *eptr,*e1ptr;
	for(vptr=head;vptr!=NULL;vptr=vptr->v)
	{
		if(vptr->city==s1)
		{
			if(vptr->h==NULL)
				return(0);
			if(vptr->h->d->city==s2)
			{
				e1ptr=vptr->h;
				vptr->h=vptr->h->next;
				if(de)
				{
					vptr->deg[1]--;
					e1ptr->d->deg[0]--;
				}
				else
					vptr->deg[0]--;
				delete(e1ptr);
				return(1);
			}
			for(eptr=vptr->h;eptr->next!=NULL;eptr=eptr->next)
			{
				if(eptr->next->d->city==s2)
				{
					e1ptr=eptr->next;
					eptr->next=eptr->next->next;
					if(de)
					{
						vptr->deg[1]--;
						e1ptr->d->deg[0]--;
					}
					else
						vptr->deg[0]--;
					delete(e1ptr);
					return(1);
				}
			}
		}
	}
	return(0);
}
void graph::rmvv()
{
	string s1;
	cout<<"Enter city to be deleted."<<endl;
	cin>>s1;
	delv(s1);
}
void graph::rmve()
{
	string s1,s2;
	cout<<"Enter name of city 1."<<endl;
	cin>>s1;
	cout<<"Enter name of city 2."<<endl;
	cin>>s2;
	if(!de&&dele(s1,s2))
		dele(s2,s1);
}
int main()
{

	graph G;
	int op;
	G.create();
	do
	{
	cout<<"Select an option.\n1.Add city.\n2.Add edge.\n3.Delete city.\n4.Delete edge.\n5.BFS of graph.\n6.DFS of graph.\n7.Display degree of vertices.\n8.Exit."<<endl;
	cin>>op;
	switch(op)
	{
		case 1:G.getv();
		break;
		
		case 2:G.gete();
		break;
		
		case 3:G.rmvv();
		break;
		
		case 4:G.rmve();
		break;
		
		case 5:G.BFS();
		break;
		
		case 6:G.DFS();
		break;
		
		case 7:G.printdeg();
		break;
		
		case 8:break;
		
		default:cout<<"Enter valid choice."<<endl;
	}
	}while(op!=8);
	
	return 0;
}
		
