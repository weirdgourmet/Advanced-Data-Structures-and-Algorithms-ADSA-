/*You have a business with several offices; you want to lease phone lines to connect
them up with each other; and the phone company charges different amounts of money
to connect different pairs of cities. You want a set of lines that connects all your
offices with a minimum total cost. Solve the problem by suggesting appropriate data
structures.
*/

#include<iostream>
#include<cstring>
using namespace std;
class graph
{
	int **adjmat;
	int cntv;
	int cnte;
	string *vlist;
	public:
	void create();
	void kruskal();
	void prim();
};
void graph::create()
{
	cout<<"Enter number of offices."<<endl;
	cin>>cntv;
	int i,k,j,l,w;
	string s1,s2;
	vlist = new string[cntv];
	for(i=0;i<cntv;i++)
	{
		cout<<"Enter city for office "<<i+1<<"."<<endl;
		cin>>vlist[i];
	}
	k=cntv*(cntv-1)/2;
	adjmat=new int*[cntv];
	for(j=0;j<cntv;j++)
	{
		adjmat[j]=new int[cntv];
		for(i=0;i<cntv;i++)
			adjmat[j][i]=0;
	}
	cout<<"Enter telephone line details.\nEnter city 1=0 to stop."<<endl;
	for(cnte=0;cnte<k;cnte++)
	{
		cout<<"Enter city 1."<<endl;
		cin>>s1;
		if(s1=="0")
			break;
		for(i=0;i<cntv;i++)
			if(vlist[i]==s1)
				break;
		if(i==cntv)
		{
			cout<<s1<<" not found."<<endl;
			cnte--;
			continue;
		}
		cout<<"Enter city 2."<<endl;
		cin>>s2;
		for(l=0;l<cntv;l++)
			if(vlist[l]==s2)
				break;
		if(l==cntv)
		{
			cout<<s2<<" not found."<<endl;
			cnte--;
			continue;
		}
		cout<<"Enter cost of telephone line."<<endl;
		cin>>w;
		if(w<=0)
		{
			cout<<"Invalid cost."<<endl;
			cnte--;
			continue;
		}
		adjmat[i][l]=adjmat[l][i]=w;	
	}			
}
void graph::kruskal()
{
	int cnt=0,mstwt=0,min,max,mine,i,j,k,temp,temp1,t,t1;
	int *father=new int[cntv];
	for(k=0;k<cntv;father[k++]=-1);
	int **etable=new int*[cnte];
	for(k=0;k<cnte;k++)
	etable[k]=new int[4];
	k=0;
	max=0;
	for(i=0;i<cntv;i++)
	for(j=i+1;j<cntv;j++)
	{
		if(adjmat[i][j]!=0)
		{
			etable[k][0]=i;
			etable[k][1]=j;
			etable[k][2]=adjmat[i][j];
			etable[k][3]=-1;
			if(max<adjmat[i][j])
				max=adjmat[i][j];
			k++;
		}
	}
	max++;
	cout<<"List of telephone lines to be constructed.\nCity1  City2"<<endl;
	k=0;
	mine=-1;
	while(cnt<cntv-1)
	{
		if(mine>-1)
			min=etable[mine][2];
		else
			min=max;
		for(;k<cnte;k++)
		{
			if(etable[k][2]!=0&&etable[k][2]<min)
			{
				min=etable[k][2];
				etable[k][3]=mine;
				mine=k;
			}
		}
		t=temp=etable[mine][0];
		t1=temp1=etable[mine][1];
			
		for(;father[temp]>-1;temp=father[temp]);
		for(;father[temp1]>-1;temp1=father[temp1]);
		if(temp!=temp1)
		{
			cout<<vlist[t]<<"  "<<vlist[t1]<<endl;
			mstwt+=min;
			father[temp1]=temp;
			cnt++;
		}
		etable[mine][2]=0;
		k=mine;
		mine=etable[mine][3];
	}
	cout<<"Total cost :"<<mstwt<<endl;
}
void graph::prim()
{
	string s1;
	int k,min,cnt,max,i,j,l,currv,mstwt=0;
	cout<<"Enter the starting vertex."<<endl;
	cin>>s1;
	int **vtable;
	vtable=new int*[cntv];
	for(k=0;k<cntv;k++)
	{
		vtable[k]=new int[2];
		vtable[k][1]=-1;
	}
	max=0;
	for(i=0;i<cntv;i++)
	for(j=i+1;j<cntv;j++)
	{
		if(max<adjmat[i][j])
			max=adjmat[i][j];
	}
	for(k=0;k<cntv;k++)
	{
		if(vlist[k]==s1)
		{
			vtable[k][0]=0;
			currv=k;
		}
		else
			vtable[k][0]=max;
	}
	cout<<"List of telephone lines to be constructed.\nCity1  City2"<<endl;
	for(cnt=0;cnt<cntv-1;cnt++)
	{
		min=max;
		l=-1;
		for(k=0;k<cntv;k++)
		{
			if(vtable[k][0]>adjmat[k][currv]&&adjmat[k][currv]>0)
			{
				vtable[k][0]=adjmat[k][currv];
				vtable[k][1]=currv;
			}
			if(vtable[k][0]<min&&vtable[k][0]>0)
			{
					min=vtable[k][0];
					l=k;
			}
		}
		mstwt+=min;
		cout<<vlist[vtable[l][1]]<<"  "<<vlist[l]<<endl;
		vtable[l][0]=0;
		currv=l;
	}
	cout<<"Total cost :"<<mstwt<<endl;
}			
			
	
int main()
{
	graph g;
	g.create();
	g.kruskal();
	g.prim();
	return 0;
}
