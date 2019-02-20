// Joseph.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdlib.h>
#include <stdio.h>


typedef struct LNode{
	int id;//���
	int code;//����
	struct LNode *next;
}LNode,*LinkList;

LinkList CreateList(int n);
void OutputList(LinkList tail);
void Play(LinkList& tail,int n,int m);

int main()
{
	int n,m;
	printf("���������ͳ�ʼ������룺\n");
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
		printf("��%d���˵����룺",i);
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
	printf("����˳��Ϊ�� ");
	while(n>1)
	{
		LinkList p=prev->next;//��һ����������
		m=m%n?m%n:n;//����ѭ������
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
	printf("%d\n",prev->id);//������һ���˵ı��
}