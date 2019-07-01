#include<iostream>
using namespace std;
class node
{
int x;
node *next,*prev;
public:
node()
{
x=0;
next=NULL;
prev=NULL;
}
friend class dll;
};
class dll
{
node *head;
public:
dll()
{
head=NULL;
}
node* getnode()
{
node *nnode=new node;
cout<<"Enter value.";
cin>>nnode->x;
nnode->next=nnode->prev=NULL;
return(nnode);
}
void inserthead(node *n)
{
if(head==NULL)
{
head=n;
n->next=n->prev=n;
}
else
{
n->next=head;
n->prev=head->prev;
head->prev=n;
head->prev->next=n;
head=n;
}
}
void insertend(node *n)
{
if(head==NULL)
inserthead(n);
else
{
n->next=head;
n->prev=head->prev;
head->prev->next=n;
head->prev=n;

}
}
node* trav(int loc)
{
if(head==NULL)
return(NULL);
if(loc==1)
return(head);
node* nptr=head->next;
int i;
for(i=2;i<=loc;i++)
{
if(nptr==head)
return(NULL);
else
nptr=nptr->next;
}
return(nptr->prev);
}
void insertafter(int l,node *n)
{
node* nptr=trav(l);
if(nptr==NULL)
{
cout<<"Invalid location."<<endl;
return;
}
else
{
n->next=nptr->next;
n->prev=nptr;
nptr->next->prev=n;
nptr->next=n;
}
}
void display()
{
if(head==NULL)
{

cout<<"Empty"<<endl;
return;
}
node *nptr=head;
do
{
cout<<nptr->x<<"\t";
nptr=nptr->next;
}while(nptr!=head);
cout<<endl;
}
void delhead()
{
node* nptr=head;
if(head!=head->next)
{
head->prev->next=head->next;
head->next->prev=head->prev;
head=head->next;
}
else
head=NULL;
delete(nptr);
}
void delend()
{
node* nptr=head->prev;
if(head==head->prev)
{
delhead();
return;
}
else
{
head->prev=head->prev->prev;
head->prev->next=head;
}
delete(nptr);
}
void delafter(int loc)
{
node *nptr=trav(loc);
if(nptr==NULL)
{
cout<<"Invalid location."<<endl;
return;
}
if(nptr==head)
{
delhead();
return;
}
nptr->prev->next=nptr->next;
nptr->next->prev=nptr->prev;
delete(nptr);
}
dll concat(dll d)
{
dll c;
node* n;
node* nptr=head;
if(nptr!=NULL)
{
do
{
n=new node;
n->x=nptr->x;
c.insertend(n);
nptr=nptr->next;
}while(nptr!=head);
}
nptr=d.head;
if(nptr!=NULL)
{
do
{
n=new node;
n->x=nptr->x;
c.insertend(n);
nptr=nptr->next;
}while(nptr!=d.head);
}
return(c);
}
void sort()
{
if(head==NULL)
return;
node *nptr=head->prev;
node *cptr;
int i=0;
do
{
nptr=nptr->prev;
i++;
}while(nptr!=head->prev);
for(;i>0;i--)
{
cptr=head;
while(cptr!=trav(i))
{
if(cptr->x>cptr->next->x)
swap(cptr,cptr->next);
cptr=cptr->next;
}
}
}
void swap(node *n,node *m)
{
int t;
t=m->x;
m->x=n->x;
n->x=t;
}
};
int main()
{
dll d,d1,d3;
int i,n;
cout<<"Enter number of nodes."<<endl;
cin>>n;
d.inserthead(d.getnode());
for(i=0;i<n-2;i++)
d.insertafter(i,d.getnode());
d.insertend(d.getnode());
cout<<"First list."<<endl;
d.display();
cout<<"Enter number of nodes."<<endl;
cin>>n;
d1.inserthead(d.getnode());
for(i=0;i<n-2;i++)
d1.insertafter(i,d.getnode());
d1.insertend(d.getnode());
cout<<"Second list."<<endl;
d1.display();
cout<<"Concatinated list.:"<<endl;
d3=d.concat(d1);
d3.display();
cout<<"After Sorting."<<endl;
d3.sort();
d3.display();
return 0;
}

