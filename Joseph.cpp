// Joseph.cpp : 定义控制台应用程序的入口点。
//

#include <stdlib.h>
#include <stdio.h>


typedef struct LNode{
	int id;//序号
	int code;//密码
	struct LNode *next;
}LNode,*LinkList;

LinkList CreateList(int n);
void OutputList(LinkList tail);
void Play(LinkList& tail,int n,int m);

int main()
{
	int n,m;
	printf("输入人数和初始随机密码：\n");
	scanf("%d %d",&n,&m);
	LinkList tail=CreateList(n);
	if(tail)
	{
		OutputList(tail);
		Play(tail,n,m);
	}
	return 0;
}

LinkList CreateList(int n)
{
	LinkList head=NULL,tail=NULL;
	for(int i=1;i<=n;i++)
	{
		LNode *p=(LNode *)malloc(sizeof(struct LNode));
		p->id=i;
		printf("第%d个人的密码：",i);
		scanf("%d",&p->code);
		if(tail)
			tail->next=p;
		else
			head=p;
		tail=p;
	}
	if(tail)
		tail->next=head;
	return tail;
}
void OutputList(LinkList tail)
{
	LinkList p=tail->next;
	LinkList head=tail->next;
	do
	{
		//printf("(%d,%d)",p->id,p->code);
		p=p->next;
	}while(p!=head);
	//printf("\n");
}
void Play(LinkList& tail,int n,int m)
{
	LinkList prev,p;
	prev=tail;
	printf("出列顺序为： ");
	while(n>1)
	{
		LinkList p=prev->next;//第一个报数的人
		m=m%n?m%n:n;//减少循环次数
		for(int k=0;k<m-1;k++)
		{
			prev=p;
			p=p->next;
		}
		printf("%d ",p->id);
		prev->next=p->next;
		//p=p->next;
		m=p->code;
		n--;
	}
	printf("%d\n",prev->id);//输出最后一个人的编号
}