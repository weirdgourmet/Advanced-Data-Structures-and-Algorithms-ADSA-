#include<iostream>
using namespace std;
class Onode
{
	Onode *left,*right;
	int key;
	public:
	friend class OBST;
};
class OBST
{
	int cntk;
	int **klist;
	int **mat;
	Onode *root1;
	public:
	void create();
	Onode* insert(int,int);
	void pre(Onode*);
	void in(Onode *);
	Onode* getroot(){return(root1);}
};
void OBST::pre(Onode *r)
{
	if(r!=NULL)
	{
		cout<<r->key<<"\t";
		pre(r->left);
		pre(r->right);
	}
}
void OBST::in(Onode *r)
{
	if(r!=NULL)
	{
		in(r->left);
		cout<<r->key<<"\t";
		in(r->right);
	}
}
Onode* OBST::insert(int i,int j)
{
	int k=mat[i][j];
	Onode *p=new Onode;
	cout<<k<<endl;
	if(i==j)
	{
		p->left=p->right=NULL;
		p->key=klist[i][0];
	}
	else
	{
		p->key=klist[k][0];
		if(k>j)
		p->left=insert(k-1,j);
		else
		p->left=NULL;
		if(k<i)
		p->right=insert(i,k+1);
		else
		p->right=NULL;
	}
	return(p);
}
void OBST::create()
{
	int k,i,j,l,a,min,root;
	cout<<"Enter number of keys."<<endl;
	cin>>cntk;
	cout<<"Enter values of "<<cntk<<" keys and their search probabilities respectively."<<endl;
	klist=new int*[cntk];
	for(k=0;k<cntk;k++)
	{
		cout<<"key"<<k<<":"<<endl;
		klist[k]=new int[2];
		cin>>klist[k][0]>>klist[k][1];
	}
	mat=new int*[cntk];
	for(k=0;k<cntk;k++)
		mat[k]=new int[cntk];
	for(k=0;k<cntk;k++)
		mat[k][k]=klist[k][1];
	for(k=1;k<cntk;k++)
	{
		for(i=0;i<cntk-k;i++)
		{
			mat[i][i+k]=0;
			for(j=i;j<=i+k;j++)
				mat[i][i+k]+=mat[j][j];
			min=9999;
			for(j=i;j<=i+k;j++)
			{
				a=0;
				if(j-1>=i)
					a+=mat[i][j-1];
				if(j+1<=i+k)
					a+=mat[j+1][i+k];
				if(min>a)
				{
					min=a;
					root=j;
				}
			}
			mat[i][i+k]+=min;
			mat[i+k][i]=root;
		}
		
	}
	for(i=0;i<cntk;i++)
		{
			for(j=0;j<cntk;j++)
				cout<<mat[i][j]<<"\t";
			cout<<endl;
		}
	root1=insert(cntk-1,0);
	
}
int main()
{
OBST o;
o.create();
cout<<"Preorder Traversal."<<endl;
o.pre(o.getroot());
cout<<endl<<"Inorder Traversal."<<endl;
o.in(o.getroot());
return 0;
}
