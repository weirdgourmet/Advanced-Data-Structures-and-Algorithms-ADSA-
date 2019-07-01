/*Implement all the functions of a dictionary (ADT) using hashing. Data: Set of (key,
value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be
unique Standard Operations: Insert(key, value), Find(key), Delete(key)*/


#include<iostream>
#include<cstring>
#include<stdio.h>
using namespace std;
class word
	{
		string w,m;
		public:
		friend class dict;
		void operator =(word w1)
		{
			w=w1.w;
			m=w1.m;
		}	
		void printWord()
		{
			cout<<w<<"\t"<<m<<endl;
		}	
	};
	
class dict
{
 word s[26];
 bool rf;
 public:
	void create();
	void addword();
	void search();
	void del();
	int hash(char);
	void printTable();
};

void dict::printTable()
{
	int i;
	for(i=0;i<26;i++)
	{
		cout<<i<<"\t";
		s[i].printWord();
	}
}
	
	
void dict::create()
{
	word N;
	N.w=N.m='\0';
	int i;
	for(i=0;i<26;i++)
	{
		s[i]=N;
	}
	cout<<"Enter 1 for hashing with replacement, 0 for hashing without replacement."<<endl;
	cin>>rf;
}
int dict::hash(char c)
{
	if(c>=97)
	{
		return(c-97);
	}
	return(c-65);
}
void dict::addword()
{
	word a,a1;
	int b,i=0;
	cout<<"Enter word."<<endl;
	cin.ignore();
	getline(cin,a.w);
	cout<<"Enter meaning."<<endl;
	getline(cin,a.m);
	b=hash(a.w[0]);
	if(rf&&hash(s[b].w[0])!=b)
	{
		a1=s[b];
		s[b]=a;
		a=a1;
		i=1;
	}
	
	for(;s[b+i].w[0]!='\0';)
	{
		if((b+i)==25)
			i=-1-b;
		i++;
		if(i==0)
		{
			cout<<"Full. Cannot add new word."<<endl;
			return;
		}	
	}
	s[b+i]=a;
	
}
void dict::search()
{
	string s1;
	cout<<"Enter word to be searched."<<endl;
	
	cin.ignore();
	getline(cin,s1);
	int i,b;
	b=hash(s1[0]);
	for(i=0;s[b+i].w!=s1;)
	{
		if((b+i)==25)
			i=-b-1;
		i++;
		if(i==0)
		{
			cout<<"Word not found."<<endl;
			return;
		}
	}
	cout<<"Meaning : "<<s[b+i].m<<endl;
}
void dict::del()
{
	word N;
	N.w=N.m='\0';
	string s1;
	cout<<"Enter word to be deleted."<<endl;
	
	cin.ignore();
	getline(cin,s1);
	int i,b;
	b=hash(s1[0]);
	for(i=0;s[b+i].w!=s1;)
	{
		if((b+i)==25)
			i=-b-1;
		i++;
		if(i==0)
		{
			cout<<"Word not found.Cannot delete."<<endl;
			return;
		}
	}
	s[i+b]=N;
}
int main()
{
	dict d;
	int op;
	d.create();
	cout<<"Options.\n1.Enter a new word.\n2.Search meaning of a word.\n3.Delete a word.\n4.Print all words of Dictionary.\n5.Exit."<<endl;
	do
	{
		cout<<"Select an option."<<endl;
		cin>>op;
		switch(op)
		{
			case 1:d.addword();
			break;
			
			case 2:d.search();
			break;
			
			case 3:d.del();
			break;
			
			case 4:d.printTable();
			break;
			
			case 5:break;
			
			default:cout<<"Enter valid option."<<endl;
			
		}
	}while(op!=4);
	
	return 0;
}
